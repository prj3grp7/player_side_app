/*******************************************************************************
* File Name: ``$INSTANCE_NAME`_Filter_1.h
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

#if !defined(``$INSTANCE_NAME`_Filter_1_H) /* FILT Header File */
#define ``$INSTANCE_NAME`_Filter_1_H

#include "cyfitter.h"
#include "CyLib.h"

extern uint8 ``$INSTANCE_NAME`_Filter_1_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/
#define ``$INSTANCE_NAME`_Filter_1_DA_RAM_SIZE_CUR        (0x200u)
#define ``$INSTANCE_NAME`_Filter_1_DB_RAM_SIZE_CUR        (0x200u)
#define ``$INSTANCE_NAME`_Filter_1_CSA_RAM_SIZE_CUR       (0x100u)
#define ``$INSTANCE_NAME`_Filter_1_CSB_RAM_SIZE_CUR       (0x100u)
#define ``$INSTANCE_NAME`_Filter_1_CFSM_RAM_SIZE_CUR      (0x100u)
#define ``$INSTANCE_NAME`_Filter_1_ACU_RAM_SIZE_CUR       (0x40u)

#define ``$INSTANCE_NAME`_Filter_1_BIQUAD_A_SIZE    (20u)
	
extern const uint8 CYCODE ``$INSTANCE_NAME`_Filter_1_ChannelABiquadCoefficients[``$INSTANCE_NAME`_Filter_1_BIQUAD_A_SIZE];


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
    uint8 saveAcu[``$INSTANCE_NAME`_Filter_1_ACU_RAM_SIZE_CUR];
}   ``$INSTANCE_NAME`_Filter_1_backupStruct;


/***************************************
* FILT component function prototypes.
****************************************/

void   ``$INSTANCE_NAME`_Filter_1_Start(void) ;
void   ``$INSTANCE_NAME`_Filter_1_Stop(void) ;
uint8 ``$INSTANCE_NAME`_Filter_1_Read8(uint8 channel) ;
uint16 ``$INSTANCE_NAME`_Filter_1_Read16(uint8 channel) ;
uint32 ``$INSTANCE_NAME`_Filter_1_Read24(uint8 channel) ;
void ``$INSTANCE_NAME`_Filter_1_Write8(uint8 channel, uint8 sample) ;
void ``$INSTANCE_NAME`_Filter_1_Write16(uint8 channel, uint16 sample) ;
void ``$INSTANCE_NAME`_Filter_1_Write24(uint8 channel, uint32 sample) ;
void ``$INSTANCE_NAME`_Filter_1_Sleep(void) ;
void ``$INSTANCE_NAME`_Filter_1_Wakeup(void) ;
void ``$INSTANCE_NAME`_Filter_1_SaveConfig(void) ;
void ``$INSTANCE_NAME`_Filter_1_RestoreConfig(void) ;
void ``$INSTANCE_NAME`_Filter_1_Init(void) ;
void ``$INSTANCE_NAME`_Filter_1_Enable(void) ;
void ``$INSTANCE_NAME`_Filter_1_SetCoherency(uint8 channel, uint8 byteSelect) ;
void ``$INSTANCE_NAME`_Filter_1_SetCoherencyEx(uint8 regSelect, uint8 key) ;
void ``$INSTANCE_NAME`_Filter_1_SetDalign(uint8 regSelect, uint8 state) ;

/*****************************************
* FILT component API Constants.
******************************************/

/* Channel Definitions */
#define ``$INSTANCE_NAME`_Filter_1_CHANNEL_A             (0u)
#define ``$INSTANCE_NAME`_Filter_1_CHANNEL_B             (1u)

#define ``$INSTANCE_NAME`_Filter_1_CHANNEL_A_INTR        (0x08u)
#define ``$INSTANCE_NAME`_Filter_1_CHANNEL_B_INTR        (0x10u)

#define ``$INSTANCE_NAME`_Filter_1_ALL_INTR              (0xf8u)

#define ``$INSTANCE_NAME`_Filter_1_SIGN_BIT              ((uint32)0x00800000u)
#define ``$INSTANCE_NAME`_Filter_1_SIGN_BYTE             ((uint32)0xFF000000u)

/* Component's enable/disable state */
#define ``$INSTANCE_NAME`_Filter_1_ENABLED               (0x01u)
#define ``$INSTANCE_NAME`_Filter_1_DISABLED              (0x00u)

/* SetCoherency API constants */
#define ``$INSTANCE_NAME`_Filter_1_KEY_LOW               (0x00u)
#define ``$INSTANCE_NAME`_Filter_1_KEY_MID               (0x01u)
#define ``$INSTANCE_NAME`_Filter_1_KEY_HIGH              (0x02u)


/*******************************************************************************
* FILT component macros.
*******************************************************************************/

#define ``$INSTANCE_NAME`_Filter_1_ClearInterruptSource() \
   (``$INSTANCE_NAME`_Filter_1_SR_REG = ``$INSTANCE_NAME`_Filter_1_ALL_INTR )

#define ``$INSTANCE_NAME`_Filter_1_IsInterruptChannelA() \
    (``$INSTANCE_NAME`_Filter_1_SR_REG & ``$INSTANCE_NAME`_Filter_1_CHANNEL_A_INTR)

#define ``$INSTANCE_NAME`_Filter_1_IsInterruptChannelB() \
    (``$INSTANCE_NAME`_Filter_1_SR_REG & ``$INSTANCE_NAME`_Filter_1_CHANNEL_B_INTR)


/*******************************************************************************
* FILT component DFB registers.
*******************************************************************************/

/* DFB Status register */
#define ``$INSTANCE_NAME`_Filter_1_SR_REG             (* (reg8 *) ``$INSTANCE_NAME`_Filter_1_DFB__SR)
#define ``$INSTANCE_NAME`_Filter_1_SR_PTR             (  (reg8 *) ``$INSTANCE_NAME`_Filter_1_DFB__SR)

/* DFB Control register */
#define ``$INSTANCE_NAME`_Filter_1_CR_REG             (* (reg8 *) ``$INSTANCE_NAME`_Filter_1_DFB__CR)
#define ``$INSTANCE_NAME`_Filter_1_CR_PTR             (  (reg8 *) ``$INSTANCE_NAME`_Filter_1_DFB__CR)


/*******************************************************************************
* DFB.COHER bit field defines.
*******************************************************************************/

/* STAGEA key coherency mask */
#define ``$INSTANCE_NAME`_Filter_1_STAGEA_COHER_MASK    (0x03u)
#define ``$INSTANCE_NAME`_Filter_1_STAGEA_COHER         ``$INSTANCE_NAME`_Filter_1_STAGEA_COHER_MASK

/* HOLDA key coherency mask */
#define ``$INSTANCE_NAME`_Filter_1_HOLDA_COHER_MASK     ((uint8)((uint8)0x03u << 4u))
#define ``$INSTANCE_NAME`_Filter_1_HOLDA_COHER          ``$INSTANCE_NAME`_Filter_1_HOLDA_COHER_MASK

/* STAGEB key coherency mask */
#define ``$INSTANCE_NAME`_Filter_1_STAGEB_COHER_MASK    (0x0Cu)
#define ``$INSTANCE_NAME`_Filter_1_STAGEB_COHER         ``$INSTANCE_NAME`_Filter_1_STAGEB_COHER_MASK

/* HOLDB key coherency mask */
#define ``$INSTANCE_NAME`_Filter_1_HOLDB_COHER_MASK     ((uint8)((uint8)0x0Cu << 4u))
#define ``$INSTANCE_NAME`_Filter_1_HOLDB_COHER          ``$INSTANCE_NAME`_Filter_1_HOLDB_COHER_MASK


/*******************************************************************************
* DFB.DALIGN bit field defines.
*******************************************************************************/

/* STAGEA dalign mask */
#define ``$INSTANCE_NAME`_Filter_1_STAGEA_DALIGN    (0x01u)

/* HOLDA dalign mask */
#define ``$INSTANCE_NAME`_Filter_1_HOLDA_DALIGN     (0x04u)

/* STAGEB dalign mask */
#define ``$INSTANCE_NAME`_Filter_1_STAGEB_DALIGN    (0x02u)

/* HOLDB dalign mask */
#define ``$INSTANCE_NAME`_Filter_1_HOLDB_DALIGN     (0x08u)


#endif /* End FILT Header File */


/* [] END OF FILE */
