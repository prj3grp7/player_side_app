/*******************************************************************************
* File Name: CupSensor_isr_DMA.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_CupSensor_isr_DMA_H)
#define CY_ISR_CupSensor_isr_DMA_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void CupSensor_isr_DMA_Start(void);
void CupSensor_isr_DMA_StartEx(cyisraddress address);
void CupSensor_isr_DMA_Stop(void);

CY_ISR_PROTO(CupSensor_isr_DMA_Interrupt);

void CupSensor_isr_DMA_SetVector(cyisraddress address);
cyisraddress CupSensor_isr_DMA_GetVector(void);

void CupSensor_isr_DMA_SetPriority(uint8 priority);
uint8 CupSensor_isr_DMA_GetPriority(void);

void CupSensor_isr_DMA_Enable(void);
uint8 CupSensor_isr_DMA_GetState(void);
void CupSensor_isr_DMA_Disable(void);

void CupSensor_isr_DMA_SetPending(void);
void CupSensor_isr_DMA_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the CupSensor_isr_DMA ISR. */
#define CupSensor_isr_DMA_INTC_VECTOR            ((reg32 *) CupSensor_isr_DMA__INTC_VECT)

/* Address of the CupSensor_isr_DMA ISR priority. */
#define CupSensor_isr_DMA_INTC_PRIOR             ((reg8 *) CupSensor_isr_DMA__INTC_PRIOR_REG)

/* Priority of the CupSensor_isr_DMA interrupt. */
#define CupSensor_isr_DMA_INTC_PRIOR_NUMBER      CupSensor_isr_DMA__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable CupSensor_isr_DMA interrupt. */
#define CupSensor_isr_DMA_INTC_SET_EN            ((reg32 *) CupSensor_isr_DMA__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the CupSensor_isr_DMA interrupt. */
#define CupSensor_isr_DMA_INTC_CLR_EN            ((reg32 *) CupSensor_isr_DMA__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the CupSensor_isr_DMA interrupt state to pending. */
#define CupSensor_isr_DMA_INTC_SET_PD            ((reg32 *) CupSensor_isr_DMA__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the CupSensor_isr_DMA interrupt. */
#define CupSensor_isr_DMA_INTC_CLR_PD            ((reg32 *) CupSensor_isr_DMA__INTC_CLR_PD_REG)


#endif /* CY_ISR_CupSensor_isr_DMA_H */


/* [] END OF FILE */
