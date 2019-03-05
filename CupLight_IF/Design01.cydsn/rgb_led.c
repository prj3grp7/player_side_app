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
#include "rgb_led.h"

void initRGBLED()
{
    //Init colors and brightness pwm
    PWM_RED_Start();
    PWM_GREEN_Start();
    PWM_BLUE_Start();
}


void setColor(color_t color)
{
    setRed(color.red);
    setGreen(color.green);
    setBlue(color.blue);
}

void setRed(uint8_t R)
{
    uint8_t red = R>=0 && R<=255 ? R : getRed(); //Bound Check
    PWM_RED_WriteCompare(red);
}

void setGreen(uint8_t G)
{
    uint8_t green = G>=0 && G<=255 ? G : getGreen(); //Bound Check
    PWM_GREEN_WriteCompare(green);
}

void setBlue(uint8_t B)
{
    uint8_t blue = B>=0 && B<=255 ? B : getBlue(); //Bound Check
    PWM_BLUE_WriteCompare(blue);
}

uint8_t getRed(void)
{
    return PWM_RED_ReadCompare();
}

uint8_t getGreen(void)
{
    return PWM_GREEN_ReadCompare();
}
uint8_t getBlue(void)
{
    return PWM_BLUE_ReadCompare();
}


/* [] END OF FILE */
