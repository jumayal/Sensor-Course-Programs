/*
 * File:   Pot_Tone.c
 * Author: jumaayal
 *
 * Created on January 7, 2020, 5:57 PM
 */


#include <AD.h>
#include <BOARD.h>
#include <stdio.h>
#include <Oled.h>
#include <math.h>

int value;
double voltage;
int frequency;
char string [30];
int prev=0;
int main(void) {
    BOARD_Init();
    AD_Init();
    OledInit();
    ToneGeneration_Init();
    printf("Begin");
  
    AD_AddPins(AD_A0);
    ToneGeneration_ToneOn();

    while(1){
    //Reads Potentiometer value from potentiometer and convert to voltage
    value = AD_ReadADPin(AD_A0);
    
    if(abs(prev-value)<20){
        value=prev;
    }else{
       prev=value;
    }
    //10k 2.2uf
    voltage = (value*3.3)/1023;
    //frequency ranges from 20-1000 because the output does not match the frequency after that
    //Human ear works exponentialy 
    frequency = pow(1.5,(((double)value*10)/1023)+7);
    ToneGeneration_SetFrequency(frequency);
    
    //Creates string from int
    sprintf(string, "Voltage: %fV \nFrequency %d", voltage,frequency);
    //Prints String on Oled
    OledDrawString(string);
    OledUpdate();
    OledClear(OLED_COLOR_BLACK);
    }
    
}
