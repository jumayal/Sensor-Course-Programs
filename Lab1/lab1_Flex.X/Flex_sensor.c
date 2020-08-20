/*
 * File:   Flex_sensor.c
 * Author: jumaayal
 *
 * Created on January 18, 2020, 10:02 PM
 */

#include <BOARD.h>
#include <ToneGeneration.h>
#include <Oled.h>
#include <AD.h>
#include <math.h>
#include <stdio.h>

#define BUFFERLENGTH 16     // # of sampled values to average
#define NOISETHRESHOLD 10   // difference between recent and previous values to be considered an event
#define PLAYTIME 250        // Code iterations till sound stops
#define PIEZOTHRESHOLD 150  // ADC threshold to be considered an event

int buffer[BUFFERLENGTH]={0};
int averageCounter, average, sum,i, past;   // To find the average and filter noise
int frequency;                              //frequency to set the frequency
int piez, timer;                            //variables for piezo ADC input and sound output time
char string [30];                           // holds string to print out
double flexVoltage,flexADC, degrees;        //flex values

int main(void) {
    //Initialize BOARD,AD,Oled, and ToneGeneration
    BOARD_Init();
    AD_Init();
    OledInit();
    ToneGeneration_Init();
    
    AD_AddPins(AD_A1 | AD_A2);
    
    //Initialize counter and holders
    averageCounter=0;
    past=0;
    timer=0;

    while(1){
        flexADC = AD_ReadADPin(AD_A1); //Read ADC voltage from flex sensor
        buffer[averageCounter%BUFFERLENGTH]=flexADC; //include lfex ADC into buffer
        
        /*Calculates the average*/
        sum=0;
        for(i=0;i<BUFFERLENGTH;i++){
            sum = buffer[i]+sum;
        }
        average = sum/BUFFERLENGTH;
        
        /*Filters out noise*/
        if(abs(average-past)<NOISETHRESHOLD){
            flexADC=past;
        }else{
            past=average;
        }
        
        /*Convert ADC reading from Flex into voltage and degrees*/
        flexVoltage=(flexADC*3.3)/1023;
        degrees=-39.9*(flexVoltage*flexVoltage)+55.3*flexVoltage+71.3;
        //frequency= pow(10,(degrees/30));
        
        /*Map degrees to a certain frequency*/
        frequency = (980/90)*degrees;
        if(frequency<0){
            frequency=0;
        }
       
        /*If Piezo is tapped above 600mv, then it turns on sound and plays for PLAYTIME*/
        piez=AD_ReadADPin(AD_A2); //Spike is usually about 600mv
        if(piez>PIEZOTHRESHOLD){
            ToneGeneration_ToneOn();
            ToneGeneration_SetFrequency(frequency);
            timer=0;
        }else if(timer>PLAYTIME){
            ToneGeneration_ToneOff();
        }
        /*Creates string with calculated values*/
        sprintf(string, "Voltage: %fV \nDegrees %f\nFrequency %dHz", flexVoltage,degrees,frequency);
        
        /*Prints String on Oled*/
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
        
        /*Increments timers*/
        timer++;
        averageCounter++;
        
    }
}
