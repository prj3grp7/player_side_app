/*******************************************************************************
* File Name: Clock_LedUpdate.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Clock_LedUpdate_H)
#define CY_CLOCK_Clock_LedUpdate_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Clock_LedUpdate_Start(void) ;
void Clock_LedUpdate_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Clock_LedUpdate_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Clock_LedUpdate_StandbyPower(uint8 state) ;
void Clock_LedUpdate_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Clock_LedUpdate_GetDividerRegister(void) ;
void Clock_LedUpdate_SetModeRegister(uint8 modeBitMask) ;
void Clock_LedUpdate_ClearModeRegister(uint8 modeBitMask) ;
uint8 Clock_LedUpdate_GetModeRegister(void) ;
void Clock_LedUpdate_SetSourceRegister(uint8 clkSource) ;
uint8 Clock_LedUpdate_GetSourceRegister(void) ;
#if defined(Clock_LedUpdate__CFG3)
void Clock_LedUpdate_SetPhaseRegister(uint8 clkPhase) ;
uint8 Clock_LedUpdate_GetPhaseRegister(void) ;
#endif /* defined(Clock_LedUpdate__CFG3) */

#define Clock_LedUpdate_Enable()                       Clock_LedUpdate_Start()
#define Clock_LedUpdate_Disable()                      Clock_LedUpdate_Stop()
#define Clock_LedUpdate_SetDivider(clkDivider)         Clock_LedUpdate_SetDividerRegister(clkDivider, 1u)
#define Clock_LedUpdate_SetDividerValue(clkDivider)    Clock_LedUpdate_SetDividerRegister((clkDivider) - 1u, 1u)
#define Clock_LedUpdate_SetMode(clkMode)               Clock_LedUpdate_SetModeRegister(clkMode)
#define Clock_LedUpdate_SetSource(clkSource)           Clock_LedUpdate_SetSourceRegister(clkSource)
#if defined(Clock_LedUpdate__CFG3)
#define Clock_LedUpdate_SetPhase(clkPhase)             Clock_LedUpdate_SetPhaseRegister(clkPhase)
#define Clock_LedUpdate_SetPhaseValue(clkPhase)        Clock_LedUpdate_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Clock_LedUpdate__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Clock_LedUpdate_CLKEN              (* (reg8 *) Clock_LedUpdate__PM_ACT_CFG)
#define Clock_LedUpdate_CLKEN_PTR          ((reg8 *) Clock_LedUpdate__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Clock_LedUpdate_CLKSTBY            (* (reg8 *) Clock_LedUpdate__PM_STBY_CFG)
#define Clock_LedUpdate_CLKSTBY_PTR        ((reg8 *) Clock_LedUpdate__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Clock_LedUpdate_DIV_LSB            (* (reg8 *) Clock_LedUpdate__CFG0)
#define Clock_LedUpdate_DIV_LSB_PTR        ((reg8 *) Clock_LedUpdate__CFG0)
#define Clock_LedUpdate_DIV_PTR            ((reg16 *) Clock_LedUpdate__CFG0)

/* Clock MSB divider configuration register. */
#define Clock_LedUpdate_DIV_MSB            (* (reg8 *) Clock_LedUpdate__CFG1)
#define Clock_LedUpdate_DIV_MSB_PTR        ((reg8 *) Clock_LedUpdate__CFG1)

/* Mode and source configuration register */
#define Clock_LedUpdate_MOD_SRC            (* (reg8 *) Clock_LedUpdate__CFG2)
#define Clock_LedUpdate_MOD_SRC_PTR        ((reg8 *) Clock_LedUpdate__CFG2)

#if defined(Clock_LedUpdate__CFG3)
/* Analog clock phase configuration register */
#define Clock_LedUpdate_PHASE              (* (reg8 *) Clock_LedUpdate__CFG3)
#define Clock_LedUpdate_PHASE_PTR          ((reg8 *) Clock_LedUpdate__CFG3)
#endif /* defined(Clock_LedUpdate__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Clock_LedUpdate_CLKEN_MASK         Clock_LedUpdate__PM_ACT_MSK
#define Clock_LedUpdate_CLKSTBY_MASK       Clock_LedUpdate__PM_STBY_MSK

/* CFG2 field masks */
#define Clock_LedUpdate_SRC_SEL_MSK        Clock_LedUpdate__CFG2_SRC_SEL_MASK
#define Clock_LedUpdate_MODE_MASK          (~(Clock_LedUpdate_SRC_SEL_MSK))

#if defined(Clock_LedUpdate__CFG3)
/* CFG3 phase mask */
#define Clock_LedUpdate_PHASE_MASK         Clock_LedUpdate__CFG3_PHASE_DLY_MASK
#endif /* defined(Clock_LedUpdate__CFG3) */

#endif /* CY_CLOCK_Clock_LedUpdate_H */


/* [] END OF FILE */
