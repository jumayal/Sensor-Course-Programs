/*
 * File:   frequency_measure.c
 * Author: jumaayal
 *
 * Created on February 7, 2020, 7:33 AM
 */

/*
 * Setup
 * Connect pin 35 to output of timer
 * 
 */

#include "xc.h"
#include <CAPTOUCH.h>
#include <stdio.h>
#include <BOARD.h>
#include <Oled.h>

char string [30];
int touched;
int main(void) {
    BOARD_Init();
    OledInit();
    CAPTOUCH_Init();

     
    printf("\nBegin\n");
    while(1){
        touched=CAPTOUCH_IsTouched();
        if(touched){
            sprintf(string,"Contact");
        }else{
            sprintf(string,"No Contact");
        }
        sprintf(string,"Frequency: %d",returnF());
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
    }
}
