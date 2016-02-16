int stem_singular_word(sastrawi_stemmer *stemmer, char *word, char **stemmed_word);
typedef int (*AFFIX_REMOVER)(sastrawi_stemmer *stemmer, char *word, char **stemmed_word);
