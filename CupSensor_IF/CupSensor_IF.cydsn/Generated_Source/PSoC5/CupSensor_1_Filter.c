/*******************************************************************************
* File Name: CupSensor_1_Filter.c
* Version 2.30
*
* Description:
*  This file provides the API source code for the FILT component.
*
* Note:
*  
*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "CupSensor_1_Filter_PVT.h"


/*******************************************************************************
* FILT component internal variables.
*******************************************************************************/

uint8 CupSensor_1_Filter_initVar = 0x0u;


/*******************************************************************************
* Function Name: CupSensor_1_Filter_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  CupSensor_1_Filter_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void CupSensor_1_Filter_Init(void) 
{
        /* Power on DFB before initializing the RAMs */
    CupSensor_1_Filter_PM_ACT_CFG_REG |= CupSensor_1_Filter_PM_ACT_MSK;

    /* Turn off Run Bit */
    CupSensor_1_Filter_CR_REG &= (uint8)~CupSensor_1_Filter_RUN_MASK;
                
    /* Enable the DFB RAMS */
    CupSensor_1_Filter_RAM_EN_REG = CupSensor_1_Filter_RAM_DIR_BUS;
        
    /* Put DFB RAM on the bus */
    CupSensor_1_Filter_RAM_DIR_REG = CupSensor_1_Filter_RAM_DIR_BUS;
        
    /* Write DFB RAMs */
    /* Control Store RAMs */
    (void)memcpy( CupSensor_1_Filter_CSA_RAM,
        CupSensor_1_Filter_control, CupSensor_1_Filter_CSA_RAM_SIZE); 
    (void)memcpy(CupSensor_1_Filter_CSB_RAM,
        CupSensor_1_Filter_control, CupSensor_1_Filter_CSB_RAM_SIZE); 
    /* CFSM RAM */
    (void)memcpy(CupSensor_1_Filter_CFSM_RAM,
        CupSensor_1_Filter_cfsm, CupSensor_1_Filter_CFSM_RAM_SIZE); 
    /* Data RAMs */
    (void)memcpy(CupSensor_1_Filter_DA_RAM,
        CupSensor_1_Filter_data_a, CupSensor_1_Filter_DA_RAM_SIZE); 
    (void)memcpy(CupSensor_1_Filter_DB_RAM,
        CupSensor_1_Filter_data_b, CupSensor_1_Filter_DB_RAM_SIZE); 
    /* ACU RAM */
    (void)memcpy(CupSensor_1_Filter_ACU_RAM,
        CupSensor_1_Filter_acu, CupSensor_1_Filter_ACU_RAM_SIZE); 

    /* Take DFB RAM off the bus */
    CupSensor_1_Filter_RAM_DIR_REG = CupSensor_1_Filter_RAM_DIR_DFB;

    /* Set up interrupt and DMA events */
    CupSensor_1_Filter_SetInterruptMode(CupSensor_1_Filter_INIT_INTERRUPT_MODE);
    CupSensor_1_Filter_SetDMAMode(CupSensor_1_Filter_INIT_DMA_MODE);
        
    /* Clear any pending interrupts */
    /* Bits [2..0] of this register are readonly. */
    CupSensor_1_Filter_SR_REG = 0xf8u;   
}


/*******************************************************************************
* Function Name: CupSensor_1_Filter_Enable
********************************************************************************
*  
* Summary: 
*  Enables the DFB run bit.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void CupSensor_1_Filter_Enable(void) 
{
    /* Power on DFB in Active mode */
    CupSensor_1_Filter_PM_ACT_CFG_REG |= CupSensor_1_Filter_PM_ACT_MSK;
        
    /* Power on DFB in Alternative Active mode */
    CupSensor_1_Filter_PM_STBY_CFG_REG |= CupSensor_1_Filter_PM_STBY_MSK;

    /* Turn on Run Bit */
    CupSensor_1_Filter_CR_REG |= CupSensor_1_Filter_RUN_MASK;
}


/*******************************************************************************
* Function Name: CupSensor_1_Filter_Start
********************************************************************************
*
* Summary:
*  This method does the prep work necessary to setup DFB.  This includes loading 
*
* Parameters:  
*  void
* 
* Return: 
*  void
*
* Global variables:
*  CupSensor_1_Filter_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
* Note: 
*  Use CupSensor_1_Filter_InterruptConfig to control which events trigger 
*  interrupts in the DFB. 
*
*******************************************************************************/
void CupSensor_1_Filter_Start(void) 
{
     /* If not Initialized then initialize all required hardware and software */
    if(CupSensor_1_Filter_initVar == 0u)
    {
        CupSensor_1_Filter_Init();
        CupSensor_1_Filter_initVar = 1u;
    }

    /* Enable the DFB block */
    CupSensor_1_Filter_Enable();
}


/*******************************************************************************
* Function Name: CupSensor_1_Filter_Stop
********************************************************************************
*
* Summary:
*  Turn off the run bit.  If DMA control is used to feed the channels, allow 
*  arguments to turn one of the TD channels off. 
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void CupSensor_1_Filter_Stop(void) 
{
    CupSensor_1_Filter_CR_REG &= (uint8)~(CupSensor_1_Filter_RUN_MASK);

    /* Power off DFB in Active mode */
    CupSensor_1_Filter_PM_ACT_CFG_REG &= (uint8)~CupSensor_1_Filter_PM_ACT_MSK;
    
    /* Power off DFB in Alternative Active mode */
    CupSensor_1_Filter_PM_STBY_CFG_REG &= (uint8)~CupSensor_1_Filter_PM_STBY_MSK;
}


/*******************************************************************************
* Function Name: CupSensor_1_Filter_Read8
********************************************************************************
*
* Summary:
*  Get the value in one of the DFB Output Holding Registers 
*
* Parameters:  
*  channel:  CupSensor_1_Filter_CHANNEL_A or CupSensor_1_Filter_CHANNEL_B
*            
* Return: 
*  The most significant 8 bits of the current output value sitting in the 
*  selected channel's holding register or 0x00 for invalid channel numbers.
*
*******************************************************************************/
uint8 CupSensor_1_Filter_Read8(uint8 channel) 
{
    uint8 value;

    if (channel == CupSensor_1_Filter_CHANNEL_A)
    {
        value = CupSensor_1_Filter_HOLDAH_REG;
    }
    else if (channel == CupSensor_1_Filter_CHANNEL_B)
    {
        value = CupSensor_1_Filter_HOLDBH_REG;
    }
    else
    {
        value = 0x0u;
    }
    return value;
}


/*******************************************************************************
* Function Name: CupSensor_1_Filter_Read16
********************************************************************************
*
* Summary:
*  Get the value in one of the DFB Output Holding Registers 
*
* Parameters:  
*  channel:  CupSensor_1_Filter_CHANNEL_A or CupSensor_1_Filter_CHANNEL_B
*            
* Return: 
*  The most significant 16 bits of the current output value sitting in the 
*  selected channel's holding register or 0x0000 for invalid channel numbers
*
* Note:
*  Order of the read is important.  On the read of the high byte, the DFB clears
*  the data ready bit.
*
*******************************************************************************/
#if defined(__C51__) || defined(__CX51__) 

    uint16 CupSensor_1_Filter_Read16(uint8 channel) 
    {
        uint16 val;
    
        if (channel == CupSensor_1_Filter_CHANNEL_A)
        {        
            val = CupSensor_1_Filter_HOLDAM_REG;
            val |= (uint16)(CupSensor_1_Filter_HOLDAH_REG) << 8u;
        }
        else if (channel == CupSensor_1_Filter_CHANNEL_B)
        {      
            val = CupSensor_1_Filter_HOLDBM_REG;
            val |= (uint16)CupSensor_1_Filter_HOLDBH_REG << 8u;
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#else

    uint16 CupSensor_1_Filter_Read16(uint8 channel) 
    {
        uint16 val;

        if (channel == CupSensor_1_Filter_CHANNEL_A)
        {        
            val = CupSensor_1_Filter_HOLDA16_REG;
        }
        else if (channel == CupSensor_1_Filter_CHANNEL_B)
        {      
            val = CupSensor_1_Filter_HOLDB16_REG;
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: CupSensor_1_Filter_Read24
********************************************************************************
*
* Summary:
*  Get the value in one of the DFB Output Holding Registers 
*
* Parameters:  
*  channel:  CupSensor_1_Filter_CHANNEL_A or CupSensor_1_Filter_CHANNEL_B
*            
* Return: 
*  The current 24-bit output value sitting in the selected channel's
*  holding register or 0x00000000 for invalid channel numbers
*
* Note:
*  Order of the read is important.  On the read of the high byte, the DFB clears
*  the data ready bit.
*
*******************************************************************************/
#if defined(__C51__) || defined(__CX51__)

    uint32 CupSensor_1_Filter_Read24(uint8 channel) 
    {
        uint32 val;
    
        if (channel == CupSensor_1_Filter_CHANNEL_A)
        {        
            val = CupSensor_1_Filter_HOLDA_REG;
            val |= (uint32)(CupSensor_1_Filter_HOLDAM_REG) << 8u;
            val |= (uint32)(CupSensor_1_Filter_HOLDAH_REG) << 16u;
            
            /* SignExtend */
            if((val & CupSensor_1_Filter_SIGN_BIT) == CupSensor_1_Filter_SIGN_BIT)
            {    
				val |= CupSensor_1_Filter_SIGN_BYTE;
			}
        }
        else if (channel == CupSensor_1_Filter_CHANNEL_B)
        {      
            val = CupSensor_1_Filter_HOLDB_REG;
            val |= (uint32)CupSensor_1_Filter_HOLDBM_REG << 8u;
            val |= (uint32)CupSensor_1_Filter_HOLDBH_REG << 16u;
            
            /* SignExtend */
            if((val & CupSensor_1_Filter_SIGN_BIT) == CupSensor_1_Filter_SIGN_BIT)
            {
				val |= CupSensor_1_Filter_SIGN_BYTE;
			}
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#else

    uint32 CupSensor_1_Filter_Read24(uint8 channel) 
    {
        uint32 val;
         
        if (channel == CupSensor_1_Filter_CHANNEL_A)
        {        
            val = CupSensor_1_Filter_HOLDA24_REG;
        }
        else if (channel == CupSensor_1_Filter_CHANNEL_B)
        {      
            val = CupSensor_1_Filter_HOLDB24_REG;
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: CupSensor_1_Filter_Write8
********************************************************************************
*
* Summary:
*  Set the value in one of the DFB Input Staging Registers 
*
* Parameters:  
*  channel:  Use either CupSensor_1_Filter_CHANNEL_A or 
*            CupSensor_1_Filter_CHANNEL_B as arguments to the function.  
*  sample:   The 8-bit, right justified input sample. 
*
* Return: 
*  void
*
* Note:
*  Order of the write is important.  On the load of the high byte, the DFB sets
*  the input ready bit.
*
*******************************************************************************/
void CupSensor_1_Filter_Write8(uint8 channel, uint8 sample) 
{
    if (channel == CupSensor_1_Filter_CHANNEL_A)
    {
        CupSensor_1_Filter_STAGEAH_REG = sample;
    }
    else if (channel == CupSensor_1_Filter_CHANNEL_B)
    {
        CupSensor_1_Filter_STAGEBH_REG = sample;
    }
	else
	{
		/* No value is loaded on bad channel input */
	}
}


/*******************************************************************************
* Function Name: CupSensor_1_Filter_Write16
********************************************************************************
*
* Summary:
*  Set the value in one of the DFB Input Staging Registers 
*
* Parameters:  
*  channel:  Use either CupSensor_1_Filter_CHANNEL_A or 
*            CupSensor_1_Filter_CHANNEL_B as arguments to the function.  
*  sample:   The 16-bit, right justified input sample. 
*
* Return: 
*  void
*
* Note:
*  Order of the write is important.  On the load of the high byte, the DFB sets
*  the input ready bit.
*
*******************************************************************************/
#if defined(__C51__) || defined(__CX51__)

    void CupSensor_1_Filter_Write16(uint8 channel, uint16 sample) 
    {
        /* Write the STAGE MSB reg last as it signals a complete wrote to the 
           DFB.*/
        if (channel == CupSensor_1_Filter_CHANNEL_A)
        {
            CupSensor_1_Filter_STAGEAM_REG = (uint8)(sample);
            CupSensor_1_Filter_STAGEAH_REG = (uint8)(sample >> 8u);
        }
        else if (channel == CupSensor_1_Filter_CHANNEL_B)
        {
            CupSensor_1_Filter_STAGEBM_REG = (uint8)(sample);
            CupSensor_1_Filter_STAGEBH_REG = (uint8)(sample >> 8u);
        }
        else
		{
			/* No value is loaded on bad channel input */
		}
    }

#else

    void CupSensor_1_Filter_Write16(uint8 channel, uint16 sample) 
    {
        if (channel == CupSensor_1_Filter_CHANNEL_A)
        {
            CupSensor_1_Filter_STAGEA16_REG = sample;
        }
        else if (channel == CupSensor_1_Filter_CHANNEL_B)
        {
            CupSensor_1_Filter_STAGEB16_REG = sample;
        }
        else
		{
			/* No value is loaded on bad channel input */
		}
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: CupSensor_1_Filter_Write24
********************************************************************************
*
* Summary:
*  Set the value in one of the DFB Input Staging Registers 
*
* Parameters:  
*  channel:  Use either CupSensor_1_Filter_CHANNEL_A or 
*            CupSensor_1_Filter_CHANNEL_B as arguments to the function.  
*  sample:   The 24-bit, right justified input sample inside of a uint32. 
*
* Return: 
*  void
*
* Note:
*  Order of the write is important.  On the load of the high byte, the DFB sets
*  the input ready bit.
*
*******************************************************************************/
#if defined(__C51__) || defined(__CX51__)

    void CupSensor_1_Filter_Write24(uint8 channel, uint32 sample) 
    {
        /* Write the STAGE LSB reg last as it signals a complete wrote to 
           the DFB.*/
        if (channel == CupSensor_1_Filter_CHANNEL_A)
        {
            CupSensor_1_Filter_STAGEA_REG  = (uint8)(sample);
            CupSensor_1_Filter_STAGEAM_REG = (uint8)(sample >> 8u);
            CupSensor_1_Filter_STAGEAH_REG = (uint8)(sample >> 16u);
        }
        else if (channel == CupSensor_1_Filter_CHANNEL_B)
        {
            CupSensor_1_Filter_STAGEB_REG = (uint8)(sample);
            CupSensor_1_Filter_STAGEBM_REG = (uint8)(sample >> 8u);
            CupSensor_1_Filter_STAGEBH_REG = (uint8)(sample >> 16u);
        }
        else
		{
			/* No value is loaded on bad channel input */
		}
    }

#else

    void CupSensor_1_Filter_Write24(uint8 channel, uint32 sample) 
    {
        if (channel == CupSensor_1_Filter_CHANNEL_A)
        {
            CupSensor_1_Filter_STAGEA24_REG = sample;
        }
        else if (channel == CupSensor_1_Filter_CHANNEL_B)
        {
            CupSensor_1_Filter_STAGEB24_REG = sample;
        }
        else
		{
			/* No value is loaded on bad channel input */
		}
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: CupSensor_1_Filter_SetCoherency
********************************************************************************
*
* Summary:
*  Sets the DFB coherency register with the user provided input 
*
* Parameters:  
*  channel:  CupSensor_1_Filter_CHANNEL_A or CupSensor_1_Filter_CHANNEL_B
*  byteSelect:  High byte, Middle byte or Low byte as the key coherency byte.
*            
* Return: 
*  None.
*
*******************************************************************************/
void CupSensor_1_Filter_SetCoherency(uint8 channel, uint8 byteSelect) 
{
    if (channel == CupSensor_1_Filter_CHANNEL_A)
    {
        CupSensor_1_Filter_COHER_REG &= 
                (uint8)(~(uint8)(CupSensor_1_Filter_STAGEA_COHER_MASK | CupSensor_1_Filter_HOLDA_COHER_MASK));
        CupSensor_1_Filter_COHER_REG |= byteSelect;
        CupSensor_1_Filter_COHER_REG |= (uint8)((uint8)byteSelect << 4u);
    }
    else if (channel == CupSensor_1_Filter_CHANNEL_B)
    {
        CupSensor_1_Filter_COHER_REG &= 
                (uint8)(~(uint8)(CupSensor_1_Filter_STAGEB_COHER_MASK | CupSensor_1_Filter_HOLDB_COHER_MASK));
        CupSensor_1_Filter_COHER_REG |= (uint8)((uint8)byteSelect << 2u);
        CupSensor_1_Filter_COHER_REG |= (uint8)((uint8)byteSelect << 6u);
    }
    else
    {
        /* Invalid channel value */
    }
}


/*******************************************************************************
* Function Name: CupSensor_1_Filter_SetCoherencyEx
********************************************************************************
* 
* Summary:
*  Configures the DFB coherency register for each of the staging and holding 
*  registers. Allows multiple registers with the same configuration to be set 
*  at the same time. This API should be used when the coherency of the staging 
*  and holding register of a channel is different. 
*
* Parameters:  
*  regSelect: This parameter is used to specify the registers that will undergo
*             the change in coherency. These are maskable and multiple registers
*             with the same configuration can passed by performing an OR 
*             operation on the following definitions. 
*            CupSensor_1_Filter_STAGEA_COHER, 
*            CupSensor_1_Filter_STAGEB_COHER,
*            CupSensor_1_Filter_HOLDA_COHER,
*            CupSensor_1_Filter_HOLDB_COHER.
*  key: The key coherency byte that will be chosen for the register(s).
*       CupSensor_1_Filter_KEY_LOW, 
*       CupSensor_1_Filter_KEY_MID,
*       CupSensor_1_Filter_KEY_HIGH.
*            
* Return: 
*  None.
*
*******************************************************************************/
void CupSensor_1_Filter_SetCoherencyEx(uint8 regSelect, uint8 key) 
{
    uint8 keyReg;
    
    keyReg = (uint8)(key << 2u) | key;
    keyReg |= (uint8)(keyReg << 4u);
    
    CupSensor_1_Filter_COHER_REG &= (uint8)~regSelect;
    CupSensor_1_Filter_COHER_REG |= keyReg & regSelect;
}


/*******************************************************************************
* Function Name: CupSensor_1_Filter_SetDalign
********************************************************************************
* 
* Summary:
*  Configures the DFB dalign register for each of the staging and holding 
*  registers. Allows multiple registers with the same configuration to be set
*  at the same time. 
*
* Parameters:  
*  regSelect: This parameter is used to specify the registers that will undergo
*             the change in data alignment. These are maskable and multiple 
*             registers with the same configuration can passed by performing 
*             an OR operation on the following definitions.
*             CupSensor_1_Filter_STAGEA_DALIGN, 
*             CupSensor_1_Filter_STAGEB_DALIGN,
*             CupSensor_1_Filter_HOLDA_DALIGN,
*             CupSensor_1_Filter_HOLDB_DALIGN.
*  state: The state is use to either enable the data alignment bits for the 
*         corresponding registers or to disable them.
*         CupSensor_1_Filter_ENABLED,
*         CupSensor_1_Filter_DISABLED
*            
* Return: 
*  None.
*
*******************************************************************************/
void CupSensor_1_Filter_SetDalign(uint8 regSelect, uint8 state) 
{    
    if (state == CupSensor_1_Filter_ENABLED)
    {
        CupSensor_1_Filter_DALIGN_REG |= regSelect;
    }
    else if (state == CupSensor_1_Filter_DISABLED)
    {
        CupSensor_1_Filter_DALIGN_REG &= (uint8)(~regSelect);
    }
    else
    {
        /* Invalid state */
    }
}

/* [] END OF FILE */

