#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/macros.h"
#include "include/file.h"
#include "include/queue.h"

int main(int argc, char **argv){

	struct word_container *words = getWords("src/words.txt");
	if(!words){
		return 1;
	}
	// for(int i = 0; i < words->num_words; i++){
	// 	printf("%d: %s\n", i+1, words->words[i]);
	// }

	linked_list *list = new_linked_list();
	for(int i = 0; i < 10; i++){
		linked_list_append(list, words->words[i]);
	}

	char *prev = words->words[10];

	printw(prev);
	return 0;
}
