typedef int (*PREFIX_REMOVER)(char *word, char **stemmed_word, char **removed_part);

int remove_prefixes(char *word, char **stemmed_word);
int remove_plain_prefix(char *word, char **stemmed_word, char **removed_part);
int remove_prefix(char *prefixes, char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule1(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule2(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule3(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule4(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule5(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule6(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule7(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule8(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule9(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule10(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule11(char *word, char **stemmed_word, char **removed_part);
