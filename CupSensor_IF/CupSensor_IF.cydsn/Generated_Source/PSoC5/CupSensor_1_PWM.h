/*******************************************************************************
* File Name: ``$INSTANCE_NAME`_PWM.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_``$INSTANCE_NAME`_PWM_H)
#define CY_PWM_``$INSTANCE_NAME`_PWM_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 ``$INSTANCE_NAME`_PWM_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define ``$INSTANCE_NAME`_PWM_Resolution                     (8u)
#define ``$INSTANCE_NAME`_PWM_UsingFixedFunction             (0u)
#define ``$INSTANCE_NAME`_PWM_DeadBandMode                   (0u)
#define ``$INSTANCE_NAME`_PWM_KillModeMinTime                (0u)
#define ``$INSTANCE_NAME`_PWM_KillMode                       (0u)
#define ``$INSTANCE_NAME`_PWM_PWMMode                        (1u)
#define ``$INSTANCE_NAME`_PWM_PWMModeIsCenterAligned         (0u)
#define ``$INSTANCE_NAME`_PWM_DeadBandUsed                   (0u)
#define ``$INSTANCE_NAME`_PWM_DeadBand2_4                    (0u)

#if !defined(``$INSTANCE_NAME`_PWM_PWMUDB_genblk8_stsreg__REMOVED)
    #define ``$INSTANCE_NAME`_PWM_UseStatus                  (1u)
#else
    #define ``$INSTANCE_NAME`_PWM_UseStatus                  (0u)
#endif /* !defined(``$INSTANCE_NAME`_PWM_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(``$INSTANCE_NAME`_PWM_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define ``$INSTANCE_NAME`_PWM_UseControl                 (1u)
#else
    #define ``$INSTANCE_NAME`_PWM_UseControl                 (0u)
#endif /* !defined(``$INSTANCE_NAME`_PWM_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define ``$INSTANCE_NAME`_PWM_UseOneCompareMode              (0u)
#define ``$INSTANCE_NAME`_PWM_MinimumKillTime                (1u)
#define ``$INSTANCE_NAME`_PWM_EnableMode                     (0u)

#define ``$INSTANCE_NAME`_PWM_CompareMode1SW                 (0u)
#define ``$INSTANCE_NAME`_PWM_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define ``$INSTANCE_NAME`_PWM__B_PWM__DISABLED 0
#define ``$INSTANCE_NAME`_PWM__B_PWM__ASYNCHRONOUS 1
#define ``$INSTANCE_NAME`_PWM__B_PWM__SINGLECYCLE 2
#define ``$INSTANCE_NAME`_PWM__B_PWM__LATCHED 3
#define ``$INSTANCE_NAME`_PWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define ``$INSTANCE_NAME`_PWM__B_PWM__DBMDISABLED 0
#define ``$INSTANCE_NAME`_PWM__B_PWM__DBM_2_4_CLOCKS 1
#define ``$INSTANCE_NAME`_PWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define ``$INSTANCE_NAME`_PWM__B_PWM__ONE_OUTPUT 0
#define ``$INSTANCE_NAME`_PWM__B_PWM__TWO_OUTPUTS 1
#define ``$INSTANCE_NAME`_PWM__B_PWM__DUAL_EDGE 2
#define ``$INSTANCE_NAME`_PWM__B_PWM__CENTER_ALIGN 3
#define ``$INSTANCE_NAME`_PWM__B_PWM__DITHER 5
#define ``$INSTANCE_NAME`_PWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define ``$INSTANCE_NAME`_PWM__B_PWM__LESS_THAN 1
#define ``$INSTANCE_NAME`_PWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define ``$INSTANCE_NAME`_PWM__B_PWM__GREATER_THAN 3
#define ``$INSTANCE_NAME`_PWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define ``$INSTANCE_NAME`_PWM__B_PWM__EQUAL 0
#define ``$INSTANCE_NAME`_PWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!``$INSTANCE_NAME`_PWM_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!``$INSTANCE_NAME`_PWM_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!``$INSTANCE_NAME`_PWM_PWMModeIsCenterAligned) */
        #if (``$INSTANCE_NAME`_PWM_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (``$INSTANCE_NAME`_PWM_UseStatus) */

        /* Backup for Deadband parameters */
        #if(``$INSTANCE_NAME`_PWM_DeadBandMode == ``$INSTANCE_NAME`_PWM__B_PWM__DBM_256_CLOCKS || \
            ``$INSTANCE_NAME`_PWM_DeadBandMode == ``$INSTANCE_NAME`_PWM__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(``$INSTANCE_NAME`_PWM_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (``$INSTANCE_NAME`_PWM_KillModeMinTime) */

        /* Backup control register */
        #if(``$INSTANCE_NAME`_PWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (``$INSTANCE_NAME`_PWM_UseControl) */

    #endif /* (!``$INSTANCE_NAME`_PWM_UsingFixedFunction) */

}``$INSTANCE_NAME`_PWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    ``$INSTANCE_NAME`_PWM_Start(void) ;
void    ``$INSTANCE_NAME`_PWM_Stop(void) ;

#if (``$INSTANCE_NAME`_PWM_UseStatus || ``$INSTANCE_NAME`_PWM_UsingFixedFunction)
    void  ``$INSTANCE_NAME`_PWM_SetInterruptMode(uint8 interruptMode) ;
    uint8 ``$INSTANCE_NAME`_PWM_ReadStatusRegister(void) ;
#endif /* (``$INSTANCE_NAME`_PWM_UseStatus || ``$INSTANCE_NAME`_PWM_UsingFixedFunction) */

#define ``$INSTANCE_NAME`_PWM_GetInterruptSource() ``$INSTANCE_NAME`_PWM_ReadStatusRegister()

#if (``$INSTANCE_NAME`_PWM_UseControl)
    uint8 ``$INSTANCE_NAME`_PWM_ReadControlRegister(void) ;
    void  ``$INSTANCE_NAME`_PWM_WriteControlRegister(uint8 control)
          ;
#endif /* (``$INSTANCE_NAME`_PWM_UseControl) */

#if (``$INSTANCE_NAME`_PWM_UseOneCompareMode)
   #if (``$INSTANCE_NAME`_PWM_CompareMode1SW)
       void    ``$INSTANCE_NAME`_PWM_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (``$INSTANCE_NAME`_PWM_CompareMode1SW) */
#else
    #if (``$INSTANCE_NAME`_PWM_CompareMode1SW)
        void    ``$INSTANCE_NAME`_PWM_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (``$INSTANCE_NAME`_PWM_CompareMode1SW) */
    #if (``$INSTANCE_NAME`_PWM_CompareMode2SW)
        void    ``$INSTANCE_NAME`_PWM_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (``$INSTANCE_NAME`_PWM_CompareMode2SW) */
#endif /* (``$INSTANCE_NAME`_PWM_UseOneCompareMode) */

#if (!``$INSTANCE_NAME`_PWM_UsingFixedFunction)
    uint8   ``$INSTANCE_NAME`_PWM_ReadCounter(void) ;
    uint8 ``$INSTANCE_NAME`_PWM_ReadCapture(void) ;

    #if (``$INSTANCE_NAME`_PWM_UseStatus)
            void ``$INSTANCE_NAME`_PWM_ClearFIFO(void) ;
    #endif /* (``$INSTANCE_NAME`_PWM_UseStatus) */

    void    ``$INSTANCE_NAME`_PWM_WriteCounter(uint8 counter)
            ;
#endif /* (!``$INSTANCE_NAME`_PWM_UsingFixedFunction) */

void    ``$INSTANCE_NAME`_PWM_WritePeriod(uint8 period)
        ;
uint8 ``$INSTANCE_NAME`_PWM_ReadPeriod(void) ;

#if (``$INSTANCE_NAME`_PWM_UseOneCompareMode)
    void    ``$INSTANCE_NAME`_PWM_WriteCompare(uint8 compare)
            ;
    uint8 ``$INSTANCE_NAME`_PWM_ReadCompare(void) ;
#else
    void    ``$INSTANCE_NAME`_PWM_WriteCompare1(uint8 compare)
            ;
    uint8 ``$INSTANCE_NAME`_PWM_ReadCompare1(void) ;
    void    ``$INSTANCE_NAME`_PWM_WriteCompare2(uint8 compare)
            ;
    uint8 ``$INSTANCE_NAME`_PWM_ReadCompare2(void) ;
#endif /* (``$INSTANCE_NAME`_PWM_UseOneCompareMode) */


#if (``$INSTANCE_NAME`_PWM_DeadBandUsed)
    void    ``$INSTANCE_NAME`_PWM_WriteDeadTime(uint8 deadtime) ;
    uint8   ``$INSTANCE_NAME`_PWM_ReadDeadTime(void) ;
#endif /* (``$INSTANCE_NAME`_PWM_DeadBandUsed) */

#if ( ``$INSTANCE_NAME`_PWM_KillModeMinTime)
    void ``$INSTANCE_NAME`_PWM_WriteKillTime(uint8 killtime) ;
    uint8 ``$INSTANCE_NAME`_PWM_ReadKillTime(void) ;
#endif /* ( ``$INSTANCE_NAME`_PWM_KillModeMinTime) */

void ``$INSTANCE_NAME`_PWM_Init(void) ;
void ``$INSTANCE_NAME`_PWM_Enable(void) ;
void ``$INSTANCE_NAME`_PWM_Sleep(void) ;
void ``$INSTANCE_NAME`_PWM_Wakeup(void) ;
void ``$INSTANCE_NAME`_PWM_SaveConfig(void) ;
void ``$INSTANCE_NAME`_PWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define ``$INSTANCE_NAME`_PWM_INIT_PERIOD_VALUE          (3u)
#define ``$INSTANCE_NAME`_PWM_INIT_COMPARE_VALUE1        (2u)
#define ``$INSTANCE_NAME`_PWM_INIT_COMPARE_VALUE2        (0u)
#define ``$INSTANCE_NAME`_PWM_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    ``$INSTANCE_NAME`_PWM_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ``$INSTANCE_NAME`_PWM_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ``$INSTANCE_NAME`_PWM_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ``$INSTANCE_NAME`_PWM_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define ``$INSTANCE_NAME`_PWM_DEFAULT_COMPARE2_MODE      (uint8)((uint8)3u <<  ``$INSTANCE_NAME`_PWM_CTRL_CMPMODE2_SHIFT)
#define ``$INSTANCE_NAME`_PWM_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  ``$INSTANCE_NAME`_PWM_CTRL_CMPMODE1_SHIFT)
#define ``$INSTANCE_NAME`_PWM_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (``$INSTANCE_NAME`_PWM_UsingFixedFunction)
   #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB              (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMHW__PER0)
   #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB_PTR          ( (reg16 *) ``$INSTANCE_NAME`_PWM_PWMHW__PER0)
   #define ``$INSTANCE_NAME`_PWM_COMPARE1_LSB            (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMHW__CNT_CMP0)
   #define ``$INSTANCE_NAME`_PWM_COMPARE1_LSB_PTR        ( (reg16 *) ``$INSTANCE_NAME`_PWM_PWMHW__CNT_CMP0)
   #define ``$INSTANCE_NAME`_PWM_COMPARE2_LSB            (0x00u)
   #define ``$INSTANCE_NAME`_PWM_COMPARE2_LSB_PTR        (0x00u)
   #define ``$INSTANCE_NAME`_PWM_COUNTER_LSB             (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMHW__CNT_CMP0)
   #define ``$INSTANCE_NAME`_PWM_COUNTER_LSB_PTR         ( (reg16 *) ``$INSTANCE_NAME`_PWM_PWMHW__CNT_CMP0)
   #define ``$INSTANCE_NAME`_PWM_CAPTURE_LSB             (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMHW__CAP0)
   #define ``$INSTANCE_NAME`_PWM_CAPTURE_LSB_PTR         ( (reg16 *) ``$INSTANCE_NAME`_PWM_PWMHW__CAP0)
   #define ``$INSTANCE_NAME`_PWM_RT1                     (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMHW__RT1)
   #define ``$INSTANCE_NAME`_PWM_RT1_PTR                 ( (reg8 *)  ``$INSTANCE_NAME`_PWM_PWMHW__RT1)

#else
   #if (``$INSTANCE_NAME`_PWM_Resolution == 8u) /* 8bit - PWM */

       #if(``$INSTANCE_NAME`_PWM_PWMModeIsCenterAligned)
           #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB      (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB_PTR  ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB      (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB_PTR  ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (``$INSTANCE_NAME`_PWM_PWMModeIsCenterAligned) */

       #define ``$INSTANCE_NAME`_PWM_COMPARE1_LSB        (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define ``$INSTANCE_NAME`_PWM_COMPARE1_LSB_PTR    ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define ``$INSTANCE_NAME`_PWM_COMPARE2_LSB        (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define ``$INSTANCE_NAME`_PWM_COMPARE2_LSB_PTR    ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define ``$INSTANCE_NAME`_PWM_COUNTERCAP_LSB      (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define ``$INSTANCE_NAME`_PWM_COUNTERCAP_LSB_PTR  ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define ``$INSTANCE_NAME`_PWM_COUNTER_LSB         (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define ``$INSTANCE_NAME`_PWM_COUNTER_LSB_PTR     ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define ``$INSTANCE_NAME`_PWM_CAPTURE_LSB         (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define ``$INSTANCE_NAME`_PWM_CAPTURE_LSB_PTR     ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(``$INSTANCE_NAME`_PWM_PWMModeIsCenterAligned)
               #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB      (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB_PTR  ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB      (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB_PTR  ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (``$INSTANCE_NAME`_PWM_PWMModeIsCenterAligned) */

            #define ``$INSTANCE_NAME`_PWM_COMPARE1_LSB       (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define ``$INSTANCE_NAME`_PWM_COMPARE1_LSB_PTR   ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define ``$INSTANCE_NAME`_PWM_COMPARE2_LSB       (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define ``$INSTANCE_NAME`_PWM_COMPARE2_LSB_PTR   ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define ``$INSTANCE_NAME`_PWM_COUNTERCAP_LSB     (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define ``$INSTANCE_NAME`_PWM_COUNTERCAP_LSB_PTR ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define ``$INSTANCE_NAME`_PWM_COUNTER_LSB        (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define ``$INSTANCE_NAME`_PWM_COUNTER_LSB_PTR    ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define ``$INSTANCE_NAME`_PWM_CAPTURE_LSB        (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define ``$INSTANCE_NAME`_PWM_CAPTURE_LSB_PTR    ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(``$INSTANCE_NAME`_PWM_PWMModeIsCenterAligned)
               #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB      (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB_PTR  ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB      (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define ``$INSTANCE_NAME`_PWM_PERIOD_LSB_PTR  ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (``$INSTANCE_NAME`_PWM_PWMModeIsCenterAligned) */

            #define ``$INSTANCE_NAME`_PWM_COMPARE1_LSB       (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define ``$INSTANCE_NAME`_PWM_COMPARE1_LSB_PTR   ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define ``$INSTANCE_NAME`_PWM_COMPARE2_LSB       (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define ``$INSTANCE_NAME`_PWM_COMPARE2_LSB_PTR   ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define ``$INSTANCE_NAME`_PWM_COUNTERCAP_LSB     (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define ``$INSTANCE_NAME`_PWM_COUNTERCAP_LSB_PTR ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define ``$INSTANCE_NAME`_PWM_COUNTER_LSB        (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define ``$INSTANCE_NAME`_PWM_COUNTER_LSB_PTR    ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define ``$INSTANCE_NAME`_PWM_CAPTURE_LSB        (*(reg16 *) ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define ``$INSTANCE_NAME`_PWM_CAPTURE_LSB_PTR    ((reg16 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define ``$INSTANCE_NAME`_PWM_AUX_CONTROLDP1          (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define ``$INSTANCE_NAME`_PWM_AUX_CONTROLDP1_PTR      ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (``$INSTANCE_NAME`_PWM_Resolution == 8) */

   #define ``$INSTANCE_NAME`_PWM_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define ``$INSTANCE_NAME`_PWM_AUX_CONTROLDP0          (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define ``$INSTANCE_NAME`_PWM_AUX_CONTROLDP0_PTR      ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (``$INSTANCE_NAME`_PWM_UsingFixedFunction) */

#if(``$INSTANCE_NAME`_PWM_KillModeMinTime )
    #define ``$INSTANCE_NAME`_PWM_KILLMODEMINTIME        (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define ``$INSTANCE_NAME`_PWM_KILLMODEMINTIME_PTR    ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (``$INSTANCE_NAME`_PWM_KillModeMinTime ) */

#if(``$INSTANCE_NAME`_PWM_DeadBandMode == ``$INSTANCE_NAME`_PWM__B_PWM__DBM_256_CLOCKS)
    #define ``$INSTANCE_NAME`_PWM_DEADBAND_COUNT         (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define ``$INSTANCE_NAME`_PWM_DEADBAND_COUNT_PTR     ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define ``$INSTANCE_NAME`_PWM_DEADBAND_LSB_PTR       ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define ``$INSTANCE_NAME`_PWM_DEADBAND_LSB           (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(``$INSTANCE_NAME`_PWM_DeadBandMode == ``$INSTANCE_NAME`_PWM__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (``$INSTANCE_NAME`_PWM_UsingFixedFunction)
        #define ``$INSTANCE_NAME`_PWM_DEADBAND_COUNT         (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMHW__CFG0)
        #define ``$INSTANCE_NAME`_PWM_DEADBAND_COUNT_PTR     ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMHW__CFG0)
        #define ``$INSTANCE_NAME`_PWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << ``$INSTANCE_NAME`_PWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define ``$INSTANCE_NAME`_PWM_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define ``$INSTANCE_NAME`_PWM_DEADBAND_COUNT         (*(reg8 *)  ``$INSTANCE_NAME`_PWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define ``$INSTANCE_NAME`_PWM_DEADBAND_COUNT_PTR     ((reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define ``$INSTANCE_NAME`_PWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << ``$INSTANCE_NAME`_PWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define ``$INSTANCE_NAME`_PWM_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (``$INSTANCE_NAME`_PWM_UsingFixedFunction) */
#endif /* (``$INSTANCE_NAME`_PWM_DeadBandMode == ``$INSTANCE_NAME`_PWM__B_PWM__DBM_256_CLOCKS) */



#if (``$INSTANCE_NAME`_PWM_UsingFixedFunction)
    #define ``$INSTANCE_NAME`_PWM_STATUS                 (*(reg8 *) ``$INSTANCE_NAME`_PWM_PWMHW__SR0)
    #define ``$INSTANCE_NAME`_PWM_STATUS_PTR             ((reg8 *) ``$INSTANCE_NAME`_PWM_PWMHW__SR0)
    #define ``$INSTANCE_NAME`_PWM_STATUS_MASK            (*(reg8 *) ``$INSTANCE_NAME`_PWM_PWMHW__SR0)
    #define ``$INSTANCE_NAME`_PWM_STATUS_MASK_PTR        ((reg8 *) ``$INSTANCE_NAME`_PWM_PWMHW__SR0)
    #define ``$INSTANCE_NAME`_PWM_CONTROL                (*(reg8 *) ``$INSTANCE_NAME`_PWM_PWMHW__CFG0)
    #define ``$INSTANCE_NAME`_PWM_CONTROL_PTR            ((reg8 *) ``$INSTANCE_NAME`_PWM_PWMHW__CFG0)
    #define ``$INSTANCE_NAME`_PWM_CONTROL2               (*(reg8 *) ``$INSTANCE_NAME`_PWM_PWMHW__CFG1)
    #define ``$INSTANCE_NAME`_PWM_CONTROL3               (*(reg8 *) ``$INSTANCE_NAME`_PWM_PWMHW__CFG2)
    #define ``$INSTANCE_NAME`_PWM_GLOBAL_ENABLE          (*(reg8 *) ``$INSTANCE_NAME`_PWM_PWMHW__PM_ACT_CFG)
    #define ``$INSTANCE_NAME`_PWM_GLOBAL_ENABLE_PTR      ( (reg8 *) ``$INSTANCE_NAME`_PWM_PWMHW__PM_ACT_CFG)
    #define ``$INSTANCE_NAME`_PWM_GLOBAL_STBY_ENABLE     (*(reg8 *) ``$INSTANCE_NAME`_PWM_PWMHW__PM_STBY_CFG)
    #define ``$INSTANCE_NAME`_PWM_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) ``$INSTANCE_NAME`_PWM_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define ``$INSTANCE_NAME`_PWM_BLOCK_EN_MASK          (``$INSTANCE_NAME`_PWM_PWMHW__PM_ACT_MSK)
    #define ``$INSTANCE_NAME`_PWM_BLOCK_STBY_EN_MASK     (``$INSTANCE_NAME`_PWM_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define ``$INSTANCE_NAME`_PWM_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define ``$INSTANCE_NAME`_PWM_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define ``$INSTANCE_NAME`_PWM_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define ``$INSTANCE_NAME`_PWM_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define ``$INSTANCE_NAME`_PWM_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define ``$INSTANCE_NAME`_PWM_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define ``$INSTANCE_NAME`_PWM_CTRL_ENABLE            (uint8)((uint8)0x01u << ``$INSTANCE_NAME`_PWM_CTRL_ENABLE_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_CTRL_RESET             (uint8)((uint8)0x01u << ``$INSTANCE_NAME`_PWM_CTRL_RESET_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << ``$INSTANCE_NAME`_PWM_CTRL_CMPMODE2_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << ``$INSTANCE_NAME`_PWM_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define ``$INSTANCE_NAME`_PWM_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define ``$INSTANCE_NAME`_PWM_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << ``$INSTANCE_NAME`_PWM_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define ``$INSTANCE_NAME`_PWM_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define ``$INSTANCE_NAME`_PWM_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define ``$INSTANCE_NAME`_PWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define ``$INSTANCE_NAME`_PWM_STATUS_TC_INT_EN_MASK_SHIFT            (``$INSTANCE_NAME`_PWM_STATUS_TC_SHIFT - 4u)
    #define ``$INSTANCE_NAME`_PWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define ``$INSTANCE_NAME`_PWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (``$INSTANCE_NAME`_PWM_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define ``$INSTANCE_NAME`_PWM_STATUS_TC              (uint8)((uint8)0x01u << ``$INSTANCE_NAME`_PWM_STATUS_TC_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_STATUS_CMP1            (uint8)((uint8)0x01u << ``$INSTANCE_NAME`_PWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define ``$INSTANCE_NAME`_PWM_STATUS_TC_INT_EN_MASK              (uint8)((uint8)``$INSTANCE_NAME`_PWM_STATUS_TC >> 4u)
    #define ``$INSTANCE_NAME`_PWM_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)``$INSTANCE_NAME`_PWM_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define ``$INSTANCE_NAME`_PWM_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define ``$INSTANCE_NAME`_PWM_RT1_MASK              (uint8)((uint8)0x03u << ``$INSTANCE_NAME`_PWM_RT1_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_SYNC                  (uint8)((uint8)0x03u << ``$INSTANCE_NAME`_PWM_RT1_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define ``$INSTANCE_NAME`_PWM_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << ``$INSTANCE_NAME`_PWM_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define ``$INSTANCE_NAME`_PWM_SYNCDSI_EN            (uint8)((uint8)0x0Fu << ``$INSTANCE_NAME`_PWM_SYNCDSI_SHIFT)


#else
    #define ``$INSTANCE_NAME`_PWM_STATUS                (*(reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define ``$INSTANCE_NAME`_PWM_STATUS_PTR            ((reg8 *)    ``$INSTANCE_NAME`_PWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define ``$INSTANCE_NAME`_PWM_STATUS_MASK           (*(reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define ``$INSTANCE_NAME`_PWM_STATUS_MASK_PTR       ((reg8 *)    ``$INSTANCE_NAME`_PWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define ``$INSTANCE_NAME`_PWM_STATUS_AUX_CTRL       (*(reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define ``$INSTANCE_NAME`_PWM_CONTROL               (*(reg8 *)   ``$INSTANCE_NAME`_PWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define ``$INSTANCE_NAME`_PWM_CONTROL_PTR           ((reg8 *)    ``$INSTANCE_NAME`_PWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define ``$INSTANCE_NAME`_PWM_CTRL_ENABLE_SHIFT      (0x07u)
    #define ``$INSTANCE_NAME`_PWM_CTRL_RESET_SHIFT       (0x06u)
    #define ``$INSTANCE_NAME`_PWM_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define ``$INSTANCE_NAME`_PWM_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define ``$INSTANCE_NAME`_PWM_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define ``$INSTANCE_NAME`_PWM_CTRL_ENABLE            (uint8)((uint8)0x01u << ``$INSTANCE_NAME`_PWM_CTRL_ENABLE_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_CTRL_RESET             (uint8)((uint8)0x01u << ``$INSTANCE_NAME`_PWM_CTRL_RESET_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << ``$INSTANCE_NAME`_PWM_CTRL_CMPMODE2_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << ``$INSTANCE_NAME`_PWM_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define ``$INSTANCE_NAME`_PWM_STATUS_KILL_SHIFT          (0x05u)
    #define ``$INSTANCE_NAME`_PWM_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define ``$INSTANCE_NAME`_PWM_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define ``$INSTANCE_NAME`_PWM_STATUS_TC_SHIFT            (0x02u)
    #define ``$INSTANCE_NAME`_PWM_STATUS_CMP2_SHIFT          (0x01u)
    #define ``$INSTANCE_NAME`_PWM_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define ``$INSTANCE_NAME`_PWM_STATUS_KILL_INT_EN_MASK_SHIFT          (``$INSTANCE_NAME`_PWM_STATUS_KILL_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (``$INSTANCE_NAME`_PWM_STATUS_FIFONEMPTY_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (``$INSTANCE_NAME`_PWM_STATUS_FIFOFULL_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_STATUS_TC_INT_EN_MASK_SHIFT            (``$INSTANCE_NAME`_PWM_STATUS_TC_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (``$INSTANCE_NAME`_PWM_STATUS_CMP2_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (``$INSTANCE_NAME`_PWM_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define ``$INSTANCE_NAME`_PWM_STATUS_KILL            (uint8)((uint8)0x00u << ``$INSTANCE_NAME`_PWM_STATUS_KILL_SHIFT )
    #define ``$INSTANCE_NAME`_PWM_STATUS_FIFOFULL        (uint8)((uint8)0x01u << ``$INSTANCE_NAME`_PWM_STATUS_FIFOFULL_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << ``$INSTANCE_NAME`_PWM_STATUS_FIFONEMPTY_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_STATUS_TC              (uint8)((uint8)0x01u << ``$INSTANCE_NAME`_PWM_STATUS_TC_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_STATUS_CMP2            (uint8)((uint8)0x01u << ``$INSTANCE_NAME`_PWM_STATUS_CMP2_SHIFT)
    #define ``$INSTANCE_NAME`_PWM_STATUS_CMP1            (uint8)((uint8)0x01u << ``$INSTANCE_NAME`_PWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define ``$INSTANCE_NAME`_PWM_STATUS_KILL_INT_EN_MASK            (``$INSTANCE_NAME`_PWM_STATUS_KILL)
    #define ``$INSTANCE_NAME`_PWM_STATUS_FIFOFULL_INT_EN_MASK        (``$INSTANCE_NAME`_PWM_STATUS_FIFOFULL)
    #define ``$INSTANCE_NAME`_PWM_STATUS_FIFONEMPTY_INT_EN_MASK      (``$INSTANCE_NAME`_PWM_STATUS_FIFONEMPTY)
    #define ``$INSTANCE_NAME`_PWM_STATUS_TC_INT_EN_MASK              (``$INSTANCE_NAME`_PWM_STATUS_TC)
    #define ``$INSTANCE_NAME`_PWM_STATUS_CMP2_INT_EN_MASK            (``$INSTANCE_NAME`_PWM_STATUS_CMP2)
    #define ``$INSTANCE_NAME`_PWM_STATUS_CMP1_INT_EN_MASK            (``$INSTANCE_NAME`_PWM_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define ``$INSTANCE_NAME`_PWM_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define ``$INSTANCE_NAME`_PWM_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define ``$INSTANCE_NAME`_PWM_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define ``$INSTANCE_NAME`_PWM_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define ``$INSTANCE_NAME`_PWM_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* ``$INSTANCE_NAME`_PWM_UsingFixedFunction */

#endif  /* CY_PWM_``$INSTANCE_NAME`_PWM_H */


/* [] END OF FILE */
