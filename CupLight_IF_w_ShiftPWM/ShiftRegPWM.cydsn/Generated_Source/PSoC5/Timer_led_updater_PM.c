/*******************************************************************************
* File Name: Timer_led_updater_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_led_updater.h"

static Timer_led_updater_backupStruct Timer_led_updater_backup;


/*******************************************************************************
* Function Name: Timer_led_updater_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_led_updater_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_led_updater_SaveConfig(void) 
{
    #if (!Timer_led_updater_UsingFixedFunction)
        Timer_led_updater_backup.TimerUdb = Timer_led_updater_ReadCounter();
        Timer_led_updater_backup.InterruptMaskValue = Timer_led_updater_STATUS_MASK;
        #if (Timer_led_updater_UsingHWCaptureCounter)
            Timer_led_updater_backup.TimerCaptureCounter = Timer_led_updater_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_led_updater_UDB_CONTROL_REG_REMOVED)
            Timer_led_updater_backup.TimerControlRegister = Timer_led_updater_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_led_updater_RestoreConfig
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
*  Timer_led_updater_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_led_updater_RestoreConfig(void) 
{   
    #if (!Timer_led_updater_UsingFixedFunction)

        Timer_led_updater_WriteCounter(Timer_led_updater_backup.TimerUdb);
        Timer_led_updater_STATUS_MASK =Timer_led_updater_backup.InterruptMaskValue;
        #if (Timer_led_updater_UsingHWCaptureCounter)
            Timer_led_updater_SetCaptureCount(Timer_led_updater_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_led_updater_UDB_CONTROL_REG_REMOVED)
            Timer_led_updater_WriteControlRegister(Timer_led_updater_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_led_updater_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_led_updater_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_led_updater_Sleep(void) 
{
    #if(!Timer_led_updater_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_led_updater_CTRL_ENABLE == (Timer_led_updater_CONTROL & Timer_led_updater_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_led_updater_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_led_updater_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_led_updater_Stop();
    Timer_led_updater_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_led_updater_Wakeup
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
*  Timer_led_updater_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_led_updater_Wakeup(void) 
{
    Timer_led_updater_RestoreConfig();
    #if(!Timer_led_updater_UDB_CONTROL_REG_REMOVED)
        if(Timer_led_updater_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_led_updater_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
