/*
 * File:   Tones.c
 * Author: jumaayal
 *
 * Created on January 7, 2020, 5:32 PM
 */

#include <Board.h>
#include<ToneGeneration.h>
#include "xc.h"

int main(void) {
    BOARD_Init();
    ToneGeneration_Init();
    ToneGeneration_SetFrequency(440);
    ToneGeneration_ToneOn();
}
