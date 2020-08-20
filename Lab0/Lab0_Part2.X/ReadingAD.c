/*
 * File:   ReadingAD.c
 * Author: jumaayal
 *
 * Created on January 7, 2020, 2:43 PM
 */

#include <AD.h>
#include <BOARD.h>
#include <stdio.h>
#include <Oled.h>
#include "xc.h"

int value;
double voltage;
char string [30];
int i;
int main(void) {
    BOARD_Init();
    AD_Init();
    OledInit();
    printf("Begin");
  
    AD_AddPins(AD_A0);
    
    while(1){
    //Reads Potentiometer value from potentiometer and convert to voltage
    value = AD_ReadADPin(AD_A0);
    voltage = (value*3.3)/1023;
    
    //Creates string from int
    sprintf(string, "Voltage: %f ", voltage);
    
    //Prints String on Oled
    OledDrawString(string);
    OledUpdate();
    OledClear(OLED_COLOR_BLACK); 
    }
    
}
