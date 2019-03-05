/*******************************************************************************
* File Name: ShiftReg_RED_PM.c
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

#include "ShiftReg_RED.h"

static ShiftReg_RED_BACKUP_STRUCT ShiftReg_RED_backup =
{
    ShiftReg_RED_DISABLED,

    ((uint8) ShiftReg_RED_DEFAULT_A0),
    ((uint8) ShiftReg_RED_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint8) ShiftReg_RED_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: ShiftReg_RED_SaveConfig
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
void ShiftReg_RED_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    ShiftReg_RED_backup.saveSrA0Reg   = CY_GET_REG8(ShiftReg_RED_SHIFT_REG_LSB_PTR);
    ShiftReg_RED_backup.saveSrA1Reg   = CY_GET_REG8(ShiftReg_RED_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        ShiftReg_RED_backup.saveSrIntMask = ShiftReg_RED_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ShiftReg_RED_RestoreConfig
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
void ShiftReg_RED_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG8(ShiftReg_RED_SHIFT_REG_LSB_PTR, ShiftReg_RED_backup.saveSrA0Reg);
    CY_SET_REG8(ShiftReg_RED_SHIFT_REG_VALUE_LSB_PTR, ShiftReg_RED_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        ShiftReg_RED_SR_STATUS_MASK = ((uint8) ShiftReg_RED_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ShiftReg_RED_Sleep
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
void ShiftReg_RED_Sleep(void) 
{
    ShiftReg_RED_backup.enableState = ((uint8) ShiftReg_RED_IS_ENABLED);

    ShiftReg_RED_Stop();
    ShiftReg_RED_SaveConfig();
}


/*******************************************************************************
* Function Name: ShiftReg_RED_Wakeup
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
void ShiftReg_RED_Wakeup(void) 
{
    ShiftReg_RED_RestoreConfig();

    if(0u != ShiftReg_RED_backup.enableState)
    {
        ShiftReg_RED_Enable();
    }
}


/* [] END OF FILE */
