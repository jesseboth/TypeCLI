#include <termios.h>


void disableInput(void);
void enableInput(void);

void discardInputBuffer(void);
void discardInputLine(void);

void setTermiosBit(int fd, tcflag_t bit, int onElseOff );
void turnEchoOff(void);
void turnEchoOn(void);
void turnCanonOff(void);
void turnCanonOn(void);
