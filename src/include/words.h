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

/* Frees container and reset terminal config  
    @param -
    @return -
*/
void goodbyeWords();