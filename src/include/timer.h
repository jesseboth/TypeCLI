#include <stdint.h>

#define TIMER_POS "\e[2A\e[32G"

int timerContinue(uint8_t set, uint8_t val);
int timerDecrement(uint8_t dec);
void timer();
