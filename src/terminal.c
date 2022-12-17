#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include "include/terminal.h"

struct termios g_terminalSettings; // global to track and change terminal settings

void disableInput(void) {
  turnEchoOff(); // so the terminal won't display all the crap the user decides to type during gameplay
  turnCanonOff(); // so the terminal will return crap characters immediately, so we can clear them later without waiting for a LF
} // end disableInput()

void enableInput(void) {
  discardInputBuffer(); // clear all crap characters before enabling input
  turnCanonOn(); // so the user can type and edit a full line of input before submitting it
  turnEchoOn(); // so the user can see what he's doing as he's typing
} // end enableInput()

void turnEchoOff(void) { setTermiosBit(0,ECHO,0); }
void turnEchoOn(void) { setTermiosBit(0,ECHO,1); }

void turnCanonOff(void) { setTermiosBit(0,ICANON,0); }
void turnCanonOn(void) { setTermiosBit(0,ICANON,1); }

void setTermiosBit(int fd, tcflag_t bit, int onElseOff ) {
  static int first = 1;
  if (first) {
    first = 0;
    tcgetattr(fd,&g_terminalSettings);
  } // end if
  if (onElseOff)
    g_terminalSettings.c_lflag |= bit;
  else
    g_terminalSettings.c_lflag &= ~bit;
  tcsetattr(fd,TCSANOW,&g_terminalSettings);
} // end setTermiosBit()

void discardInputBuffer(void) {
  struct timeval tv;
  fd_set rfds;
  while (1) {
    // poll stdin to see if there's anything on it
    FD_ZERO(&rfds);
    FD_SET(0,&rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    if (select(1,&rfds,0,0,&tv) == -1) { fprintf(stderr, "[error] select() failed: %s", strerror(errno) ); exit(1); }
    if (!FD_ISSET(0,&rfds)) break; // can break if the input buffer is clean
    // select() doesn't tell us how many characters are ready to be read; just grab a big chunk of whatever is there
    char buf[500];
    ssize_t numRead = read(0,buf,500);
    if (numRead == -1) { fprintf(stderr, "[error] read() failed: %s", strerror(errno) ); exit(1); }
    printf("[debug] cleared %ld chars\n",numRead);
  } // end while
} // end discardInputBuffer()

void discardInputLine(void) {
  // assumes the input line has already been submitted and is sitting in the input buffer
  int c;
  while ((c = getchar()) != EOF && c != '\n');
} // end discardInputLine()