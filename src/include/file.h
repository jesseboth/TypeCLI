#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct word_container{
    unsigned int num_words;
    unsigned long num_bytes;
    char **words;
};

struct word_container *getWords(char *filename);
int freeWords(struct word_container *words);
char *nextWord(char **buffer);
unsigned long numWords(void *buffer);