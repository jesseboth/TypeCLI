#include "include/words.h"

#define SHOW 11
#define COMPlETED 5
#define ONDECK 5

#define CAT_UNSET 0
#define CAT_WRONG -1
#define CAT_CORRECT 1
#define CAT_CURRENT 0xFF
#define CAT_UPCOMING 0xF0

static int used(int num_words, int check_word){
    static uint8_t *u;
    if(!num_words && !check_word){
        free(u);
    }
    else if(num_words == 0){
        // 1 for used, 0 for unused
        if(!u[check_word]){
            u[check_word] ^= 1;
        }
        return !u[check_word];
    }
    else{
        u = calloc(num_words, sizeof(uint8_t));
        return 1;
    }

    return 0;
}

static linked_list *getList(){
    static linked_list *list;
    if(list == NULL){
        list = new_linked_list();
    }

    return list;
}

static char *randWord(struct word_container *words){
    // want an error if this isn't set
    int idx = -1;
    do{
        idx = rand() % words->num_words;
    }while(used(0, idx));

    return words->words[idx];
}

void setupWords(struct word_container *words){

    static char *placeholder = "    ";
    if(!used(words->num_words, 0)){
        printf("Array not initialized");
    }

    linked_list *list = getList();
	for(int i = 0; i < COMPlETED; i++){
        linked_list_append(list, placeholder, CAT_UNSET);
	}

    // Current Word
    linked_list_append(list, randWord(words), CAT_CURRENT);

	for(int i = 0; i < ONDECK; i++){
        linked_list_append(list, randWord(words), CAT_UPCOMING);
	}

	linked_node *cur = list->head;

	for(int i = 0; i < COMPlETED; i++){
		printw(DEFAULT, cur->val);
		cur = cur->next;
	}
	printw(CURRENT, cur->val);
	cur = cur->next;
	for(int i = 0; i < ONDECK; i++){
		printw(UPCOMING, cur->val);
		cur = cur->next;
	}

}