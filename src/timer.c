#include "include/timer.h"
#include <unistd.h>
#include <stdio.h>
#include "include/colors.h"

void timer(){
    for(int i = 60; i >= 0; i--){
        printf(CURSOR_SAVE TIMER_POS "Time: %d \n" CURSOR_RESTORE, i);
        sleep(1);
    }
    printf(CURSOR_SAVE TIMER_POS ERASE_LINE "\n" CURSOR_RESTORE);
    return;
}