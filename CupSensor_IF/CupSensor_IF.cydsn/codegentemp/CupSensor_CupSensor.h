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
#if !defined(CupSensor_CUP_SESNOR_H)
#define CupSensor_CUP_SESNOR_H

void CupSensor_Start();
void CupSensor_statusCallback(void (*callback)(uint8_t));
void CupSensor_hitStatusCallback(void (*callback)(uint8_t));
uint8_t CupSensor_getStatus();
uint8_t CupSensor_getHitStatus();


#endif /* CupSensor_CUP_SESNOR_H */
/* [] END OF FILE */
