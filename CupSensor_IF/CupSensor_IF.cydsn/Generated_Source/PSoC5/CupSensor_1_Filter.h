/*******************************************************************************
* File Name: CupSensor_1_Filter.h
* Version 2.30
*
* Description:
*  This header file contains definitions associated with the FILT component.
*
* Note:
* 
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CupSensor_1_Filter_H) /* FILT Header File */
#define CupSensor_1_Filter_H

#include "cyfitter.h"
#include "CyLib.h"

extern uint8 CupSensor_1_Filter_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/
#define CupSensor_1_Filter_DA_RAM_SIZE_CUR        (0x200u)
#define CupSensor_1_Filter_DB_RAM_SIZE_CUR        (0x200u)
#define CupSensor_1_Filter_CSA_RAM_SIZE_CUR       (0x100u)
#define CupSensor_1_Filter_CSB_RAM_SIZE_CUR       (0x100u)
#define CupSensor_1_Filter_CFSM_RAM_SIZE_CUR      (0x100u)
#define CupSensor_1_Filter_ACU_RAM_SIZE_CUR       (0x40u)

#define CupSensor_1_Filter_BIQUAD_A_SIZE    (60u)
	
extern const uint8 CYCODE CupSensor_1_Filter_ChannelABiquadCoefficients[CupSensor_1_Filter_BIQUAD_A_SIZE];


/***************************************
*     Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct 
{
    uint8 enableState;
    uint8 cr;
    uint8 sr;
    uint8 sema;
    uint8 saveAcu[CupSensor_1_Filter_ACU_RAM_SIZE_CUR];
}   CupSensor_1_Filter_backupStruct;


/***************************************
* FILT component function prototypes.
****************************************/

void   CupSensor_1_Filter_Start(void) ;
void   CupSensor_1_Filter_Stop(void) ;
uint8 CupSensor_1_Filter_Read8(uint8 channel) ;
uint16 CupSensor_1_Filter_Read16(uint8 channel) ;
uint32 CupSensor_1_Filter_Read24(uint8 channel) ;
void CupSensor_1_Filter_Write8(uint8 channel, uint8 sample) ;
void CupSensor_1_Filter_Write16(uint8 channel, uint16 sample) ;
void CupSensor_1_Filter_Write24(uint8 channel, uint32 sample) ;
void CupSensor_1_Filter_Sleep(void) ;
void CupSensor_1_Filter_Wakeup(void) ;
void CupSensor_1_Filter_SaveConfig(void) ;
void CupSensor_1_Filter_RestoreConfig(void) ;
void CupSensor_1_Filter_Init(void) ;
void CupSensor_1_Filter_Enable(void) ;
void CupSensor_1_Filter_SetCoherency(uint8 channel, uint8 byteSelect) ;
void CupSensor_1_Filter_SetCoherencyEx(uint8 regSelect, uint8 key) ;
void CupSensor_1_Filter_SetDalign(uint8 regSelect, uint8 state) ;

/*****************************************
* FILT component API Constants.
******************************************/

/* Channel Definitions */
#define CupSensor_1_Filter_CHANNEL_A             (0u)
#define CupSensor_1_Filter_CHANNEL_B             (1u)

#define CupSensor_1_Filter_CHANNEL_A_INTR        (0x08u)
#define CupSensor_1_Filter_CHANNEL_B_INTR        (0x10u)

#define CupSensor_1_Filter_ALL_INTR              (0xf8u)

#define CupSensor_1_Filter_SIGN_BIT              ((uint32)0x00800000u)
#define CupSensor_1_Filter_SIGN_BYTE             ((uint32)0xFF000000u)

/* Component's enable/disable state */
#define CupSensor_1_Filter_ENABLED               (0x01u)
#define CupSensor_1_Filter_DISABLED              (0x00u)

/* SetCoherency API constants */
#define CupSensor_1_Filter_KEY_LOW               (0x00u)
#define CupSensor_1_Filter_KEY_MID               (0x01u)
#define CupSensor_1_Filter_KEY_HIGH              (0x02u)


/*******************************************************************************
* FILT component macros.
*******************************************************************************/

#define CupSensor_1_Filter_ClearInterruptSource() \
   (CupSensor_1_Filter_SR_REG = CupSensor_1_Filter_ALL_INTR )

#define CupSensor_1_Filter_IsInterruptChannelA() \
    (CupSensor_1_Filter_SR_REG & CupSensor_1_Filter_CHANNEL_A_INTR)

#define CupSensor_1_Filter_IsInterruptChannelB() \
    (CupSensor_1_Filter_SR_REG & CupSensor_1_Filter_CHANNEL_B_INTR)


/*******************************************************************************
* FILT component DFB registers.
*******************************************************************************/

/* DFB Status register */
#define CupSensor_1_Filter_SR_REG             (* (reg8 *) CupSensor_1_Filter_DFB__SR)
#define CupSensor_1_Filter_SR_PTR             (  (reg8 *) CupSensor_1_Filter_DFB__SR)

/* DFB Control register */
#define CupSensor_1_Filter_CR_REG             (* (reg8 *) CupSensor_1_Filter_DFB__CR)
#define CupSensor_1_Filter_CR_PTR             (  (reg8 *) CupSensor_1_Filter_DFB__CR)


/*******************************************************************************
* DFB.COHER bit field defines.
*******************************************************************************/

/* STAGEA key coherency mask */
#define CupSensor_1_Filter_STAGEA_COHER_MASK    (0x03u)
#define CupSensor_1_Filter_STAGEA_COHER         CupSensor_1_Filter_STAGEA_COHER_MASK

/* HOLDA key coherency mask */
#define CupSensor_1_Filter_HOLDA_COHER_MASK     ((uint8)((uint8)0x03u << 4u))
#define CupSensor_1_Filter_HOLDA_COHER          CupSensor_1_Filter_HOLDA_COHER_MASK

/* STAGEB key coherency mask */
#define CupSensor_1_Filter_STAGEB_COHER_MASK    (0x0Cu)
#define CupSensor_1_Filter_STAGEB_COHER         CupSensor_1_Filter_STAGEB_COHER_MASK

/* HOLDB key coherency mask */
#define CupSensor_1_Filter_HOLDB_COHER_MASK     ((uint8)((uint8)0x0Cu << 4u))
#define CupSensor_1_Filter_HOLDB_COHER          CupSensor_1_Filter_HOLDB_COHER_MASK


/*******************************************************************************
* DFB.DALIGN bit field defines.
*******************************************************************************/

/* STAGEA dalign mask */
#define CupSensor_1_Filter_STAGEA_DALIGN    (0x01u)

/* HOLDA dalign mask */
#define CupSensor_1_Filter_HOLDA_DALIGN     (0x04u)

/* STAGEB dalign mask */
#define CupSensor_1_Filter_STAGEB_DALIGN    (0x02u)

/* HOLDB dalign mask */
#define CupSensor_1_Filter_HOLDB_DALIGN     (0x08u)


#endif /* End FILT Header File */


/* [] END OF FILE */
