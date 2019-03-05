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

volatile uint8_t time = 0;
volatile uint8_t shiftRegData[RESOLUTION*SHIFT_REGISTERS] = {0};

void initShiftRegPWM()
{
    isr_update_leds_StartEx(updater_handler);
    SPIM_led_control_Start();
    Timer_led_updater_Start();
}

void setPin(uint8_t pin, uint8_t value)
{
    value = (uint8_t) (value / 255.0 * RESOLUTION); //Scale value
    uint8_t shiftRegister = pin / 8; //8 pins per shift register
    for (int t = 0; t < RESOLUTION; ++t)
    {
      // set (pin % 8)th bit to (value > t)
      shiftRegData[t + shiftRegister * RESOLUTION] ^= (-(value > t) ^ shiftRegData[t + shiftRegister * RESOLUTION]) & (1 << (pin % 8));
    }
}

CY_ISR(updater_handler)
{
    update();
}                   

void update()
{
    for (int i = SHIFT_REGISTERS - 1; i >= 0; i--)
    {
      SPIM_led_control_WriteTxData(shiftRegData[time + i * RESOLUTION]);
    }
    toggleLatchShiftReg();
    
    if (++time == RESOLUTION) {
      time = 0;
    }
    Timer_led_updater_ReadStatusRegister();
}

void toggleLatchShiftReg()
{
    Pin_latch_Write(0);
    Pin_latch_Write(1);
}
/* [] END OF FILE */
