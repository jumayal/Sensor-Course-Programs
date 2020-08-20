/*
 * File:   QEI.c
 * Author: jumaayal
 *
 * Created on February 6, 2020, 1:09 PM
 */


#include "xc.h"
#include <QEI.h>
#include <stdio.h>

#define PHASEA PORTDbits.RD6 //Pin 36
#define PHASEB PORTDbits.RD7 //pin 37
#define DEGREEPERTURN 3.75

enum turn{
    init,
    CW,
    CCW
}direction;

enum phaseBits{ //A B
    zero,   //0 0
    one,    //0 1
    two,    //1 0
    three,   //1 1
    skip
};

int AB;
int degrees;
int A;
int B;
enum phaseBits state;

char QEI_Init(void) {
      // INIT Change notify
      CNCONbits.ON = 1; // Change Notify On
      CNENbits.CNEN15 = 1; //enable one phase
      CNENbits.CNEN16 = 1; //enable other phase
      int temp = PORTD; // this is intentional to ensure a interrupt occur immediately upon enabling
      IFS1bits.CNIF = 0; // clear interrupt flag
      IPC6bits.CNIP = 1; //set priority
      IPC6bits.CNIS = 3; // and sub priority
      IEC1bits.CNIE = 1; // enable change notify
      
      degrees=0;
      //Initialize State
      AB= PHASEA*2+PHASEB;
      switch(AB){
          case 0:
              state=zero;
              break;
          case 1:
              state=one;
              break;
          case 2:
              state=two;
              break;
          case 3:
              state=three;
              break;
      }
      
      //initialize direction
      direction=init;
  }
void __ISR(_CHANGE_NOTICE_VECTOR) changeInPhase(void) {
        static char readPort = 0;
        readPort = PORTD; // this read is required to make the interrupt work
        IFS1bits.CNIF = 0;
       //anything else that needs to happen goes here
        A=PHASEA;
        B=PHASEB;
       stateMachine();
  }

int QEI_GetPosition(void){
    return degrees;
}

void QEI_ResetPosition(){
    degrees=0;
    state=zero;
}

void stateMachine(){
    switch(state){
        case zero:
              if(A & !B){   //If phase A changes it is moving left else Phase B changed
                  direction=CCW;
                  degrees-= DEGREEPERTURN;
                  state=two;
              }else if(!A & B){
                  direction=CW;
                  degrees+= DEGREEPERTURN;
                  state=one;
              }else if (A & B){
                  state=skip;
              }
              break;
        case one:
              if(A & B){   //If phase A changes it is moving right else Phase B changed
                  direction=CW;
                  degrees+= DEGREEPERTURN;
                  state=three;
              }else if (!A & !B){
                  direction=CCW;
                  degrees-= DEGREEPERTURN;
                  state=zero;
              }else if(!A&B){
                  state =skip;
              }
              break;
        case two:
              if(A & B){   //If phase A is constant it is moving left else phase A changes going right
                  direction=CCW;
                  degrees-= DEGREEPERTURN;
                  state=three;
              }else if ( !A & !B){
                  direction=CW;
                  degrees+= DEGREEPERTURN;
                  state=zero;
              }else if(!A & B){
                  state = skip;
              }
              break;
        case three:
              if(A & !B){   //If phase A is constant it is moving right  else phase A changes going left
                  direction=CW;
                  degrees+= DEGREEPERTURN;
                  state=two;
              }else if(!A & B){
                  direction=CCW;
                  degrees-= DEGREEPERTURN;
                  state=one;
              }else if (!A&!B) {
                  state=skip;
              }
              break;
        case skip:
            state=PHASEA*2+PHASEB;
            break;
        default:
            printf("Error in State");
              
    }
}