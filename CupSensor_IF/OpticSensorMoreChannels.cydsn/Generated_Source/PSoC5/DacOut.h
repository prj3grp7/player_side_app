/*******************************************************************************
* File Name: DacOut.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DacOut_H) /* Pins DacOut_H */
#define CY_PINS_DacOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DacOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DacOut__PORT == 15 && ((DacOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DacOut_Write(uint8 value);
void    DacOut_SetDriveMode(uint8 mode);
uint8   DacOut_ReadDataReg(void);
uint8   DacOut_Read(void);
void    DacOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   DacOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DacOut_SetDriveMode() function.
     *  @{
     */
        #define DacOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DacOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DacOut_DM_RES_UP          PIN_DM_RES_UP
        #define DacOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define DacOut_DM_OD_LO           PIN_DM_OD_LO
        #define DacOut_DM_OD_HI           PIN_DM_OD_HI
        #define DacOut_DM_STRONG          PIN_DM_STRONG
        #define DacOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DacOut_MASK               DacOut__MASK
#define DacOut_SHIFT              DacOut__SHIFT
#define DacOut_WIDTH              1u

/* Interrupt constants */
#if defined(DacOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DacOut_SetInterruptMode() function.
     *  @{
     */
        #define DacOut_INTR_NONE      (uint16)(0x0000u)
        #define DacOut_INTR_RISING    (uint16)(0x0001u)
        #define DacOut_INTR_FALLING   (uint16)(0x0002u)
        #define DacOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DacOut_INTR_MASK      (0x01u) 
#endif /* (DacOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DacOut_PS                     (* (reg8 *) DacOut__PS)
/* Data Register */
#define DacOut_DR                     (* (reg8 *) DacOut__DR)
/* Port Number */
#define DacOut_PRT_NUM                (* (reg8 *) DacOut__PRT) 
/* Connect to Analog Globals */                                                  
#define DacOut_AG                     (* (reg8 *) DacOut__AG)                       
/* Analog MUX bux enable */
#define DacOut_AMUX                   (* (reg8 *) DacOut__AMUX) 
/* Bidirectional Enable */                                                        
#define DacOut_BIE                    (* (reg8 *) DacOut__BIE)
/* Bit-mask for Aliased Register Access */
#define DacOut_BIT_MASK               (* (reg8 *) DacOut__BIT_MASK)
/* Bypass Enable */
#define DacOut_BYP                    (* (reg8 *) DacOut__BYP)
/* Port wide control signals */                                                   
#define DacOut_CTL                    (* (reg8 *) DacOut__CTL)
/* Drive Modes */
#define DacOut_DM0                    (* (reg8 *) DacOut__DM0) 
#define DacOut_DM1                    (* (reg8 *) DacOut__DM1)
#define DacOut_DM2                    (* (reg8 *) DacOut__DM2) 
/* Input Buffer Disable Override */
#define DacOut_INP_DIS                (* (reg8 *) DacOut__INP_DIS)
/* LCD Common or Segment Drive */
#define DacOut_LCD_COM_SEG            (* (reg8 *) DacOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define DacOut_LCD_EN                 (* (reg8 *) DacOut__LCD_EN)
/* Slew Rate Control */
#define DacOut_SLW                    (* (reg8 *) DacOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DacOut_PRTDSI__CAPS_SEL       (* (reg8 *) DacOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DacOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DacOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DacOut_PRTDSI__OE_SEL0        (* (reg8 *) DacOut__PRTDSI__OE_SEL0) 
#define DacOut_PRTDSI__OE_SEL1        (* (reg8 *) DacOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DacOut_PRTDSI__OUT_SEL0       (* (reg8 *) DacOut__PRTDSI__OUT_SEL0) 
#define DacOut_PRTDSI__OUT_SEL1       (* (reg8 *) DacOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DacOut_PRTDSI__SYNC_OUT       (* (reg8 *) DacOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DacOut__SIO_CFG)
    #define DacOut_SIO_HYST_EN        (* (reg8 *) DacOut__SIO_HYST_EN)
    #define DacOut_SIO_REG_HIFREQ     (* (reg8 *) DacOut__SIO_REG_HIFREQ)
    #define DacOut_SIO_CFG            (* (reg8 *) DacOut__SIO_CFG)
    #define DacOut_SIO_DIFF           (* (reg8 *) DacOut__SIO_DIFF)
#endif /* (DacOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(DacOut__INTSTAT)
    #define DacOut_INTSTAT            (* (reg8 *) DacOut__INTSTAT)
    #define DacOut_SNAP               (* (reg8 *) DacOut__SNAP)
    
	#define DacOut_0_INTTYPE_REG 		(* (reg8 *) DacOut__0__INTTYPE)
#endif /* (DacOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DacOut_H */


/* [] END OF FILE */
