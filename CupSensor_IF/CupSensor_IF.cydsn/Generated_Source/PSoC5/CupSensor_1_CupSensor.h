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
#if !defined(CupSensor_1_CUP_SESNOR_H)
#define CupSensor_1_CUP_SESNOR_H

void CupSensor_1_Start();
void CupSensor_1_statusCallback(void (*callback)(uint8_t));
void CupSensor_1_hitStatusCallback(void (*callback)(uint8_t));
uint8_t CupSensor_1_getStatus();
uint8_t CupSensor_1_getHitStatus();


#endif /* CupSensor_1_CUP_SESNOR_H */
/* [] END OF FILE */
