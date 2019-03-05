/*******************************************************************************
* File Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_PM.c
* Version 3.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR.h"


/***************************************
* Local data allocation
***************************************/

static ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_BACKUP_STRUCT  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_backup =
{
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DISABLED
};


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Sleep(void)
{
    if((``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_PWRMGR_SAR_REG  & ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ACT_PWR_SAR_EN) != 0u)
    {
        if((``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR0_REG & ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_SOF_START_CONV) != 0u)
        {
            ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_backup.enableState = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ENABLED | ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_STARTED;
        }
        else
        {
            ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_backup.enableState = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ENABLED;
        }
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Stop();
    }
    else
    {
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_backup.enableState = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Sleep() was called. If the component was enabled before the
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Sleep() function was called, the
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Wakeup(void)
{
    if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_backup.enableState != ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DISABLED)
    {
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Enable();
        #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_CONV_MODE != ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__HARDWARE_TRIGGER)
            if((``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_backup.enableState & ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_STARTED) != 0u)
            {
                ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_StartConvert();
            }
        #endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_CONV_MODE != ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
