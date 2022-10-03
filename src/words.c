#include "include/words.h"
#include "include/terminal.h"
#include "include/params.h"
#include <time.h>

#include "utility/util.h"

#define SHOW 11
#define COMPlETED 5
#define ONDECK 5

#define CAT_UNSET 0
#define CAT_WRONG 0xFF
#define CAT_CORRECT 1
#define CAT_CURRENT 0xAA
#define CAT_UPCOMING 0xF0


/* Check if the random word has been used 
    @param num_words the number of available words
    @param check_word the word index to be checked
    @return boolean True/False
*/
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

/* Gets the linked list 
    @param -
    @return linked_list*
*/
static linked_list *getList(){
    static linked_list *list;
    if(list == NULL){
        list = new_linked_list();
    }

    return list;
}

/* Finds a random number 1 - num_words
    @param *words the words array
    @return char* random word
*/
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

    int idx = rand() % words->num_words;
    while(used(0, idx)){
        ++idx; 
        idx %= words->num_words;
    }
    return words->words[idx];
}

/* Creates/get/frees word container based on an input
    @param option Option to free/get
    @param filename filename to create word_container from
    @return option=1 word_container | option=0 free word_conatiner
*/
static struct word_container *getWordContainer(int option, char *filename){
    static struct word_container *words;
    if(filename){
        words = getWords(filename);
        if(!words){
            printf("Words not found\n");
            return NULL;
        }
    }
    else if(!option){
        freeWords(words);
        return NULL;
    }

    return words;
}

/* Increments and returns word count
    @param add number to be added
    @return word count
*/
static int wordCount(int add){
    static int count;
    count+=add;
    return count;
}

static int wordIdx(int add, int reset){
    static int count;
    if(reset){
        count = 0;
    }
    count+=add;

    return count;
}

static int charCount(int add){
    static int count;
    count+=add;
    return count;
}

static int strCompare(char *a, char *b){
    while(*a && *b){
        if(*a != *b){
            return 0;
        }
        a++;
        b++;
    }

    if(*a || *b){
        return 0;
    }

    return 1;
}

static int rmEscape(char *check){
    static int esc;
    if(*check == '\e'){
        fgetc(stdin);
        fgetc(stdin);
        fgetc(stdin);
        esc = 1;
    }
    else if(esc && *check == '['){
        fgetc(stdin);
        fgetc(stdin);
    }
    else{
        esc = 0;
    }

    return esc;
}

int setupWords(char *filename){
    struct word_container *words;

	printEscape(CURSOR_HIDE);		// Make sure cursor hides

    if(filename == NULL){
        words = getWordContainer(0, (char *)1);
    }
    else{
        words = getWordContainer(0, filename);
    }

    static char *placeholder = "    ";
    if(!words || !used(words->num_words, 0)){
        printf("Array not initialized\n");
        return 0;
    }
    
	disableInput();
    
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

    printf("\n\n\n\n" CURSOR_START);
    printWords();

	enableInput();
	turnEchoOff();
	turnCanonOff();

    return 1;
}

void printWords(){
	linked_node *cur = getList()->head;
    
    printEscape(CURSOR_HIDE CURSOR_HOME);
	for(int i = 0; i < COMPlETED; i++){
        if(cur->category == CAT_CORRECT){printw(DONE_CORRECT, cur->val);}
        else if(cur->category == CAT_WRONG){printw(DONE_WRONG, cur->val);}
        else{printw(DEFAULT, cur->val);}
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

/* Print words starting at a specific node \
    @brief callers job to save/restore cursor 
    @param *start node from linked list to start at
    @return -
*/
static void printWordsAt(linked_node *start){
    while(start){
        if(start->category == CAT_CORRECT){
            printw(DONE_CORRECT, start->val);
        }
        else if(start->category == CAT_CURRENT){
            printw(CURRENT, start->val);
        }
        else if(start->category == CAT_UPCOMING){
            printw(UPCOMING, start->val);
        }
        else if(start->category == CAT_WRONG){
            printw(DONE_WRONG, start->val);
        }
        else if(start->category == CAT_UNSET){
            printw(DEFAULT, start->val);
        }
		start = start->next;
	}
    fflush(NULL);
}

/* Check the char to determin if the current word is right/wrong
    and print the char appropriately
    @param *word current word
    @param idx current index of word
    @param typed the most recently typed char (assumed to be a char from string)
    @param *string the string of all typed letters since last space char
    @param correct bool for if the word has been typed correctly thus far
*/
static int checkChar(char *word, int idx, char **typed, char *string, int *correct){

    /* Special Cases: \
        BackSpace \
        Delete \
        c > ' ' && c < 127 (Normal) \
        IGNORE everything else \
    */
   char c = **typed; 

    /* verify that the char is okay */  
    if((c < ' ' || c >= 126) && (c != 127 && c != 23)){
        (*typed)--;
        return 0;
    }

    if(c == '\b' || c == 127){
        if(*typed >= string){
            **typed = 0;
            (*typed)--;
        }

        if(*typed >= string){
            **typed = 0;
            (*typed)--;

            charCount(wordIdx(0, 0)*-1);
            wordIdx(0, 1);      // reset
        
            while(*string && *word && *string == *word){
                wordIdx(1, 0);
                charCount(1);
                string++;
                word++;
            }

            /* indicates the previous chars are correct */

            if(!*word && !*string){
                printf("  ");
            }
            else if(!*correct && *word && !(*(word+1))){
                printf(CURSOR_BACK CURSOR_SAVE CURRENT "%s  ", word);
            }
            else if(*word && !(*(word+1))){
                printf(CURSOR_SAVE CURRENT "%s  ", word);
            }
            else if(!*word && *string){
                printf(CURSOR_SAVE CURRENT "%s  ", word);
            }
            else if(*word){
                printf(CURSOR_BACK CURSOR_SAVE CURRENT "%s  ", word);
            }
   
            printWordsAt(getList()->current->next);
            printEscape(CURSOR_RESTORE);
        }

        if(!*string){*correct = 1;}
        return 0;       // don't increment
    }
    else if(!word[idx] && *correct){
        printf(CURSOR_FORWARD CUR_WRONG "%c", c);
        printf(CURSOR_SAVE "  ");
        printWordsAt(getList()->current->next);
        printEscape(CURSOR_RESTORE);
        return 0;
    }
    else if(word[idx] == c && *correct){
        printf(CUR_CORRECT "%c" CURRENT, c);
        return *correct;
    }
    else if(word[idx] != c && *correct){
        if(idx != 0){
            printf("\e[%dD" CUR_CORRECT "%s", idx, string);
            printEscape(CURSOR_BACK);
        }
        printf(CUR_WRONG "%c", c);
        printEscape(CURSOR_SAVE);
        printf(CURRENT "%s  ", word+idx);
        printWordsAt(getList()->current->next);
        printEscape(CURSOR_RESTORE);
        *correct = 0;
    }
    else if(!*correct){
        printf(CUR_WRONG "%c", c);
        printEscape(CURSOR_SAVE);
        printf(CURRENT "%s  ", word+idx);
        printWordsAt(getList()->current->next);
        printEscape(CURSOR_RESTORE);
        return *correct;
    }

    
   return 0;
}

void typeCurrentWord(){
    linked_list *list = getList();
    char *word = list->current->val;
    wordIdx(0, 1);      // reset
    int correct = 1;

    char typed_arr[50];
    char *typed = typed_arr;

    typed[0] = 0;           // maintain null termination

    while(1){
    printf(CURSOR_BG CURRENT "%c" CURSOR_BACK DEFAULT, word[wordIdx(0,0)]);
		*typed = fgetc(stdin);
        *(typed+1) = 0;
        rmEscape(typed);

        if(checkParam(PARAM_DEBUG)){
            printf(CURSOR_SAVE "\n\n\e[A");
            hex_dump(typed_arr, 16);
            printEscape(CURSOR_RESTORE); 
        }

        if(*typed == ' '){
            *typed = 0;     // null terminal for string compare
            break;
        }
        else if(checkChar(word, wordIdx(0,0), &typed, typed_arr, &correct)){
            wordIdx(1, 0);
            charCount(1);
        }

        typed++;    // increment typed every loop
    }

    if(strCompare(word, typed_arr)){
        wordCount(1);
        list->current->category = CAT_CORRECT;
    }
    else{
        list->current->category = CAT_WRONG;
    }

    printf(CURSOR_FORWARD DEFAULT "  ");
}

void *type(){
    struct word_container *words = getWordContainer(1, 0);
    linked_list *list = getList();

    while(1){
    // for(int i = 0; i < 5; i++){
        typeCurrentWord();
        linked_list_append(list, randWord(words), CAT_UPCOMING);
        linked_list_remove_head(list);
        list->current = list->current->next;
        printWords();
    }

    return NULL;
}

void goodbyeWords(){
    disableInput();

    free_linked_list(getList());
    used(0, 0);
    randWord(0);
    getWordContainer(0, 0);
    printf(DEFAULT ERASE_LINE CURSOR_HOME CURSOR_WPM "WPM: %d\t    CPM:%d\n\n" ERASE_LINE CURSOR_SHOW, wordCount(0), charCount(0));
	turnEchoOn();
	enableInput();
	turnCanonOn();
    fflush(stdout);
}
