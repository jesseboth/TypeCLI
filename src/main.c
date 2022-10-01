#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include "include/colors.h"
#include "include/terminal.h"
#include "include/timer.h"
#include "include/words.h"

pthread_t pthread(){
	static pthread_t thread;
	return thread;
}

void sigint_handler(int signum) { //Handler for SIGINT
	signal(SIGINT, sigint_handler);
	timerContinue(1, 0);
	fflush(stdout);
}

int main(int argc, char **argv){
	char *filename = "src/words.txt";
	atexit(goodbyeWords); 				// exit function
	signal(SIGINT, sigint_handler);
	

	setupWords(filename);
	pthread_t thread = pthread();
	pthread_create(&thread, NULL, &type, NULL);

	timer();
	pthread_cancel(thread);

	return 0;
}