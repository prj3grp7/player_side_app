/*******************************************************************************
* File Name: ShiftReg_led_control_PM.c
* Version 2.30
*
* Description:
*  This file provides the API source code for sleep mode support for Shift
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ShiftReg_led_control.h"

static ShiftReg_led_control_BACKUP_STRUCT ShiftReg_led_control_backup =
{
    ShiftReg_led_control_DISABLED,

    ((uint8) ShiftReg_led_control_DEFAULT_A0),
    ((uint8) ShiftReg_led_control_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint8) ShiftReg_led_control_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: ShiftReg_led_control_SaveConfig
********************************************************************************
*
* Summary:
*  Saves Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ShiftReg_led_control_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    ShiftReg_led_control_backup.saveSrA0Reg   = CY_GET_REG8(ShiftReg_led_control_SHIFT_REG_LSB_PTR);
    ShiftReg_led_control_backup.saveSrA1Reg   = CY_GET_REG8(ShiftReg_led_control_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        ShiftReg_led_control_backup.saveSrIntMask = ShiftReg_led_control_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ShiftReg_led_control_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ShiftReg_led_control_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG8(ShiftReg_led_control_SHIFT_REG_LSB_PTR, ShiftReg_led_control_backup.saveSrA0Reg);
    CY_SET_REG8(ShiftReg_led_control_SHIFT_REG_VALUE_LSB_PTR, ShiftReg_led_control_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        ShiftReg_led_control_SR_STATUS_MASK = ((uint8) ShiftReg_led_control_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ShiftReg_led_control_Sleep
********************************************************************************
*
* Summary:
*  Prepare the component to enter a Sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ShiftReg_led_control_Sleep(void) 
{
    ShiftReg_led_control_backup.enableState = ((uint8) ShiftReg_led_control_IS_ENABLED);

    ShiftReg_led_control_Stop();
    ShiftReg_led_control_SaveConfig();
}


/*******************************************************************************
* Function Name: ShiftReg_led_control_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ShiftReg_led_control_Wakeup(void) 
{
    ShiftReg_led_control_RestoreConfig();

    if(0u != ShiftReg_led_control_backup.enableState)
    {
        ShiftReg_led_control_Enable();
    }
}


/* [] END OF FILE */
