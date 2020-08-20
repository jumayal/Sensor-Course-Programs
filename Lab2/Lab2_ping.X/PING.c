/*
 * File:   PING.c
 * Author: jumaayal
 *
 * Created on February 6, 2020, 11:35 PM
 */


#include "xc.h"
#include <PING.h>
#include <timers.h>
#include <stdio.h>

#define TRIGGER PORTDbits.RD11 //pin 35
#define ECHO PORTDbits.RD5 //pin 34
#define DELAYTIME 0x927C //37500 //60ms
#define LISTENTIME 0x927C //7360 //11.7ms
#define TRIGGERTIME 0x000A //10 //16us
#define HALFTIME 0.5
#define SPEEDOFSOUND 0.034 // centimeters per microseconds
#define SLOPE 0.988
#define YINT -6.16

//For moving average
#define BUFFERLENGTH 20
enum pingState{
    trigger,
    listen,
}STATE;

//For moving Average
int average;
int counter;
int  buffer[BUFFERLENGTH]={0};
//

int startTime;

int  returnedTime;
char PING_Init(void) {
            // following block inits the timer
             T4CON = 0;
             T4CONbits.TCKPS = 0b110;
             PR4 = TRIGGERTIME; //Every 16us!
             T4CONbits.ON = 1;
             IFS0bits.T4IF = 0;
             IPC4bits.T4IP = 3;
             IEC0bits.T4IE = 1;
  
             // following block inits change notify
             CNCONbits.ON = 1; // Change Notify On
             CNENbits.CNEN14 = 1;
             int temp = PORTD; // this is intentional to ensure a interrupt occur immediately upon enabling
             IFS1bits.CNIF = 0; // clear interrupt flag
             IPC6bits.CNIP = 1; //set priority
             IPC6bits.CNIS = 3; // and sub priority
             IEC1bits.CNIE = 1; // enable change notify
               //Anything else that needs to occur goes here
             
            TIMERS_Init();
             TRISDbits.TRISD11=0; //Setting pin 35 as an output
             TRIGGER=1;
             STATE=listen;
             //For moving average
             counter=0;
             average=0;
           }

unsigned int PING_GetDistance(void){
    return SLOPE*HALFTIME*SPEEDOFSOUND*average+YINT;
}
unsigned int PING_GetTimeofFlight(void){
    return returnedTime;
}
void __ISR(_CHANGE_NOTICE_VECTOR) soundBack(void) {
    static char readPort = 0;
    readPort = PORTD; // this read is required to make the interrupt work
    IFS1bits.CNIF = 0; 
    if(ECHO!=0){
        startTime=TIMERS_GetMicroSeconds();
        printf("Set startTime");
    }else{
         returnedTime=TIMERS_GetMicroSeconds()-startTime;
        movingAverage(returnedTime,BUFFERLENGTH,&buffer,&counter,&average);
            //STATE=trigger;
        printf("Sound back: %d \n", returnedTime);
    }
       //PR4 = DELAYTIME;
}
void pingStateMachine(){
  switch (STATE){
      case trigger:
          //printf("Entering Trigger: %d\n",TIMERS_GetMicroSeconds());
          TRIGGER=1;
          STATE=listen;
          //startTime=TIMERS_GetMicroSeconds();
          PR4 = TRIGGERTIME;
          break;
      case listen:
          //printf("Entering Listen: %d\n",TIMERS_GetMicroSeconds());
            TRIGGER=0;
            PR4 = DELAYTIME;
            STATE=trigger;
          break;
      default:
          printf("Error in state");
  }
}
void __ISR(_TIMER_4_VECTOR) Timer4IntHandler(void) {
    IFS0bits.T4IF = 0;
    //Anything else that needs to occur goes here
    pingStateMachine();
}

int movingAverage(int value,int bufferlength,int *bufferArray, int *count,int *mean){
    if(value<0){
        return;
    }
    bufferArray[(*count)%bufferlength]=value/bufferlength;
    *mean=*mean+(value/bufferlength)- bufferArray[((*count)+1)%bufferlength];
    *count=*count+1;
}