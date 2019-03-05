/*******************************************************************************
* File Name: SPIM_LC_PM.c
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

#include "SPIM_LC_PVT.h"

static SPIM_LC_BACKUP_STRUCT SPIM_LC_backup =
{
    SPIM_LC_DISABLED,
    SPIM_LC_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: SPIM_LC_SaveConfig
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
void SPIM_LC_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_LC_RestoreConfig
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
void SPIM_LC_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_LC_Sleep
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
*  SPIM_LC_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_LC_Sleep(void) 
{
    /* Save components enable state */
    SPIM_LC_backup.enableState = ((uint8) SPIM_LC_IS_ENABLED);

    SPIM_LC_Stop();
}


/*******************************************************************************
* Function Name: SPIM_LC_Wakeup
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
*  SPIM_LC_backup - used when non-retention registers are restored.
*  SPIM_LC_txBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_LC_txBufferRead - modified every function call - resets to
*  zero.
*  SPIM_LC_rxBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_LC_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_LC_Wakeup(void) 
{
    #if(SPIM_LC_RX_SOFTWARE_BUF_ENABLED)
        SPIM_LC_rxBufferFull  = 0u;
        SPIM_LC_rxBufferRead  = 0u;
        SPIM_LC_rxBufferWrite = 0u;
    #endif /* (SPIM_LC_RX_SOFTWARE_BUF_ENABLED) */

    #if(SPIM_LC_TX_SOFTWARE_BUF_ENABLED)
        SPIM_LC_txBufferFull  = 0u;
        SPIM_LC_txBufferRead  = 0u;
        SPIM_LC_txBufferWrite = 0u;
    #endif /* (SPIM_LC_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    SPIM_LC_ClearFIFO();

    /* Restore components block enable state */
    if(0u != SPIM_LC_backup.enableState)
    {
        SPIM_LC_Enable();
    }
}


/* [] END OF FILE */
