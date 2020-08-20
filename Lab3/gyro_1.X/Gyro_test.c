/*
 * File:   Gyro_test.c
 * Author: jumaayal
 *
 * Created on February 23, 2020, 9:52 PM
 */

#include <BOARD.h>
#include <Oled.h>
#include <math.h>
#include <stdio.h>
#include<timers.h>

#define TEN 10000
#define HOUR 3600000
#define FIFTYHZ 20

int main(void) {
    BOARD_Init();
    TIMERS_Init();
    if(MPU9250_Init()!=1){
        printf("fail");
    }
    printf("Begin");
    printf("X,Y,Z,Time\r\n");
    while(1){
        //while(TIMERS_GetMilliSeconds()<TEN){
//            printf("X: %d,Y: %d,Z: %d",MPU9250_ReadGyroX(),MPU9250_ReadGyroY(),MPU9250_ReadGyroZ());
//        }
//        printf(Hour)
        //while(TIMERS_GetMilliSeconds()<HOUR){
        if(TIMERS_GetMilliSeconds()%FIFTYHZ ==0){
           //printf("%d,%d,%d,%d\r\n",MPU9250_ReadGyroX(),MPU9250_ReadGyroY(),MPU9250_ReadGyroZ(),TIMERS_GetMilliSeconds());
            printf("X: %d,Y: %d,Z: %d\r\n",MPU9250_ReadGyroX(),MPU9250_ReadGyroY(),MPU9250_ReadGyroZ());
        }
    }
}
