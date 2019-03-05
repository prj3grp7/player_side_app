/*******************************************************************************
* File Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "``$INSTANCE_NAME`_ADC_SAR_Seq_1.h"
#include "``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR.h"
#if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_SOURCE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_INTERNAL)
    #include "``$INSTANCE_NAME`_ADC_SAR_Seq_1_IntClock.h"
#endif   /* ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_SOURCE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_INTERNAL */


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_Sleep(void)
{
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Stop();
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Sleep();
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_Disable();

    #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_SOURCE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_INTERNAL)
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_IntClock_Stop();
    #endif   /* ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_SOURCE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_INTERNAL */
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers. This should
*  be called just after awaking from sleep mode
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_Wakeup(void)
{
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Wakeup();
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Enable();

    #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_SOURCE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_INTERNAL)
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_IntClock_Start();
    #endif   /* ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_SOURCE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_CLOCK_INTERNAL */

    /* The block is ready to use 10 us after the SAR enable signal is set high. */
    CyDelayUs(10u);
    
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_Enable();

    #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAMPLE_MODE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAMPLE_MODE_FREE_RUNNING)
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_StartConvert();
    #endif /* (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAMPLE_MODE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAMPLE_MODE_FREE_RUNNING) */

    (void) CY_GET_REG8(``$INSTANCE_NAME`_ADC_SAR_Seq_1_STATUS_PTR);
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current configuration of ADC non-retention registers
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the configuration of ADC non-retention registers
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_RestoreConfig(void)
{

}


/* [] END OF FILE */
