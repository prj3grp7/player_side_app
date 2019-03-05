/*******************************************************************************
* File Name: CupSensor_1_Mixer_PM.c  
* Version 2.0
*
* Description:
*  This file provides the power manager source code to the API for 
*  the MIXER component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "CupSensor_1_Mixer.h"

static CupSensor_1_Mixer_backupStruct  CupSensor_1_Mixer_backup;


/*******************************************************************************
* Function Name: CupSensor_1_Mixer_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*  
* Parameters:  
*  void.
*
* Return: 
*  void.
*
*******************************************************************************/
void CupSensor_1_Mixer_SaveConfig(void) 
{
    /* Nothing to save before entering into sleep mode as all the registers used 
       here are retension registers. */
}


/*******************************************************************************
* Function Name: CupSensor_1_Mixer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void.
*
* Return: 
*  void
*
*******************************************************************************/
void CupSensor_1_Mixer_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************
* Function Name: CupSensor_1_Mixer_Sleep
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
*  CupSensor_1_Mixer_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void CupSensor_1_Mixer_Sleep(void) 
{
    /* Save Mixer enable state */
    if((CupSensor_1_Mixer_PM_ACT_CFG_REG & CupSensor_1_Mixer_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        CupSensor_1_Mixer_backup.enableState = 1u;
        /* Stop the configuration */
        CupSensor_1_Mixer_Stop();
    }
    else
    {
        /* Component is disabled */
        CupSensor_1_Mixer_backup.enableState = 0u;
    }
    /* Saves the user configuration */
    CupSensor_1_Mixer_SaveConfig();
}


/*******************************************************************************
* Function Name: CupSensor_1_Mixer_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  void
*
* Global variables:
*  CupSensor_1_Mixer_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void CupSensor_1_Mixer_Wakeup(void) 
{
    /* Restore the user configuration */
    CupSensor_1_Mixer_RestoreConfig();
    
    /* Enable's the component operation */
    if(CupSensor_1_Mixer_backup.enableState == 1u)
    {
        CupSensor_1_Mixer_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
