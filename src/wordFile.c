#include "include/wordFile.h"
#include "include/defaultwords.h"

/* load words into a buffer and return a words container */
struct word_container *getWords(char *filename){
  struct word_container *words = malloc(sizeof(struct word_container));

  if(filename != (char *)1){
    FILE *file;
    file = fopen(filename, "r");
    if(file == NULL){
      printf("File not found\n");
      return NULL;
    }

    fseek(file, 0L, SEEK_END);
    words->num_bytes = ftell(file);
    fseek(file, 0L, SEEK_SET);

    void *buffer = calloc(words->num_bytes, sizeof(char));
    if(buffer == NULL){
      return NULL;
    }

    fread(buffer, sizeof(char), words->num_bytes, file);
    fclose(file);

    words->num_words = numWords(buffer);
    words->words = malloc(sizeof(char *)*words->num_words);
    char *store = (char *)buffer;
    int i = 0;
    words->words[i] = store;
    while((store = nextWord(&store))){
      words->words[++i] = store;
    }
  }
  else{
    words->num_words = DEFAULT_NUMWORDS;
    words->num_bytes = sizeof(DEFAULT_WORDS);
    words->words = DEFAULT_WORDS;
  }

    return words;
}

void freeWords(struct word_container *words){
  if(words->words != DEFAULT_WORDS){
    free(words->words[0]);   // free buffer
    free(words->words);    // free array
  }
  free(words);       // free container
}

char *nextWord(char **buffer){
  while(**buffer && **buffer != '\n'){
    (*buffer)++;
  }

  char *c = *buffer;
  if(*c){
    *c = '\0';
    return ++(*buffer);
  }

  return NULL;
}

/* get the number of words */
unsigned long numWords(void *buffer){
  unsigned long num = 1;
  char *chars = (char *)buffer;
  while(*chars++){
    if(*chars == '\n'){
      num++;
    }
  }
  return num;
}