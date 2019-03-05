/*******************************************************************************
* File Name: CapSense_CSD_MBX.h
* Version 3.50
*
* Description:
*  This file provides constants and structure declarations for the tuner 
*  communication the for CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_MBX_CapSense_CSD_H)
#define CY_CAPSENSE_CSD_MBX_CapSense_CSD_H

#include "CapSense_CSD.h"
#include "CapSense_CSD_CSHL.h"


/***************************************
*   Condition compilation parameters
***************************************/

/* Check Sum to identify data */
#define CapSense_CSD_CHECK_SUM      (9u)

#define CapSense_CSD_TOTAL_SENSOR_MASK_COUNT     (((CapSense_CSD_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)

/* Do nothing from big endian compilers (__C51__), for ARM compilers need to swap bytes */
#if defined(__C51__) || defined(__CX51__)
    #define CapSense_CSD_SWAP_ENDIAN16(x) (x)
#else
    #define CapSense_CSD_SWAP_ENDIAN16(x) ((uint16)(((uint16)(x) << 8) | ((x) >> 8)))
#endif  /* (defined(__C51__)) */

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
    #define CapSense_CSD_PACKED_STRUCT __attribute__ ((packed))
#elif defined(__ICCARM__)
    #define CapSense_CSD_PACKED_STRUCT __packed
#else
    #define CapSense_CSD_PACKED_STRUCT
#endif /* (defined(__GNUC__) || defined(__ARMCC_VERSION)) */

#if defined(__GNUC__)
	#define CapSense_CSD_NO_STRICT_VOLATILE __attribute__((optimize("-fno-strict-volatile-bitfields")))
#else
	#define CapSense_CSD_NO_STRICT_VOLATILE	
#endif /* (defined(__GNUC__)) */

/***************************************
*      Type defines for mailboxes
***************************************/

/* Outbox structure definition */
typedef struct
{       
    #if (CapSense_CSD_TOTAL_CENTROIDS_COUNT)
        uint16   position[CapSense_CSD_TOTAL_CENTROIDS_COUNT];
    #endif  /* (CapSense_CSD_TOTAL_CENTROIDS_COUNT) */

    #if (CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT)
        uint8   mbPosition[CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT * 2u];
    #endif /* (CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT) */

    uint16   rawData[CapSense_CSD_TOTAL_SENSOR_COUNT];
    uint16   baseLine[CapSense_CSD_TOTAL_SENSOR_COUNT];
    uint8    signal[CapSense_CSD_TOTAL_SENSOR_COUNT];
    uint8    onMask[CapSense_CSD_TOTAL_SENSOR_MASK_COUNT];
    
    #if (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING)
        uint8   fingerThreshold[CapSense_CSD_WIDGET_CSHL_PARAMETERS_COUNT];
        uint8   noiseThreshold[CapSense_CSD_WIDGET_CSHL_PARAMETERS_COUNT];
        uint8   scanResolution[CapSense_CSD_WIDGET_RESOLUTION_PARAMETERS_COUNT];
        uint8   idacValue[CapSense_CSD_TOTAL_SENSOR_COUNT];
		uint8   analogSwitchDivider[CapSense_CSD_TOTAL_SCANSLOT_COUNT];
    #endif  /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD_MANUAL_TUNING) */

    #if(CapSense_CSD_TUNING_METHOD == CapSense_CSD_MANUAL_TUNING)
        uint8   noReadMsg;
    #endif  /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD_MANUAL_TUNING) */
    uint16  checkSum;
    
} CapSense_CSD_PACKED_STRUCT CapSense_CSD_OUTBOX;

/* Inbox structure definition */
#if (CapSense_CSD_TUNING_METHOD == CapSense_CSD_MANUAL_TUNING)
    typedef struct
    {
        uint8   sensorIndex;
        #if (CapSense_CSD_CURRENT_SOURCE)
            uint8   idacSettings;
        #endif /* CapSense_CSD_CURRENT_SOURCE */
        uint8   resolution;
        uint8   fingerThreshold;
        uint8   noiseThreshold;
        uint8   hysteresis;
        uint8   debounce;
        uint8   analogSwitchDivider;
    } CapSense_CSD_PACKED_STRUCT CapSense_CSD_INBOX;
    
#endif  /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD_MANUAL_TUNING) */

/* Mailbox structure definition */
typedef struct
{
    uint8   type;               /* Must be the first byte with values ranging from 0-119 */
    uint16  size;               /* Must be the size of this data structure. Range between 0-127 */
    CapSense_CSD_OUTBOX  outbox;
    #if (CapSense_CSD_TUNING_METHOD == CapSense_CSD_MANUAL_TUNING)
        CapSense_CSD_INBOX inbox;
    #endif  /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD_MANUAL_TUNING) */
    
} CapSense_CSD_PACKED_STRUCT CapSense_CSD_MAILBOX;


/* Mailboxes structure definition */
typedef struct
{
    uint8   numMailBoxes;       /* This must always be the first. Represents # of mailboxes */
    CapSense_CSD_MAILBOX    csdMailbox;
} CapSense_CSD_PACKED_STRUCT CapSense_CSD_MAILBOXES;


/***************************************
*        Function Prototypes
***************************************/

CapSense_CSD_NO_STRICT_VOLATILE void CapSense_CSD_InitMailbox(volatile CapSense_CSD_MAILBOX *mbx) \
                                  ;
CapSense_CSD_NO_STRICT_VOLATILE void CapSense_CSD_PostMessage(volatile CapSense_CSD_MAILBOX *mbx) \
                                  ;
#if (CapSense_CSD_TUNING_METHOD == CapSense_CSD_MANUAL_TUNING)
CapSense_CSD_NO_STRICT_VOLATILE void CapSense_CSD_ReadMessage(volatile CapSense_CSD_MAILBOX *mbx) \
	                                  ;
#endif  /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD_MANUAL_TUNING) */


/***************************************
*           API Constants        
***************************************/

/* The selected ID for this version of Tuner */
#define CapSense_CSD_TYPE_ID        (0x04u)

#define CapSense_CSD_BUSY_FLAG      (CapSense_CSD_TYPE_ID | 0x80u)
#define CapSense_CSD_HAVE_MSG       (sizeof(CapSense_CSD_MAILBOX) | 0x8000u)


#if (CapSense_CSD_CURRENT_SOURCE)
    extern uint8 CapSense_CSD_idacSettings[CapSense_CSD_TOTAL_SENSOR_COUNT];
#endif /* CapSense_CSD_CURRENT_SOURCE */

extern uint8 CapSense_CSD_widgetResolution[CapSense_CSD_WIDGET_RESOLUTION_PARAMETERS_COUNT];

extern uint8 CapSense_CSD_fingerThreshold[CapSense_CSD_WIDGET_CSHL_PARAMETERS_COUNT];
extern uint8 CapSense_CSD_noiseThreshold[CapSense_CSD_WIDGET_CSHL_PARAMETERS_COUNT];
extern uint8 CapSense_CSD_hysteresis[CapSense_CSD_WIDGET_CSHL_PARAMETERS_COUNT];
extern uint8 CapSense_CSD_debounce[CapSense_CSD_WIDGET_CSHL_PARAMETERS_COUNT];
   
#if (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING)
    extern uint8 CapSense_CSD_lowLevelTuningDone;
    extern uint8 CapSense_CSD_GetPrescaler(void);
#endif  /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD_MANUAL_TUNING) */

#if ( (CapSense_CSD_MULTIPLE_PRESCALER_ENABLED) || \
      (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) )
    extern uint8 CapSense_CSD_analogSwitchDivider[CapSense_CSD_TOTAL_SCANSLOT_COUNT];
#else
    extern uint8 CapSense_CSD_analogSwitchDivider;
#endif /* ( (CapSense_CSD_MULTIPLE_PRESCALER_ENABLED) || \
       *    (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) )
       */


#endif  /* (CY_CAPSENSE_CSD_MBX_CapSense_CSD_H) */

/* [] END OF FILE */
