#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "include/colors.h"
#include "include/terminal.h"

#include "include/words.h"

void *signalHandler(int sig){
	goodbyeWords();
}

int main(int argc, char **argv){
	char *filename = "src/words.txt";
	atexit(goodbyeWords); 				// exit function

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
			printf(CURSOR_BG "%c" DEFAULT, c);
		}
	}

	return 0;
}
