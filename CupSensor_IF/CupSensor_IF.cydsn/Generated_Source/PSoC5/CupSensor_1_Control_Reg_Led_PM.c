/*******************************************************************************
* File Name: CupSensor_1_Control_Reg_Led_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "CupSensor_1_Control_Reg_Led.h"

/* Check for removal by optimization */
#if !defined(CupSensor_1_Control_Reg_Led_Sync_ctrl_reg__REMOVED)

static CupSensor_1_Control_Reg_Led_BACKUP_STRUCT  CupSensor_1_Control_Reg_Led_backup = {0u};

    
/*******************************************************************************
* Function Name: CupSensor_1_Control_Reg_Led_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CupSensor_1_Control_Reg_Led_SaveConfig(void) 
{
    CupSensor_1_Control_Reg_Led_backup.controlState = CupSensor_1_Control_Reg_Led_Control;
}


/*******************************************************************************
* Function Name: CupSensor_1_Control_Reg_Led_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void CupSensor_1_Control_Reg_Led_RestoreConfig(void) 
{
     CupSensor_1_Control_Reg_Led_Control = CupSensor_1_Control_Reg_Led_backup.controlState;
}


/*******************************************************************************
* Function Name: CupSensor_1_Control_Reg_Led_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CupSensor_1_Control_Reg_Led_Sleep(void) 
{
    CupSensor_1_Control_Reg_Led_SaveConfig();
}


/*******************************************************************************
* Function Name: CupSensor_1_Control_Reg_Led_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CupSensor_1_Control_Reg_Led_Wakeup(void)  
{
    CupSensor_1_Control_Reg_Led_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
