/*******************************************************************************
* File Name: ShiftReg_GREEN_PM.c
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

#include "ShiftReg_GREEN.h"

static ShiftReg_GREEN_BACKUP_STRUCT ShiftReg_GREEN_backup =
{
    ShiftReg_GREEN_DISABLED,

    ((uint8) ShiftReg_GREEN_DEFAULT_A0),
    ((uint8) ShiftReg_GREEN_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint8) ShiftReg_GREEN_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: ShiftReg_GREEN_SaveConfig
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
void ShiftReg_GREEN_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    ShiftReg_GREEN_backup.saveSrA0Reg   = CY_GET_REG8(ShiftReg_GREEN_SHIFT_REG_LSB_PTR);
    ShiftReg_GREEN_backup.saveSrA1Reg   = CY_GET_REG8(ShiftReg_GREEN_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        ShiftReg_GREEN_backup.saveSrIntMask = ShiftReg_GREEN_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ShiftReg_GREEN_RestoreConfig
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
void ShiftReg_GREEN_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG8(ShiftReg_GREEN_SHIFT_REG_LSB_PTR, ShiftReg_GREEN_backup.saveSrA0Reg);
    CY_SET_REG8(ShiftReg_GREEN_SHIFT_REG_VALUE_LSB_PTR, ShiftReg_GREEN_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        ShiftReg_GREEN_SR_STATUS_MASK = ((uint8) ShiftReg_GREEN_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ShiftReg_GREEN_Sleep
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
void ShiftReg_GREEN_Sleep(void) 
{
    ShiftReg_GREEN_backup.enableState = ((uint8) ShiftReg_GREEN_IS_ENABLED);

    ShiftReg_GREEN_Stop();
    ShiftReg_GREEN_SaveConfig();
}


/*******************************************************************************
* Function Name: ShiftReg_GREEN_Wakeup
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
void ShiftReg_GREEN_Wakeup(void) 
{
    ShiftReg_GREEN_RestoreConfig();

    if(0u != ShiftReg_GREEN_backup.enableState)
    {
        ShiftReg_GREEN_Enable();
    }
}


/* [] END OF FILE */
