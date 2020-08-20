/*
 * File:   Measuring_AcceL_Mag.c
 * Author: jumaayal
 *
 * Created on February 25, 2020, 2:48 AM
 */


#include <BOARD.h>
#include <stdio.h>
#include <MPU9250.h>

#define FIFTYHZ 20
int main(void) {
    BOARD_Init();
    if(MPU9250_Init()!=1){
        printf("fail");
    }
    /*printf("%d\r\n",MPU9250_ReadAccelX());
    printf("%d\r\n",MPU9250_ReadAccelY());
    printf("%d\r\n",MPU9250_ReadAccelZ());
      */
    //printf("X: %d Y:%d Z: %d",MPU9250_ReadMagX(),MPU9250_ReadMagY(),MPU9250_ReadMagZ() );
    while(1){
        if(TIMERS_GetMilliSeconds()%FIFTYHZ ==0){
           printf("%d,%d,%d,%d,%d,%d\r\n",MPU9250_ReadAccelX(),MPU9250_ReadAccelY(),MPU9250_ReadAccelZ(),MPU9250_ReadMagX(),MPU9250_ReadMagY(),MPU9250_ReadMagZ());
        }
    }
}
