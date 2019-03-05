/*******************************************************************************
* File Name: CupSensor_ADC_DelSig_PM.c
* Version 3.30
*
* Description:
*  This file provides the power manager source code to the API for the
*  Delta-Sigma ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CupSensor_ADC_DelSig.h"

static CupSensor_ADC_DelSig_BACKUP_STRUCT CupSensor_ADC_DelSig_backup =
{
    CupSensor_ADC_DelSig_DISABLED,
    CupSensor_ADC_DelSig_CFG1_DEC_CR
};


/*******************************************************************************
* Function Name: CupSensor_ADC_DelSig_SaveConfig
********************************************************************************
*
* Summary:
*  Save the register configuration which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  CupSensor_ADC_DelSig_backup:  This global structure variable is used to store
*  configuration registers which are non retention whenever user wants to go
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void CupSensor_ADC_DelSig_SaveConfig(void) 
{
    CupSensor_ADC_DelSig_backup.deccr = CupSensor_ADC_DelSig_DEC_CR_REG;
}


/*******************************************************************************
* Function Name: CupSensor_ADC_DelSig_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  CupSensor_ADC_DelSig_backup:  This global structure variable is used to restore
*  configuration registers which are non retention whenever user wants to switch
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void CupSensor_ADC_DelSig_RestoreConfig(void) 
{
    CupSensor_ADC_DelSig_DEC_CR_REG = CupSensor_ADC_DelSig_backup.deccr;
}


/*******************************************************************************
* Function Name: CupSensor_ADC_DelSig_Sleep
********************************************************************************
*
* Summary:
*  Stops the operation of the block and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  CupSensor_ADC_DelSig_backup:  The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void CupSensor_ADC_DelSig_Sleep(void) 
{
    /* Save ADC enable state */
    if((CupSensor_ADC_DelSig_ACT_PWR_DEC_EN == (CupSensor_ADC_DelSig_PWRMGR_DEC_REG & CupSensor_ADC_DelSig_ACT_PWR_DEC_EN)) &&
       (CupSensor_ADC_DelSig_ACT_PWR_DSM_EN == (CupSensor_ADC_DelSig_PWRMGR_DSM_REG & CupSensor_ADC_DelSig_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        CupSensor_ADC_DelSig_backup.enableState = CupSensor_ADC_DelSig_ENABLED;
        if((CupSensor_ADC_DelSig_DEC_CR_REG & CupSensor_ADC_DelSig_DEC_START_CONV) != 0u)
        {   
            /* Conversion is started */
            CupSensor_ADC_DelSig_backup.enableState |= CupSensor_ADC_DelSig_STARTED;
        }
		
        /* Stop the configuration */
        CupSensor_ADC_DelSig_Stop();
    }
    else
    {
        /* Component is disabled */
        CupSensor_ADC_DelSig_backup.enableState = CupSensor_ADC_DelSig_DISABLED;
    }

    /* Save the user configuration */
    CupSensor_ADC_DelSig_SaveConfig();
}


/*******************************************************************************
* Function Name: CupSensor_ADC_DelSig_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and enables the power to the block.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  CupSensor_ADC_DelSig_backup:  The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void CupSensor_ADC_DelSig_Wakeup(void) 
{
    /* Restore the configuration */
    CupSensor_ADC_DelSig_RestoreConfig();

    /* Enables the component operation */
    if(CupSensor_ADC_DelSig_backup.enableState != CupSensor_ADC_DelSig_DISABLED)
    {
        CupSensor_ADC_DelSig_Enable();
        if((CupSensor_ADC_DelSig_backup.enableState & CupSensor_ADC_DelSig_STARTED) != 0u)
        {
            CupSensor_ADC_DelSig_StartConvert();
        }
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
