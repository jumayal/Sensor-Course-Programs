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
#define DELAYLENGTH 3750 //60ms
#define LISTENTIME 736 //11.7ms
#define HALFTIME 0.5
#define SPEEDOFSOUND 0.034 // centimeters per microseconds
#define SLOPE 0.988
#define YINT -6.16

enum pingState{
    delay,
    trigger,
    listen,
}STATE;
int startTime;
int listenTimer;
int delayTimer;

int  returnedTime;
char PING_Init(void) {
            // following block inits the timer
             T4CON = 0;
             T4CONbits.TCKPS = 0b110;
             PR4 = 0x000A; //Every 16us!
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
             delayTimer=0;
             listenTimer=0;
             TRISDbits.TRISD11=0; //Setting pin 35 as an output
             TRIGGER=0;
             STATE=delay;
           }

unsigned int PING_GetDistance(void){
    return SLOPE*HALFTIME*SPEEDOFSOUND*returnedTime+YINT;
}
unsigned int PING_GetTimeofFlight(void){
    return returnedTime;
}
void __ISR(_CHANGE_NOTICE_VECTOR) soundBack(void) {
    static char readPort = 0;
    readPort = PORTD; // this read is required to make the interrupt work
    IFS1bits.CNIF = 0; 
    returnedTime=TIMERS_GetMicroSeconds()-startTime;
    //Anything else that needs to occur goes here
}
void pingStateMachine(){
  switch (STATE){
      case delay:
          delayTimer++;

          if(delayTimer>DELAYLENGTH){
              STATE=trigger;
          }
          break;
      case trigger:
          startTime = TIMERS_GetMicroSeconds();
          TRIGGER=1;
          delayTimer=0;
          STATE=listen;
          break;
      case listen:
          TRIGGER=0;
          delayTimer++;
          listenTimer++;
          if(listenTimer>LISTENTIME){
              STATE=delay;
          }
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
