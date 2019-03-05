/*******************************************************************************
* File Name: CupSensor_1_ADC_DelSig_AMux.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_CupSensor_1_ADC_DelSig_AMux_H)
#define CY_AMUX_CupSensor_1_ADC_DelSig_AMux_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void CupSensor_1_ADC_DelSig_AMux_Start(void) ;
#define CupSensor_1_ADC_DelSig_AMux_Init() CupSensor_1_ADC_DelSig_AMux_Start()
void CupSensor_1_ADC_DelSig_AMux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void CupSensor_1_ADC_DelSig_AMux_Stop(void); */
/* void CupSensor_1_ADC_DelSig_AMux_Select(uint8 channel); */
/* void CupSensor_1_ADC_DelSig_AMux_Connect(uint8 channel); */
/* void CupSensor_1_ADC_DelSig_AMux_Disconnect(uint8 channel); */
/* void CupSensor_1_ADC_DelSig_AMux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define CupSensor_1_ADC_DelSig_AMux_CHANNELS  2u
#define CupSensor_1_ADC_DelSig_AMux_MUXTYPE   1
#define CupSensor_1_ADC_DelSig_AMux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define CupSensor_1_ADC_DelSig_AMux_NULL_CHANNEL 0xFFu
#define CupSensor_1_ADC_DelSig_AMux_MUX_SINGLE   1
#define CupSensor_1_ADC_DelSig_AMux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if CupSensor_1_ADC_DelSig_AMux_MUXTYPE == CupSensor_1_ADC_DelSig_AMux_MUX_SINGLE
# if !CupSensor_1_ADC_DelSig_AMux_ATMOSTONE
#  define CupSensor_1_ADC_DelSig_AMux_Connect(channel) CupSensor_1_ADC_DelSig_AMux_Set(channel)
# endif
# define CupSensor_1_ADC_DelSig_AMux_Disconnect(channel) CupSensor_1_ADC_DelSig_AMux_Unset(channel)
#else
# if !CupSensor_1_ADC_DelSig_AMux_ATMOSTONE
void CupSensor_1_ADC_DelSig_AMux_Connect(uint8 channel) ;
# endif
void CupSensor_1_ADC_DelSig_AMux_Disconnect(uint8 channel) ;
#endif

#if CupSensor_1_ADC_DelSig_AMux_ATMOSTONE
# define CupSensor_1_ADC_DelSig_AMux_Stop() CupSensor_1_ADC_DelSig_AMux_DisconnectAll()
# define CupSensor_1_ADC_DelSig_AMux_Select(channel) CupSensor_1_ADC_DelSig_AMux_FastSelect(channel)
void CupSensor_1_ADC_DelSig_AMux_DisconnectAll(void) ;
#else
# define CupSensor_1_ADC_DelSig_AMux_Stop() CupSensor_1_ADC_DelSig_AMux_Start()
void CupSensor_1_ADC_DelSig_AMux_Select(uint8 channel) ;
# define CupSensor_1_ADC_DelSig_AMux_DisconnectAll() CupSensor_1_ADC_DelSig_AMux_Start()
#endif

#endif /* CY_AMUX_CupSensor_1_ADC_DelSig_AMux_H */


/* [] END OF FILE */
