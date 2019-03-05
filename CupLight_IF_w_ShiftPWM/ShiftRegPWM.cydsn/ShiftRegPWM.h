/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * OBS: INSPIRATION FROM https://github.com/Simsso/ShiftRegister-PWM-Library/
 * 
 * ========================================
*/
#include "project.h"

#define SHIFT_REGISTERS 2
#define RESOLUTION 255

extern volatile uint8_t time;
extern volatile uint8_t shiftRegData[RESOLUTION*SHIFT_REGISTERS];

//The interrupt service routine to create the PWM signal.

CY_ISR_PROTO(updater_handler);

//Initializes the Shift Register PWM generator
void initShiftRegPWM();

//Sets a pin on the shiftregister to a given PWM value
//@param pin: the pin to set the PWM value of
//@param value: the value of the PWM signal between 0 and @RESOLUTION
void setPin(uint8_t pin, uint8_t value);


//Initializes the Shift Register PWM generator
void update();

//Helper function of update to latch the shiftregister
void toggleLatchShiftReg();

/* [] END OF FILE */
