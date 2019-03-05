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
#if !defined(`$INSTANCE_NAME`_CUP_SESNOR_H)
#define `$INSTANCE_NAME`_CUP_SESNOR_H

void `$INSTANCE_NAME`_Start();
void `$INSTANCE_NAME`_statusCallback(void (*callback)(uint8_t));
void `$INSTANCE_NAME`_hitStatusCallback(void (*callback)(uint8_t));
uint8_t `$INSTANCE_NAME`_getStatus();
uint8_t `$INSTANCE_NAME`_getHitStatus();


#endif /* `$INSTANCE_NAME`_CUP_SESNOR_H */
/* [] END OF FILE */
