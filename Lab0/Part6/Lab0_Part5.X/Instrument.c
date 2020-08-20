/*
 * File:   Instrument.c
 * Author: jumaayal
 *
 * Created on January 8, 2020, 2:18 PM
 */
//1.5k 0.1uf RC filter

#include <AD.h>
#include <BOARD.h>
#include <stdio.h>
#include <Oled.h>
#include <math.h>
#include<ToneGeneration.h>

int value;
double voltage;
int frequency=0;
int diff=0;
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
        
        //each button adds to the frequency output
        if(BTN1){
            frequency= frequency + TONE_196; 
        }
        if(BTN2){
            frequency= frequency + TONE_293; 
        }
        if(BTN3){
            frequency= frequency + TONE_440; 
        }
        if(BTN4){
            frequency= frequency + TONE_659; 
        }
        if(frequency==0){
            ToneGeneration_ToneOff();
            continue;
        }
     
        //Reads Potentiometer value from potentiometer and convert to voltage
        value = AD_ReadADPin(AD_A0);

        //Filters out noise
        if(abs(prev-value)<20){
            value=prev;
        }else{
            prev=value;
        }

        //Converts digital to voltage reading
        voltage = (value*3.3)/1023;

        //The potentiometer alters frequency from button by + or - 97
        diff = ((double)value*194)/1023-97;
        ToneGeneration_ToneOn();
        ToneGeneration_SetFrequency(frequency+diff);

        //Creates string from int
        sprintf(string, "Voltage: %fV \nFrequency %dHz\nChange %dHz", voltage,frequency,diff);
        //Prints String on Oled
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);

        //resets frequency
        frequency=0;
    }  
}
