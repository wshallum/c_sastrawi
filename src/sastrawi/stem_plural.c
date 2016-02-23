#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sastrawi_internal.h"
#include "stem_plural.h"
#include "stem_singular.h"
#include "../regex/preg.h"
#include "../dbg.h"

int is_plural(sastrawi_stemmer *stemmer, char *word)
{
  char **matches;

  int matches_count, dash_count;
    
  matches_count = preg_match(&stemmer->regex_cache, "^(.*)-(ku|mu|nya)$", word, &matches);

  if(matches_count > 0) {
    dash_count = strchr(matches[1], '-') != NULL;
    free_matches(matches_count, &matches);
  } else {
    dash_count = strchr(word, '-') != NULL;
  }

  return dash_count;

}

int plural_parts(sastrawi_stemmer *stemmer, char *word, char **parts[])
{
  char **matches;
  int matches_count, parts_count, rc;

  matches_count = preg_match(&stemmer->regex_cache, "^(.*)-(.*)-(ku|mu|nya)$", word, &matches);

  if(matches_count < 0) {
    matches_count = preg_match(&stemmer->regex_cache, "^(.*)-(.*)$", word, &matches);
  }

  if(matches_count>0) {

    char *second_part;

    if(matches_count == 4) {
      rc = asprintf(&second_part, "%s-%s",matches[2], matches[3]);
      check_debug(rc != -1, "Cannot allocate memory");
    } else {
      second_part = strndup(matches[2], strlen(matches[2]));
    }

    *parts = malloc(2 * sizeof(char*));
    (*parts)[0] = strndup(matches[1], strlen(matches[1]));
    (*parts)[1] = second_part;

    parts_count = 2;

    free_matches(matches_count, &matches);
  } else {
    *parts = malloc(1 * sizeof(char*));
    (*parts)[0] = strndup(word, strlen(word));
    parts_count = 1;
  }


  return parts_count;
error:
  exit(1);
}


int stem_plural_word(sastrawi_stemmer *stemmer, char *word, char **stemmed_word)
{

  char **word_parts = NULL;
  char *root_word0 = NULL;
  char *root_word1 = NULL;
  int stemmed;

  int rc = plural_parts(stemmer, word, &word_parts);

  stem_singular_word(stemmer, word_parts[0], &root_word0, &stemmed);
  stem_singular_word(stemmer, word_parts[1], &root_word1, &stemmed);


  debug("word parts %s => %s, %s => %s", word_parts[0], root_word0, word_parts[1], root_word1);

  if(strcmp(root_word0, root_word1) == 0) {
    (*stemmed_word) = strndup(word_parts[0], strlen(word_parts[0]));
  } else {
    (*stemmed_word) = strndup(word, strlen(word));
  }

  free_matches(rc, &word_parts);
  free(root_word0);
  free(root_word1);

  return 1;
}
