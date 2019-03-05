/***************************************************************************
* File Name: CupSensor_1_DMA_Filter_to_DAC_dma.c  
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
#include <CupSensor_1_DMA_Filter_to_DAC_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* CupSensor_1_DMA_Filter_to_DAC__DRQ_CTL_REG
* 
* 
* CupSensor_1_DMA_Filter_to_DAC__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* CupSensor_1_DMA_Filter_to_DAC__NUMBEROF_TDS
* 
* Priority of this channel.
* CupSensor_1_DMA_Filter_to_DAC__PRIORITY
* 
* True if CupSensor_1_DMA_Filter_to_DAC_TERMIN_SEL is used.
* CupSensor_1_DMA_Filter_to_DAC__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* CupSensor_1_DMA_Filter_to_DAC__TERMIN_SEL
* 
* 
* True if CupSensor_1_DMA_Filter_to_DAC_TERMOUT0_SEL is used.
* CupSensor_1_DMA_Filter_to_DAC__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* CupSensor_1_DMA_Filter_to_DAC__TERMOUT0_SEL
* 
* 
* True if CupSensor_1_DMA_Filter_to_DAC_TERMOUT1_SEL is used.
* CupSensor_1_DMA_Filter_to_DAC__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* CupSensor_1_DMA_Filter_to_DAC__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of CupSensor_1_DMA_Filter_to_DAC dma channel */
uint8 CupSensor_1_DMA_Filter_to_DAC_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 CupSensor_1_DMA_Filter_to_DAC_DmaInitalize
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
uint8 CupSensor_1_DMA_Filter_to_DAC_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    CupSensor_1_DMA_Filter_to_DAC_DmaHandle = (uint8)CupSensor_1_DMA_Filter_to_DAC__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(CupSensor_1_DMA_Filter_to_DAC_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)CupSensor_1_DMA_Filter_to_DAC__TERMOUT0_SEL,
                                  (uint8)CupSensor_1_DMA_Filter_to_DAC__TERMOUT1_SEL,
                                  (uint8)CupSensor_1_DMA_Filter_to_DAC__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(CupSensor_1_DMA_Filter_to_DAC_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(CupSensor_1_DMA_Filter_to_DAC_DmaHandle, (uint8)CupSensor_1_DMA_Filter_to_DAC__PRIORITY);
    
    return CupSensor_1_DMA_Filter_to_DAC_DmaHandle;
}

/*********************************************************************
* Function Name: void CupSensor_1_DMA_Filter_to_DAC_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with CupSensor_1_DMA_Filter_to_DAC.
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
void CupSensor_1_DMA_Filter_to_DAC_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(CupSensor_1_DMA_Filter_to_DAC_DmaHandle);
}

