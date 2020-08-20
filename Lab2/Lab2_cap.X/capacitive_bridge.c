/*
 * File:   capacitive_bridge.c
 * Author: jumaayal
 *
 * Created on February 7, 2020, 5:52 AM
 */

/*
 *Setup
 * Connect 3.3V and GRN power pins to breadboard
 *Connected OPAMP output to A1
 *
 */

#include "xc.h"
#include <BOARD.h>
#include <Oled.h>
#include <stdio.h>
#include <AD.h>

enum signal{
    touch,
    potential,
    noContact
}SQR;
#define VOLTAGECONVERTER 3.3/1023
#define HIGHVOLTAGETHRESHOLD 2.0
#define LOWVOLTAGETHRESHOLD 1.0
#define COUNTERTHRESHOLD 5
int input;
int voltageInput;
int counter;
char string [30];
int main(void) {
    BOARD_Init();
    AD_Init();
    OledInit();
    AD_AddPins(AD_A1);
    SQR=noContact;
    counter=0;
    while(1){
        input = AD_ReadADPin(AD_A1);
        voltageInput=input *VOLTAGECONVERTER;
        switch(SQR){
            case noContact:
                 if(voltageInput>HIGHVOLTAGETHRESHOLD){
                    SQR=touch;
                }else{
                    sprintf(string,"No Contact");   
                }
                 break;
            case touch:
                counter=0;
                if(voltageInput<LOWVOLTAGETHRESHOLD){
                    SQR=potential;
                }else{
                    sprintf(string,"Contact");  
                }
                break;
            case potential:
                counter++;
                if(voltageInput>LOWVOLTAGETHRESHOLD){
                    SQR=touch;
                }else if(counter>COUNTERTHRESHOLD){
                    SQR=noContact;
                }else{
                    sprintf(string,"Contact");  
                }
                break;
            default:
                printf("Error in state");
        }
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
    }
}
