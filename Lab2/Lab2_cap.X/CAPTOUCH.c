/*
 * File:   CAPTOUCH.c
 * Author: jumaayal
 *
 * Created on February 7, 2020, 7:26 AM
 */


#include "xc.h"
#include <CAPTOUCH.h>
#include <stdio.h>
#define BUFFERLENGTH 20
#define TOUCHTHRESHOLD 800
#define SECPTICK 0.0000002

enum SquareWave{
    STATE_1,
    STATE_2,
}STATE;

int frequency;
int average;
int counter;
int  buffer[BUFFERLENGTH]={0};
double Period;
double startTime;
double endTime;
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
  STATE=STATE_1;
  counter=0;
  average=0;
 //lastSampled=1;

}


char CAPTOUCH_IsTouched(void){
    if(average<TOUCHTHRESHOLD){
        return TRUE;
    }
    return FALSE;
}
int returnF(void){
    return average;
}

void capStateMachine(){
    switch(STATE){
        case STATE_1:

            startTime=IC4BUF;  
            STATE=STATE_2;
            break;
        case STATE_2:
            endTime=IC4BUF;
            Period=(endTime-startTime)*SECPTICK;
            if(Period<0){
                STATE=STATE_1;
                startTime=endTime;
                break;
            }
            frequency=1/(Period);
            movingAverage(frequency,BUFFERLENGTH,&buffer,&counter,&average);
            STATE=STATE_1;
            startTime=endTime;
            break;
        default:
            printf("Error In State");
    }
}

void __ISR(_INPUT_CAPTURE_4_VECTOR) InputCapture_Handler(void)
{
    IFS0bits.IC4IF = 0;
    // IC4BUF contains the timer value when the rising edge occurred.
    capStateMachine();
}

int movingAverage(int value,int bufferlength,int *bufferArray, int *count,int *mean){
    bufferArray[(*count)%bufferlength]=value/bufferlength;
    *mean=*mean+(value/bufferlength)- bufferArray[((*count)+1)%bufferlength];
    //*mean=bufferArray[(*count)%bufferlength];
    *count=*count+1;
}