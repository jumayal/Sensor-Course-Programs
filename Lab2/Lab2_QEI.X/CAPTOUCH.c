/*
 * File:   CAPTOUCH.c
 * Author: jumaayal
 *
 * Created on February 7, 2020, 7:26 AM
 */


#include "xc.h"
#include <CAPTOUCH.h>

#define BUFFERLENGTH 20
#define TOUCHTHRESHOLD 300000

int frequency;
int average;
int counter;
int lastSampled;
int halfPeriod;
int startTime;
int endTime;
int buffer[BUFFERLENGTH];
char CAPTOUCH_Init(void)
{
// following block inits the timer
  T2CON = 0;
  T2CONbits.TCKPS = 0b011;
  PR2 = 0xFFFF;
  T2CONbits.ON = 1;

  //this block inits input capture
  IC4CON = 0;
  IC4CONbits.ICTMR = 1;
  IC4CONbits.ICM = 0b010;

  IFS0bits.IC4IF = 0;
  IPC4bits.IC4IP = 7;
  IEC0bits.IC4IE = 1;
  IC4CONbits.ON = 1;
  // whatever else you need to do to initialize your module
  TIMERS_Init();
  startTime= TIMERS_GetMicroSeconds();
  lastSampled=BUFFERLENGTH-1;

}

void __ISR(_INPUT_CAPTURE_4_VECTOR) InputCapture_Handler(void)
{
    IFS0bits.IC4IF = 0;
    // IC4BUF contains the timer value when the rising edge occurred.
    endTime=TIMERS_GetMicroSeconds();
    halfPeriod=endTime-startTime;
    frequency=1/(halfPeriod*2);

    buffer[counter%BUFFERLENGTH]=frequency/2;
    average=average+(frequency/2)- buffer[lastSampled];
    lastSampled= (lastSampled+1)%BUFFERLENGTH;
    counter++;
}

char CAPTOUCH_IsTouched(void){
    if(average<TOUCHTHRESHOLD){
        return TRUE;
    }
    return FALSE;
}