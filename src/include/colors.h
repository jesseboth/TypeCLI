

#define RGB(r, g, b) "\e[38;5;{" r "};{" g "};{" b "}m"
#define DEFAULT "\e[0m"

#define CURRENT "\e[38;5;255m"
#define UPCOMING "\e[38;5;244m"
#define CUR_CORRECT "\e[38;5;47m"

#define CUR_WRONG "\e[38;5;160m"

#define CURSOR_BG "\e[48;5;241m"

#define DONE_CORRECT "\e[38;5;22m"
#define DONE_WRONG "\e[38;5;88m"

#define CURSOR_START "\e[2A\e[0G"

#define CURSOR_HOME "\e[0G"
#define CURSOR_SAVE "\e[s"
#define CURSOR_RESTORE "\e[u"

#define CURSOR_HIDE "\e[?25l"
#define CURSOR_SHOW "\e[?25h"
#define CURSOR_BACK "\e[1D"
#define CURSOR_FORWARD "\e[1C"

// TODO: This will change
#define CURSOR_DONE "\e[2B\e[0G"

#define ERASE_LINE "\e[2K"