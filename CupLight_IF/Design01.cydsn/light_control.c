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
#include "light_control.h"


void initLedControl()
{
    isr_update_leds_StartEx(led_updater_handler );
    initRGBLED();
    color_t white = {255,255,255};
    controlAllLights(white);
    SPIM_led_control_Start();
    Timer_led_updater_Start();
}

CY_ISR(led_updater_handler)
{
    updateLight();
}

void updateLight()
{
    SPIM_led_control_WriteTxData(~(1<<ledToUpdate)); //OBS CHANGE IF TRANSISTORS ARE USED
    disableLights(); //Disable lights while updating output
    setColor(rgb_leds[ledToUpdate]); //Update color
    latchShiftReg();
    enableLights();
    if(ledToUpdate++ == LEDS_TO_CONTROL)
    {
        ledToUpdate = 0;
    }
}

void latchShiftReg()
{
    Pin_latch_Write(0);
    Pin_latch_Write(1);
    Pin_latch_Write(0);
}

void disableLights()
{
    Pin_output_enable_Write(1);
}

void enableLights()
{
    Pin_output_enable_Write(0);
}

void controlLight(uint8_t nr, color_t color)
{
    if (nr >= 0 && nr < LEDS_TO_CONTROL)
    {
        rgb_leds[nr] = color;
    }
}

void controlAllLights(color_t color)
{
    for (uint8_t i = 0; i < LEDS_TO_CONTROL; i++){
         controlLight(i,color);
    }
}
/* [] END OF FILE */
