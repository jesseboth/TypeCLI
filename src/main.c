#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/colors.h"
#include "include/terminal.h"

#include "include/words.h"

int main(int argc, char **argv){
	char *filename = "src/words.txt";

	disableInput();
	setupWords(filename);

	
	char c;
	enableInput();
	turnEchoOff();
	turnCanonOff();
	for(int i = 0; i < 10; i++){
		printEscape(CURSOR_BG)
		// scanf(" %s", &c);
		c = fgetc(stdin);
		if(c == ' '){
			printf(DEFAULT "  ");
		}
		else{
			printf(CURSOR_BG "%c", c);
		}
	}
	disableInput();
	printf("DONE");
	goodbyeWords();

	turnEchoOn();
	enableInput();
	turnCanonOn();

	return 0;
}
