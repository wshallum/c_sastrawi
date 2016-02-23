#ifdef __linux
  #define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include "sastrawi_internal.h"
#include "text_util.h"
#include "remove_suffixes.h"
#include "dictionary.h"
#include "../dbg.h"

sastrawi_err remove_suffixes(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, int *stemmed)
{
  *stemmed = NOT_STEMMED;

  char *removed_parts = NULL;
  char *suffix_remove1 = NULL;
  char *suffix_remove2 = NULL;
  sastrawi_err err;
  int stemmed_unused;

  //step 2a
  err = remove_inflectional_particle(stemmer, word, &suffix_remove1, &removed_parts, &stemmed_unused);
  if (SASTRAWI_FAILED(err)) {
    return err;
  }
  free(removed_parts);

  //step 2b
  err = remove_possessive_pronoun(stemmer, suffix_remove1, &suffix_remove2, &removed_parts, &stemmed_unused);
  if (SASTRAWI_FAILED(err)) {
    free(suffix_remove1);
    return err;
  }
  free(removed_parts);

  //step 3
  err = remove_derivational_suffix(stemmer, suffix_remove2, stemmed_word, &removed_parts, &stemmed_unused);
  if (SASTRAWI_FAILED(err)) {
    free(suffix_remove1);
    free(suffix_remove2);
    return err;
  }
  free(removed_parts);
  free(suffix_remove1);
  free(suffix_remove2);

  *stemmed = 0;
  if(dictionary_contains(*stemmed_word)) {
    *stemmed = FULLY_STEMMED;
  }

  return SASTRAWI_E_OK;
}


sastrawi_err remove_inflectional_particle(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part, int *stemmed)
{
  return remove_suffix(stemmer, "lah|kah|tah|pun", word, stemmed_word, removed_part, stemmed);
}

sastrawi_err remove_possessive_pronoun(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part, int *stemmed)
{
  return remove_suffix(stemmer, "ku|mu|nya", word, stemmed_word, removed_part, stemmed);
}

sastrawi_err remove_derivational_suffix(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part, int *stemmed)
{
  return remove_suffix(stemmer, "is|isme|isasi|i|kan|an", word, stemmed_word, removed_part, stemmed);
}

sastrawi_err remove_suffix(sastrawi_stemmer *stemmer, char *suffixes, char *word, char **stemmed_word, char **removed_part, int *stemmed)
{
  char *pattern = NULL;

  if (asprintf(&pattern, "(\\w+?)-?(%s)$", suffixes) == -1) {
    return SASTRAWI_E_MEMORY;
  }

  *stemmed = suffix_split_word(stemmer, pattern, word, stemmed_word, removed_part);

  free(pattern);
  return SASTRAWI_E_OK;
}
