/*******************************************************************************
* File Name: ExtClock.h  
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

#if !defined(CY_PINS_ExtClock_H) /* Pins ExtClock_H */
#define CY_PINS_ExtClock_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ExtClock_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ExtClock__PORT == 15 && ((ExtClock__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ExtClock_Write(uint8 value);
void    ExtClock_SetDriveMode(uint8 mode);
uint8   ExtClock_ReadDataReg(void);
uint8   ExtClock_Read(void);
void    ExtClock_SetInterruptMode(uint16 position, uint16 mode);
uint8   ExtClock_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ExtClock_SetDriveMode() function.
     *  @{
     */
        #define ExtClock_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ExtClock_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ExtClock_DM_RES_UP          PIN_DM_RES_UP
        #define ExtClock_DM_RES_DWN         PIN_DM_RES_DWN
        #define ExtClock_DM_OD_LO           PIN_DM_OD_LO
        #define ExtClock_DM_OD_HI           PIN_DM_OD_HI
        #define ExtClock_DM_STRONG          PIN_DM_STRONG
        #define ExtClock_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ExtClock_MASK               ExtClock__MASK
#define ExtClock_SHIFT              ExtClock__SHIFT
#define ExtClock_WIDTH              1u

/* Interrupt constants */
#if defined(ExtClock__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ExtClock_SetInterruptMode() function.
     *  @{
     */
        #define ExtClock_INTR_NONE      (uint16)(0x0000u)
        #define ExtClock_INTR_RISING    (uint16)(0x0001u)
        #define ExtClock_INTR_FALLING   (uint16)(0x0002u)
        #define ExtClock_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ExtClock_INTR_MASK      (0x01u) 
#endif /* (ExtClock__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ExtClock_PS                     (* (reg8 *) ExtClock__PS)
/* Data Register */
#define ExtClock_DR                     (* (reg8 *) ExtClock__DR)
/* Port Number */
#define ExtClock_PRT_NUM                (* (reg8 *) ExtClock__PRT) 
/* Connect to Analog Globals */                                                  
#define ExtClock_AG                     (* (reg8 *) ExtClock__AG)                       
/* Analog MUX bux enable */
#define ExtClock_AMUX                   (* (reg8 *) ExtClock__AMUX) 
/* Bidirectional Enable */                                                        
#define ExtClock_BIE                    (* (reg8 *) ExtClock__BIE)
/* Bit-mask for Aliased Register Access */
#define ExtClock_BIT_MASK               (* (reg8 *) ExtClock__BIT_MASK)
/* Bypass Enable */
#define ExtClock_BYP                    (* (reg8 *) ExtClock__BYP)
/* Port wide control signals */                                                   
#define ExtClock_CTL                    (* (reg8 *) ExtClock__CTL)
/* Drive Modes */
#define ExtClock_DM0                    (* (reg8 *) ExtClock__DM0) 
#define ExtClock_DM1                    (* (reg8 *) ExtClock__DM1)
#define ExtClock_DM2                    (* (reg8 *) ExtClock__DM2) 
/* Input Buffer Disable Override */
#define ExtClock_INP_DIS                (* (reg8 *) ExtClock__INP_DIS)
/* LCD Common or Segment Drive */
#define ExtClock_LCD_COM_SEG            (* (reg8 *) ExtClock__LCD_COM_SEG)
/* Enable Segment LCD */
#define ExtClock_LCD_EN                 (* (reg8 *) ExtClock__LCD_EN)
/* Slew Rate Control */
#define ExtClock_SLW                    (* (reg8 *) ExtClock__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ExtClock_PRTDSI__CAPS_SEL       (* (reg8 *) ExtClock__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ExtClock_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ExtClock__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ExtClock_PRTDSI__OE_SEL0        (* (reg8 *) ExtClock__PRTDSI__OE_SEL0) 
#define ExtClock_PRTDSI__OE_SEL1        (* (reg8 *) ExtClock__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ExtClock_PRTDSI__OUT_SEL0       (* (reg8 *) ExtClock__PRTDSI__OUT_SEL0) 
#define ExtClock_PRTDSI__OUT_SEL1       (* (reg8 *) ExtClock__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ExtClock_PRTDSI__SYNC_OUT       (* (reg8 *) ExtClock__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ExtClock__SIO_CFG)
    #define ExtClock_SIO_HYST_EN        (* (reg8 *) ExtClock__SIO_HYST_EN)
    #define ExtClock_SIO_REG_HIFREQ     (* (reg8 *) ExtClock__SIO_REG_HIFREQ)
    #define ExtClock_SIO_CFG            (* (reg8 *) ExtClock__SIO_CFG)
    #define ExtClock_SIO_DIFF           (* (reg8 *) ExtClock__SIO_DIFF)
#endif /* (ExtClock__SIO_CFG) */

/* Interrupt Registers */
#if defined(ExtClock__INTSTAT)
    #define ExtClock_INTSTAT            (* (reg8 *) ExtClock__INTSTAT)
    #define ExtClock_SNAP               (* (reg8 *) ExtClock__SNAP)
    
	#define ExtClock_0_INTTYPE_REG 		(* (reg8 *) ExtClock__0__INTTYPE)
#endif /* (ExtClock__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ExtClock_H */


/* [] END OF FILE */
