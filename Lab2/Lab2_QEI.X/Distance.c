/*
 * File:   Distance.c
 * Author: jumaayal
 *
 * Created on February 6, 2020, 11:36 PM
 */

/*
 * Setup
 * Connect pin35 to trigger of PIN SENSOR
 * Connect Pin 34 to echo pin of PING Sensor
 * Connect Pin 2 to input of Audio Amp
 */

#include "xc.h"
#include <BOARD.h>
#include <Oled.h>
#include <stdio.h>
#include <PING.h>
#include <ToneGeneration.h>

#define CONVERTER 16
#define BUFFERLENGTH 20
#define THRESHOLD 2
int distance;
char string [30];
int frequency;
int buffer[BUFFERLENGTH];
int average;
int counter;
int lastSampled;
int past;
int main(void) {
    BOARD_Init();
    OledInit();
    PING_Init();
    ToneGeneration_Init();
    printf("\nBegin\n");
    ToneGeneration_ToneOn();
    counter=0;
    average=0;
    lastSampled=BUFFERLENGTH-1;
    past=0;
    while(1){
        distance=PING_GetDistance();
        if(abs(distance-past)<THRESHOLD){
            distance=past;
        }else{
            past=distance;
        }
        buffer[counter%BUFFERLENGTH]=distance/2;
        average=average+(distance/2)- buffer[lastSampled];
        frequency=CONVERTER*average;
        if(frequency>1000){
            frequency=1000;
        }else if(frequency<0){
            frequency=0;
        }
        ToneGeneration_SetFrequency(frequency);
        
        sprintf(string, "\nDistance:%d \n", distance);
        /*Prints String on Oled*/
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
        lastSampled= (lastSampled+1)%BUFFERLENGTH;
        counter++;
    }
}
