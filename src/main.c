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

	setupWords(filename);
	typeCurrentWord();
	typeCurrentWord();

	return 0;
}
