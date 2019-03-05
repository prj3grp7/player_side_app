/*******************************************************************************
* File Name: leds.h  
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

#if !defined(CY_PINS_leds_H) /* Pins leds_H */
#define CY_PINS_leds_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "leds_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 leds__PORT == 15 && ((leds__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    leds_Write(uint8 value);
void    leds_SetDriveMode(uint8 mode);
uint8   leds_ReadDataReg(void);
uint8   leds_Read(void);
void    leds_SetInterruptMode(uint16 position, uint16 mode);
uint8   leds_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the leds_SetDriveMode() function.
     *  @{
     */
        #define leds_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define leds_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define leds_DM_RES_UP          PIN_DM_RES_UP
        #define leds_DM_RES_DWN         PIN_DM_RES_DWN
        #define leds_DM_OD_LO           PIN_DM_OD_LO
        #define leds_DM_OD_HI           PIN_DM_OD_HI
        #define leds_DM_STRONG          PIN_DM_STRONG
        #define leds_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define leds_MASK               leds__MASK
#define leds_SHIFT              leds__SHIFT
#define leds_WIDTH              6u

/* Interrupt constants */
#if defined(leds__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in leds_SetInterruptMode() function.
     *  @{
     */
        #define leds_INTR_NONE      (uint16)(0x0000u)
        #define leds_INTR_RISING    (uint16)(0x0001u)
        #define leds_INTR_FALLING   (uint16)(0x0002u)
        #define leds_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define leds_INTR_MASK      (0x01u) 
#endif /* (leds__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define leds_PS                     (* (reg8 *) leds__PS)
/* Data Register */
#define leds_DR                     (* (reg8 *) leds__DR)
/* Port Number */
#define leds_PRT_NUM                (* (reg8 *) leds__PRT) 
/* Connect to Analog Globals */                                                  
#define leds_AG                     (* (reg8 *) leds__AG)                       
/* Analog MUX bux enable */
#define leds_AMUX                   (* (reg8 *) leds__AMUX) 
/* Bidirectional Enable */                                                        
#define leds_BIE                    (* (reg8 *) leds__BIE)
/* Bit-mask for Aliased Register Access */
#define leds_BIT_MASK               (* (reg8 *) leds__BIT_MASK)
/* Bypass Enable */
#define leds_BYP                    (* (reg8 *) leds__BYP)
/* Port wide control signals */                                                   
#define leds_CTL                    (* (reg8 *) leds__CTL)
/* Drive Modes */
#define leds_DM0                    (* (reg8 *) leds__DM0) 
#define leds_DM1                    (* (reg8 *) leds__DM1)
#define leds_DM2                    (* (reg8 *) leds__DM2) 
/* Input Buffer Disable Override */
#define leds_INP_DIS                (* (reg8 *) leds__INP_DIS)
/* LCD Common or Segment Drive */
#define leds_LCD_COM_SEG            (* (reg8 *) leds__LCD_COM_SEG)
/* Enable Segment LCD */
#define leds_LCD_EN                 (* (reg8 *) leds__LCD_EN)
/* Slew Rate Control */
#define leds_SLW                    (* (reg8 *) leds__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define leds_PRTDSI__CAPS_SEL       (* (reg8 *) leds__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define leds_PRTDSI__DBL_SYNC_IN    (* (reg8 *) leds__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define leds_PRTDSI__OE_SEL0        (* (reg8 *) leds__PRTDSI__OE_SEL0) 
#define leds_PRTDSI__OE_SEL1        (* (reg8 *) leds__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define leds_PRTDSI__OUT_SEL0       (* (reg8 *) leds__PRTDSI__OUT_SEL0) 
#define leds_PRTDSI__OUT_SEL1       (* (reg8 *) leds__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define leds_PRTDSI__SYNC_OUT       (* (reg8 *) leds__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(leds__SIO_CFG)
    #define leds_SIO_HYST_EN        (* (reg8 *) leds__SIO_HYST_EN)
    #define leds_SIO_REG_HIFREQ     (* (reg8 *) leds__SIO_REG_HIFREQ)
    #define leds_SIO_CFG            (* (reg8 *) leds__SIO_CFG)
    #define leds_SIO_DIFF           (* (reg8 *) leds__SIO_DIFF)
#endif /* (leds__SIO_CFG) */

/* Interrupt Registers */
#if defined(leds__INTSTAT)
    #define leds_INTSTAT            (* (reg8 *) leds__INTSTAT)
    #define leds_SNAP               (* (reg8 *) leds__SNAP)
    
	#define leds_0_INTTYPE_REG 		(* (reg8 *) leds__0__INTTYPE)
	#define leds_1_INTTYPE_REG 		(* (reg8 *) leds__1__INTTYPE)
	#define leds_2_INTTYPE_REG 		(* (reg8 *) leds__2__INTTYPE)
	#define leds_3_INTTYPE_REG 		(* (reg8 *) leds__3__INTTYPE)
	#define leds_4_INTTYPE_REG 		(* (reg8 *) leds__4__INTTYPE)
	#define leds_5_INTTYPE_REG 		(* (reg8 *) leds__5__INTTYPE)
#endif /* (leds__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_leds_H */


/* [] END OF FILE */
