/*******************************************************************************
* File Name: AmpOut.h  
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

#if !defined(CY_PINS_AmpOut_H) /* Pins AmpOut_H */
#define CY_PINS_AmpOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "AmpOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 AmpOut__PORT == 15 && ((AmpOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    AmpOut_Write(uint8 value);
void    AmpOut_SetDriveMode(uint8 mode);
uint8   AmpOut_ReadDataReg(void);
uint8   AmpOut_Read(void);
void    AmpOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   AmpOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the AmpOut_SetDriveMode() function.
     *  @{
     */
        #define AmpOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define AmpOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define AmpOut_DM_RES_UP          PIN_DM_RES_UP
        #define AmpOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define AmpOut_DM_OD_LO           PIN_DM_OD_LO
        #define AmpOut_DM_OD_HI           PIN_DM_OD_HI
        #define AmpOut_DM_STRONG          PIN_DM_STRONG
        #define AmpOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define AmpOut_MASK               AmpOut__MASK
#define AmpOut_SHIFT              AmpOut__SHIFT
#define AmpOut_WIDTH              1u

/* Interrupt constants */
#if defined(AmpOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AmpOut_SetInterruptMode() function.
     *  @{
     */
        #define AmpOut_INTR_NONE      (uint16)(0x0000u)
        #define AmpOut_INTR_RISING    (uint16)(0x0001u)
        #define AmpOut_INTR_FALLING   (uint16)(0x0002u)
        #define AmpOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define AmpOut_INTR_MASK      (0x01u) 
#endif /* (AmpOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AmpOut_PS                     (* (reg8 *) AmpOut__PS)
/* Data Register */
#define AmpOut_DR                     (* (reg8 *) AmpOut__DR)
/* Port Number */
#define AmpOut_PRT_NUM                (* (reg8 *) AmpOut__PRT) 
/* Connect to Analog Globals */                                                  
#define AmpOut_AG                     (* (reg8 *) AmpOut__AG)                       
/* Analog MUX bux enable */
#define AmpOut_AMUX                   (* (reg8 *) AmpOut__AMUX) 
/* Bidirectional Enable */                                                        
#define AmpOut_BIE                    (* (reg8 *) AmpOut__BIE)
/* Bit-mask for Aliased Register Access */
#define AmpOut_BIT_MASK               (* (reg8 *) AmpOut__BIT_MASK)
/* Bypass Enable */
#define AmpOut_BYP                    (* (reg8 *) AmpOut__BYP)
/* Port wide control signals */                                                   
#define AmpOut_CTL                    (* (reg8 *) AmpOut__CTL)
/* Drive Modes */
#define AmpOut_DM0                    (* (reg8 *) AmpOut__DM0) 
#define AmpOut_DM1                    (* (reg8 *) AmpOut__DM1)
#define AmpOut_DM2                    (* (reg8 *) AmpOut__DM2) 
/* Input Buffer Disable Override */
#define AmpOut_INP_DIS                (* (reg8 *) AmpOut__INP_DIS)
/* LCD Common or Segment Drive */
#define AmpOut_LCD_COM_SEG            (* (reg8 *) AmpOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define AmpOut_LCD_EN                 (* (reg8 *) AmpOut__LCD_EN)
/* Slew Rate Control */
#define AmpOut_SLW                    (* (reg8 *) AmpOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define AmpOut_PRTDSI__CAPS_SEL       (* (reg8 *) AmpOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define AmpOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) AmpOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define AmpOut_PRTDSI__OE_SEL0        (* (reg8 *) AmpOut__PRTDSI__OE_SEL0) 
#define AmpOut_PRTDSI__OE_SEL1        (* (reg8 *) AmpOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define AmpOut_PRTDSI__OUT_SEL0       (* (reg8 *) AmpOut__PRTDSI__OUT_SEL0) 
#define AmpOut_PRTDSI__OUT_SEL1       (* (reg8 *) AmpOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define AmpOut_PRTDSI__SYNC_OUT       (* (reg8 *) AmpOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(AmpOut__SIO_CFG)
    #define AmpOut_SIO_HYST_EN        (* (reg8 *) AmpOut__SIO_HYST_EN)
    #define AmpOut_SIO_REG_HIFREQ     (* (reg8 *) AmpOut__SIO_REG_HIFREQ)
    #define AmpOut_SIO_CFG            (* (reg8 *) AmpOut__SIO_CFG)
    #define AmpOut_SIO_DIFF           (* (reg8 *) AmpOut__SIO_DIFF)
#endif /* (AmpOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(AmpOut__INTSTAT)
    #define AmpOut_INTSTAT            (* (reg8 *) AmpOut__INTSTAT)
    #define AmpOut_SNAP               (* (reg8 *) AmpOut__SNAP)
    
	#define AmpOut_0_INTTYPE_REG 		(* (reg8 *) AmpOut__0__INTTYPE)
#endif /* (AmpOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_AmpOut_H */


/* [] END OF FILE */
