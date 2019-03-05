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
#ifndef _RPI_IF
#define _RPI_IF

#include "project.h"
#include "GameController.h"


void RPI_IF_init();


void sendCupStatus(uint8_t status);
void resetReadBuffer();
void timer_update(int value);
void RPi_IF_handleData();

#endif

/* [] END OF FILE */
