#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/file.h"

int main(int argc, char **argv){

	struct word_container *words = getWords("src/words.txt");
	if(!words){
		return 1;
	}
	for(int i = 0; i < words->num_words; i++){
		printf("%d: %s\n", i, words->words[i]);
	}

	return 0;
}
