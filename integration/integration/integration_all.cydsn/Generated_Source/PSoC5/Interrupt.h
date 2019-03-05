/*******************************************************************************
* File Name: Interrupt.h  
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

#if !defined(CY_PINS_Interrupt_H) /* Pins Interrupt_H */
#define CY_PINS_Interrupt_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Interrupt_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Interrupt__PORT == 15 && ((Interrupt__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Interrupt_Write(uint8 value);
void    Interrupt_SetDriveMode(uint8 mode);
uint8   Interrupt_ReadDataReg(void);
uint8   Interrupt_Read(void);
void    Interrupt_SetInterruptMode(uint16 position, uint16 mode);
uint8   Interrupt_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Interrupt_SetDriveMode() function.
     *  @{
     */
        #define Interrupt_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Interrupt_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Interrupt_DM_RES_UP          PIN_DM_RES_UP
        #define Interrupt_DM_RES_DWN         PIN_DM_RES_DWN
        #define Interrupt_DM_OD_LO           PIN_DM_OD_LO
        #define Interrupt_DM_OD_HI           PIN_DM_OD_HI
        #define Interrupt_DM_STRONG          PIN_DM_STRONG
        #define Interrupt_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Interrupt_MASK               Interrupt__MASK
#define Interrupt_SHIFT              Interrupt__SHIFT
#define Interrupt_WIDTH              1u

/* Interrupt constants */
#if defined(Interrupt__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Interrupt_SetInterruptMode() function.
     *  @{
     */
        #define Interrupt_INTR_NONE      (uint16)(0x0000u)
        #define Interrupt_INTR_RISING    (uint16)(0x0001u)
        #define Interrupt_INTR_FALLING   (uint16)(0x0002u)
        #define Interrupt_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Interrupt_INTR_MASK      (0x01u) 
#endif /* (Interrupt__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Interrupt_PS                     (* (reg8 *) Interrupt__PS)
/* Data Register */
#define Interrupt_DR                     (* (reg8 *) Interrupt__DR)
/* Port Number */
#define Interrupt_PRT_NUM                (* (reg8 *) Interrupt__PRT) 
/* Connect to Analog Globals */                                                  
#define Interrupt_AG                     (* (reg8 *) Interrupt__AG)                       
/* Analog MUX bux enable */
#define Interrupt_AMUX                   (* (reg8 *) Interrupt__AMUX) 
/* Bidirectional Enable */                                                        
#define Interrupt_BIE                    (* (reg8 *) Interrupt__BIE)
/* Bit-mask for Aliased Register Access */
#define Interrupt_BIT_MASK               (* (reg8 *) Interrupt__BIT_MASK)
/* Bypass Enable */
#define Interrupt_BYP                    (* (reg8 *) Interrupt__BYP)
/* Port wide control signals */                                                   
#define Interrupt_CTL                    (* (reg8 *) Interrupt__CTL)
/* Drive Modes */
#define Interrupt_DM0                    (* (reg8 *) Interrupt__DM0) 
#define Interrupt_DM1                    (* (reg8 *) Interrupt__DM1)
#define Interrupt_DM2                    (* (reg8 *) Interrupt__DM2) 
/* Input Buffer Disable Override */
#define Interrupt_INP_DIS                (* (reg8 *) Interrupt__INP_DIS)
/* LCD Common or Segment Drive */
#define Interrupt_LCD_COM_SEG            (* (reg8 *) Interrupt__LCD_COM_SEG)
/* Enable Segment LCD */
#define Interrupt_LCD_EN                 (* (reg8 *) Interrupt__LCD_EN)
/* Slew Rate Control */
#define Interrupt_SLW                    (* (reg8 *) Interrupt__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Interrupt_PRTDSI__CAPS_SEL       (* (reg8 *) Interrupt__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Interrupt_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Interrupt__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Interrupt_PRTDSI__OE_SEL0        (* (reg8 *) Interrupt__PRTDSI__OE_SEL0) 
#define Interrupt_PRTDSI__OE_SEL1        (* (reg8 *) Interrupt__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Interrupt_PRTDSI__OUT_SEL0       (* (reg8 *) Interrupt__PRTDSI__OUT_SEL0) 
#define Interrupt_PRTDSI__OUT_SEL1       (* (reg8 *) Interrupt__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Interrupt_PRTDSI__SYNC_OUT       (* (reg8 *) Interrupt__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Interrupt__SIO_CFG)
    #define Interrupt_SIO_HYST_EN        (* (reg8 *) Interrupt__SIO_HYST_EN)
    #define Interrupt_SIO_REG_HIFREQ     (* (reg8 *) Interrupt__SIO_REG_HIFREQ)
    #define Interrupt_SIO_CFG            (* (reg8 *) Interrupt__SIO_CFG)
    #define Interrupt_SIO_DIFF           (* (reg8 *) Interrupt__SIO_DIFF)
#endif /* (Interrupt__SIO_CFG) */

/* Interrupt Registers */
#if defined(Interrupt__INTSTAT)
    #define Interrupt_INTSTAT            (* (reg8 *) Interrupt__INTSTAT)
    #define Interrupt_SNAP               (* (reg8 *) Interrupt__SNAP)
    
	#define Interrupt_0_INTTYPE_REG 		(* (reg8 *) Interrupt__0__INTTYPE)
#endif /* (Interrupt__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Interrupt_H */


/* [] END OF FILE */
