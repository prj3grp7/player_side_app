/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "CupLight_IF.h"

volatile uint8_t NUM_LEDS = (8*SHIFT_REGISTERS)/3;

void controlLight(uint8_t nr, color_t color)
{
    if (nr < NUMLEDS)
    {
        uint8_t shiftRegPos = 3*nr;
        setPin(shiftRegPos,color.Red);
        setPin(shiftRegPos+1,color.Green);
        setPin(shiftRegPos+2,color.Blue);
    }
}

void controlAllLights(color_t color)
{
    for (uint8_t i = 0; i < NUMLEDS; i++){
         controlLight(i,color);
    }
}

/* [] END OF FILE */
