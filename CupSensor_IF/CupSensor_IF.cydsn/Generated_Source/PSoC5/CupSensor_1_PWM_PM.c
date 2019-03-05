/*******************************************************************************
* File Name: ``$INSTANCE_NAME`_PWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "``$INSTANCE_NAME`_PWM.h"

static ``$INSTANCE_NAME`_PWM_backupStruct ``$INSTANCE_NAME`_PWM_backup;


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ``$INSTANCE_NAME`_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_PWM_SaveConfig(void) 
{

    #if(!``$INSTANCE_NAME`_PWM_UsingFixedFunction)
        #if(!``$INSTANCE_NAME`_PWM_PWMModeIsCenterAligned)
            ``$INSTANCE_NAME`_PWM_backup.PWMPeriod = ``$INSTANCE_NAME`_PWM_ReadPeriod();
        #endif /* (!``$INSTANCE_NAME`_PWM_PWMModeIsCenterAligned) */
        ``$INSTANCE_NAME`_PWM_backup.PWMUdb = ``$INSTANCE_NAME`_PWM_ReadCounter();
        #if (``$INSTANCE_NAME`_PWM_UseStatus)
            ``$INSTANCE_NAME`_PWM_backup.InterruptMaskValue = ``$INSTANCE_NAME`_PWM_STATUS_MASK;
        #endif /* (``$INSTANCE_NAME`_PWM_UseStatus) */

        #if(``$INSTANCE_NAME`_PWM_DeadBandMode == ``$INSTANCE_NAME`_PWM__B_PWM__DBM_256_CLOCKS || \
            ``$INSTANCE_NAME`_PWM_DeadBandMode == ``$INSTANCE_NAME`_PWM__B_PWM__DBM_2_4_CLOCKS)
            ``$INSTANCE_NAME`_PWM_backup.PWMdeadBandValue = ``$INSTANCE_NAME`_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(``$INSTANCE_NAME`_PWM_KillModeMinTime)
             ``$INSTANCE_NAME`_PWM_backup.PWMKillCounterPeriod = ``$INSTANCE_NAME`_PWM_ReadKillTime();
        #endif /* (``$INSTANCE_NAME`_PWM_KillModeMinTime) */

        #if(``$INSTANCE_NAME`_PWM_UseControl)
            ``$INSTANCE_NAME`_PWM_backup.PWMControlRegister = ``$INSTANCE_NAME`_PWM_ReadControlRegister();
        #endif /* (``$INSTANCE_NAME`_PWM_UseControl) */
    #endif  /* (!``$INSTANCE_NAME`_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ``$INSTANCE_NAME`_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_PWM_RestoreConfig(void) 
{
        #if(!``$INSTANCE_NAME`_PWM_UsingFixedFunction)
            #if(!``$INSTANCE_NAME`_PWM_PWMModeIsCenterAligned)
                ``$INSTANCE_NAME`_PWM_WritePeriod(``$INSTANCE_NAME`_PWM_backup.PWMPeriod);
            #endif /* (!``$INSTANCE_NAME`_PWM_PWMModeIsCenterAligned) */

            ``$INSTANCE_NAME`_PWM_WriteCounter(``$INSTANCE_NAME`_PWM_backup.PWMUdb);

            #if (``$INSTANCE_NAME`_PWM_UseStatus)
                ``$INSTANCE_NAME`_PWM_STATUS_MASK = ``$INSTANCE_NAME`_PWM_backup.InterruptMaskValue;
            #endif /* (``$INSTANCE_NAME`_PWM_UseStatus) */

            #if(``$INSTANCE_NAME`_PWM_DeadBandMode == ``$INSTANCE_NAME`_PWM__B_PWM__DBM_256_CLOCKS || \
                ``$INSTANCE_NAME`_PWM_DeadBandMode == ``$INSTANCE_NAME`_PWM__B_PWM__DBM_2_4_CLOCKS)
                ``$INSTANCE_NAME`_PWM_WriteDeadTime(``$INSTANCE_NAME`_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(``$INSTANCE_NAME`_PWM_KillModeMinTime)
                ``$INSTANCE_NAME`_PWM_WriteKillTime(``$INSTANCE_NAME`_PWM_backup.PWMKillCounterPeriod);
            #endif /* (``$INSTANCE_NAME`_PWM_KillModeMinTime) */

            #if(``$INSTANCE_NAME`_PWM_UseControl)
                ``$INSTANCE_NAME`_PWM_WriteControlRegister(``$INSTANCE_NAME`_PWM_backup.PWMControlRegister);
            #endif /* (``$INSTANCE_NAME`_PWM_UseControl) */
        #endif  /* (!``$INSTANCE_NAME`_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_PWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ``$INSTANCE_NAME`_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_PWM_Sleep(void) 
{
    #if(``$INSTANCE_NAME`_PWM_UseControl)
        if(``$INSTANCE_NAME`_PWM_CTRL_ENABLE == (``$INSTANCE_NAME`_PWM_CONTROL & ``$INSTANCE_NAME`_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            ``$INSTANCE_NAME`_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            ``$INSTANCE_NAME`_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (``$INSTANCE_NAME`_PWM_UseControl) */

    /* Stop component */
    ``$INSTANCE_NAME`_PWM_Stop();

    /* Save registers configuration */
    ``$INSTANCE_NAME`_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ``$INSTANCE_NAME`_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_PWM_Wakeup(void) 
{
     /* Restore registers values */
    ``$INSTANCE_NAME`_PWM_RestoreConfig();

    if(``$INSTANCE_NAME`_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        ``$INSTANCE_NAME`_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
