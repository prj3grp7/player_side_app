/*******************************************************************************
* File Name: ``$INSTANCE_NAME`_Filter_1_PM.c
* Version 2.30
*
* Description:
*  This file provides the power managaer API source code for the FILT component.
*
* Note:
*  
*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "``$INSTANCE_NAME`_Filter_1_PVT.h"

static ``$INSTANCE_NAME`_Filter_1_backupStruct  ``$INSTANCE_NAME`_Filter_1_backup = 
{
    ``$INSTANCE_NAME`_Filter_1_DISABLED,
    ``$INSTANCE_NAME`_Filter_1_RUN_MASK,
    
};


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ``$INSTANCE_NAME`_Filter_1_backup:  This global structure variable is used to store 
*  configuration registers which are non retention whenever user wants to go 
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Filter_1_SaveConfig(void) 
{
    ``$INSTANCE_NAME`_Filter_1_backup.sr = ``$INSTANCE_NAME`_Filter_1_SR_REG;
    ``$INSTANCE_NAME`_Filter_1_backup.sema = ``$INSTANCE_NAME`_Filter_1_SEMA_REG;

    /* Put DFB RAM on the bus */
    ``$INSTANCE_NAME`_Filter_1_RAM_DIR_REG = ``$INSTANCE_NAME`_Filter_1_RAM_DIR_BUS;

    /* Save the ACU RAM as this is not retension */
    (void)memcpy(``$INSTANCE_NAME`_Filter_1_backup.saveAcu,
        ``$INSTANCE_NAME`_Filter_1_ACU_RAM, ``$INSTANCE_NAME`_Filter_1_ACU_RAM_SIZE); 

    /* Take DFB RAM off the bus */
    ``$INSTANCE_NAME`_Filter_1_RAM_DIR_REG = ``$INSTANCE_NAME`_Filter_1_RAM_DIR_DFB;
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_RestoreConfig
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
* Global variables:
*  ``$INSTANCE_NAME`_Filter_1_backup:  This global structure variable is used to restore 
*  configuration registers which are non retention whenever user wants to switch 
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Filter_1_RestoreConfig(void) 
{
    ``$INSTANCE_NAME`_Filter_1_SR_REG = ``$INSTANCE_NAME`_Filter_1_backup.sr;
    ``$INSTANCE_NAME`_Filter_1_SEMA_REG = ``$INSTANCE_NAME`_Filter_1_backup.sema;
    
    /* Power on DFB before initializing the RAMs */
    ``$INSTANCE_NAME`_Filter_1_PM_ACT_CFG_REG |= ``$INSTANCE_NAME`_Filter_1_PM_ACT_MSK;

    /* Put DFB RAM on the bus */
    ``$INSTANCE_NAME`_Filter_1_RAM_DIR_REG = ``$INSTANCE_NAME`_Filter_1_RAM_DIR_BUS;

    /* Restore ACU RAM as this is not retension */
    (void)memcpy(``$INSTANCE_NAME`_Filter_1_ACU_RAM,
        ``$INSTANCE_NAME`_Filter_1_backup.saveAcu, ``$INSTANCE_NAME`_Filter_1_ACU_RAM_SIZE); 

    /* Take DFB RAM off the bus */
    ``$INSTANCE_NAME`_Filter_1_RAM_DIR_REG = ``$INSTANCE_NAME`_Filter_1_RAM_DIR_DFB;
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ``$INSTANCE_NAME`_Filter_1_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Filter_1_Sleep(void) 
{
    /* Save Filter enable state */
    if(``$INSTANCE_NAME`_Filter_1_PM_ACT_MSK == (``$INSTANCE_NAME`_Filter_1_PM_ACT_CFG_REG & ``$INSTANCE_NAME`_Filter_1_PM_ACT_MSK))
    {
        /* Component is enabled */
        ``$INSTANCE_NAME`_Filter_1_backup.enableState = ``$INSTANCE_NAME`_Filter_1_ENABLED;
    }
    else
    {
        /* Component is disabled */
        ``$INSTANCE_NAME`_Filter_1_backup.enableState = ``$INSTANCE_NAME`_Filter_1_DISABLED;
    }

    /* Save the configuration */
    ``$INSTANCE_NAME`_Filter_1_SaveConfig();
    
    /* Stop the component */
    ``$INSTANCE_NAME`_Filter_1_Stop();
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ``$INSTANCE_NAME`_Filter_1_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Filter_1_Wakeup(void) 
{
    /* Restore the configuration */
    ``$INSTANCE_NAME`_Filter_1_RestoreConfig();
    
    /* Enable's the component operation */
    if(``$INSTANCE_NAME`_Filter_1_backup.enableState == ``$INSTANCE_NAME`_Filter_1_ENABLED)
    {
        ``$INSTANCE_NAME`_Filter_1_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
