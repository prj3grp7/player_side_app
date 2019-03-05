/*******************************************************************************
* File Name: CupSensor_VDAC8_PM.c  
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

#include "CupSensor_VDAC8.h"

static CupSensor_VDAC8_backupStruct CupSensor_VDAC8_backup;


/*******************************************************************************
* Function Name: CupSensor_VDAC8_SaveConfig
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
void CupSensor_VDAC8_SaveConfig(void) 
{
    if (!((CupSensor_VDAC8_CR1 & CupSensor_VDAC8_SRC_MASK) == CupSensor_VDAC8_SRC_UDB))
    {
        CupSensor_VDAC8_backup.data_value = CupSensor_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: CupSensor_VDAC8_RestoreConfig
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
void CupSensor_VDAC8_RestoreConfig(void) 
{
    if (!((CupSensor_VDAC8_CR1 & CupSensor_VDAC8_SRC_MASK) == CupSensor_VDAC8_SRC_UDB))
    {
        if((CupSensor_VDAC8_Strobe & CupSensor_VDAC8_STRB_MASK) == CupSensor_VDAC8_STRB_EN)
        {
            CupSensor_VDAC8_Strobe &= (uint8)(~CupSensor_VDAC8_STRB_MASK);
            CupSensor_VDAC8_Data = CupSensor_VDAC8_backup.data_value;
            CupSensor_VDAC8_Strobe |= CupSensor_VDAC8_STRB_EN;
        }
        else
        {
            CupSensor_VDAC8_Data = CupSensor_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: CupSensor_VDAC8_Sleep
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
*  CupSensor_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void CupSensor_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(CupSensor_VDAC8_ACT_PWR_EN == (CupSensor_VDAC8_PWRMGR & CupSensor_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        CupSensor_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        CupSensor_VDAC8_backup.enableState = 0u;
    }
    
    CupSensor_VDAC8_Stop();
    CupSensor_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: CupSensor_VDAC8_Wakeup
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
*  CupSensor_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CupSensor_VDAC8_Wakeup(void) 
{
    CupSensor_VDAC8_RestoreConfig();
    
    if(CupSensor_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        CupSensor_VDAC8_Enable();

        /* Restore the data register */
        CupSensor_VDAC8_SetValue(CupSensor_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
