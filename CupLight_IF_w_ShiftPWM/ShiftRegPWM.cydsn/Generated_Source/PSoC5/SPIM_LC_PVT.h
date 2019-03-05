/*******************************************************************************
* File Name: .h
* Version 2.50
*
* Description:
*  This private header file contains internal definitions for the SPIM
*  component. Do not use these definitions directly in your application.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_PVT_SPIM_LC_H)
#define CY_SPIM_PVT_SPIM_LC_H

#include "SPIM_LC.h"


/**********************************
*   Functions with external linkage
**********************************/


/**********************************
*   Variables with external linkage
**********************************/

extern volatile uint8 SPIM_LC_swStatusTx;
extern volatile uint8 SPIM_LC_swStatusRx;

#if(SPIM_LC_TX_SOFTWARE_BUF_ENABLED)
    extern volatile uint8 SPIM_LC_txBuffer[SPIM_LC_TX_BUFFER_SIZE];
    extern volatile uint8 SPIM_LC_txBufferRead;
    extern volatile uint8 SPIM_LC_txBufferWrite;
    extern volatile uint8 SPIM_LC_txBufferFull;
#endif /* (SPIM_LC_TX_SOFTWARE_BUF_ENABLED) */

#if(SPIM_LC_RX_SOFTWARE_BUF_ENABLED)
    extern volatile uint8 SPIM_LC_rxBuffer[SPIM_LC_RX_BUFFER_SIZE];
    extern volatile uint8 SPIM_LC_rxBufferRead;
    extern volatile uint8 SPIM_LC_rxBufferWrite;
    extern volatile uint8 SPIM_LC_rxBufferFull;
#endif /* (SPIM_LC_RX_SOFTWARE_BUF_ENABLED) */

#endif /* CY_SPIM_PVT_SPIM_LC_H */


/* [] END OF FILE */
