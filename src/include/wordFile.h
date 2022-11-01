#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Container to hold words/elements
  @param num_words    number of words
  @param num_bytes    total bytes words occupy
  @param words        ptr to words array
*/
struct word_container{
  unsigned int num_words;     // Number of words in file
  unsigned long num_bytes;
  char **words;
};

/* Get words from file
  @param *filename     file that contains words
  @return -
*/
struct word_container *getWords(char *filename);

/* Free words buffer and containers
  @param *words      `words_container
  @return -
*/
void freeWords(struct word_container *words);

/* Get next word
  @param **buffer     buffer of all words
  @return char*       null terminated word
*/
char *nextWord(char **buffer);

/* numWords 
  @param *buffer      checks how may words 
  @return -
*/
unsigned long numWords(void *buffer);