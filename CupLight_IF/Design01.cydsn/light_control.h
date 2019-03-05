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
#include "project.h"
#include "rgb_led.h"

#define LEDS_TO_CONTROL 8

static color_t rgb_leds[LEDS_TO_CONTROL];
static uint8_t ledToUpdate = 0;
CY_ISR_PROTO(led_updater_handler);

void initLedControl();
void updateLight();
void latchShiftReg();
void controlLight(uint8_t nr, color_t color);
void controlAllLights(color_t color);
void disableLights();
void enableLights();

/* [] END OF FILE */
