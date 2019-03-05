/*******************************************************************************
* File Name: ``$INSTANCE_NAME`_Sample_Hold_6.c
* Version 1.40
*
* Description:
*  This file provides the source code to the API for the SAMPLE/TRACK AND HOLD 
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "``$INSTANCE_NAME`_Sample_Hold_6.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

uint8 ``$INSTANCE_NAME`_Sample_Hold_6_initVar = 0u;

/* static ``$INSTANCE_NAME`_Sample_Hold_6_backupStruct  ``$INSTANCE_NAME`_Sample_Hold_6_backup; */
#if (CY_PSOC5A)
    static ``$INSTANCE_NAME`_Sample_Hold_6_backupStruct  ``$INSTANCE_NAME`_Sample_Hold_6_P5backup;
#endif /* CY_PSOC5A */



/*******************************************************************************   
* Function Name: ``$INSTANCE_NAME`_Sample_Hold_6_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  ``$INSTANCE_NAME`_Sample_Hold_6_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Sample_Hold_6_Init(void) 
{   
    /* Configure SC Block based on selected Sample/Track type */
    #if (``$INSTANCE_NAME`_Sample_Hold_6_SAMPLE_TRACK_MODE == ``$INSTANCE_NAME`_Sample_Hold_6_SAMPLEANDHOLD) /* Sample and hold mode */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        ``$INSTANCE_NAME`_Sample_Hold_6_CR0_REG = ``$INSTANCE_NAME`_Sample_Hold_6_MODE_SAMPLEANDHOLD;
        
        /* SC Block CR1 */ 
        ``$INSTANCE_NAME`_Sample_Hold_6_CR1_REG = (``$INSTANCE_NAME`_Sample_Hold_6_COMP_4P35PF  |
                                ``$INSTANCE_NAME`_Sample_Hold_6_GAIN_0DB);
        #if(``$INSTANCE_NAME`_Sample_Hold_6_SAMPLE_CLOCK_EDGE == ``$INSTANCE_NAME`_Sample_Hold_6_EDGE_POSITIVENEGATIVE)
            ``$INSTANCE_NAME`_Sample_Hold_6_CR1_REG =  ``$INSTANCE_NAME`_Sample_Hold_6_CR1_REG  | ``$INSTANCE_NAME`_Sample_Hold_6_DIV2_DISABLE ;
        #else
            ``$INSTANCE_NAME`_Sample_Hold_6_CR1_REG =  ``$INSTANCE_NAME`_Sample_Hold_6_CR1_REG  | ``$INSTANCE_NAME`_Sample_Hold_6_DIV2_ENABLE ;
        #endif
         
        #if(``$INSTANCE_NAME`_Sample_Hold_6_VREF_TYPE == ``$INSTANCE_NAME`_Sample_Hold_6_EXTERNAL)
            ``$INSTANCE_NAME`_Sample_Hold_6_CR2_REG = ``$INSTANCE_NAME`_Sample_Hold_6_BIAS_LOW |
                                       ``$INSTANCE_NAME`_Sample_Hold_6_REDC_00 | 
                                       ``$INSTANCE_NAME`_Sample_Hold_6_GNDVREF_DI;
        #else
            ``$INSTANCE_NAME`_Sample_Hold_6_CR2_REG = ``$INSTANCE_NAME`_Sample_Hold_6_BIAS_LOW |
                                       ``$INSTANCE_NAME`_Sample_Hold_6_REDC_00 | 
                                       ``$INSTANCE_NAME`_Sample_Hold_6_GNDVREF_E;
        #endif
    #else
        /* Track and Hold Mode */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        ``$INSTANCE_NAME`_Sample_Hold_6_CR0_REG = ``$INSTANCE_NAME`_Sample_Hold_6_MODE_TRACKANDHOLD; 
        
        /* SC Block CR1 */ 
        ``$INSTANCE_NAME`_Sample_Hold_6_CR1_REG = ``$INSTANCE_NAME`_Sample_Hold_6_COMP_4P35PF  |
                                   ``$INSTANCE_NAME`_Sample_Hold_6_DIV2_ENABLE |
                                   ``$INSTANCE_NAME`_Sample_Hold_6_GAIN_0DB;
                                
        /* SC Block CR2 */
        ``$INSTANCE_NAME`_Sample_Hold_6_CR2_REG = ``$INSTANCE_NAME`_Sample_Hold_6_BIAS_LOW |
                                   ``$INSTANCE_NAME`_Sample_Hold_6_REDC_00 |
                                   ``$INSTANCE_NAME`_Sample_Hold_6_GNDVREF_E;
    #endif /* end if - Sample/Track Type */
    
    /* Enable SC Block clocking */
    ``$INSTANCE_NAME`_Sample_Hold_6_CLK_REG |= ``$INSTANCE_NAME`_Sample_Hold_6_CLK_EN;
    
    /* Set default power */
    ``$INSTANCE_NAME`_Sample_Hold_6_SetPower(``$INSTANCE_NAME`_Sample_Hold_6_INIT_POWER);
}


/*******************************************************************************   
* Function Name: ``$INSTANCE_NAME`_Sample_Hold_6_Enable
********************************************************************************
*
* Summary:
*  Enables the Sample/Track and Hold block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Sample_Hold_6_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(``$INSTANCE_NAME`_Sample_Hold_6_P5backup.enableState == 1u)
        {
            ``$INSTANCE_NAME`_Sample_Hold_6_CR1_REG = ``$INSTANCE_NAME`_Sample_Hold_6_P5backup.scCR1Reg;
            ``$INSTANCE_NAME`_Sample_Hold_6_CR2_REG = ``$INSTANCE_NAME`_Sample_Hold_6_P5backup.scCR2Reg;
            ``$INSTANCE_NAME`_Sample_Hold_6_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */
    
    /* Enable power to SC block in active mode */
    ``$INSTANCE_NAME`_Sample_Hold_6_PM_ACT_CFG_REG |= ``$INSTANCE_NAME`_Sample_Hold_6_ACT_PWR_EN;
    
    /* Enable power to SC block in Alternative active mode */
    ``$INSTANCE_NAME`_Sample_Hold_6_PM_STBY_CFG_REG |= ``$INSTANCE_NAME`_Sample_Hold_6_STBY_PWR_EN;

    ``$INSTANCE_NAME`_Sample_Hold_6_PUMP_CR1_REG |= ``$INSTANCE_NAME`_Sample_Hold_6_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                ``$INSTANCE_NAME`_Sample_Hold_6_BSTCLK_REG &= (uint8)(~``$INSTANCE_NAME`_Sample_Hold_6_BST_CLK_INDEX_MASK);
                ``$INSTANCE_NAME`_Sample_Hold_6_BSTCLK_REG |= ``$INSTANCE_NAME`_Sample_Hold_6_BST_CLK_EN | CyScBoostClk__INDEX;
                ``$INSTANCE_NAME`_Sample_Hold_6_SC_MISC_REG |= ``$INSTANCE_NAME`_Sample_Hold_6_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                ``$INSTANCE_NAME`_Sample_Hold_6_BSTCLK_REG &= (uint8)(~``$INSTANCE_NAME`_Sample_Hold_6_BST_CLK_EN);
                ``$INSTANCE_NAME`_Sample_Hold_6_SC_MISC_REG &= (uint8)(~``$INSTANCE_NAME`_Sample_Hold_6_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Sample_Hold_6_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Sample and Hold with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Sample_Hold_6_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(``$INSTANCE_NAME`_Sample_Hold_6_initVar == 0u)
    {
        ``$INSTANCE_NAME`_Sample_Hold_6_Init();
        ``$INSTANCE_NAME`_Sample_Hold_6_initVar = 1u;
    }
    ``$INSTANCE_NAME`_Sample_Hold_6_Enable();
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Sample_Hold_6_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Sample_Hold_6_Stop(void) 
{   
    /* Disble power to the Amp in Active mode template */
    ``$INSTANCE_NAME`_Sample_Hold_6_PM_ACT_CFG_REG &= (uint8)(~``$INSTANCE_NAME`_Sample_Hold_6_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    ``$INSTANCE_NAME`_Sample_Hold_6_PM_STBY_CFG_REG &= (uint8)(~``$INSTANCE_NAME`_Sample_Hold_6_STBY_PWR_EN);
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            ``$INSTANCE_NAME`_Sample_Hold_6_BSTCLK_REG &= (uint8)(~``$INSTANCE_NAME`_Sample_Hold_6_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((``$INSTANCE_NAME`_Sample_Hold_6_PM_ACT_CFG_REG & ``$INSTANCE_NAME`_Sample_Hold_6_PM_ACT_CFG_MASK) == 0u)
            {
                ``$INSTANCE_NAME`_Sample_Hold_6_SC_MISC_REG &= (uint8)(~``$INSTANCE_NAME`_Sample_Hold_6_PUMP_FORCE);
                ``$INSTANCE_NAME`_Sample_Hold_6_PUMP_CR1_REG &= (uint8)(~``$INSTANCE_NAME`_Sample_Hold_6_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
 
    /* This sets Sample and hold in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        ``$INSTANCE_NAME`_Sample_Hold_6_P5backup.scCR1Reg = ``$INSTANCE_NAME`_Sample_Hold_6_CR1_REG;
        ``$INSTANCE_NAME`_Sample_Hold_6_P5backup.scCR2Reg = ``$INSTANCE_NAME`_Sample_Hold_6_CR2_REG;
        ``$INSTANCE_NAME`_Sample_Hold_6_CR1_REG = 0x00u;
        ``$INSTANCE_NAME`_Sample_Hold_6_CR2_REG = 0x00u;
        ``$INSTANCE_NAME`_Sample_Hold_6_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Sample_Hold_6_SetPower
********************************************************************************
*
* Summary:
*  Set the power of the Sample/Track and Hold.
*
* Parameters:
*  power: Sets power level between (0) and (3) high power
*
* Return:
*  void
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Sample_Hold_6_SetPower(uint8 power) 
{
    uint8 tmpCR;

    /* Sets drive bits in SC Block Control Register 1:  SCxx_CR[1:0] */
    tmpCR = ``$INSTANCE_NAME`_Sample_Hold_6_CR1_REG & (uint8)(~``$INSTANCE_NAME`_Sample_Hold_6_DRIVE_MASK);
    tmpCR |= (power & ``$INSTANCE_NAME`_Sample_Hold_6_DRIVE_MASK);
    ``$INSTANCE_NAME`_Sample_Hold_6_CR1_REG = tmpCR;
}


/* [] END OF FILE */
