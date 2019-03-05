/*******************************************************************************
* File Name: CupSensor_1_VDAC8_1_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "CupSensor_1_VDAC8_1.h"

static CupSensor_1_VDAC8_1_backupStruct CupSensor_1_VDAC8_1_backup;


/*******************************************************************************
* Function Name: CupSensor_1_VDAC8_1_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void CupSensor_1_VDAC8_1_SaveConfig(void) 
{
    if (!((CupSensor_1_VDAC8_1_CR1 & CupSensor_1_VDAC8_1_SRC_MASK) == CupSensor_1_VDAC8_1_SRC_UDB))
    {
        CupSensor_1_VDAC8_1_backup.data_value = CupSensor_1_VDAC8_1_Data;
    }
}


/*******************************************************************************
* Function Name: CupSensor_1_VDAC8_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void CupSensor_1_VDAC8_1_RestoreConfig(void) 
{
    if (!((CupSensor_1_VDAC8_1_CR1 & CupSensor_1_VDAC8_1_SRC_MASK) == CupSensor_1_VDAC8_1_SRC_UDB))
    {
        if((CupSensor_1_VDAC8_1_Strobe & CupSensor_1_VDAC8_1_STRB_MASK) == CupSensor_1_VDAC8_1_STRB_EN)
        {
            CupSensor_1_VDAC8_1_Strobe &= (uint8)(~CupSensor_1_VDAC8_1_STRB_MASK);
            CupSensor_1_VDAC8_1_Data = CupSensor_1_VDAC8_1_backup.data_value;
            CupSensor_1_VDAC8_1_Strobe |= CupSensor_1_VDAC8_1_STRB_EN;
        }
        else
        {
            CupSensor_1_VDAC8_1_Data = CupSensor_1_VDAC8_1_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: CupSensor_1_VDAC8_1_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  CupSensor_1_VDAC8_1_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void CupSensor_1_VDAC8_1_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(CupSensor_1_VDAC8_1_ACT_PWR_EN == (CupSensor_1_VDAC8_1_PWRMGR & CupSensor_1_VDAC8_1_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        CupSensor_1_VDAC8_1_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        CupSensor_1_VDAC8_1_backup.enableState = 0u;
    }
    
    CupSensor_1_VDAC8_1_Stop();
    CupSensor_1_VDAC8_1_SaveConfig();
}


/*******************************************************************************
* Function Name: CupSensor_1_VDAC8_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  CupSensor_1_VDAC8_1_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CupSensor_1_VDAC8_1_Wakeup(void) 
{
    CupSensor_1_VDAC8_1_RestoreConfig();
    
    if(CupSensor_1_VDAC8_1_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        CupSensor_1_VDAC8_1_Enable();

        /* Restore the data register */
        CupSensor_1_VDAC8_1_SetValue(CupSensor_1_VDAC8_1_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
