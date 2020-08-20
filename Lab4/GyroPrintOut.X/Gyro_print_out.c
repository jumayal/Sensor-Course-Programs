/*
 * File:   Gyro_print_out.c
 * Author: Juan Ayala
 *
 * Created on March 13, 2020, 5:40 PM
 */


#include <BOARD.h>
#include <Oled.h>
#include <math.h>
#include <stdio.h>
#include <MPU9250.h>
#include<timers.h>

#define TEN 10000
#define HOUR 3600000
#define FIFTYHZ 20

int main(void) {
    BOARD_Init();
    TIMERS_Init();
    MPU9250_Init();
    printf("Begin");
    printf("X,Y,Z\r\n");
    while(1){
//        if(TIMERS_GetMilliSeconds()<TEN){
//            printf("%d,%d,%d\r\n",MPU9250_ReadGyroX(),MPU9250_ReadGyroY(),MPU9250_ReadGyroZ());
//        }
        //while(TIMERS_GetMilliSeconds()<HOUR){
            if(TIMERS_GetMilliSeconds()%FIFTYHZ ==0){
                printf("%d,%d,%d\r\n",MPU9250_ReadGyroX(),MPU9250_ReadGyroY(),MPU9250_ReadGyroZ());
            }
      //  }
    }
}
