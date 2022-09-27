#include "include/words.h"
#include "include/terminal.h"
#include <time.h>

#define SHOW 11
#define COMPlETED 5
#define ONDECK 5

#define CAT_UNSET 0
#define CAT_WRONG -1
#define CAT_CORRECT 1
#define CAT_CURRENT 0xAA
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
    static int reset;

    if(!reset){
        reset = 1;
        srand(time(NULL));
    }
    else if(!words){
        reset = 0;
        return NULL;
    }

    // want an error if this isn't set
    int idx = -1;
    do{
        idx = rand() % words->num_words;
    }while(used(0, idx));

    return words->words[idx];
}

static struct word_container *getWordContainer(void *option, char *filename){
    static struct word_container *words;
    if(filename){
        words = getWords(filename);
        if(!words){
            printf("Words not found");
            return NULL;
        }
    }
    else if(!option){
        freeWords(words);
        return NULL;
    }

    return words;
}

int wordCount(int add){
    static int count;
    return count+=add;
}

void setupWords(char *filename){

	disableInput();
    struct word_container *words = getWordContainer(0, filename);

    static char *placeholder = "    ";
    if(!used(words->num_words, 0)){
        printf("Array not initialized");
        return;
    }
    
    linked_list *list = getList();
	for(int i = 0; i < COMPlETED; i++){
        linked_list_append(list, placeholder, CAT_UNSET);
	}

    // Current Word
    linked_list_append(list, randWord(words), CAT_CURRENT);
    list->current = list->tail;

	for(int i = 0; i < ONDECK; i++){
        linked_list_append(list, randWord(words), CAT_UPCOMING);
	}

    printf("\n\n\n" CURSOR_START);
    printWords();

	enableInput();
	turnEchoOff();
	turnCanonOff();
}

void printWords(){
	linked_node *cur = getList()->head;
    
    printEscape(CURSOR_HIDE CURSOR_HOME);
	for(int i = 0; i < COMPlETED; i++){
		printw(DEFAULT, cur->val);
		cur = cur->next;
	}
    printEscape(CURSOR_SAVE);
	printw(CURRENT, cur->val);
	cur = cur->next;
	for(int i = 0; i < ONDECK; i++){
		printw(UPCOMING, cur->val);
		cur = cur->next;
	}
    printEscape(CURSOR_RESTORE);
    fflush(NULL);
}

/* callers job to save/restore cursor */
void printWordsAt(linked_node *start){
    while(start){
        if(start->category == CAT_CORRECT){
            printw(DONE_CORRECT, start->val);
        }
        else if(start->category = CAT_CURRENT){
            printw(CURRENT, start->val);
        }
        else if(start->category = CAT_UPCOMING){
            printw(UPCOMING, start->val);
        }
        else if(start->category = CAT_WRONG){
            printw(DONE_WRONG, start->val);
        }
        else if(start->category = CAT_UNSET){
            printw(DEFAULT, start->val);
        }
		start = start->next;
	}
    fflush(NULL);
}

    /* Special Cases:
        Arrow: L + R   (MAYBE)
        BackSpace
        Delete
        c > ' ' && c < 127 (Normal)
        IGNORE everything else
    */
int checkChar(char *word, uint8_t idx, char typed, char *string, int correct){

    if(word[idx] == typed && correct){
        printf(CUR_CORRECT "%c" CURRENT, typed);
        return 1;
    }
    else if(word[idx] != typed && correct){
        printf("\e[%dD" CUR_CORRECT "%s", idx, string);
        printf(CURSOR_BACK CUR_WRONG "%c", typed);
        printEscape(CURSOR_SAVE);
        printf(CURRENT "%s  ", word+idx);
        printWordsAt(getList()->current->next);
        printEscape(CURSOR_RESTORE);
    }
    else if(!correct && typed != '\b'){
        printf(CUR_WRONG "%c", typed);
        printEscape(CURSOR_SAVE);
        printf(CURRENT "%s  ", word+idx);
        printWordsAt(getList()->current->next);
        printEscape(CURSOR_RESTORE);
    }

   return 0;
}

void typeCurrentWord(){
    linked_list *list = getList();
    char *word = list->current->val;
    uint8_t word_i = 0;
    int correct = 1;

    static char typed_arr[50];
    static char *typed = typed_arr;

    typed[0] = 0;           // maintain null termination

    while(1){
    printf(CURSOR_BG CURRENT "%c" CURSOR_BACK DEFAULT, word[word_i]);
		*typed = fgetc(stdin);
        *(typed+1) = 0;

        if(*typed == ' '){
			printf(DEFAULT "  ");
            return;
        }
        else if(correct = checkChar(word, word_i, *typed, typed_arr, correct)){
            word_i++;
        }

        typed++;    // increment typed every loop
    }
}

void goodbyeWords(){
    disableInput();

    free_linked_list(getList());
    used(0, 0);
    randWord(0);
    getWordContainer(0, 0);
    printf(DEFAULT ERASE_LINE CURSOR_HOME "WPM: %d" CURSOR_DONE CURSOR_SHOW, wordCount(0));

	turnEchoOn();
	enableInput();
	turnCanonOn();
}