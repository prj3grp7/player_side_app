/*******************************************************************************
* File Name: ``$INSTANCE_NAME`_ExtClock.h  
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

#if !defined(CY_PINS_``$INSTANCE_NAME`_ExtClock_H) /* Pins ``$INSTANCE_NAME`_ExtClock_H */
#define CY_PINS_``$INSTANCE_NAME`_ExtClock_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "``$INSTANCE_NAME`_ExtClock_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ``$INSTANCE_NAME`_ExtClock__PORT == 15 && ((``$INSTANCE_NAME`_ExtClock__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ``$INSTANCE_NAME`_ExtClock_Write(uint8 value);
void    ``$INSTANCE_NAME`_ExtClock_SetDriveMode(uint8 mode);
uint8   ``$INSTANCE_NAME`_ExtClock_ReadDataReg(void);
uint8   ``$INSTANCE_NAME`_ExtClock_Read(void);
void    ``$INSTANCE_NAME`_ExtClock_SetInterruptMode(uint16 position, uint16 mode);
uint8   ``$INSTANCE_NAME`_ExtClock_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ``$INSTANCE_NAME`_ExtClock_SetDriveMode() function.
     *  @{
     */
        #define ``$INSTANCE_NAME`_ExtClock_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ``$INSTANCE_NAME`_ExtClock_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ``$INSTANCE_NAME`_ExtClock_DM_RES_UP          PIN_DM_RES_UP
        #define ``$INSTANCE_NAME`_ExtClock_DM_RES_DWN         PIN_DM_RES_DWN
        #define ``$INSTANCE_NAME`_ExtClock_DM_OD_LO           PIN_DM_OD_LO
        #define ``$INSTANCE_NAME`_ExtClock_DM_OD_HI           PIN_DM_OD_HI
        #define ``$INSTANCE_NAME`_ExtClock_DM_STRONG          PIN_DM_STRONG
        #define ``$INSTANCE_NAME`_ExtClock_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ``$INSTANCE_NAME`_ExtClock_MASK               ``$INSTANCE_NAME`_ExtClock__MASK
#define ``$INSTANCE_NAME`_ExtClock_SHIFT              ``$INSTANCE_NAME`_ExtClock__SHIFT
#define ``$INSTANCE_NAME`_ExtClock_WIDTH              1u

/* Interrupt constants */
#if defined(``$INSTANCE_NAME`_ExtClock__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ``$INSTANCE_NAME`_ExtClock_SetInterruptMode() function.
     *  @{
     */
        #define ``$INSTANCE_NAME`_ExtClock_INTR_NONE      (uint16)(0x0000u)
        #define ``$INSTANCE_NAME`_ExtClock_INTR_RISING    (uint16)(0x0001u)
        #define ``$INSTANCE_NAME`_ExtClock_INTR_FALLING   (uint16)(0x0002u)
        #define ``$INSTANCE_NAME`_ExtClock_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ``$INSTANCE_NAME`_ExtClock_INTR_MASK      (0x01u) 
#endif /* (``$INSTANCE_NAME`_ExtClock__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ``$INSTANCE_NAME`_ExtClock_PS                     (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__PS)
/* Data Register */
#define ``$INSTANCE_NAME`_ExtClock_DR                     (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__DR)
/* Port Number */
#define ``$INSTANCE_NAME`_ExtClock_PRT_NUM                (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__PRT) 
/* Connect to Analog Globals */                                                  
#define ``$INSTANCE_NAME`_ExtClock_AG                     (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__AG)                       
/* Analog MUX bux enable */
#define ``$INSTANCE_NAME`_ExtClock_AMUX                   (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__AMUX) 
/* Bidirectional Enable */                                                        
#define ``$INSTANCE_NAME`_ExtClock_BIE                    (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__BIE)
/* Bit-mask for Aliased Register Access */
#define ``$INSTANCE_NAME`_ExtClock_BIT_MASK               (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__BIT_MASK)
/* Bypass Enable */
#define ``$INSTANCE_NAME`_ExtClock_BYP                    (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__BYP)
/* Port wide control signals */                                                   
#define ``$INSTANCE_NAME`_ExtClock_CTL                    (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__CTL)
/* Drive Modes */
#define ``$INSTANCE_NAME`_ExtClock_DM0                    (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__DM0) 
#define ``$INSTANCE_NAME`_ExtClock_DM1                    (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__DM1)
#define ``$INSTANCE_NAME`_ExtClock_DM2                    (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__DM2) 
/* Input Buffer Disable Override */
#define ``$INSTANCE_NAME`_ExtClock_INP_DIS                (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__INP_DIS)
/* LCD Common or Segment Drive */
#define ``$INSTANCE_NAME`_ExtClock_LCD_COM_SEG            (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__LCD_COM_SEG)
/* Enable Segment LCD */
#define ``$INSTANCE_NAME`_ExtClock_LCD_EN                 (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__LCD_EN)
/* Slew Rate Control */
#define ``$INSTANCE_NAME`_ExtClock_SLW                    (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ``$INSTANCE_NAME`_ExtClock_PRTDSI__CAPS_SEL       (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ``$INSTANCE_NAME`_ExtClock_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ``$INSTANCE_NAME`_ExtClock_PRTDSI__OE_SEL0        (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__PRTDSI__OE_SEL0) 
#define ``$INSTANCE_NAME`_ExtClock_PRTDSI__OE_SEL1        (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ``$INSTANCE_NAME`_ExtClock_PRTDSI__OUT_SEL0       (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__PRTDSI__OUT_SEL0) 
#define ``$INSTANCE_NAME`_ExtClock_PRTDSI__OUT_SEL1       (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ``$INSTANCE_NAME`_ExtClock_PRTDSI__SYNC_OUT       (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(``$INSTANCE_NAME`_ExtClock__SIO_CFG)
    #define ``$INSTANCE_NAME`_ExtClock_SIO_HYST_EN        (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__SIO_HYST_EN)
    #define ``$INSTANCE_NAME`_ExtClock_SIO_REG_HIFREQ     (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__SIO_REG_HIFREQ)
    #define ``$INSTANCE_NAME`_ExtClock_SIO_CFG            (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__SIO_CFG)
    #define ``$INSTANCE_NAME`_ExtClock_SIO_DIFF           (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__SIO_DIFF)
#endif /* (``$INSTANCE_NAME`_ExtClock__SIO_CFG) */

/* Interrupt Registers */
#if defined(``$INSTANCE_NAME`_ExtClock__INTSTAT)
    #define ``$INSTANCE_NAME`_ExtClock_INTSTAT            (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__INTSTAT)
    #define ``$INSTANCE_NAME`_ExtClock_SNAP               (* (reg8 *) ``$INSTANCE_NAME`_ExtClock__SNAP)
    
	#define ``$INSTANCE_NAME`_ExtClock_0_INTTYPE_REG 		(* (reg8 *) ``$INSTANCE_NAME`_ExtClock__0__INTTYPE)
#endif /* (``$INSTANCE_NAME`_ExtClock__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_``$INSTANCE_NAME`_ExtClock_H */


/* [] END OF FILE */
