#ifdef __linux
  #define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sastrawi_internal.h"
#include "dictionary.h"
#include "remove_suffixes.h"
#include "remove_prefixes.h"
#include "stem_singular.h"
#include "precedence_adjustment.h"
#include "../dbg.h"


const AFFIX_REMOVER prefix_suffix_removers[2] = {remove_prefixes, remove_suffixes};
const AFFIX_REMOVER suffix_prefix_removers[2] = {remove_suffixes, remove_prefixes};
sastrawi_err apply_affix_removers(sastrawi_stemmer *, char *, char **, const AFFIX_REMOVER[], int *);

sastrawi_err stem_singular_word(sastrawi_stemmer *stemmer, char *original_word, char **stemmed_word, int *rc)
{

  //step 1: word already in dictionary
  if(dictionary_contains(original_word)) {
    (*stemmed_word) = strndup(original_word, strlen(original_word));
    *rc = 1;
  }

  char *post_remove = NULL;
  int remover_rc = 0;
  sastrawi_err err;

  if(is_precedence_adjustment_satisfied(original_word)) {
    err = apply_affix_removers(stemmer, original_word, &post_remove, prefix_suffix_removers, &remover_rc);
    if (SASTRAWI_FAILED(err)) {
      return err;
    }
  }

  if(remover_rc == 0) {
    err = apply_affix_removers(stemmer, original_word, &post_remove, suffix_prefix_removers, &remover_rc);
    if (SASTRAWI_FAILED(err)) {
      return err;
    }
  }

  if(remover_rc == 1) {
    *stemmed_word = strndup(post_remove, strlen(post_remove));
    if (*stemmed_word == NULL) {
      return SASTRAWI_E_MEMORY;
    }
    free(post_remove);
  } else {
    *stemmed_word = strndup(original_word, strlen(original_word));
    if (*stemmed_word == NULL) {
      return SASTRAWI_E_MEMORY;
    }
  }

  *rc = remover_rc;
  return SASTRAWI_E_OK;
}


sastrawi_err apply_affix_removers(sastrawi_stemmer *stemmer, char *original_word, char **stemmed_word, const AFFIX_REMOVER affix_removers[], int *stemmed) {

  char *word = strndup(original_word, strlen(original_word));
  sastrawi_err remover_err = SASTRAWI_E_OK;
  *stemmed = 0;

  for(int i = 0; i<2; i++) {
    int remover_stemmed = 0;
    remover_err = affix_removers[i](stemmer, word, stemmed_word, &remover_stemmed);
    if (SASTRAWI_FAILED(remover_err)) {
      free(word);
      return remover_err;
    }
    if (remover_stemmed) {
      *stemmed = remover_stemmed;
      break;
    } else {
      free(word);
      word = strndup(*stemmed_word, strlen(*stemmed_word));
      free(*stemmed_word);
    }
  }

  free(word);

  return SASTRAWI_E_OK;
}
