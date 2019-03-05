/*******************************************************************************
* File Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1.h
* Version 2.10
*
* Description:
*  Contains the function prototypes, constants and register definition of the
*  ADC SAR Sequencer Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_``$INSTANCE_NAME`_ADC_SAR_Seq_1_H)
    #define CY_``$INSTANCE_NAME`_ADC_SAR_Seq_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"
#include "``$INSTANCE_NAME`_ADC_SAR_Seq_1_TempBuf_dma.h"
#include "``$INSTANCE_NAME`_ADC_SAR_Seq_1_FinalBuf_dma.h"
#include "``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR.h"

#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_NUMBER_OF_CHANNELS    (4u)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAMPLE_MODE           (0u)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_SOURCE          (0u)

extern int16  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_finalArray[``$INSTANCE_NAME`_ADC_SAR_Seq_1_NUMBER_OF_CHANNELS];
extern uint32 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_initVar;

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component ADC_SAR_SEQ_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*        Function Prototypes
***************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_Init(void);
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_Enable(void);
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_Disable(void);
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_Start(void);
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_Stop(void);

uint32 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_IsEndConversion(uint8 retMode);
int16 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_GetResult16(uint16 chan);
int16 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_GetAdcResult(void);
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SetOffset(int32 offset);
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SetResolution(uint8 resolution);
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SetScaledGain(int32 adcGain);
int32 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CountsTo_mVolts(int16 adcCounts);
int32 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CountsTo_uVolts(int16 adcCounts);
float32 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CountsTo_Volts(int16 adcCounts);
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_Sleep(void);
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_Wakeup(void);
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SaveConfig(void);
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_RestoreConfig(void);

CY_ISR_PROTO( ``$INSTANCE_NAME`_ADC_SAR_Seq_1_ISR );

/* Obsolete API for backward compatibility.
*  Should not be used in new designs.
*/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SetGain(int32 adcGain);


/**************************************
*    Initial Parameter Constants
**************************************/
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_IRQ_REMOVE             (0u)                /* Removes internal interrupt */


/***************************************
*             Registers
***************************************/
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CYCLE_COUNTER_AUX_CONTROL_REG \
                                               (*(reg8 *) ``$INSTANCE_NAME`_ADC_SAR_Seq_1_bSAR_SEQ_ChannelCounter__CONTROL_AUX_CTL_REG)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CYCLE_COUNTER_AUX_CONTROL_PTR \
                                               ( (reg8 *) ``$INSTANCE_NAME`_ADC_SAR_Seq_1_bSAR_SEQ_ChannelCounter__CONTROL_AUX_CTL_REG)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CONTROL_REG    (*(reg8 *) \
                                             ``$INSTANCE_NAME`_ADC_SAR_Seq_1_bSAR_SEQ_CtrlReg__CONTROL_REG)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CONTROL_PTR    ( (reg8 *) \
                                             ``$INSTANCE_NAME`_ADC_SAR_Seq_1_bSAR_SEQ_CtrlReg__CONTROL_REG)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_COUNT_REG      (*(reg8 *) \
                                             ``$INSTANCE_NAME`_ADC_SAR_Seq_1_bSAR_SEQ_ChannelCounter__COUNT_REG)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_COUNT_PTR      ( (reg8 *) \
                                             ``$INSTANCE_NAME`_ADC_SAR_Seq_1_bSAR_SEQ_ChannelCounter__COUNT_REG)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_STATUS_REG     (*(reg8 *) ``$INSTANCE_NAME`_ADC_SAR_Seq_1_bSAR_SEQ_EOCSts__STATUS_REG)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_STATUS_PTR     ( (reg8 *) ``$INSTANCE_NAME`_ADC_SAR_Seq_1_bSAR_SEQ_EOCSts__STATUS_REG)

#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DATA_ADDR_0 (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ADC_SAR__WRK0)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DATA_ADDR_1 (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ADC_SAR__WRK1)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DATA_ADDR_0_REG (*(reg8 *) \
                                              ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ADC_SAR__WRK0)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DATA_ADDR_1_REG (*(reg8 *) \
                                              ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ADC_SAR__WRK1)


/**************************************
*       Register Constants
**************************************/

#if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_IRQ_REMOVE == 0u)

    /* Priority of the ADC_SAR_IRQ interrupt. */
    #define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_INTC_PRIOR_NUMBER          (uint8)(``$INSTANCE_NAME`_ADC_SAR_Seq_1_IRQ__INTC_PRIOR_NUM)

    /* ADC_SAR_IRQ interrupt number */
    #define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_INTC_NUMBER                (uint8)(``$INSTANCE_NAME`_ADC_SAR_Seq_1_IRQ__INTC_NUMBER)

#endif   /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_IRQ_REMOVE */


/***************************************
*       API Constants
***************************************/

/* Constants for IsEndConversion() "retMode" parameter */
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_RETURN_STATUS              (0x01u)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_WAIT_FOR_RESULT            (0x00u)

/* Defines for the Resolution parameter */
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_BITS_12    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__BITS_12
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_BITS_10    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__BITS_10
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_BITS_8     ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__BITS_8

#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CYCLE_COUNTER_ENABLE    (0x20u)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_BASE_COMPONENT_ENABLE   (0x01u)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_LOAD_COUNTER_PERIOD     (0x02u)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SOFTWARE_SOC_PULSE      (0x04u)

/* Generic DMA Configuration parameters */
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_TEMP_BYTES_PER_BURST     (uint8)(2u)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_TEMP_TRANSFER_COUNT      ((uint16)``$INSTANCE_NAME`_ADC_SAR_Seq_1_NUMBER_OF_CHANNELS << 1u)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_FINAL_BYTES_PER_BURST    ((uint16)``$INSTANCE_NAME`_ADC_SAR_Seq_1_NUMBER_OF_CHANNELS << 1u)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_REQUEST_PER_BURST        (uint8)(1u)

#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_GET_RESULT_INDEX_OFFSET    ((uint8)``$INSTANCE_NAME`_ADC_SAR_Seq_1_NUMBER_OF_CHANNELS - 1u)

/* Define for Sample Mode  */
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAMPLE_MODE_FREE_RUNNING    (0x00u)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAMPLE_MODE_SW_TRIGGERED    (0x01u)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAMPLE_MODE_HW_TRIGGERED    (0x02u)

/* Define for Clock Source  */
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_INTERNAL              (0x00u)
#define ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_EXTERNAL              (0x01u)


/***************************************
*        Optional Function Prototypes
***************************************/
#if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAMPLE_MODE != ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAMPLE_MODE_HW_TRIGGERED)
    void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_StartConvert(void);
    void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_StopConvert(void);
#endif /* ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAMPLE_MODE != ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAMPLE_MODE_HW_TRIGGERED */

#endif  /* !defined(CY_``$INSTANCE_NAME`_ADC_SAR_Seq_1_H) */

/* [] END OF FILE */
