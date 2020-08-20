/*
 * File:   Encoder.c
 * Author: jumaayal
 *
 * Created on February 6, 2020, 5:03 PM
 */

/*
 * Setup
 * Connect pin36 to pin A of encoder
 * Connect pin 37 to pin B of encoder
 */

#include "xc.h"
#include <BOARD.h>
#include <Oled.h>
#include <stdio.h>
#include <QEI.h>

int position;
char string [30]; 
int main(void) {
    BOARD_Init();
    OledInit();
    QEI_Init();
    position =0;
    printf("\nBegin\n");
    while(1){
        position=QEI_GetPosition();
        sprintf(string, "\nDegrees:%d \n", position);
        /*Prints String on Oled*/
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
    }
}
