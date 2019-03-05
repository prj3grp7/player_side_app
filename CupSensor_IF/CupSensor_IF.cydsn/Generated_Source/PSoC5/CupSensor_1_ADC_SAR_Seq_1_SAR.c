/*******************************************************************************
* File Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the Successive
*  approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR.h"

#if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_INTERNAL_CLK)
    #include "``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_theACLK.h"
#endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_INTERNAL_CLK */


/***************************************
* Forward function references
***************************************/
static void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CalcGain(uint8 resolution);


/***************************************
* Global data allocation
***************************************/
uint8 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_initVar = 0u;
volatile int16 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_offset;
volatile int16 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPerVolt;     /* Obsolete Gain compensation */
volatile int32 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPer10Volt;   /* Gain compensation */
volatile int16 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_shift;


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Start() sets the initVar variable, calls the
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Init() function, and then calls the
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_initVar variable is used to indicate when/if initial
*  configuration of this component has happened. The variable is initialized to
*  zero and set to 1 the first time ADC_Start() is called. This allows for
*  component Re-Start without re-initialization in all subsequent calls to the
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Start() routine.
*  If re-initialization of the component is required the variable should be set
*  to zero before call of ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Start() routine, or the user may call
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Init() and ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Enable() as done in the
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Start() routine.
*
* Side Effect:
*  If the initVar variable is already set, this function only calls the
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Enable() function.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Start(void)
{

    /* If not Initialized then initialize all required hardware and software */
    if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_initVar == 0u)
    {
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Init();
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_initVar = 1u;
    }
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Enable();
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_offset variable is initialized to 0.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Init(void)
{

    /* This is only valid if there is an internal clock */
    #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_INTERNAL_CLK)
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_theACLK_SetMode(CYCLK_DUTY);
    #endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_INTERNAL_CLK */

    #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_IRQ_REMOVE == 0u)
        /* Start and set interrupt vector */
        CyIntSetPriority(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_INTC_NUMBER, ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_INTC_PRIOR_NUMBER);
        (void)CyIntSetVector(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_INTC_NUMBER, &``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ISR);
    #endif   /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_IRQ_REMOVE */

    /* Enable IRQ mode*/
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR1_REG |= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_IRQ_MASK_EN | ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_IRQ_MODE_EDGE;

    /*Set SAR ADC resolution ADC */
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SetResolution(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RESOLUTION);
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_offset = 0;
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Enable
********************************************************************************
*
* Summary:
*  Enables the reference, clock and power for SAR ADC.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Enable(void)
{
    uint8 tmpReg;
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Enable the SAR ADC block in Active Power Mode */
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_PWRMGR_SAR_REG |= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ACT_PWR_SAR_EN;

     /* Enable the SAR ADC in Standby Power Mode*/
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_STBY_PWRMGR_SAR_REG |= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_STBY_PWR_SAR_EN;

    /* This is only valid if there is an internal clock */
    #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_INTERNAL_CLK)
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_PWRMGR_CLK_REG |= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ACT_PWR_CLK_EN;
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_STBY_PWRMGR_CLK_REG |= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_STBY_PWR_CLK_EN;
    #endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_INTERNAL_CLK */

    /* Enable VCM buffer and Enable Int Ref Amp */
    tmpReg = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR3_REG;
    tmpReg |= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_EN_BUF_VCM_EN;
    /* PD_BUF_VREF is OFF in External reference or Vdda reference mode */
    #if((``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_REFERENCE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__EXT_REF) || \
        (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VNEG_VDDA_DIFF))
        tmpReg &= (uint8)~``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_EN_BUF_VREF_EN;
    #else /* In INTREF or INTREF Bypassed this buffer is ON */
        tmpReg |= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_EN_BUF_VREF_EN;
    #endif /* ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_REFERENCE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__EXT_REF */
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR3_REG = tmpReg;

    /* Set reference for ADC */
    #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VNEG_VDDA_DIFF)
        #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_REFERENCE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__EXT_REF)
            ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR6_REG = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_INT_BYPASS_EXT_VREF; /* S2 */
        #else /* Internal Vdda reference or obsolete bypass mode */
            ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR6_REG = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_VDDA_VREF;           /* S7 */
        #endif /* ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_REFERENCE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__EXT_REF */
    #else  /* Reference goes through internal buffer */
        #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_REFERENCE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__INT_REF_NOT_BYPASSED)
            ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR6_REG = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_INT_VREF;            /* S3 + S4 */
        #else /* INTREF Bypassed of External */
            ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR6_REG = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_INT_BYPASS_EXT_VREF; /* S2 */
        #endif /* ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_REFERENCE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__INT_REF_NOT_BYPASSED */
    #endif /* VNEG_VDDA_DIFF */

    /* Low non-overlap delay for sampling clock signals (for 1MSPS) */
    #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_HIGH_POWER_PULSE == 0u) /* MinPulseWidth <= 50 ns */
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR5_REG &= (uint8)~``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_DLY_INC;
    #else /* Set High non-overlap delay for sampling clock signals (for <500KSPS)*/
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR5_REG |= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_DLY_INC;
    #endif /* ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_HIGH_POWER_PULSE == 0u */

    /* Increase comparator latch enable delay by 20%, 
    *  Increase comparator bias current by 30% without impacting delaysDelay 
    *  Default for 1MSPS) 
    */
    #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_HIGH_POWER_PULSE == 0u)    /* MinPulseWidth <= 50 ns */
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR5_REG |= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_SEL_CSEL_DFT_CHAR;
    #else /* for <500ksps */
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR5_REG &= (uint8)~``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_SEL_CSEL_DFT_CHAR;
    #endif /* ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_HIGH_POWER_PULSE == 0u */

    /* Set default power and other configurations for control register 0 in multiple lines */
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR0_REG = (uint8)((uint8)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_POWER << ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_POWER_SHIFT)
    /* SAR_HIZ_CLEAR:   Should not be used for LP */
    #if ((CY_PSOC5LP) || (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_REFERENCE != ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__EXT_REF))
        | ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_HIZ_CLEAR
    #endif /* SAR_HIZ_CLEAR */
    /*Set Convertion mode */
    #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_CONV_MODE != ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__FREE_RUNNING)      /* If triggered mode */
        | ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_MX_SOF_UDB           /* source: UDB */
        | ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_SOF_MODE_EDGE        /* Set edge-sensitive sof source */
    #endif /* ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_CONV_MODE */
    ; /* end of multiple line initialization */

    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_TR0_REG = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CAP_TRIM_2;

    /* Enable clock for SAR ADC*/
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CLK_REG |= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_MX_CLK_EN;

    CyDelayUs(10u); /* The block is ready to use 10 us after the enable signal is set high. */

    #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_IRQ_REMOVE == 0u)
        /* Clear a pending interrupt */
        CyIntClearPending(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_INTC_NUMBER);
    #endif   /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_IRQ_REMOVE */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Stop
********************************************************************************
*
* Summary:
*  Stops ADC conversions and puts the ADC into its lowest power mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_Stop(void)
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Stop all conversions */
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR0_REG &= (uint8)~``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_SOF_START_CONV;
    /* Disable the SAR ADC block in Active Power Mode */
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_PWRMGR_SAR_REG &= (uint8)~``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ACT_PWR_SAR_EN;
    /* Disable the SAR ADC in Standby Power Mode */
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_STBY_PWRMGR_SAR_REG &= (uint8)~``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_STBY_PWR_SAR_EN;

    /* This is only valid if there is an internal clock */
    #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_INTERNAL_CLK)
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_PWRMGR_CLK_REG &= (uint8)~``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_ACT_PWR_CLK_EN;
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_STBY_PWRMGR_CLK_REG &= (uint8)~``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_STBY_PWR_CLK_EN;
    #endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_INTERNAL_CLK */

    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SetPower
********************************************************************************
*
* Summary:
*  Sets the operational power of the ADC. You should use the higher power
*  settings with faster clock speeds.
*
* Parameters:
*  power:  Power setting for ADC
*  0 ->    Normal
*  1 ->    Medium power
*  2 ->    1.25 power
*  3 ->    Minimum power.
*
* Return:
*  None.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SetPower(uint8 power)
{
    uint8 tmpReg;

    /* mask off invalid power settings */
    power &= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_API_POWER_MASK;

    /* Set Power parameter  */
    tmpReg = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR0_REG & (uint8)~``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_POWER_MASK;
    tmpReg |= (uint8)(power << ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_POWER_SHIFT);
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR0_REG = tmpReg;
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SetResolution
********************************************************************************
*
* Summary:
*  Sets the Relution of the SAR.
*
* Parameters:
*  resolution:
*  12 ->    RES12
*  10 ->    RES10
*  8  ->    RES8
*
* Return:
*  None.
*
* Side Effects:
*  The ADC resolution cannot be changed during a conversion cycle. The
*  recommended best practice is to stop conversions with
*  ADC_StopConvert(), change the resolution, then restart the
*  conversions with ADC_StartConvert().
*  If you decide not to stop conversions before calling this API, you
*  should use ADC_IsEndConversion() to wait until conversion is complete
*  before changing the resolution.
*  If you call ADC_SetResolution() during a conversion, the resolution will
*  not be changed until the current conversion is complete. Data will not be
*  available in the new resolution for another 6 + "New Resolution(in bits)"
*  clock cycles.
*  You may need add a delay of this number of clock cycles after
*  ADC_SetResolution() is called before data is valid again.
*  Affects ADC_CountsTo_Volts(), ADC_CountsTo_mVolts(), and
*  ADC_CountsTo_uVolts() by calculating the correct conversion between ADC
*  counts and the applied input voltage. Calculation depends on resolution,
*  input range, and voltage reference.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SetResolution(uint8 resolution)
{
    uint8 tmpReg;

    /* Set SAR ADC resolution and sample width: 18 conversion cycles at 12bits + 1 gap */
    switch (resolution)
    {
        case (uint8)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__BITS_12:
            tmpReg = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_RESOLUTION_12BIT | ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_SAMPLE_WIDTH;
            break;
        case (uint8)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__BITS_10:
            tmpReg = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_RESOLUTION_10BIT | ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_SAMPLE_WIDTH;
            break;
        case (uint8)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__BITS_8:
            tmpReg = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_RESOLUTION_8BIT | ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_SAMPLE_WIDTH;
            break;
        default:
            tmpReg = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_RESOLUTION_12BIT | ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_SAMPLE_WIDTH;
            /* Halt CPU in debug mode if resolution is out of valid range */
            CYASSERT(0u != 0u);
            break;
    }
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR2_REG = tmpReg;

     /* Calculate gain for convert counts to volts */
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CalcGain(resolution);
}


#if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_CONV_MODE != ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__HARDWARE_TRIGGER)


    /*******************************************************************************
    * Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_StartConvert
    ********************************************************************************
    *
    * Summary:
    *  Forces the ADC to initiate a conversion. In free-running mode, the ADC runs
    *  continuously. In software trigger mode, the function also acts as a software
    *  version of the SOC and every conversion must be triggered by
    *  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_StartConvert(). This function is not available when the
    *  Hardware Trigger sample mode is selected.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Forces the ADC to initiate a conversion. In Free Running mode, the ADC will
    *  run continuously. In a software trigger mode the function also acts as a
    *  software version of the SOC. Here every conversion has to be triggered by
    *  the routine. This writes into the SOC bit in SAR_CTRL reg.
    *
    * Side Effects:
    *  In a software trigger mode the function switches source for SOF from the
    *  external pin to the internal SOF generation. Application should not call
    *  StartConvert if external source used for SOF.
    *
    *******************************************************************************/
    void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_StartConvert(void)
    {
        #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_CONV_MODE != ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__FREE_RUNNING)  /* If software triggered mode */
            ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR0_REG &= (uint8)~``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_MX_SOF_UDB;   /* source: SOF bit */
        #endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_CONV_MODE */

        /* Start the conversion */
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR0_REG |= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_SOF_START_CONV;
    }


    /*******************************************************************************
    * Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_StopConvert
    ********************************************************************************
    *
    * Summary:
    *  Forces the ADC to stop conversions. If a conversion is currently executing,
    *  that conversion will complete, but no further conversions will occur. This
    *  function is not available when the Hardware Trigger sample mode is selected.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Stops ADC conversion in Free Running mode.
    *
    * Side Effects:
    *  In Software Trigger sample mode, this function sets a software version of the
    *  SOC to low level and switches the SOC source to hardware SOC input.
    *
    *******************************************************************************/
    void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_StopConvert(void)
    {
        /* Stop all conversions */
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR0_REG &= (uint8)~``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_SOF_START_CONV;

        #if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_CONV_MODE != ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__FREE_RUNNING)  /* If software triggered mode */
            /* Return source to UDB for hardware SOF signal */
            ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR0_REG |= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_MX_SOF_UDB;    /* source: UDB */
        #endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_CONV_MODE */

    }

#endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_CONV_MODE != ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__HARDWARE_TRIGGER */


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_IsEndConversion
********************************************************************************
*
* Summary:
*  Immediately returns the status of the conversion or does not return
*  (blocking) until the conversion completes, depending on the retMode
*  parameter.
*
* Parameters:
*  retMode:  Check conversion return mode.
*   ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_RETURN_STATUS: Immediately returns the status. If the
*     value returned is zero, the conversion is not complete, and this function
*     should be retried until a nonzero result is returned.
*   ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_WAIT_FOR_RESULT: Does not return a result until the ADC
*     conversion is complete.
*
* Return:
*  (uint8)  0 =>  The ADC is still calculating the last result.
*           1 =>  The last conversion is complete.
*
* Side Effects:
*  This function reads the end of conversion status, which is cleared on read.
*
*******************************************************************************/
uint8 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_IsEndConversion(uint8 retMode)
{
    uint8 status;

    do
    {
        status = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR1_REG & ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_EOF_1;
    } while ((status != ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_EOF_1) && (retMode == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_WAIT_FOR_RESULT));
    /* If convertion complete, wait until EOF bit released */
    if(status == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_EOF_1)
    {
        /* wait one ADC clock to let the EOC status bit release */
        CyDelayUs(1u);
        /* Do the unconditional read operation of the CSR1 register to make sure the EOC bit has been cleared */
        CY_GET_REG8(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_CSR1_PTR);
    }

    return(status);
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_GetResult8
********************************************************************************
*
* Summary:
*  Returns the result of an 8-bit conversion. If the resolution is set greater
*  than 8 bits, the function returns the LSB of the result.
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_IsEndConversion() should be called to verify that the data
*   sample is ready.
*
* Parameters:
*  None.
*
* Return:
*  The LSB of the last ADC conversion.
*
* Global Variables:
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_shift - used to convert the ADC counts to the 2s
*  compliment form.
*
* Side Effects:
*  Converts the ADC counts to the 2s complement form.
*
*******************************************************************************/
int8 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_GetResult8( void )
{
    return( (int8)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_WRK0_REG - (int8)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_shift);
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_GetResult16
********************************************************************************
*
* Summary:
*  Returns a 16-bit result for a conversion with a result that has a resolution
*  of 8 to 12 bits.
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_IsEndConversion() should be called to verify that the data
*   sample is ready
*
* Parameters:
*  None.
*
* Return:
*  The 16-bit result of the last ADC conversion
*
* Global Variables:
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_shift - used to convert the ADC counts to the 2s
*  compliment form.
*
* Side Effects:
*  Converts the ADC counts to the 2s complement form.
*
*******************************************************************************/
int16 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_GetResult16( void )
{
    uint16 res;

    res = CY_GET_REG16(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_WRK_PTR);

    return( (int16)res - ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_shift );
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SetOffset
********************************************************************************
*
* Summary:
*  Sets the ADC offset, which is used by ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CountsTo_Volts(),
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CountsTo_mVolts(), and ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CountsTo_uVolts()
*  to subtract the offset from the given reading before calculating the voltage
*  conversion.
*
* Parameters:
*  int16: This value is measured when the inputs are shorted or connected to
   the same input voltage.
*
* Return:
*  None.
*
* Global Variables:
*  The ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_offset variable modified. This variable is used for
*  offset calibration purpose.
*  Affects the ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CountsTo_Volts,
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CountsTo_mVolts, ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CountsTo_uVolts functions
*  by subtracting the given offset.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SetOffset(int16 offset)
{
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_offset = offset;
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CalcGain
********************************************************************************
*
* Summary:
*  This function calculates the ADC gain in counts per 10 volt.
*
* Parameters:
*  uint8: resolution
*
* Return:
*  None.
*
* Global Variables:
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_shift variable initialized. This variable is used to
*  convert the ADC counts to the 2s compliment form.
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPer10Volt variable initialized. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
static void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CalcGain( uint8 resolution )
{
    int32 counts;
    #if(!((``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSS_TO_VREF) || \
         (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSSA_TO_VDDA) || \
         (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSSA_TO_VDAC)) )
        uint16 diff_zero;
    #endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE */

    switch (resolution)
    {
        case (uint8)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__BITS_12:
            counts = (int32)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_WRK_MAX_12BIT;
            #if(!((``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSS_TO_VREF) || \
                 (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSSA_TO_VDDA) || \
                 (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSSA_TO_VDAC)) )
                diff_zero = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_DIFF_SHIFT;
            #endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE */
            break;
        case (uint8)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__BITS_10:
            counts = (int32)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_WRK_MAX_10BIT;
            #if(!((``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSS_TO_VREF) || \
                 (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSSA_TO_VDDA) || \
                 (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSSA_TO_VDAC)) )
                diff_zero = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_DIFF_SHIFT >> 2u;
            #endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE */
            break;
        case (uint8)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__BITS_8:
            counts = (int32)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_WRK_MAX_8BIT;
            #if(!((``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSS_TO_VREF) || \
                 (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSSA_TO_VDDA) || \
                 (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSSA_TO_VDAC)) )
                diff_zero = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SAR_DIFF_SHIFT >> 4u;
            #endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE */
            break;
        default: /* Halt CPU in debug mode if resolution is out of valid range */
            counts = 0;
            #if(!((``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSS_TO_VREF) || \
                 (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSSA_TO_VDDA) || \
                 (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSSA_TO_VDAC)) )
                diff_zero = 0u;
            #endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE */
            CYASSERT(0u != 0u);
            break;
    }
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPerVolt = 0; /* Clear obsolete variable */
    /* Calculate gain in counts per 10 volts with rounding */
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPer10Volt = (((counts * ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_10MV_COUNTS) +
                        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_REF_VOLTAGE_MV) / (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_REF_VOLTAGE_MV * 2));

    #if( (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSS_TO_VREF) || \
         (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSSA_TO_VDDA) || \
         (``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE == ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR__VSSA_TO_VDAC) )
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_shift = 0;
    #else
        ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_shift = diff_zero;
    #endif /* End ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_DEFAULT_RANGE */
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SetGain
********************************************************************************
*
* Summary:
*  Sets the ADC gain in counts per volt for the voltage conversion functions
*  that follow. This value is set by default by the reference and input range
*  settings. It should only be used to further calibrate the ADC with a known
*  input or if the ADC is using an external reference.
*
* Parameters:
*  int16 adcGain counts per volt
*
* Return:
*  None.
*
* Global Variables:
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPer10Volt variable modified. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SetGain(int16 adcGain)
{
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPer10Volt = (int32)adcGain * 10;
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SetScaledGain
********************************************************************************
*
* Summary:
*  Sets the ADC gain in counts per 10 volt for the voltage conversion functions
*  that follow. This value is set by default by the reference and input range
*  settings. It should only be used to further calibrate the ADC with a known
*  input or if the ADC is using an external reference.
*
* Parameters:
*  int32 adcGain  counts per 10 volt
*
* Return:
*  None.
*
* Global Variables:
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPer10Volt variable modified. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_SetScaledGain(int32 adcGain)
{
    ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPer10Volt = adcGain;
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  Converts the ADC output to millivolts as a 16-bit integer.
*
* Parameters:
*  int16 adcCounts:  Result from the ADC conversion
*
* Return:
*  int16 Result in mVolts
*
* Global Variables:
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_offset variable used.
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPer10Volt variable used.
*
*******************************************************************************/
int16 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CountsTo_mVolts(int16 adcCounts)
{
    int16 mVolts;
    int32 countsPer10Volt;

    if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPerVolt != 0)
    {   /* Support obsolete method */
        countsPer10Volt = (int32)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPerVolt * 10;
    }
    else
    {
        countsPer10Volt = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPer10Volt;
    }

    /* Subtract ADC offset */
    adcCounts -= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_offset;
    /* Convert to millivolts with rounding */
    mVolts = (int16)( (( (int32)adcCounts * ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_10MV_COUNTS ) + ( (adcCounts > 0) ?
                       (countsPer10Volt / 2) : (-(countsPer10Volt / 2)) )) / countsPer10Volt);

    return( mVolts );
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CountsTo_uVolts
********************************************************************************
*
* Summary:
*  Converts the ADC output to microvolts as a 32-bit integer.
*
* Parameters:
*  int16 adcCounts: Result from the ADC conversion
*
* Return:
*  int32 Result in micro Volts
*
* Global Variables:
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_offset variable used.
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPer10Volt used to convert ADC counts to uVolts.
*
*******************************************************************************/
int32 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CountsTo_uVolts(int16 adcCounts)
{

    int64 uVolts;
    int32 countsPer10Volt;

    if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPerVolt != 0)
    {   /* Support obsolete method */
        countsPer10Volt = (int32)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPerVolt * 10;
    }
    else
    {
        countsPer10Volt = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPer10Volt;
    }

    /* Subtract ADC offset */
    adcCounts -= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_offset;
    /* To convert adcCounts to microVolts it is required to be multiplied
    *  on 10 million and later divide on gain in counts per 10V.
    */
    uVolts = (( (int64)adcCounts * ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_10UV_COUNTS ) / countsPer10Volt);

    return((int32) uVolts );
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CountsTo_Volts
********************************************************************************
*
* Summary:
*  Converts the ADC output to volts as a floating-point number.
*
* Parameters:
*  int16 adcCounts: Result from the ADC conversion
*
* Return:
*  float Result in Volts
*
* Global Variables:
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_offset variable used.
*  ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPer10Volt used to convert ADC counts to Volts.
*
*******************************************************************************/
float32 ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_CountsTo_Volts(int16 adcCounts)
{
    float32 volts;
    int32 countsPer10Volt;

    if(``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPerVolt != 0)
    {   /* Support obsolete method */
        countsPer10Volt = (int32)``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPerVolt * 10;
    }
    else
    {
        countsPer10Volt = ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_countsPer10Volt;
    }

    /* Subtract ADC offset */
    adcCounts -= ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_offset;

    volts = ((float32)adcCounts * ``$INSTANCE_NAME`_ADC_SAR_Seq_1_SAR_10V_COUNTS) / (float32)countsPer10Volt;

    return( volts );
}


/* [] END OF FILE */
