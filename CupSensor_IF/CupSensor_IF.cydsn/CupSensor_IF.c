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

#include "CupSensor_IF.h"

extern void updateCupStatus(uint8_t status);
extern void updateHitStatus(uint8_t status);

void CupSensor_IF_init()
{
    CupSensor_Start();
    CupSensor_statusCallback(&updateCupStatus);
    CupSensor_hitStatusCallback(&updateHitStatus);    
}

uint8_t getStatus()
{
    return CupSensor_getStatus();
}

uint8_t getHitStatus()
{
    return CupSensor_getHitStatus();
}

/* [] END OF FILE */
