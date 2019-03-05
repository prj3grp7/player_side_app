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

#include "ShiftRegPWM.h"

extern volatile uint8_t NUMLEDS;

//RGB color type
typedef struct color
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
}color_t;

//Control a specific light to a specific color
//@param nr: the light number to control
//@param color: the color to control the light to
void controlLight(uint8_t nr, color_t color);

//Control all lights to a specific color
//@param color: the color to control the light to
void controlAllLights(color_t color);

/* [] END OF FILE */
