#include <termios.h>


/* Disable all user input
  @param -
  @return -
*/
void disableInput(void);

/* Enable user input (default)
  @param -
  @return -
*/
void enableInput(void);

/* Discard the input buffer stdin
  @param -
  @return -
*/
void discardInputBuffer(void);

/* Discard the current input line stdin (before \n)
  @param -
  @return -
*/
void discardInputLine(void);

/* set termios bit
  @param fd
  @param bit
  @param onElseOff
  @return -
*/
void setTermiosBit(int fd, tcflag_t bit, int onElseOff );

/* Disable input echo
  @param -
  @return -
*/
void turnEchoOff(void);

/* Enable input echo (default) 
  @param -
  @return -
*/
void turnEchoOn(void);

/* Disable cannon
  @param -
  @return -
*/
void turnCanonOff(void);

/* Enable cannon (default)
  @param -
  @return -
*/
void turnCanonOn(void);
