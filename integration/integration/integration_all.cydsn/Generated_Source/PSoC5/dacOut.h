/*******************************************************************************
* File Name: dacOut.h  
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

#if !defined(CY_PINS_dacOut_H) /* Pins dacOut_H */
#define CY_PINS_dacOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "dacOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 dacOut__PORT == 15 && ((dacOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    dacOut_Write(uint8 value);
void    dacOut_SetDriveMode(uint8 mode);
uint8   dacOut_ReadDataReg(void);
uint8   dacOut_Read(void);
void    dacOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   dacOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the dacOut_SetDriveMode() function.
     *  @{
     */
        #define dacOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define dacOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define dacOut_DM_RES_UP          PIN_DM_RES_UP
        #define dacOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define dacOut_DM_OD_LO           PIN_DM_OD_LO
        #define dacOut_DM_OD_HI           PIN_DM_OD_HI
        #define dacOut_DM_STRONG          PIN_DM_STRONG
        #define dacOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define dacOut_MASK               dacOut__MASK
#define dacOut_SHIFT              dacOut__SHIFT
#define dacOut_WIDTH              1u

/* Interrupt constants */
#if defined(dacOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in dacOut_SetInterruptMode() function.
     *  @{
     */
        #define dacOut_INTR_NONE      (uint16)(0x0000u)
        #define dacOut_INTR_RISING    (uint16)(0x0001u)
        #define dacOut_INTR_FALLING   (uint16)(0x0002u)
        #define dacOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define dacOut_INTR_MASK      (0x01u) 
#endif /* (dacOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define dacOut_PS                     (* (reg8 *) dacOut__PS)
/* Data Register */
#define dacOut_DR                     (* (reg8 *) dacOut__DR)
/* Port Number */
#define dacOut_PRT_NUM                (* (reg8 *) dacOut__PRT) 
/* Connect to Analog Globals */                                                  
#define dacOut_AG                     (* (reg8 *) dacOut__AG)                       
/* Analog MUX bux enable */
#define dacOut_AMUX                   (* (reg8 *) dacOut__AMUX) 
/* Bidirectional Enable */                                                        
#define dacOut_BIE                    (* (reg8 *) dacOut__BIE)
/* Bit-mask for Aliased Register Access */
#define dacOut_BIT_MASK               (* (reg8 *) dacOut__BIT_MASK)
/* Bypass Enable */
#define dacOut_BYP                    (* (reg8 *) dacOut__BYP)
/* Port wide control signals */                                                   
#define dacOut_CTL                    (* (reg8 *) dacOut__CTL)
/* Drive Modes */
#define dacOut_DM0                    (* (reg8 *) dacOut__DM0) 
#define dacOut_DM1                    (* (reg8 *) dacOut__DM1)
#define dacOut_DM2                    (* (reg8 *) dacOut__DM2) 
/* Input Buffer Disable Override */
#define dacOut_INP_DIS                (* (reg8 *) dacOut__INP_DIS)
/* LCD Common or Segment Drive */
#define dacOut_LCD_COM_SEG            (* (reg8 *) dacOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define dacOut_LCD_EN                 (* (reg8 *) dacOut__LCD_EN)
/* Slew Rate Control */
#define dacOut_SLW                    (* (reg8 *) dacOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define dacOut_PRTDSI__CAPS_SEL       (* (reg8 *) dacOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define dacOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) dacOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define dacOut_PRTDSI__OE_SEL0        (* (reg8 *) dacOut__PRTDSI__OE_SEL0) 
#define dacOut_PRTDSI__OE_SEL1        (* (reg8 *) dacOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define dacOut_PRTDSI__OUT_SEL0       (* (reg8 *) dacOut__PRTDSI__OUT_SEL0) 
#define dacOut_PRTDSI__OUT_SEL1       (* (reg8 *) dacOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define dacOut_PRTDSI__SYNC_OUT       (* (reg8 *) dacOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(dacOut__SIO_CFG)
    #define dacOut_SIO_HYST_EN        (* (reg8 *) dacOut__SIO_HYST_EN)
    #define dacOut_SIO_REG_HIFREQ     (* (reg8 *) dacOut__SIO_REG_HIFREQ)
    #define dacOut_SIO_CFG            (* (reg8 *) dacOut__SIO_CFG)
    #define dacOut_SIO_DIFF           (* (reg8 *) dacOut__SIO_DIFF)
#endif /* (dacOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(dacOut__INTSTAT)
    #define dacOut_INTSTAT            (* (reg8 *) dacOut__INTSTAT)
    #define dacOut_SNAP               (* (reg8 *) dacOut__SNAP)
    
	#define dacOut_0_INTTYPE_REG 		(* (reg8 *) dacOut__0__INTTYPE)
#endif /* (dacOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_dacOut_H */


/* [] END OF FILE */
