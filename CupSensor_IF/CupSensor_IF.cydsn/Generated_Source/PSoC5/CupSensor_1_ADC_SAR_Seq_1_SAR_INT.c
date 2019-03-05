/*******************************************************************************
* File Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_INT.c
* Version 3.10
*
*  Description:
*    This file contains the code that operates during the ADC_SAR interrupt
*    service routine.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR.h"
#include "cyapicallbacks.h"


/******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START ADC_SYS_VAR`  */

/* `#END`  */

#if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_IRQ_REMOVE == 0u)


    /******************************************************************************
    * Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ISR
    *******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ******************************************************************************/
    CY_ISR( ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ISR )
    {
        #ifdef ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ISR_INTERRUPT_CALLBACK
            ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ISR_InterruptCallback();
        #endif /* ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ISR_INTERRUPT_CALLBACK */          

        
        /************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        *************************************************************************/
          /* `#START MAIN_ADC_ISR`  */

          /* `#END`  */
    }

#endif   /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_IRQ_REMOVE */

/* [] END OF FILE */
