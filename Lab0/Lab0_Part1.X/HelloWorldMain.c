/*
 * File:   HelloWorldMain.c
 * Author: jumaayal
 *
 * Created on January 7, 2020, 2:02 PM
 */
#include <BOARD.h>
#include <stdio.h>

int main(void) {
    BOARD_Init();

    printf("Hello World!");
    while (1) {
        ;
    }
}
