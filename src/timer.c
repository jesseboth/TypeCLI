#include "include/timer.h"
#include <unistd.h>
#include <stdio.h>
#include "include/colors.h"

int timerContinue(uint8_t set, uint8_t val){
    static uint8_t timerExit;

    if(set){
        timerExit = val;
    }

    return (int)timerExit;
}

void timer(){
    timerContinue(1,1);
    for(int i = 60; i >= 0 && timerContinue(0,0); i--){
        printf(CURSOR_SAVE TIMER_POS "Time: %d \n" CURSOR_RESTORE, i);
        sleep(1);
    }
    printf(CURSOR_SAVE TIMER_POS ERASE_LINE "\n" CURSOR_RESTORE);
    return;
}