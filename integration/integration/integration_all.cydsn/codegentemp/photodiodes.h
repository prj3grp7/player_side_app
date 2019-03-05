/*******************************************************************************
* File Name: photodiodes.h  
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

#if !defined(CY_PINS_photodiodes_H) /* Pins photodiodes_H */
#define CY_PINS_photodiodes_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "photodiodes_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 photodiodes__PORT == 15 && ((photodiodes__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    photodiodes_Write(uint8 value);
void    photodiodes_SetDriveMode(uint8 mode);
uint8   photodiodes_ReadDataReg(void);
uint8   photodiodes_Read(void);
void    photodiodes_SetInterruptMode(uint16 position, uint16 mode);
uint8   photodiodes_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the photodiodes_SetDriveMode() function.
     *  @{
     */
        #define photodiodes_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define photodiodes_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define photodiodes_DM_RES_UP          PIN_DM_RES_UP
        #define photodiodes_DM_RES_DWN         PIN_DM_RES_DWN
        #define photodiodes_DM_OD_LO           PIN_DM_OD_LO
        #define photodiodes_DM_OD_HI           PIN_DM_OD_HI
        #define photodiodes_DM_STRONG          PIN_DM_STRONG
        #define photodiodes_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define photodiodes_MASK               photodiodes__MASK
#define photodiodes_SHIFT              photodiodes__SHIFT
#define photodiodes_WIDTH              1u

/* Interrupt constants */
#if defined(photodiodes__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in photodiodes_SetInterruptMode() function.
     *  @{
     */
        #define photodiodes_INTR_NONE      (uint16)(0x0000u)
        #define photodiodes_INTR_RISING    (uint16)(0x0001u)
        #define photodiodes_INTR_FALLING   (uint16)(0x0002u)
        #define photodiodes_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define photodiodes_INTR_MASK      (0x01u) 
#endif /* (photodiodes__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define photodiodes_PS                     (* (reg8 *) photodiodes__PS)
/* Data Register */
#define photodiodes_DR                     (* (reg8 *) photodiodes__DR)
/* Port Number */
#define photodiodes_PRT_NUM                (* (reg8 *) photodiodes__PRT) 
/* Connect to Analog Globals */                                                  
#define photodiodes_AG                     (* (reg8 *) photodiodes__AG)                       
/* Analog MUX bux enable */
#define photodiodes_AMUX                   (* (reg8 *) photodiodes__AMUX) 
/* Bidirectional Enable */                                                        
#define photodiodes_BIE                    (* (reg8 *) photodiodes__BIE)
/* Bit-mask for Aliased Register Access */
#define photodiodes_BIT_MASK               (* (reg8 *) photodiodes__BIT_MASK)
/* Bypass Enable */
#define photodiodes_BYP                    (* (reg8 *) photodiodes__BYP)
/* Port wide control signals */                                                   
#define photodiodes_CTL                    (* (reg8 *) photodiodes__CTL)
/* Drive Modes */
#define photodiodes_DM0                    (* (reg8 *) photodiodes__DM0) 
#define photodiodes_DM1                    (* (reg8 *) photodiodes__DM1)
#define photodiodes_DM2                    (* (reg8 *) photodiodes__DM2) 
/* Input Buffer Disable Override */
#define photodiodes_INP_DIS                (* (reg8 *) photodiodes__INP_DIS)
/* LCD Common or Segment Drive */
#define photodiodes_LCD_COM_SEG            (* (reg8 *) photodiodes__LCD_COM_SEG)
/* Enable Segment LCD */
#define photodiodes_LCD_EN                 (* (reg8 *) photodiodes__LCD_EN)
/* Slew Rate Control */
#define photodiodes_SLW                    (* (reg8 *) photodiodes__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define photodiodes_PRTDSI__CAPS_SEL       (* (reg8 *) photodiodes__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define photodiodes_PRTDSI__DBL_SYNC_IN    (* (reg8 *) photodiodes__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define photodiodes_PRTDSI__OE_SEL0        (* (reg8 *) photodiodes__PRTDSI__OE_SEL0) 
#define photodiodes_PRTDSI__OE_SEL1        (* (reg8 *) photodiodes__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define photodiodes_PRTDSI__OUT_SEL0       (* (reg8 *) photodiodes__PRTDSI__OUT_SEL0) 
#define photodiodes_PRTDSI__OUT_SEL1       (* (reg8 *) photodiodes__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define photodiodes_PRTDSI__SYNC_OUT       (* (reg8 *) photodiodes__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(photodiodes__SIO_CFG)
    #define photodiodes_SIO_HYST_EN        (* (reg8 *) photodiodes__SIO_HYST_EN)
    #define photodiodes_SIO_REG_HIFREQ     (* (reg8 *) photodiodes__SIO_REG_HIFREQ)
    #define photodiodes_SIO_CFG            (* (reg8 *) photodiodes__SIO_CFG)
    #define photodiodes_SIO_DIFF           (* (reg8 *) photodiodes__SIO_DIFF)
#endif /* (photodiodes__SIO_CFG) */

/* Interrupt Registers */
#if defined(photodiodes__INTSTAT)
    #define photodiodes_INTSTAT            (* (reg8 *) photodiodes__INTSTAT)
    #define photodiodes_SNAP               (* (reg8 *) photodiodes__SNAP)
    
	#define photodiodes_0_INTTYPE_REG 		(* (reg8 *) photodiodes__0__INTTYPE)
#endif /* (photodiodes__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_photodiodes_H */


/* [] END OF FILE */
