/*******************************************************************************
* File Name: ``$INSTANCE_NAME`_Filter_1.c
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

#include "``$INSTANCE_NAME`_Filter_1_PVT.h"


/*******************************************************************************
* FILT component internal variables.
*******************************************************************************/

uint8 ``$INSTANCE_NAME`_Filter_1_initVar = 0x0u;


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  ``$INSTANCE_NAME`_Filter_1_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Filter_1_Init(void) 
{
        /* Power on DFB before initializing the RAMs */
    ``$INSTANCE_NAME`_Filter_1_PM_ACT_CFG_REG |= ``$INSTANCE_NAME`_Filter_1_PM_ACT_MSK;

    /* Turn off Run Bit */
    ``$INSTANCE_NAME`_Filter_1_CR_REG &= (uint8)~``$INSTANCE_NAME`_Filter_1_RUN_MASK;
                
    /* Enable the DFB RAMS */
    ``$INSTANCE_NAME`_Filter_1_RAM_EN_REG = ``$INSTANCE_NAME`_Filter_1_RAM_DIR_BUS;
        
    /* Put DFB RAM on the bus */
    ``$INSTANCE_NAME`_Filter_1_RAM_DIR_REG = ``$INSTANCE_NAME`_Filter_1_RAM_DIR_BUS;
        
    /* Write DFB RAMs */
    /* Control Store RAMs */
    (void)memcpy( ``$INSTANCE_NAME`_Filter_1_CSA_RAM,
        ``$INSTANCE_NAME`_Filter_1_control, ``$INSTANCE_NAME`_Filter_1_CSA_RAM_SIZE); 
    (void)memcpy(``$INSTANCE_NAME`_Filter_1_CSB_RAM,
        ``$INSTANCE_NAME`_Filter_1_control, ``$INSTANCE_NAME`_Filter_1_CSB_RAM_SIZE); 
    /* CFSM RAM */
    (void)memcpy(``$INSTANCE_NAME`_Filter_1_CFSM_RAM,
        ``$INSTANCE_NAME`_Filter_1_cfsm, ``$INSTANCE_NAME`_Filter_1_CFSM_RAM_SIZE); 
    /* Data RAMs */
    (void)memcpy(``$INSTANCE_NAME`_Filter_1_DA_RAM,
        ``$INSTANCE_NAME`_Filter_1_data_a, ``$INSTANCE_NAME`_Filter_1_DA_RAM_SIZE); 
    (void)memcpy(``$INSTANCE_NAME`_Filter_1_DB_RAM,
        ``$INSTANCE_NAME`_Filter_1_data_b, ``$INSTANCE_NAME`_Filter_1_DB_RAM_SIZE); 
    /* ACU RAM */
    (void)memcpy(``$INSTANCE_NAME`_Filter_1_ACU_RAM,
        ``$INSTANCE_NAME`_Filter_1_acu, ``$INSTANCE_NAME`_Filter_1_ACU_RAM_SIZE); 

    /* Take DFB RAM off the bus */
    ``$INSTANCE_NAME`_Filter_1_RAM_DIR_REG = ``$INSTANCE_NAME`_Filter_1_RAM_DIR_DFB;

    /* Set up interrupt and DMA events */
    ``$INSTANCE_NAME`_Filter_1_SetInterruptMode(``$INSTANCE_NAME`_Filter_1_INIT_INTERRUPT_MODE);
    ``$INSTANCE_NAME`_Filter_1_SetDMAMode(``$INSTANCE_NAME`_Filter_1_INIT_DMA_MODE);
        
    /* Clear any pending interrupts */
    /* Bits [2..0] of this register are readonly. */
    ``$INSTANCE_NAME`_Filter_1_SR_REG = 0xf8u;   
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_Enable
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
void ``$INSTANCE_NAME`_Filter_1_Enable(void) 
{
    /* Power on DFB in Active mode */
    ``$INSTANCE_NAME`_Filter_1_PM_ACT_CFG_REG |= ``$INSTANCE_NAME`_Filter_1_PM_ACT_MSK;
        
    /* Power on DFB in Alternative Active mode */
    ``$INSTANCE_NAME`_Filter_1_PM_STBY_CFG_REG |= ``$INSTANCE_NAME`_Filter_1_PM_STBY_MSK;

    /* Turn on Run Bit */
    ``$INSTANCE_NAME`_Filter_1_CR_REG |= ``$INSTANCE_NAME`_Filter_1_RUN_MASK;
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_Start
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
*  ``$INSTANCE_NAME`_Filter_1_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
* Note: 
*  Use ``$INSTANCE_NAME`_Filter_1_InterruptConfig to control which events trigger 
*  interrupts in the DFB. 
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Filter_1_Start(void) 
{
     /* If not Initialized then initialize all required hardware and software */
    if(``$INSTANCE_NAME`_Filter_1_initVar == 0u)
    {
        ``$INSTANCE_NAME`_Filter_1_Init();
        ``$INSTANCE_NAME`_Filter_1_initVar = 1u;
    }

    /* Enable the DFB block */
    ``$INSTANCE_NAME`_Filter_1_Enable();
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_Stop
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
void ``$INSTANCE_NAME`_Filter_1_Stop(void) 
{
    ``$INSTANCE_NAME`_Filter_1_CR_REG &= (uint8)~(``$INSTANCE_NAME`_Filter_1_RUN_MASK);

    /* Power off DFB in Active mode */
    ``$INSTANCE_NAME`_Filter_1_PM_ACT_CFG_REG &= (uint8)~``$INSTANCE_NAME`_Filter_1_PM_ACT_MSK;
    
    /* Power off DFB in Alternative Active mode */
    ``$INSTANCE_NAME`_Filter_1_PM_STBY_CFG_REG &= (uint8)~``$INSTANCE_NAME`_Filter_1_PM_STBY_MSK;
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_Read8
********************************************************************************
*
* Summary:
*  Get the value in one of the DFB Output Holding Registers 
*
* Parameters:  
*  channel:  ``$INSTANCE_NAME`_Filter_1_CHANNEL_A or ``$INSTANCE_NAME`_Filter_1_CHANNEL_B
*            
* Return: 
*  The most significant 8 bits of the current output value sitting in the 
*  selected channel's holding register or 0x00 for invalid channel numbers.
*
*******************************************************************************/
uint8 ``$INSTANCE_NAME`_Filter_1_Read8(uint8 channel) 
{
    uint8 value;

    if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_A)
    {
        value = ``$INSTANCE_NAME`_Filter_1_HOLDAH_REG;
    }
    else if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_B)
    {
        value = ``$INSTANCE_NAME`_Filter_1_HOLDBH_REG;
    }
    else
    {
        value = 0x0u;
    }
    return value;
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_Read16
********************************************************************************
*
* Summary:
*  Get the value in one of the DFB Output Holding Registers 
*
* Parameters:  
*  channel:  ``$INSTANCE_NAME`_Filter_1_CHANNEL_A or ``$INSTANCE_NAME`_Filter_1_CHANNEL_B
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

    uint16 ``$INSTANCE_NAME`_Filter_1_Read16(uint8 channel) 
    {
        uint16 val;
    
        if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_A)
        {        
            val = ``$INSTANCE_NAME`_Filter_1_HOLDAM_REG;
            val |= (uint16)(``$INSTANCE_NAME`_Filter_1_HOLDAH_REG) << 8u;
        }
        else if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_B)
        {      
            val = ``$INSTANCE_NAME`_Filter_1_HOLDBM_REG;
            val |= (uint16)``$INSTANCE_NAME`_Filter_1_HOLDBH_REG << 8u;
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#else

    uint16 ``$INSTANCE_NAME`_Filter_1_Read16(uint8 channel) 
    {
        uint16 val;

        if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_A)
        {        
            val = ``$INSTANCE_NAME`_Filter_1_HOLDA16_REG;
        }
        else if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_B)
        {      
            val = ``$INSTANCE_NAME`_Filter_1_HOLDB16_REG;
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_Read24
********************************************************************************
*
* Summary:
*  Get the value in one of the DFB Output Holding Registers 
*
* Parameters:  
*  channel:  ``$INSTANCE_NAME`_Filter_1_CHANNEL_A or ``$INSTANCE_NAME`_Filter_1_CHANNEL_B
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

    uint32 ``$INSTANCE_NAME`_Filter_1_Read24(uint8 channel) 
    {
        uint32 val;
    
        if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_A)
        {        
            val = ``$INSTANCE_NAME`_Filter_1_HOLDA_REG;
            val |= (uint32)(``$INSTANCE_NAME`_Filter_1_HOLDAM_REG) << 8u;
            val |= (uint32)(``$INSTANCE_NAME`_Filter_1_HOLDAH_REG) << 16u;
            
            /* SignExtend */
            if((val & ``$INSTANCE_NAME`_Filter_1_SIGN_BIT) == ``$INSTANCE_NAME`_Filter_1_SIGN_BIT)
            {    
				val |= ``$INSTANCE_NAME`_Filter_1_SIGN_BYTE;
			}
        }
        else if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_B)
        {      
            val = ``$INSTANCE_NAME`_Filter_1_HOLDB_REG;
            val |= (uint32)``$INSTANCE_NAME`_Filter_1_HOLDBM_REG << 8u;
            val |= (uint32)``$INSTANCE_NAME`_Filter_1_HOLDBH_REG << 16u;
            
            /* SignExtend */
            if((val & ``$INSTANCE_NAME`_Filter_1_SIGN_BIT) == ``$INSTANCE_NAME`_Filter_1_SIGN_BIT)
            {
				val |= ``$INSTANCE_NAME`_Filter_1_SIGN_BYTE;
			}
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#else

    uint32 ``$INSTANCE_NAME`_Filter_1_Read24(uint8 channel) 
    {
        uint32 val;
         
        if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_A)
        {        
            val = ``$INSTANCE_NAME`_Filter_1_HOLDA24_REG;
        }
        else if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_B)
        {      
            val = ``$INSTANCE_NAME`_Filter_1_HOLDB24_REG;
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_Write8
********************************************************************************
*
* Summary:
*  Set the value in one of the DFB Input Staging Registers 
*
* Parameters:  
*  channel:  Use either ``$INSTANCE_NAME`_Filter_1_CHANNEL_A or 
*            ``$INSTANCE_NAME`_Filter_1_CHANNEL_B as arguments to the function.  
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
void ``$INSTANCE_NAME`_Filter_1_Write8(uint8 channel, uint8 sample) 
{
    if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_A)
    {
        ``$INSTANCE_NAME`_Filter_1_STAGEAH_REG = sample;
    }
    else if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_B)
    {
        ``$INSTANCE_NAME`_Filter_1_STAGEBH_REG = sample;
    }
	else
	{
		/* No value is loaded on bad channel input */
	}
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_Write16
********************************************************************************
*
* Summary:
*  Set the value in one of the DFB Input Staging Registers 
*
* Parameters:  
*  channel:  Use either ``$INSTANCE_NAME`_Filter_1_CHANNEL_A or 
*            ``$INSTANCE_NAME`_Filter_1_CHANNEL_B as arguments to the function.  
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

    void ``$INSTANCE_NAME`_Filter_1_Write16(uint8 channel, uint16 sample) 
    {
        /* Write the STAGE MSB reg last as it signals a complete wrote to the 
           DFB.*/
        if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_A)
        {
            ``$INSTANCE_NAME`_Filter_1_STAGEAM_REG = (uint8)(sample);
            ``$INSTANCE_NAME`_Filter_1_STAGEAH_REG = (uint8)(sample >> 8u);
        }
        else if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_B)
        {
            ``$INSTANCE_NAME`_Filter_1_STAGEBM_REG = (uint8)(sample);
            ``$INSTANCE_NAME`_Filter_1_STAGEBH_REG = (uint8)(sample >> 8u);
        }
        else
		{
			/* No value is loaded on bad channel input */
		}
    }

#else

    void ``$INSTANCE_NAME`_Filter_1_Write16(uint8 channel, uint16 sample) 
    {
        if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_A)
        {
            ``$INSTANCE_NAME`_Filter_1_STAGEA16_REG = sample;
        }
        else if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_B)
        {
            ``$INSTANCE_NAME`_Filter_1_STAGEB16_REG = sample;
        }
        else
		{
			/* No value is loaded on bad channel input */
		}
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_Write24
********************************************************************************
*
* Summary:
*  Set the value in one of the DFB Input Staging Registers 
*
* Parameters:  
*  channel:  Use either ``$INSTANCE_NAME`_Filter_1_CHANNEL_A or 
*            ``$INSTANCE_NAME`_Filter_1_CHANNEL_B as arguments to the function.  
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

    void ``$INSTANCE_NAME`_Filter_1_Write24(uint8 channel, uint32 sample) 
    {
        /* Write the STAGE LSB reg last as it signals a complete wrote to 
           the DFB.*/
        if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_A)
        {
            ``$INSTANCE_NAME`_Filter_1_STAGEA_REG  = (uint8)(sample);
            ``$INSTANCE_NAME`_Filter_1_STAGEAM_REG = (uint8)(sample >> 8u);
            ``$INSTANCE_NAME`_Filter_1_STAGEAH_REG = (uint8)(sample >> 16u);
        }
        else if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_B)
        {
            ``$INSTANCE_NAME`_Filter_1_STAGEB_REG = (uint8)(sample);
            ``$INSTANCE_NAME`_Filter_1_STAGEBM_REG = (uint8)(sample >> 8u);
            ``$INSTANCE_NAME`_Filter_1_STAGEBH_REG = (uint8)(sample >> 16u);
        }
        else
		{
			/* No value is loaded on bad channel input */
		}
    }

#else

    void ``$INSTANCE_NAME`_Filter_1_Write24(uint8 channel, uint32 sample) 
    {
        if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_A)
        {
            ``$INSTANCE_NAME`_Filter_1_STAGEA24_REG = sample;
        }
        else if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_B)
        {
            ``$INSTANCE_NAME`_Filter_1_STAGEB24_REG = sample;
        }
        else
		{
			/* No value is loaded on bad channel input */
		}
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_SetCoherency
********************************************************************************
*
* Summary:
*  Sets the DFB coherency register with the user provided input 
*
* Parameters:  
*  channel:  ``$INSTANCE_NAME`_Filter_1_CHANNEL_A or ``$INSTANCE_NAME`_Filter_1_CHANNEL_B
*  byteSelect:  High byte, Middle byte or Low byte as the key coherency byte.
*            
* Return: 
*  None.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Filter_1_SetCoherency(uint8 channel, uint8 byteSelect) 
{
    if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_A)
    {
        ``$INSTANCE_NAME`_Filter_1_COHER_REG &= 
                (uint8)(~(uint8)(``$INSTANCE_NAME`_Filter_1_STAGEA_COHER_MASK | ``$INSTANCE_NAME`_Filter_1_HOLDA_COHER_MASK));
        ``$INSTANCE_NAME`_Filter_1_COHER_REG |= byteSelect;
        ``$INSTANCE_NAME`_Filter_1_COHER_REG |= (uint8)((uint8)byteSelect << 4u);
    }
    else if (channel == ``$INSTANCE_NAME`_Filter_1_CHANNEL_B)
    {
        ``$INSTANCE_NAME`_Filter_1_COHER_REG &= 
                (uint8)(~(uint8)(``$INSTANCE_NAME`_Filter_1_STAGEB_COHER_MASK | ``$INSTANCE_NAME`_Filter_1_HOLDB_COHER_MASK));
        ``$INSTANCE_NAME`_Filter_1_COHER_REG |= (uint8)((uint8)byteSelect << 2u);
        ``$INSTANCE_NAME`_Filter_1_COHER_REG |= (uint8)((uint8)byteSelect << 6u);
    }
    else
    {
        /* Invalid channel value */
    }
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_SetCoherencyEx
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
*            ``$INSTANCE_NAME`_Filter_1_STAGEA_COHER, 
*            ``$INSTANCE_NAME`_Filter_1_STAGEB_COHER,
*            ``$INSTANCE_NAME`_Filter_1_HOLDA_COHER,
*            ``$INSTANCE_NAME`_Filter_1_HOLDB_COHER.
*  key: The key coherency byte that will be chosen for the register(s).
*       ``$INSTANCE_NAME`_Filter_1_KEY_LOW, 
*       ``$INSTANCE_NAME`_Filter_1_KEY_MID,
*       ``$INSTANCE_NAME`_Filter_1_KEY_HIGH.
*            
* Return: 
*  None.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Filter_1_SetCoherencyEx(uint8 regSelect, uint8 key) 
{
    uint8 keyReg;
    
    keyReg = (uint8)(key << 2u) | key;
    keyReg |= (uint8)(keyReg << 4u);
    
    ``$INSTANCE_NAME`_Filter_1_COHER_REG &= (uint8)~regSelect;
    ``$INSTANCE_NAME`_Filter_1_COHER_REG |= keyReg & regSelect;
}


/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Filter_1_SetDalign
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
*             ``$INSTANCE_NAME`_Filter_1_STAGEA_DALIGN, 
*             ``$INSTANCE_NAME`_Filter_1_STAGEB_DALIGN,
*             ``$INSTANCE_NAME`_Filter_1_HOLDA_DALIGN,
*             ``$INSTANCE_NAME`_Filter_1_HOLDB_DALIGN.
*  state: The state is use to either enable the data alignment bits for the 
*         corresponding registers or to disable them.
*         ``$INSTANCE_NAME`_Filter_1_ENABLED,
*         ``$INSTANCE_NAME`_Filter_1_DISABLED
*            
* Return: 
*  None.
*
*******************************************************************************/
void ``$INSTANCE_NAME`_Filter_1_SetDalign(uint8 regSelect, uint8 state) 
{    
    if (state == ``$INSTANCE_NAME`_Filter_1_ENABLED)
    {
        ``$INSTANCE_NAME`_Filter_1_DALIGN_REG |= regSelect;
    }
    else if (state == ``$INSTANCE_NAME`_Filter_1_DISABLED)
    {
        ``$INSTANCE_NAME`_Filter_1_DALIGN_REG &= (uint8)(~regSelect);
    }
    else
    {
        /* Invalid state */
    }
}

/* [] END OF FILE */

