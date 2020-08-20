/*
 * File:   frequency_measure.c
 * Author: jumaayal
 *
 * Created on February 7, 2020, 7:33 AM
 */


#include "xc.h"
#include <CAPTOUCH.h>
#include <stdio.h>
#include <BOARD.h>
#include <Oled.h>
int touched;
char string[30];
int main(void) {
    BOARD_Init();
    OledInit();
    CAPTOUCH_Init();
    
    while(1){
        touched=CAPTOUCH_IsTouched();
        if(touched){
            sprintf(string,"Contact");  
        }else{
            sprintf(string,"No Contact");  
        }
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
    }
}
