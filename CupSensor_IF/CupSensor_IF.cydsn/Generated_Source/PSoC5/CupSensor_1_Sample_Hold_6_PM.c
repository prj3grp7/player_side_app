/*******************************************************************************
* File Name: ``$INSTANCE_NAME`_Sample_Hold_6.c
* Version 1.40
*
* Description:
*  This file provides the power manager source code to the API for 
*  the SAMPLE/TRACK AND HOLD component.
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

#include "``$INSTANCE_NAME`_Sample_Hold_6.h"

static ``$INSTANCE_NAME`_Sample_Hold_6_backupStruct  ``$INSTANCE_NAME`_Sample_Hold_6_backup;


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Sample_Hold_6_SaveConfig
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
void ``$INSTANCE_NAME`_Sample_Hold_6_SaveConfig(void) 
{
    /* Nothing to save before entering into sleep mode as all the registers used 
       here are retention registers. */
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Sample_Hold_6_RestoreConfig
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
void ``$INSTANCE_NAME`_Sample_Hold_6_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Sample_Hold_6_Sleep
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
*  ``$INSTANCE_NAME`_Sample_Hold_6_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Sample_Hold_6_Sleep(void) 
{
    /* Save TIA enable state */
    if((``$INSTANCE_NAME`_Sample_Hold_6_PM_ACT_CFG_REG & ``$INSTANCE_NAME`_Sample_Hold_6_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        ``$INSTANCE_NAME`_Sample_Hold_6_backup.enableState = 1u;
        /* Stop the configuration */
        ``$INSTANCE_NAME`_Sample_Hold_6_Stop();
    }
    else
    {
        /* Component is disabled */
        ``$INSTANCE_NAME`_Sample_Hold_6_backup.enableState = 0u;
    }
    /* Saves the user configuration */
    ``$INSTANCE_NAME`_Sample_Hold_6_SaveConfig();
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Sample_Hold_6_Wakeup
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
*  ``$INSTANCE_NAME`_Sample_Hold_6_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Sample_Hold_6_Wakeup(void) 
{
    /* Restore the user configuration */
    ``$INSTANCE_NAME`_Sample_Hold_6_RestoreConfig();
    
    /* Enable's the component operation */
    if(``$INSTANCE_NAME`_Sample_Hold_6_backup.enableState == 1u)
    {
        ``$INSTANCE_NAME`_Sample_Hold_6_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
