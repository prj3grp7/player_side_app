/*******************************************************************************
* File Name: leds.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_leds_ALIASES_H) /* Pins leds_ALIASES_H */
#define CY_PINS_leds_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define leds_0			(leds__0__PC)
#define leds_0_INTR	((uint16)((uint16)0x0001u << leds__0__SHIFT))

#define leds_1			(leds__1__PC)
#define leds_1_INTR	((uint16)((uint16)0x0001u << leds__1__SHIFT))

#define leds_2			(leds__2__PC)
#define leds_2_INTR	((uint16)((uint16)0x0001u << leds__2__SHIFT))

#define leds_3			(leds__3__PC)
#define leds_3_INTR	((uint16)((uint16)0x0001u << leds__3__SHIFT))

#define leds_4			(leds__4__PC)
#define leds_4_INTR	((uint16)((uint16)0x0001u << leds__4__SHIFT))

#define leds_5			(leds__5__PC)
#define leds_5_INTR	((uint16)((uint16)0x0001u << leds__5__SHIFT))

#define leds_INTR_ALL	 ((uint16)(leds_0_INTR| leds_1_INTR| leds_2_INTR| leds_3_INTR| leds_4_INTR| leds_5_INTR))

#endif /* End Pins leds_ALIASES_H */


/* [] END OF FILE */
