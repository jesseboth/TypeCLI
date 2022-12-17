#include <stdio.h>

#define printw(color, str) printf(color "%s  ", str)
#define printEscape(...) printf(__VA_ARGS__);
#define DEBUG(string, ...) printf(CURSOR_SAVE "\n" string CURSOR_RESTORE, __VA_ARGS__);
