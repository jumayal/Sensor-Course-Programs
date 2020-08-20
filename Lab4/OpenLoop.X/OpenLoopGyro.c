/*
 * File:   OpenLoopGyro.c
 * Author: jumaayal
 *
 * Created on March 13, 2020, 9:34 PM
 */

#include <BOARD.h>
#include <Oled.h>
#include <stdio.h>
#include <MPU9250.h>
#include <Matrix_AnglesRotation_utils.h>
#include<timers.h>
#define FIFTYHZ 20
#define TEN 10000
char string [30];
int main(void) {
    BOARD_Init();
    TIMERS_Init();
    OledInit();
    MPU9250_Init();
    printf("begin");
    printf("\n\r");
    float bias[3]={67.5572,57.5043,-287.1544};
    float R[3][3]={{1,0,0},{0,1,0},{0,0,1}}; 
    float w[3]={0};
    float angles[3]={0};
    float buffer[3][3] = {0};
    float buffer_two[3][3]={0};
    int input1;
    int input2;
    int input3;
    while(1){
        input1=MPU9250_ReadGyroX();
        input2=MPU9250_ReadGyroY();
        input3=MPU9250_ReadGyroZ();
        w[0]= degrees2radian((input1-bias[0]));
        w[1]=degrees2radian((input2-bias[1]));
        w[2]=degrees2radian((input3-bias[2]));
//        w[0]= degrees2radian((MPU9250_ReadGyroX()-bias[0]));
//        w[1]=degrees2radian((MPU9250_ReadGyroY()-bias[1]));
//        w[2]=degrees2radian((MPU9250_ReadGyroZ()-bias[2]));
        printf("R:");
        printMatrix((float*)R,3,3);
        printf("W:");
        printMatrix((float*)w,1,3);
        int_exp(R,w,(float)1/50,buffer);
        printMatrix((float*)buffer,3,3);
        multiplyMatrix3x3(R,buffer,buffer_two);
        copyMatrixR(buffer_two,R);
        printf("R+:");
        printMatrix((float*)R,3,3);
        findAngles(R,angles);
        printf("%f,%f,%f\r\n",angles[0],angles[1],angles[2]);
        //printMatrix(angles,1,3);
//        if(TIMERS_GetMilliSeconds()%FIFTYHZ ==0 && TIMERS_GetMilliSeconds()<TEN){
//            printf("%d,%d,%d,%f,%f,%f\r\n",input1,input2,input3,angles[0],angles[1],angles[2]);
//        }
        sprintf(string,"x:%0.2f\ny:%0.2f\nz:%0.2f", radian2degrees(angles[0]),radian2degrees(angles[1]),radian2degrees(angles[3]));  
        OledDrawString(string);
        OledUpdate();
        OledClear(OLED_COLOR_BLACK);
        while(BTN1!=1);
    }
}
