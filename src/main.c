#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "include/colors.h"
#include "include/terminal.h"
#include "include/timer.h"
#include "include/words.h"

int main(int argc, char **argv){
	char *filename = "src/words.txt";
	atexit(goodbyeWords); 				// exit function

	setupWords(filename);
	pthread_t thread;
	pthread_create(&thread, NULL, &type, NULL);

	timer();
	pthread_cancel(thread);

	return 0;
}
