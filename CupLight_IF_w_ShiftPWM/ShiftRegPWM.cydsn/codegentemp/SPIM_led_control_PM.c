/*******************************************************************************
* File Name: SPIM_led_control_PM.c
* Version 2.50
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIM_led_control_PVT.h"

static SPIM_led_control_BACKUP_STRUCT SPIM_led_control_backup =
{
    SPIM_led_control_DISABLED,
    SPIM_led_control_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: SPIM_led_control_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPIM_led_control_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_led_control_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPIM_led_control_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_led_control_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPIM_led_control_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_led_control_Sleep(void) 
{
    /* Save components enable state */
    SPIM_led_control_backup.enableState = ((uint8) SPIM_led_control_IS_ENABLED);

    SPIM_led_control_Stop();
}


/*******************************************************************************
* Function Name: SPIM_led_control_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPIM_led_control_backup - used when non-retention registers are restored.
*  SPIM_led_control_txBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_led_control_txBufferRead - modified every function call - resets to
*  zero.
*  SPIM_led_control_rxBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_led_control_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_led_control_Wakeup(void) 
{
    #if(SPIM_led_control_RX_SOFTWARE_BUF_ENABLED)
        SPIM_led_control_rxBufferFull  = 0u;
        SPIM_led_control_rxBufferRead  = 0u;
        SPIM_led_control_rxBufferWrite = 0u;
    #endif /* (SPIM_led_control_RX_SOFTWARE_BUF_ENABLED) */

    #if(SPIM_led_control_TX_SOFTWARE_BUF_ENABLED)
        SPIM_led_control_txBufferFull  = 0u;
        SPIM_led_control_txBufferRead  = 0u;
        SPIM_led_control_txBufferWrite = 0u;
    #endif /* (SPIM_led_control_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    SPIM_led_control_ClearFIFO();

    /* Restore components block enable state */
    if(0u != SPIM_led_control_backup.enableState)
    {
        SPIM_led_control_Enable();
    }
}


/* [] END OF FILE */
