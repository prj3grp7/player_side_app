/*******************************************************************************
* File Name: CupSensor_TIA.c  
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the TIA User Module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "CupSensor_TIA.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

/* Fixed configuration of SC Block only performed once */
uint8 CupSensor_TIA_initVar = 0u;

#if (CY_PSOC5A)
    static CupSensor_TIA_BACKUP_STRUCT  CupSensor_TIA_P5backup;
#endif /* (CY_PSOC5A) */


/*******************************************************************************   
* Function Name: CupSensor_TIA_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  CupSensor_TIA_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void CupSensor_TIA_Init(void) 
{
    /* Set SC Block Mode to TIA - SCxx_CR0[3:1] */
    CupSensor_TIA_CR0_REG = CupSensor_TIA_MODE_TIA;
    
    /*    Set SC Block CR1 Control Register fields to support TIA mode 
            drive field set by SetPower() API
            compensation Cap - 5.1 pF
            div2 - disable, n/a for TIA mode
            Mixer/PGA Gain - 0db, n/a for TIA mode   */

    CupSensor_TIA_CR1_REG = (CupSensor_TIA_COMP_5P1PF |
                                CupSensor_TIA_DIV2_DISABLE |
                                CupSensor_TIA_GAIN_0DB);


    /*    Set SC Block CR2 Control Register fields to support TIA mode
            Bias - Low
            r20_r40 - 40K, n/a for TIA mode
            redc - set by SetCapFB() API
            rval - set by SetResFB() API
            PGA Ground Ref - disable, n/a for TIA mode    */

    CupSensor_TIA_CR2_REG = (CupSensor_TIA_BIAS_LOW |
                                CupSensor_TIA_R20_40B_40K |
                                CupSensor_TIA_GNDVREF_DI);
                          
    /* Set default resistive feedback value */
    CupSensor_TIA_SetResFB(CupSensor_TIA_INIT_RES_FEEDBACK);
      
    /* Set default capacitive feedback value */
    CupSensor_TIA_SetCapFB(CupSensor_TIA_INIT_CAP_FEEDBACK);

    /* Set default power */
    CupSensor_TIA_SetPower(CupSensor_TIA_INIT_POWER);
}


/*******************************************************************************   
* Function Name: CupSensor_TIA_Enable
********************************************************************************
*
* Summary:
*  Enables the TIA block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void CupSensor_TIA_Enable(void) 
{
	/* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
	#if (CY_PSOC5A)
        if(CupSensor_TIA_P5backup.enableState == 1u)
        {
			CupSensor_TIA_CR1_REG = CupSensor_TIA_P5backup.scCR1Reg;
            CupSensor_TIA_CR2_REG =CupSensor_TIA_P5backup.scCR2Reg;
            CupSensor_TIA_P5backup.enableState = 0u;
        }
    #endif
    /* Enable power to Amp in Active mode */
    CupSensor_TIA_PM_ACT_CFG_REG |= CupSensor_TIA_ACT_PWR_EN;

    /* Enable the power to Amp in Alternative active mode*/
    CupSensor_TIA_PM_STBY_CFG_REG |= CupSensor_TIA_STBY_PWR_EN;
    
    CupSensor_TIA_PUMP_CR1_REG |= CupSensor_TIA_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                CupSensor_TIA_BSTCLK_REG &= (uint8)(~CupSensor_TIA_BST_CLK_INDEX_MASK);
                CupSensor_TIA_BSTCLK_REG |= CupSensor_TIA_BST_CLK_EN | CyScBoostClk__INDEX;
                CupSensor_TIA_SC_MISC_REG |= CupSensor_TIA_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                CupSensor_TIA_BSTCLK_REG &= (uint8)(~CupSensor_TIA_BST_CLK_EN);
                CupSensor_TIA_SC_MISC_REG &= (uint8)(~CupSensor_TIA_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: CupSensor_TIA_Start
********************************************************************************
*
* Summary:
*  The start function initializes the TIA with the default values and enables
*  power to the SC block.
*
* Parameters:
*  void
*
* Return:
*  void 
*
* Global variables:
*  CupSensor_TIA_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
* Theory:
*  Full initialization of the SC Block configuration registers is only perfomed
*  the first time the routine executes - global variable  is used to
*  CupSensor_TIA_initVar is used to indicate that the static configuration 
*  has been completed.
*
*******************************************************************************/
void CupSensor_TIA_Start(void) 
{
    if(CupSensor_TIA_initVar == 0u)
    {
        CupSensor_TIA_initVar = 1u;  
        CupSensor_TIA_Init();
    }

    CupSensor_TIA_Enable();
}


/*******************************************************************************
* Function Name: CupSensor_TIA_Stop
********************************************************************************
*
* Summary: 
*  Disables power to SC block.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void CupSensor_TIA_Stop(void) 
{
     /* Disble power to the Amp in Active mode template*/
    CupSensor_TIA_PM_ACT_CFG_REG &= (uint8)(~CupSensor_TIA_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative active mode template*/
    CupSensor_TIA_PM_STBY_CFG_REG &= (uint8)(~CupSensor_TIA_STBY_PWR_EN);
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            CupSensor_TIA_BSTCLK_REG &= (uint8)(~CupSensor_TIA_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((CupSensor_TIA_PM_ACT_CFG_REG & CupSensor_TIA_PM_ACT_CFG_MASK) == 0u)
            {
                CupSensor_TIA_SC_MISC_REG &= (uint8)(~CupSensor_TIA_PUMP_FORCE);
                CupSensor_TIA_PUMP_CR1_REG &= (uint8)(~CupSensor_TIA_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
    /* This sets TIA in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        CupSensor_TIA_P5backup.scCR1Reg = CupSensor_TIA_CR1_REG;
        CupSensor_TIA_P5backup.scCR2Reg = CupSensor_TIA_CR2_REG;
        CupSensor_TIA_CR1_REG = 0x00u;
        CupSensor_TIA_CR2_REG = 0x00u;
        CupSensor_TIA_P5backup.enableState = 1u;
    #endif /* (CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: CupSensor_TIA_SetPower
********************************************************************************
*
* Summary:
*  Set the drive power of the TIA.
*
* Parameters:
*  Power: Sets power level between (0) and (3) high power.
*
* Return:
*  void
*
*******************************************************************************/
void CupSensor_TIA_SetPower(uint8 power) 
{
    uint8 tmpCR;

    /* Sets drive bits in SC Block Control Register 1:  SCxx_CR[1:0] */
    tmpCR = CupSensor_TIA_CR1_REG & (uint8)(~CupSensor_TIA_DRIVE_MASK);
    tmpCR |= (power & CupSensor_TIA_DRIVE_MASK);
    CupSensor_TIA_CR1_REG = tmpCR;  
}


/*******************************************************************************
* Function Name: CupSensor_TIA_SetResFB
********************************************************************************
*
* Summary:
*  This function sets value for the resistive feedback of the amplifier.
*
* Parameters:
*  res_feedback: specifies resistive feedback value (see header file for gain 
*                values.)
*
* Return:
*  void
*
*******************************************************************************/
void CupSensor_TIA_SetResFB(uint8 res_feedback) 
{
    /* Only set new gain if it is a valid gain */
    if( res_feedback <= CupSensor_TIA_RES_FEEDBACK_MAX)
    {
        /* Clear SCxx_CR2 rval bits - SCxx_CR2[6:4] */
        CupSensor_TIA_CR2_REG &= (uint8)(~CupSensor_TIA_RVAL_MASK);

        /* Set resistive feedback value */
        CupSensor_TIA_CR2_REG |= (uint8)(res_feedback << 4);
    }
}


/*******************************************************************************
* Function Name: CupSensor_TIA_SetCapFB
********************************************************************************
*
* Summary:
*  This function sets the value for the capacitive feedback of the amplifier.
*
* Parameters:
*  cap_feedback: specifies capacitive feedback value (see header file for gain 
*                values.)
*
* Return:
*  void
*
*******************************************************************************/
void CupSensor_TIA_SetCapFB(uint8 cap_feedback) 
{
    /* Only set new gain if it is a valid gain */
    if( cap_feedback <= CupSensor_TIA_CAP_FEEDBACK_MAX)
    {
        /* Clear SCxx_CR2 redc bits -  - CR2[3:2] */
        CupSensor_TIA_CR2_REG &= (uint8)(~CupSensor_TIA_REDC_MASK);

        /* Set redc capacitive feedback value */
        CupSensor_TIA_CR2_REG |= (uint8)(cap_feedback << 2);
    }
}


/* [] END OF FILE */
