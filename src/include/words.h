#include "linked_list.h"
#include "wordFile.h"
#include "colors.h"
#include "macros.h"

/* Initialize words and all necessary containers 
    @param *filename    name of file containing words
    @return true/false  failure/success  
*/
int setupWords(char *filename);

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

/* wait for Enter key to be pressed
    @param -
    @return -
*/
void waitForEnter();

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