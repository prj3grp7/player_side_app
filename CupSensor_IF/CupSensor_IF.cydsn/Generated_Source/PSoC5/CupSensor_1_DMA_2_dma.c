/***************************************************************************
* File Name: ``$INSTANCE_NAME`_DMA_2_dma.c  
* Version 1.70
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*
*   Note:
*     This module requires the developer to finish or fill in the auto
*     generated funcions and setup the dma channel and TD's.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include <CYLIB.H>
#include <CYDMAC.H>
#include <``$INSTANCE_NAME`_DMA_2_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* ``$INSTANCE_NAME`_DMA_2__DRQ_CTL_REG
* 
* 
* ``$INSTANCE_NAME`_DMA_2__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* ``$INSTANCE_NAME`_DMA_2__NUMBEROF_TDS
* 
* Priority of this channel.
* ``$INSTANCE_NAME`_DMA_2__PRIORITY
* 
* True if ``$INSTANCE_NAME`_DMA_2_TERMIN_SEL is used.
* ``$INSTANCE_NAME`_DMA_2__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* ``$INSTANCE_NAME`_DMA_2__TERMIN_SEL
* 
* 
* True if ``$INSTANCE_NAME`_DMA_2_TERMOUT0_SEL is used.
* ``$INSTANCE_NAME`_DMA_2__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* ``$INSTANCE_NAME`_DMA_2__TERMOUT0_SEL
* 
* 
* True if ``$INSTANCE_NAME`_DMA_2_TERMOUT1_SEL is used.
* ``$INSTANCE_NAME`_DMA_2__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* ``$INSTANCE_NAME`_DMA_2__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of ``$INSTANCE_NAME`_DMA_2 dma channel */
uint8 ``$INSTANCE_NAME`_DMA_2_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 ``$INSTANCE_NAME`_DMA_2_DmaInitalize
**********************************************************************
* Summary:
*   Allocates and initialises a channel of the DMAC to be used by the
*   caller.
*
* Parameters:
*   BurstCount.
*       
*       
*   ReqestPerBurst.
*       
*       
*   UpperSrcAddress.
*       
*       
*   UpperDestAddress.
*       
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL (0xFF) if there are no channels left. 
*
*
*******************************************************************/
uint8 ``$INSTANCE_NAME`_DMA_2_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    ``$INSTANCE_NAME`_DMA_2_DmaHandle = (uint8)``$INSTANCE_NAME`_DMA_2__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(``$INSTANCE_NAME`_DMA_2_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)``$INSTANCE_NAME`_DMA_2__TERMOUT0_SEL,
                                  (uint8)``$INSTANCE_NAME`_DMA_2__TERMOUT1_SEL,
                                  (uint8)``$INSTANCE_NAME`_DMA_2__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(``$INSTANCE_NAME`_DMA_2_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(``$INSTANCE_NAME`_DMA_2_DmaHandle, (uint8)``$INSTANCE_NAME`_DMA_2__PRIORITY);
    
    return ``$INSTANCE_NAME`_DMA_2_DmaHandle;
}

/*********************************************************************
* Function Name: void ``$INSTANCE_NAME`_DMA_2_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with ``$INSTANCE_NAME`_DMA_2.
*
*
* Parameters:
*   void.
*
*
*
* Return:
*   void.
*
*******************************************************************/
void ``$INSTANCE_NAME`_DMA_2_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(``$INSTANCE_NAME`_DMA_2_DmaHandle);
}

