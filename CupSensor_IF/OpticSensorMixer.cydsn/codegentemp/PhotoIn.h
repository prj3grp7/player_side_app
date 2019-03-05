/*******************************************************************************
* File Name: PhotoIn.h  
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

#if !defined(CY_PINS_PhotoIn_H) /* Pins PhotoIn_H */
#define CY_PINS_PhotoIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PhotoIn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PhotoIn__PORT == 15 && ((PhotoIn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PhotoIn_Write(uint8 value);
void    PhotoIn_SetDriveMode(uint8 mode);
uint8   PhotoIn_ReadDataReg(void);
uint8   PhotoIn_Read(void);
void    PhotoIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   PhotoIn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PhotoIn_SetDriveMode() function.
     *  @{
     */
        #define PhotoIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PhotoIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PhotoIn_DM_RES_UP          PIN_DM_RES_UP
        #define PhotoIn_DM_RES_DWN         PIN_DM_RES_DWN
        #define PhotoIn_DM_OD_LO           PIN_DM_OD_LO
        #define PhotoIn_DM_OD_HI           PIN_DM_OD_HI
        #define PhotoIn_DM_STRONG          PIN_DM_STRONG
        #define PhotoIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PhotoIn_MASK               PhotoIn__MASK
#define PhotoIn_SHIFT              PhotoIn__SHIFT
#define PhotoIn_WIDTH              1u

/* Interrupt constants */
#if defined(PhotoIn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PhotoIn_SetInterruptMode() function.
     *  @{
     */
        #define PhotoIn_INTR_NONE      (uint16)(0x0000u)
        #define PhotoIn_INTR_RISING    (uint16)(0x0001u)
        #define PhotoIn_INTR_FALLING   (uint16)(0x0002u)
        #define PhotoIn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PhotoIn_INTR_MASK      (0x01u) 
#endif /* (PhotoIn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PhotoIn_PS                     (* (reg8 *) PhotoIn__PS)
/* Data Register */
#define PhotoIn_DR                     (* (reg8 *) PhotoIn__DR)
/* Port Number */
#define PhotoIn_PRT_NUM                (* (reg8 *) PhotoIn__PRT) 
/* Connect to Analog Globals */                                                  
#define PhotoIn_AG                     (* (reg8 *) PhotoIn__AG)                       
/* Analog MUX bux enable */
#define PhotoIn_AMUX                   (* (reg8 *) PhotoIn__AMUX) 
/* Bidirectional Enable */                                                        
#define PhotoIn_BIE                    (* (reg8 *) PhotoIn__BIE)
/* Bit-mask for Aliased Register Access */
#define PhotoIn_BIT_MASK               (* (reg8 *) PhotoIn__BIT_MASK)
/* Bypass Enable */
#define PhotoIn_BYP                    (* (reg8 *) PhotoIn__BYP)
/* Port wide control signals */                                                   
#define PhotoIn_CTL                    (* (reg8 *) PhotoIn__CTL)
/* Drive Modes */
#define PhotoIn_DM0                    (* (reg8 *) PhotoIn__DM0) 
#define PhotoIn_DM1                    (* (reg8 *) PhotoIn__DM1)
#define PhotoIn_DM2                    (* (reg8 *) PhotoIn__DM2) 
/* Input Buffer Disable Override */
#define PhotoIn_INP_DIS                (* (reg8 *) PhotoIn__INP_DIS)
/* LCD Common or Segment Drive */
#define PhotoIn_LCD_COM_SEG            (* (reg8 *) PhotoIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define PhotoIn_LCD_EN                 (* (reg8 *) PhotoIn__LCD_EN)
/* Slew Rate Control */
#define PhotoIn_SLW                    (* (reg8 *) PhotoIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PhotoIn_PRTDSI__CAPS_SEL       (* (reg8 *) PhotoIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PhotoIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PhotoIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PhotoIn_PRTDSI__OE_SEL0        (* (reg8 *) PhotoIn__PRTDSI__OE_SEL0) 
#define PhotoIn_PRTDSI__OE_SEL1        (* (reg8 *) PhotoIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PhotoIn_PRTDSI__OUT_SEL0       (* (reg8 *) PhotoIn__PRTDSI__OUT_SEL0) 
#define PhotoIn_PRTDSI__OUT_SEL1       (* (reg8 *) PhotoIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PhotoIn_PRTDSI__SYNC_OUT       (* (reg8 *) PhotoIn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PhotoIn__SIO_CFG)
    #define PhotoIn_SIO_HYST_EN        (* (reg8 *) PhotoIn__SIO_HYST_EN)
    #define PhotoIn_SIO_REG_HIFREQ     (* (reg8 *) PhotoIn__SIO_REG_HIFREQ)
    #define PhotoIn_SIO_CFG            (* (reg8 *) PhotoIn__SIO_CFG)
    #define PhotoIn_SIO_DIFF           (* (reg8 *) PhotoIn__SIO_DIFF)
#endif /* (PhotoIn__SIO_CFG) */

/* Interrupt Registers */
#if defined(PhotoIn__INTSTAT)
    #define PhotoIn_INTSTAT            (* (reg8 *) PhotoIn__INTSTAT)
    #define PhotoIn_SNAP               (* (reg8 *) PhotoIn__SNAP)
    
	#define PhotoIn_0_INTTYPE_REG 		(* (reg8 *) PhotoIn__0__INTTYPE)
#endif /* (PhotoIn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PhotoIn_H */


/* [] END OF FILE */
