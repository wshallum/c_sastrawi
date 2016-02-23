#ifndef SASTRAWI_STEM_SINGULAR_H_INCLUDED
#define SASTRAWI_STEM_SINGULAR_H_INCLUDED
sastrawi_err stem_singular_word(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, int *stemmed);
typedef sastrawi_err (*AFFIX_REMOVER)(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, int *stemmed);
#endif
