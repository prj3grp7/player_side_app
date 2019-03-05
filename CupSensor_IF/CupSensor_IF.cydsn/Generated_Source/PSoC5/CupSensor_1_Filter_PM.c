/*******************************************************************************
* File Name: CupSensor_1_Filter_PM.c
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

#include "CupSensor_1_Filter_PVT.h"

static CupSensor_1_Filter_backupStruct  CupSensor_1_Filter_backup = 
{
    CupSensor_1_Filter_DISABLED,
    CupSensor_1_Filter_RUN_MASK,
    
};


/*******************************************************************************
* Function Name: CupSensor_1_Filter_SaveConfig
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
*  CupSensor_1_Filter_backup:  This global structure variable is used to store 
*  configuration registers which are non retention whenever user wants to go 
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void CupSensor_1_Filter_SaveConfig(void) 
{
    CupSensor_1_Filter_backup.sr = CupSensor_1_Filter_SR_REG;
    CupSensor_1_Filter_backup.sema = CupSensor_1_Filter_SEMA_REG;

    /* Put DFB RAM on the bus */
    CupSensor_1_Filter_RAM_DIR_REG = CupSensor_1_Filter_RAM_DIR_BUS;

    /* Save the ACU RAM as this is not retension */
    (void)memcpy(CupSensor_1_Filter_backup.saveAcu,
        CupSensor_1_Filter_ACU_RAM, CupSensor_1_Filter_ACU_RAM_SIZE); 

    /* Take DFB RAM off the bus */
    CupSensor_1_Filter_RAM_DIR_REG = CupSensor_1_Filter_RAM_DIR_DFB;
}


/*******************************************************************************
* Function Name: CupSensor_1_Filter_RestoreConfig
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
*  CupSensor_1_Filter_backup:  This global structure variable is used to restore 
*  configuration registers which are non retention whenever user wants to switch 
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void CupSensor_1_Filter_RestoreConfig(void) 
{
    CupSensor_1_Filter_SR_REG = CupSensor_1_Filter_backup.sr;
    CupSensor_1_Filter_SEMA_REG = CupSensor_1_Filter_backup.sema;
    
    /* Power on DFB before initializing the RAMs */
    CupSensor_1_Filter_PM_ACT_CFG_REG |= CupSensor_1_Filter_PM_ACT_MSK;

    /* Put DFB RAM on the bus */
    CupSensor_1_Filter_RAM_DIR_REG = CupSensor_1_Filter_RAM_DIR_BUS;

    /* Restore ACU RAM as this is not retension */
    (void)memcpy(CupSensor_1_Filter_ACU_RAM,
        CupSensor_1_Filter_backup.saveAcu, CupSensor_1_Filter_ACU_RAM_SIZE); 

    /* Take DFB RAM off the bus */
    CupSensor_1_Filter_RAM_DIR_REG = CupSensor_1_Filter_RAM_DIR_DFB;
}


/*******************************************************************************
* Function Name: CupSensor_1_Filter_Sleep
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
*  CupSensor_1_Filter_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void CupSensor_1_Filter_Sleep(void) 
{
    /* Save Filter enable state */
    if(CupSensor_1_Filter_PM_ACT_MSK == (CupSensor_1_Filter_PM_ACT_CFG_REG & CupSensor_1_Filter_PM_ACT_MSK))
    {
        /* Component is enabled */
        CupSensor_1_Filter_backup.enableState = CupSensor_1_Filter_ENABLED;
    }
    else
    {
        /* Component is disabled */
        CupSensor_1_Filter_backup.enableState = CupSensor_1_Filter_DISABLED;
    }

    /* Save the configuration */
    CupSensor_1_Filter_SaveConfig();
    
    /* Stop the component */
    CupSensor_1_Filter_Stop();
}


/*******************************************************************************
* Function Name: CupSensor_1_Filter_Wakeup
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
*  CupSensor_1_Filter_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void CupSensor_1_Filter_Wakeup(void) 
{
    /* Restore the configuration */
    CupSensor_1_Filter_RestoreConfig();
    
    /* Enable's the component operation */
    if(CupSensor_1_Filter_backup.enableState == CupSensor_1_Filter_ENABLED)
    {
        CupSensor_1_Filter_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
