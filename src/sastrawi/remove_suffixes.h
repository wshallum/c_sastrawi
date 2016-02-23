#ifndef SASTRAWI_REMOVE_SUFFIXES_H_INCLUDED
#define SASTRAWI_REMOVE_SUFFIXES_H_INCLUDED

#define NOT_STEMMED 0
#define FULLY_STEMMED 1
#define PARTIALLY_STEMMED 2

sastrawi_err remove_suffixes(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, int *stemmed);
sastrawi_err remove_inflectional_particle(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part, int *stemmed);
sastrawi_err remove_possessive_pronoun(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part, int *stemmed);
sastrawi_err remove_derivational_suffix(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part, int *stemmed);
sastrawi_err remove_suffix(sastrawi_stemmer *stemmer, char *suffixes, char *word, char **stemmed_word, char **removed_part, int *stemmed);
#endif
