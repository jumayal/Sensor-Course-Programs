/*
 * Setup
 * Connect pin36 to pin A of encoder
 * Connect pin 37 to pin B of encoder
 * Connect pin 3 to red
 * connect pin 5 to green
 * connect pin 6 to blue
 */


#include "xc.h"
#include <BOARD.h>
#include <Oled.h>
#include <stdio.h>
#include <QEI.h>
#include <pwm.h>

#define DUTYCYCLECHANGE 8.3
int position;
char string [30];
int redDuty,grnDuty,blueDuty;
int relativeDegree;
int main(void) {
    BOARD_Init();
    OledInit();
    PWM_Init();
    QEI_Init();
    PWM_AddPins(PWM_PORTZ06|PWM_PORTY12|PWM_PORTY10);
    redDuty=0;
    grnDuty=0;
    blueDuty=1000;
    position =0;
    printf("\nBegin\n");
    while(1){
        position=QEI_GetPosition();
        if(position>0){
            relativeDegree=position%360;
            if(relativeDegree<=120){
                blueDuty=1000-(DUTYCYCLECHANGE*relativeDegree);
                grnDuty=(DUTYCYCLECHANGE*relativeDegree);
                redDuty=0;
            }else if(relativeDegree<=240) {
                blueDuty=0;
                grnDuty=1000- (DUTYCYCLECHANGE*(relativeDegree-120));
                redDuty=(DUTYCYCLECHANGE*(relativeDegree-120));
            }else if(relativeDegree<=360){
                blueDuty=(DUTYCYCLECHANGE*(relativeDegree-240));
                grnDuty=0;
                redDuty=1000-(DUTYCYCLECHANGE*(relativeDegree-240));
            }
        }else{
            relativeDegree=(-1*position)%360;
            if(relativeDegree<=120){
                blueDuty=1000-(DUTYCYCLECHANGE*relativeDegree);
                redDuty=(DUTYCYCLECHANGE*relativeDegree);
                grnDuty=0;
            }else if(relativeDegree<=240){
                blueDuty=0;
                redDuty=1000-(DUTYCYCLECHANGE*(relativeDegree-120));
                grnDuty=(DUTYCYCLECHANGE*(relativeDegree-120));
            }else if(relativeDegree<=360){
                blueDuty=(DUTYCYCLECHANGE*(relativeDegree-240));
                redDuty=0;
                grnDuty=1000-(DUTYCYCLECHANGE*(relativeDegree-240));
            }
        }
        
        PWM_SetDutyCycle(PWM_PORTZ06, 1000-redDuty);
        PWM_SetDutyCycle(PWM_PORTY12, 1000-grnDuty);
        PWM_SetDutyCycle(PWM_PORTY10, 1000-blueDuty);
        sprintf(string, "\nDegrees:%d\nBlue: %d Red: %d\nGreen: %d\n ", position, blueDuty, redDuty, grnDuty);
        /*Prints String on Oled*/
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
    }
}
