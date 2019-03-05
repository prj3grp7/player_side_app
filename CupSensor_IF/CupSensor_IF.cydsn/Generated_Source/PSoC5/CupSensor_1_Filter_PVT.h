/*******************************************************************************
* File Name: CupSensor_1_Filter_PVT.h
* Version 2.30
*
* Description:
*  This header file contains internal definitions for the FILT component.
*  It must be included after CupSensor_1_Filter.h.
*
* Note:
* 
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CupSensor_1_Filter_PVT_H) /* FILT Header File */
#define CupSensor_1_Filter_PVT_H

#include "CupSensor_1_Filter.H"


/*******************************************************************************
* FILT component internal function prototypes.
*******************************************************************************/

extern void CupSensor_1_Filter_SetInterruptMode(uint8 events) ;
extern void CupSensor_1_Filter_SetDMAMode(uint8 events) ;


/*******************************************************************************
* FILT component internal variables.
*******************************************************************************/

extern const uint8 CYCODE CupSensor_1_Filter_control[CupSensor_1_Filter_CSA_RAM_SIZE_CUR]; 
extern const uint8 CYCODE CupSensor_1_Filter_data_a[CupSensor_1_Filter_DA_RAM_SIZE_CUR];
extern const uint8 CYCODE CupSensor_1_Filter_data_b[CupSensor_1_Filter_DB_RAM_SIZE_CUR];
extern const uint8 CYCODE CupSensor_1_Filter_cfsm[CupSensor_1_Filter_CFSM_RAM_SIZE_CUR];
extern const uint8 CYCODE CupSensor_1_Filter_acu[CupSensor_1_Filter_ACU_RAM_SIZE_CUR];


/*******************************************************************************
* FILT component internal constants.
*******************************************************************************/

/* Parameters */
#define CupSensor_1_Filter_INIT_INTERRUPT_MODE    (0u)
#define CupSensor_1_Filter_INIT_DMA_MODE          (1u)
#define CupSensor_1_Filter_INIT_COHER             (0x00u)
#define CupSensor_1_Filter_INIT_DALIGN            (0x0Fu)

/* RAM memory map offsets */
#define CupSensor_1_Filter_DA_RAM                 (void XDATA *) (CupSensor_1_Filter_DFB__DPA_SRAM_DATA)
#define CupSensor_1_Filter_DB_RAM                 (void XDATA *) (CupSensor_1_Filter_DFB__DPB_SRAM_DATA)
#define CupSensor_1_Filter_CSA_RAM                (void XDATA *) (CupSensor_1_Filter_DFB__CSA_SRAM_DATA)
#define CupSensor_1_Filter_CSB_RAM                (void XDATA *) (CupSensor_1_Filter_DFB__CSB_SRAM_DATA)
#define CupSensor_1_Filter_CFSM_RAM               (void XDATA *) (CupSensor_1_Filter_DFB__FSM_SRAM_DATA)
#define CupSensor_1_Filter_ACU_RAM                (void XDATA *) (CupSensor_1_Filter_DFB__ACU_SRAM_DATA)

/* RAM register space sizes in bytes. */
#if (CY_PSOC3)
    #define CupSensor_1_Filter_DA_RAM_SIZE            ((int16)0x0200)
    #define CupSensor_1_Filter_DB_RAM_SIZE            ((int16)0x0200)
    #define CupSensor_1_Filter_CSA_RAM_SIZE           ((int16)0x0100)
    #define CupSensor_1_Filter_CSB_RAM_SIZE           ((int16)0x0100)
    #define CupSensor_1_Filter_CFSM_RAM_SIZE          ((int16)0x0100)
    #define CupSensor_1_Filter_ACU_RAM_SIZE           ((int16)0x0040)
#else
    #define CupSensor_1_Filter_DA_RAM_SIZE            ((uint16)0x0200u)
    #define CupSensor_1_Filter_DB_RAM_SIZE            ((uint16)0x0200u)
    #define CupSensor_1_Filter_CSA_RAM_SIZE           ((uint16)0x0100u)
    #define CupSensor_1_Filter_CSB_RAM_SIZE           ((uint16)0x0100u)
    #define CupSensor_1_Filter_CFSM_RAM_SIZE          ((uint16)0x0100u)
    #define CupSensor_1_Filter_ACU_RAM_SIZE           ((uint16)0x0040u)
#endif /* (CY_PSOC3) */


/*******************************************************************************
* FILT component internal register contents.
*******************************************************************************/

#define CupSensor_1_Filter_PM_ACT_MSK             CupSensor_1_Filter_DFB__PM_ACT_MSK 
#define CupSensor_1_Filter_PM_STBY_MSK            CupSensor_1_Filter_DFB__PM_STBY_MSK 

#define CupSensor_1_Filter_RUN_MASK               (0x01u)
#define CupSensor_1_Filter_EVENT_MASK             (0x1Fu)
#define CupSensor_1_Filter_SR_EVENT_SHIFT         (0x03u)
#define CupSensor_1_Filter_DMA_CTRL_MASK          (0x0Fu)
#define CupSensor_1_Filter_RAM_DIR_BUS            (0x3Fu)
#define CupSensor_1_Filter_RAM_DIR_DFB            (0x00u)


/*******************************************************************************
* FILT component internal DFB registers.
*******************************************************************************/

/* DFB interrupt control register */
#define CupSensor_1_Filter_INT_CTRL_REG           (* (reg8 *) CupSensor_1_Filter_DFB__INT_CTRL)
#define CupSensor_1_Filter_INT_CTRL_PTR           (  (reg8 *) CupSensor_1_Filter_DFB__INT_CTRL)

/* DFB DMA control register */
#define CupSensor_1_Filter_DMA_CTRL_REG           (* (reg8 *) CupSensor_1_Filter_DFB__DMA_CTRL)
#define CupSensor_1_Filter_DMA_CTRL_PTR           (  (reg8 *) CupSensor_1_Filter_DFB__DMA_CTRL)

/* DFB ram direction register */
#define CupSensor_1_Filter_RAM_DIR_REG            (* (reg8 *) CupSensor_1_Filter_DFB__RAM_DIR)
#define CupSensor_1_Filter_RAM_DIR_PTR            (  (reg8 *) CupSensor_1_Filter_DFB__RAM_DIR)

/* DFB DSI control register */
#define CupSensor_1_Filter_DSI_CTRL_REG           (* (reg8 *) CupSensor_1_Filter_DFB__DSI_CTRL)
#define CupSensor_1_Filter_DSI_CTRL_PTR           (  (reg8 *) CupSensor_1_Filter_DFB__DSI_CTRL)

/* DFB HOLDA(Output LSB) register */
#define CupSensor_1_Filter_HOLDA_REG              (* (reg8 *) CupSensor_1_Filter_DFB__HOLDA)
#define CupSensor_1_Filter_HOLDA_PTR              (  (reg8 *) CupSensor_1_Filter_DFB__HOLDA)

/* DFB HOLDAH(Output MSB) register */
#define CupSensor_1_Filter_HOLDAH_REG             (* (reg8 *) CupSensor_1_Filter_DFB__HOLDAH)
#define CupSensor_1_Filter_HOLDAH_PTR             (  (reg8 *) CupSensor_1_Filter_DFB__HOLDAH)

/* DFB HOLDAM(Output middle) register */
#define CupSensor_1_Filter_HOLDAM_REG             (* (reg8 *) CupSensor_1_Filter_DFB__HOLDAM)
#define CupSensor_1_Filter_HOLDAM_PTR             (  (reg8 *) CupSensor_1_Filter_DFB__HOLDAM)

/* DFB HOLDB(Output LSB) register */
#define CupSensor_1_Filter_HOLDB_REG              (* (reg8 *) CupSensor_1_Filter_DFB__HOLDB)
#define CupSensor_1_Filter_HOLDB_PTR              (  (reg8 *) CupSensor_1_Filter_DFB__HOLDB)

/* DFB HOLDBH(Output MSB) register */
#define CupSensor_1_Filter_HOLDBH_REG             (* (reg8 *) CupSensor_1_Filter_DFB__HOLDBH)
#define CupSensor_1_Filter_HOLDBH_PTR             (  (reg8 *) CupSensor_1_Filter_DFB__HOLDBH)

/* DFB HOLDBM(Output middle) register */
#define CupSensor_1_Filter_HOLDBM_REG             (* (reg8 *) CupSensor_1_Filter_DFB__HOLDBM)
#define CupSensor_1_Filter_HOLDBM_PTR             (  (reg8 *) CupSensor_1_Filter_DFB__HOLDBM)

/* Active mode power control register */
#define CupSensor_1_Filter_PM_ACT_CFG_REG         (* (reg8 *) CupSensor_1_Filter_DFB__PM_ACT_CFG)
#define CupSensor_1_Filter_PM_ACT_CFG_PTR         (  (reg8 *) CupSensor_1_Filter_DFB__PM_ACT_CFG)

/* Alternative active mode power control register */
#define CupSensor_1_Filter_PM_STBY_CFG_REG        (* (reg8 *) CupSensor_1_Filter_DFB__PM_STBY_CFG)
#define CupSensor_1_Filter_PM_STBY_CFG_PTR        (  (reg8 *) CupSensor_1_Filter_DFB__PM_STBY_CFG)

/* DFB ram enable register */
#define CupSensor_1_Filter_RAM_EN_REG             (* (reg8 *) CupSensor_1_Filter_DFB__RAM_EN)
#define CupSensor_1_Filter_RAM_EN_PTR             (  (reg8 *) CupSensor_1_Filter_DFB__RAM_EN)

/* DFB STAGEA(Input LSB) register */
#define CupSensor_1_Filter_STAGEA_REG             (* (reg8 *) CupSensor_1_Filter_DFB__STAGEA)
#define CupSensor_1_Filter_STAGEA_PTR             (  (reg8 *) CupSensor_1_Filter_DFB__STAGEA)

/* DFB STAGEAH(Input MSB) register */
#define CupSensor_1_Filter_STAGEAH_REG            (* (reg8 *) CupSensor_1_Filter_DFB__STAGEAH)
#define CupSensor_1_Filter_STAGEAH_PTR            (  (reg8 *) CupSensor_1_Filter_DFB__STAGEAH)

/* DFB STAGEAM(Input middle) register */
#define CupSensor_1_Filter_STAGEAM_REG            (* (reg8 *) CupSensor_1_Filter_DFB__STAGEAM)
#define CupSensor_1_Filter_STAGEAM_PTR            (  (reg8 *) CupSensor_1_Filter_DFB__STAGEAM)

/* DFB STAGEB(Input LSB) register */
#define CupSensor_1_Filter_STAGEB_REG             (* (reg8 *) CupSensor_1_Filter_DFB__STAGEB )
#define CupSensor_1_Filter_STAGEB_PTR             (  (reg8 *) CupSensor_1_Filter_DFB__STAGEB )

/* DFB STAGEBH(Input MSB) register */
#define CupSensor_1_Filter_STAGEBH_REG            (* (reg8 *) CupSensor_1_Filter_DFB__STAGEBH)
#define CupSensor_1_Filter_STAGEBH_PTR            (  (reg8 *) CupSensor_1_Filter_DFB__STAGEBH)

/* DFB STAGEBM(Input middle) register */
#define CupSensor_1_Filter_STAGEBM_REG            (* (reg8 *) CupSensor_1_Filter_DFB__STAGEBM)
#define CupSensor_1_Filter_STAGEBM_PTR            (  (reg8 *) CupSensor_1_Filter_DFB__STAGEBM)

/* DFB coherence register */
#define CupSensor_1_Filter_COHER_REG              (* (reg8 *) CupSensor_1_Filter_DFB__COHER)
#define CupSensor_1_Filter_COHER_PTR              (  (reg8 *) CupSensor_1_Filter_DFB__COHER)

/* DFB data align register */
#define CupSensor_1_Filter_DALIGN_REG             (* (reg8 *) CupSensor_1_Filter_DFB__DALIGN)
#define CupSensor_1_Filter_DALIGN_PTR             (  (reg8 *) CupSensor_1_Filter_DFB__DALIGN)

/* DFB semaphore register */
#define CupSensor_1_Filter_SEMA_REG               (* (reg8 *) CupSensor_1_Filter_DFB__SEMA)
#define CupSensor_1_Filter_SEMA_PTR               (  (reg8 *) CupSensor_1_Filter_DFB__SEMA)

/* DFB output register which are 16 bit aligned */
#define CupSensor_1_Filter_HOLDA16_REG            (* (reg16 *) CupSensor_1_Filter_DFB__HOLDAM)
#define CupSensor_1_Filter_HOLDA16_PTR            (  (reg16 *) CupSensor_1_Filter_DFB__HOLDAM)

#define CupSensor_1_Filter_HOLDB16_REG            (* (reg16 *) CupSensor_1_Filter_DFB__HOLDBM)
#define CupSensor_1_Filter_HOLDB16_PTR            (  (reg16 *) CupSensor_1_Filter_DFB__HOLDBM)

/* DFB input register which are 16 bit aligned */
#define CupSensor_1_Filter_STAGEA16_REG           (* (reg16 *) CupSensor_1_Filter_DFB__STAGEAM)
#define CupSensor_1_Filter_STAGEA16_PTR           (  (reg16 *) CupSensor_1_Filter_DFB__STAGEAM)

#define CupSensor_1_Filter_STAGEB16_REG           (* (reg16 *) CupSensor_1_Filter_DFB__STAGEBM)
#define CupSensor_1_Filter_STAGEB16_PTR           (  (reg16 *) CupSensor_1_Filter_DFB__STAGEBM)

/* DFB output registers which are 24 bit aligned */
#define CupSensor_1_Filter_HOLDA24_REG            (* (reg32 *) CupSensor_1_Filter_DFB__HOLDA)
#define CupSensor_1_Filter_HOLDA24_PTR            (  (reg32 *) CupSensor_1_Filter_DFB__HOLDA)

#define CupSensor_1_Filter_HOLDB24_REG            (* (reg32 *) CupSensor_1_Filter_DFB__HOLDB)
#define CupSensor_1_Filter_HOLDB24_PTR            (  (reg32 *) CupSensor_1_Filter_DFB__HOLDB)

/* DFB input registers which are 24 bit aligned */
#define CupSensor_1_Filter_STAGEA24_REG           (* (reg32 *) CupSensor_1_Filter_DFB__STAGEA)
#define CupSensor_1_Filter_STAGEA24_PTR           (  (reg32 *) CupSensor_1_Filter_DFB__STAGEA)

#define CupSensor_1_Filter_STAGEB24_REG           (* (reg32 *) CupSensor_1_Filter_DFB__STAGEB)
#define CupSensor_1_Filter_STAGEB24_PTR           (  (reg32 *) CupSensor_1_Filter_DFB__STAGEB)

#endif /* End CupSensor_1_Filter_PVT_H Header File */


/* [] END OF FILE */
