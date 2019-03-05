/*******************************************************************************
* File Name: CupSensor_TIA_PM.c  
* Version 2.0
*
* Description:
*  This file provides the power management source code to the API for the 
*  TIA component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "CupSensor_TIA.h"

static CupSensor_TIA_BACKUP_STRUCT  CupSensor_TIA_backup;


/*******************************************************************************  
* Function Name: CupSensor_TIA_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
*
* Parameters:
*  CupSensor_TIA_backup - global structure, where configuration registers are
*  stored.
*
* Return:
*  None
*
*******************************************************************************/
void CupSensor_TIA_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: CupSensor_TIA_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None
*
* Return:
*  void
*
*******************************************************************************/
void CupSensor_TIA_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: CupSensor_TIA_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  CupSensor_TIA_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void CupSensor_TIA_Sleep(void) 
{
    /* Save TIA enable state */
    if((CupSensor_TIA_PM_ACT_CFG_REG & CupSensor_TIA_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        CupSensor_TIA_backup.enableState = 1u;
        /* Stop the configuration */
        CupSensor_TIA_Stop();
    }
    else
    {
        /* Component is disabled */
        CupSensor_TIA_backup.enableState = 0u;
    }
    /* Save the configuration */
    CupSensor_TIA_SaveConfig();
}


/*******************************************************************************  
* Function Name: CupSensor_TIA_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  void
*
* Global variables:
*  CupSensor_TIA_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void CupSensor_TIA_Wakeup(void) 
{
    /* Restore the configuration */
    CupSensor_TIA_RestoreConfig();

    /* Enable's the component operation */
    if(CupSensor_TIA_backup.enableState == 1u)
    {
        CupSensor_TIA_Enable();
    } /* Do nothing if component was disabled before */
}


/* [] END OF FILE */
