#include "linked_list.h"
#include "wordFile.h"
#include "colors.h"
#include "macros.h"

/* Initialize words and all necessary containers 
    @param *filename    name of file containing words
    @return -
*/
void setupWords(char *filename);

/* Prints the formatted words  
    @param -
    @return -
*/
void printWords();

/* Performs necessary operations to type the current word until space char
    @param -
    @return -
*/
void typeCurrentWord();

/* Loop and swap words
    @param -
    @return -
*/
void *type();

/* Frees container and reset terminal config  
    @param -
    @return -
*/
void goodbyeWords();