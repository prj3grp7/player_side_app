/*******************************************************************************
* File Name: cyfittergnu.inc
* 
* PSoC Creator  4.2
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2018 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

.ifndef INCLUDED_CYFITTERGNU_INC
.set INCLUDED_CYFITTERGNU_INC, 1
.include "cydevicegnu.inc"
.include "cydevicegnu_trm.inc"

/* Led */
.set Led__0__INTTYPE, CYREG_PICU1_INTTYPE5
.set Led__0__MASK, 0x20
.set Led__0__PC, CYREG_PRT1_PC5
.set Led__0__PORT, 1
.set Led__0__SHIFT, 5
.set Led__AG, CYREG_PRT1_AG
.set Led__AMUX, CYREG_PRT1_AMUX
.set Led__BIE, CYREG_PRT1_BIE
.set Led__BIT_MASK, CYREG_PRT1_BIT_MASK
.set Led__BYP, CYREG_PRT1_BYP
.set Led__CTL, CYREG_PRT1_CTL
.set Led__DM0, CYREG_PRT1_DM0
.set Led__DM1, CYREG_PRT1_DM1
.set Led__DM2, CYREG_PRT1_DM2
.set Led__DR, CYREG_PRT1_DR
.set Led__INP_DIS, CYREG_PRT1_INP_DIS
.set Led__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU1_BASE
.set Led__LCD_COM_SEG, CYREG_PRT1_LCD_COM_SEG
.set Led__LCD_EN, CYREG_PRT1_LCD_EN
.set Led__MASK, 0x20
.set Led__PORT, 1
.set Led__PRT, CYREG_PRT1_PRT
.set Led__PRTDSI__CAPS_SEL, CYREG_PRT1_CAPS_SEL
.set Led__PRTDSI__DBL_SYNC_IN, CYREG_PRT1_DBL_SYNC_IN
.set Led__PRTDSI__OE_SEL0, CYREG_PRT1_OE_SEL0
.set Led__PRTDSI__OE_SEL1, CYREG_PRT1_OE_SEL1
.set Led__PRTDSI__OUT_SEL0, CYREG_PRT1_OUT_SEL0
.set Led__PRTDSI__OUT_SEL1, CYREG_PRT1_OUT_SEL1
.set Led__PRTDSI__SYNC_OUT, CYREG_PRT1_SYNC_OUT
.set Led__PS, CYREG_PRT1_PS
.set Led__SHIFT, 5
.set Led__SLW, CYREG_PRT1_SLW

/* PGA_1 */
.set PGA_1_SC__BST, CYREG_SC0_BST
.set PGA_1_SC__CLK, CYREG_SC0_CLK
.set PGA_1_SC__CMPINV, CYREG_SC_CMPINV
.set PGA_1_SC__CMPINV_MASK, 0x01
.set PGA_1_SC__CPTR, CYREG_SC_CPTR
.set PGA_1_SC__CPTR_MASK, 0x01
.set PGA_1_SC__CR0, CYREG_SC0_CR0
.set PGA_1_SC__CR1, CYREG_SC0_CR1
.set PGA_1_SC__CR2, CYREG_SC0_CR2
.set PGA_1_SC__MSK, CYREG_SC_MSK
.set PGA_1_SC__MSK_MASK, 0x01
.set PGA_1_SC__PM_ACT_CFG, CYREG_PM_ACT_CFG9
.set PGA_1_SC__PM_ACT_MSK, 0x01
.set PGA_1_SC__PM_STBY_CFG, CYREG_PM_STBY_CFG9
.set PGA_1_SC__PM_STBY_MSK, 0x01
.set PGA_1_SC__SR, CYREG_SC_SR
.set PGA_1_SC__SR_MASK, 0x01
.set PGA_1_SC__SW0, CYREG_SC0_SW0
.set PGA_1_SC__SW10, CYREG_SC0_SW10
.set PGA_1_SC__SW2, CYREG_SC0_SW2
.set PGA_1_SC__SW3, CYREG_SC0_SW3
.set PGA_1_SC__SW4, CYREG_SC0_SW4
.set PGA_1_SC__SW6, CYREG_SC0_SW6
.set PGA_1_SC__SW7, CYREG_SC0_SW7
.set PGA_1_SC__SW8, CYREG_SC0_SW8
.set PGA_1_SC__WRK1, CYREG_SC_WRK1
.set PGA_1_SC__WRK1_MASK, 0x01

/* TIA_1 */
.set TIA_1_SC__BST, CYREG_SC3_BST
.set TIA_1_SC__CLK, CYREG_SC3_CLK
.set TIA_1_SC__CMPINV, CYREG_SC_CMPINV
.set TIA_1_SC__CMPINV_MASK, 0x08
.set TIA_1_SC__CPTR, CYREG_SC_CPTR
.set TIA_1_SC__CPTR_MASK, 0x08
.set TIA_1_SC__CR0, CYREG_SC3_CR0
.set TIA_1_SC__CR1, CYREG_SC3_CR1
.set TIA_1_SC__CR2, CYREG_SC3_CR2
.set TIA_1_SC__MSK, CYREG_SC_MSK
.set TIA_1_SC__MSK_MASK, 0x08
.set TIA_1_SC__PM_ACT_CFG, CYREG_PM_ACT_CFG9
.set TIA_1_SC__PM_ACT_MSK, 0x08
.set TIA_1_SC__PM_STBY_CFG, CYREG_PM_STBY_CFG9
.set TIA_1_SC__PM_STBY_MSK, 0x08
.set TIA_1_SC__SR, CYREG_SC_SR
.set TIA_1_SC__SR_MASK, 0x08
.set TIA_1_SC__SW0, CYREG_SC3_SW0
.set TIA_1_SC__SW10, CYREG_SC3_SW10
.set TIA_1_SC__SW2, CYREG_SC3_SW2
.set TIA_1_SC__SW3, CYREG_SC3_SW3
.set TIA_1_SC__SW4, CYREG_SC3_SW4
.set TIA_1_SC__SW6, CYREG_SC3_SW6
.set TIA_1_SC__SW7, CYREG_SC3_SW7
.set TIA_1_SC__SW8, CYREG_SC3_SW8
.set TIA_1_SC__WRK1, CYREG_SC_WRK1
.set TIA_1_SC__WRK1_MASK, 0x08

/* AmpOut */
.set AmpOut__0__INTTYPE, CYREG_PICU1_INTTYPE6
.set AmpOut__0__MASK, 0x40
.set AmpOut__0__PC, CYREG_PRT1_PC6
.set AmpOut__0__PORT, 1
.set AmpOut__0__SHIFT, 6
.set AmpOut__AG, CYREG_PRT1_AG
.set AmpOut__AMUX, CYREG_PRT1_AMUX
.set AmpOut__BIE, CYREG_PRT1_BIE
.set AmpOut__BIT_MASK, CYREG_PRT1_BIT_MASK
.set AmpOut__BYP, CYREG_PRT1_BYP
.set AmpOut__CTL, CYREG_PRT1_CTL
.set AmpOut__DM0, CYREG_PRT1_DM0
.set AmpOut__DM1, CYREG_PRT1_DM1
.set AmpOut__DM2, CYREG_PRT1_DM2
.set AmpOut__DR, CYREG_PRT1_DR
.set AmpOut__INP_DIS, CYREG_PRT1_INP_DIS
.set AmpOut__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU1_BASE
.set AmpOut__LCD_COM_SEG, CYREG_PRT1_LCD_COM_SEG
.set AmpOut__LCD_EN, CYREG_PRT1_LCD_EN
.set AmpOut__MASK, 0x40
.set AmpOut__PORT, 1
.set AmpOut__PRT, CYREG_PRT1_PRT
.set AmpOut__PRTDSI__CAPS_SEL, CYREG_PRT1_CAPS_SEL
.set AmpOut__PRTDSI__DBL_SYNC_IN, CYREG_PRT1_DBL_SYNC_IN
.set AmpOut__PRTDSI__OE_SEL0, CYREG_PRT1_OE_SEL0
.set AmpOut__PRTDSI__OE_SEL1, CYREG_PRT1_OE_SEL1
.set AmpOut__PRTDSI__OUT_SEL0, CYREG_PRT1_OUT_SEL0
.set AmpOut__PRTDSI__OUT_SEL1, CYREG_PRT1_OUT_SEL1
.set AmpOut__PRTDSI__SYNC_OUT, CYREG_PRT1_SYNC_OUT
.set AmpOut__PS, CYREG_PRT1_PS
.set AmpOut__SHIFT, 6
.set AmpOut__SLW, CYREG_PRT1_SLW

/* Clock_1 */
.set Clock_1__CFG0, CYREG_CLKDIST_DCFG0_CFG0
.set Clock_1__CFG1, CYREG_CLKDIST_DCFG0_CFG1
.set Clock_1__CFG2, CYREG_CLKDIST_DCFG0_CFG2
.set Clock_1__CFG2_SRC_SEL_MASK, 0x07
.set Clock_1__INDEX, 0x00
.set Clock_1__PM_ACT_CFG, CYREG_PM_ACT_CFG2
.set Clock_1__PM_ACT_MSK, 0x01
.set Clock_1__PM_STBY_CFG, CYREG_PM_STBY_CFG2
.set Clock_1__PM_STBY_MSK, 0x01

/* Mixer_1 */
.set Mixer_1_SC__BST, CYREG_SC2_BST
.set Mixer_1_SC__CLK, CYREG_SC2_CLK
.set Mixer_1_SC__CMPINV, CYREG_SC_CMPINV
.set Mixer_1_SC__CMPINV_MASK, 0x04
.set Mixer_1_SC__CPTR, CYREG_SC_CPTR
.set Mixer_1_SC__CPTR_MASK, 0x04
.set Mixer_1_SC__CR0, CYREG_SC2_CR0
.set Mixer_1_SC__CR1, CYREG_SC2_CR1
.set Mixer_1_SC__CR2, CYREG_SC2_CR2
.set Mixer_1_SC__MSK, CYREG_SC_MSK
.set Mixer_1_SC__MSK_MASK, 0x04
.set Mixer_1_SC__PM_ACT_CFG, CYREG_PM_ACT_CFG9
.set Mixer_1_SC__PM_ACT_MSK, 0x04
.set Mixer_1_SC__PM_STBY_CFG, CYREG_PM_STBY_CFG9
.set Mixer_1_SC__PM_STBY_MSK, 0x04
.set Mixer_1_SC__SR, CYREG_SC_SR
.set Mixer_1_SC__SR_MASK, 0x04
.set Mixer_1_SC__SW0, CYREG_SC2_SW0
.set Mixer_1_SC__SW10, CYREG_SC2_SW10
.set Mixer_1_SC__SW2, CYREG_SC2_SW2
.set Mixer_1_SC__SW3, CYREG_SC2_SW3
.set Mixer_1_SC__SW4, CYREG_SC2_SW4
.set Mixer_1_SC__SW6, CYREG_SC2_SW6
.set Mixer_1_SC__SW7, CYREG_SC2_SW7
.set Mixer_1_SC__SW8, CYREG_SC2_SW8
.set Mixer_1_SC__WRK1, CYREG_SC_WRK1
.set Mixer_1_SC__WRK1_MASK, 0x04

/* PhotoIn */
.set PhotoIn__0__INTTYPE, CYREG_PICU1_INTTYPE7
.set PhotoIn__0__MASK, 0x80
.set PhotoIn__0__PC, CYREG_PRT1_PC7
.set PhotoIn__0__PORT, 1
.set PhotoIn__0__SHIFT, 7
.set PhotoIn__AG, CYREG_PRT1_AG
.set PhotoIn__AMUX, CYREG_PRT1_AMUX
.set PhotoIn__BIE, CYREG_PRT1_BIE
.set PhotoIn__BIT_MASK, CYREG_PRT1_BIT_MASK
.set PhotoIn__BYP, CYREG_PRT1_BYP
.set PhotoIn__CTL, CYREG_PRT1_CTL
.set PhotoIn__DM0, CYREG_PRT1_DM0
.set PhotoIn__DM1, CYREG_PRT1_DM1
.set PhotoIn__DM2, CYREG_PRT1_DM2
.set PhotoIn__DR, CYREG_PRT1_DR
.set PhotoIn__INP_DIS, CYREG_PRT1_INP_DIS
.set PhotoIn__INTTYPE_BASE, CYDEV_PICU_INTTYPE_PICU1_BASE
.set PhotoIn__LCD_COM_SEG, CYREG_PRT1_LCD_COM_SEG
.set PhotoIn__LCD_EN, CYREG_PRT1_LCD_EN
.set PhotoIn__MASK, 0x80
.set PhotoIn__PORT, 1
.set PhotoIn__PRT, CYREG_PRT1_PRT
.set PhotoIn__PRTDSI__CAPS_SEL, CYREG_PRT1_CAPS_SEL
.set PhotoIn__PRTDSI__DBL_SYNC_IN, CYREG_PRT1_DBL_SYNC_IN
.set PhotoIn__PRTDSI__OE_SEL0, CYREG_PRT1_OE_SEL0
.set PhotoIn__PRTDSI__OE_SEL1, CYREG_PRT1_OE_SEL1
.set PhotoIn__PRTDSI__OUT_SEL0, CYREG_PRT1_OUT_SEL0
.set PhotoIn__PRTDSI__OUT_SEL1, CYREG_PRT1_OUT_SEL1
.set PhotoIn__PRTDSI__SYNC_OUT, CYREG_PRT1_SYNC_OUT
.set PhotoIn__PS, CYREG_PRT1_PS
.set PhotoIn__SHIFT, 7
.set PhotoIn__SLW, CYREG_PRT1_SLW

/* Miscellaneous */
.set BCLK__BUS_CLK__HZ, 24000000
.set BCLK__BUS_CLK__KHZ, 24000
.set BCLK__BUS_CLK__MHZ, 24
.set CYDEV_CHIP_DIE_LEOPARD, 1
.set CYDEV_CHIP_DIE_PSOC4A, 18
.set CYDEV_CHIP_DIE_PSOC5LP, 2
.set CYDEV_CHIP_DIE_PSOC5TM, 3
.set CYDEV_CHIP_DIE_TMA4, 4
.set CYDEV_CHIP_DIE_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_FM0P, 5
.set CYDEV_CHIP_FAMILY_FM3, 6
.set CYDEV_CHIP_FAMILY_FM4, 7
.set CYDEV_CHIP_FAMILY_PSOC3, 1
.set CYDEV_CHIP_FAMILY_PSOC4, 2
.set CYDEV_CHIP_FAMILY_PSOC5, 3
.set CYDEV_CHIP_FAMILY_PSOC6, 4
.set CYDEV_CHIP_FAMILY_UNKNOWN, 0
.set CYDEV_CHIP_FAMILY_USED, CYDEV_CHIP_FAMILY_PSOC5
.set CYDEV_CHIP_JTAG_ID, 0x2E161069
.set CYDEV_CHIP_MEMBER_3A, 1
.set CYDEV_CHIP_MEMBER_4A, 18
.set CYDEV_CHIP_MEMBER_4D, 13
.set CYDEV_CHIP_MEMBER_4E, 6
.set CYDEV_CHIP_MEMBER_4F, 19
.set CYDEV_CHIP_MEMBER_4G, 4
.set CYDEV_CHIP_MEMBER_4H, 17
.set CYDEV_CHIP_MEMBER_4I, 23
.set CYDEV_CHIP_MEMBER_4J, 14
.set CYDEV_CHIP_MEMBER_4K, 15
.set CYDEV_CHIP_MEMBER_4L, 22
.set CYDEV_CHIP_MEMBER_4M, 21
.set CYDEV_CHIP_MEMBER_4N, 10
.set CYDEV_CHIP_MEMBER_4O, 7
.set CYDEV_CHIP_MEMBER_4P, 20
.set CYDEV_CHIP_MEMBER_4Q, 12
.set CYDEV_CHIP_MEMBER_4R, 8
.set CYDEV_CHIP_MEMBER_4S, 11
.set CYDEV_CHIP_MEMBER_4T, 9
.set CYDEV_CHIP_MEMBER_4U, 5
.set CYDEV_CHIP_MEMBER_4V, 16
.set CYDEV_CHIP_MEMBER_5A, 3
.set CYDEV_CHIP_MEMBER_5B, 2
.set CYDEV_CHIP_MEMBER_6A, 24
.set CYDEV_CHIP_MEMBER_FM3, 28
.set CYDEV_CHIP_MEMBER_FM4, 29
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1, 25
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2, 26
.set CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3, 27
.set CYDEV_CHIP_MEMBER_UNKNOWN, 0
.set CYDEV_CHIP_MEMBER_USED, CYDEV_CHIP_MEMBER_5B
.set CYDEV_CHIP_DIE_EXPECT, CYDEV_CHIP_MEMBER_USED
.set CYDEV_CHIP_DIE_ACTUAL, CYDEV_CHIP_DIE_EXPECT
.set CYDEV_CHIP_REV_LEOPARD_ES1, 0
.set CYDEV_CHIP_REV_LEOPARD_ES2, 1
.set CYDEV_CHIP_REV_LEOPARD_ES3, 3
.set CYDEV_CHIP_REV_LEOPARD_PRODUCTION, 3
.set CYDEV_CHIP_REV_PSOC4A_ES0, 17
.set CYDEV_CHIP_REV_PSOC4A_PRODUCTION, 17
.set CYDEV_CHIP_REV_PSOC5LP_ES0, 0
.set CYDEV_CHIP_REV_PSOC5LP_PRODUCTION, 0
.set CYDEV_CHIP_REV_PSOC5TM_ES0, 0
.set CYDEV_CHIP_REV_PSOC5TM_ES1, 1
.set CYDEV_CHIP_REV_PSOC5TM_PRODUCTION, 1
.set CYDEV_CHIP_REV_TMA4_ES, 17
.set CYDEV_CHIP_REV_TMA4_ES2, 33
.set CYDEV_CHIP_REV_TMA4_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_3A_ES1, 0
.set CYDEV_CHIP_REVISION_3A_ES2, 1
.set CYDEV_CHIP_REVISION_3A_ES3, 3
.set CYDEV_CHIP_REVISION_3A_PRODUCTION, 3
.set CYDEV_CHIP_REVISION_4A_ES0, 17
.set CYDEV_CHIP_REVISION_4A_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4D_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD, 0
.set CYDEV_CHIP_REVISION_4E_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA, 0
.set CYDEV_CHIP_REVISION_4F_PRODUCTION_256K, 0
.set CYDEV_CHIP_REVISION_4G_ES, 17
.set CYDEV_CHIP_REVISION_4G_ES2, 33
.set CYDEV_CHIP_REVISION_4G_PRODUCTION, 17
.set CYDEV_CHIP_REVISION_4H_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4I_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4J_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4K_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4L_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4M_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4N_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4O_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4P_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4Q_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4R_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4S_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4T_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4U_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_4V_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_5A_ES0, 0
.set CYDEV_CHIP_REVISION_5A_ES1, 1
.set CYDEV_CHIP_REVISION_5A_PRODUCTION, 1
.set CYDEV_CHIP_REVISION_5B_ES0, 0
.set CYDEV_CHIP_REVISION_5B_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_6A_ES, 17
.set CYDEV_CHIP_REVISION_6A_NO_UDB, 33
.set CYDEV_CHIP_REVISION_6A_PRODUCTION, 33
.set CYDEV_CHIP_REVISION_FM3_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_FM4_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION, 0
.set CYDEV_CHIP_REVISION_USED, CYDEV_CHIP_REVISION_5B_PRODUCTION
.set CYDEV_CHIP_REV_EXPECT, CYDEV_CHIP_REVISION_USED
.set CYDEV_CONFIG_FASTBOOT_ENABLED, 1
.set CYDEV_CONFIG_UNUSED_IO_AllowButWarn, 0
.set CYDEV_CONFIG_UNUSED_IO, CYDEV_CONFIG_UNUSED_IO_AllowButWarn
.set CYDEV_CONFIG_UNUSED_IO_AllowWithInfo, 1
.set CYDEV_CONFIG_UNUSED_IO_Disallowed, 2
.set CYDEV_CONFIGURATION_COMPRESSED, 1
.set CYDEV_CONFIGURATION_DMA, 0
.set CYDEV_CONFIGURATION_ECC, 1
.set CYDEV_CONFIGURATION_IMOENABLED, CYDEV_CONFIG_FASTBOOT_ENABLED
.set CYDEV_CONFIGURATION_MODE_COMPRESSED, 0
.set CYDEV_CONFIGURATION_MODE, CYDEV_CONFIGURATION_MODE_COMPRESSED
.set CYDEV_CONFIGURATION_MODE_DMA, 2
.set CYDEV_CONFIGURATION_MODE_UNCOMPRESSED, 1
.set CYDEV_DEBUG_ENABLE_MASK, 0x20
.set CYDEV_DEBUG_ENABLE_REGISTER, CYREG_MLOGIC_DEBUG
.set CYDEV_DEBUGGING_DPS_Disable, 3
.set CYDEV_DEBUGGING_DPS_JTAG_4, 1
.set CYDEV_DEBUGGING_DPS_JTAG_5, 0
.set CYDEV_DEBUGGING_DPS_SWD, 2
.set CYDEV_DEBUGGING_DPS_SWD_SWV, 6
.set CYDEV_DEBUGGING_DPS, CYDEV_DEBUGGING_DPS_SWD_SWV
.set CYDEV_DEBUGGING_ENABLE, 1
.set CYDEV_DEBUGGING_XRES, 0
.set CYDEV_DMA_CHANNELS_AVAILABLE, 24
.set CYDEV_ECC_ENABLE, 0
.set CYDEV_HEAP_SIZE, 0x80
.set CYDEV_INSTRUCT_CACHE_ENABLED, 1
.set CYDEV_INTR_RISING, 0x00000000
.set CYDEV_IS_EXPORTING_CODE, 0
.set CYDEV_IS_IMPORTING_CODE, 0
.set CYDEV_PROJ_TYPE, 0
.set CYDEV_PROJ_TYPE_BOOTLOADER, 1
.set CYDEV_PROJ_TYPE_LAUNCHER, 5
.set CYDEV_PROJ_TYPE_LOADABLE, 2
.set CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER, 4
.set CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER, 3
.set CYDEV_PROJ_TYPE_STANDARD, 0
.set CYDEV_PROTECTION_ENABLE, 0
.set CYDEV_STACK_SIZE, 0x0800
.set CYDEV_USE_BUNDLED_CMSIS, 1
.set CYDEV_VARIABLE_VDDA, 0
.set CYDEV_VDDA_MV, 5000
.set CYDEV_VDDD_MV, 5000
.set CYDEV_VDDIO0_MV, 5000
.set CYDEV_VDDIO1_MV, 5000
.set CYDEV_VDDIO2_MV, 5000
.set CYDEV_VDDIO3_MV, 5000
.set CYDEV_VIO0_MV, 5000
.set CYDEV_VIO1_MV, 5000
.set CYDEV_VIO2_MV, 5000
.set CYDEV_VIO3_MV, 5000
.set CYIPBLOCK_ARM_CM3_VERSION, 0
.set CYIPBLOCK_P3_ANAIF_VERSION, 0
.set CYIPBLOCK_P3_CAN_VERSION, 0
.set CYIPBLOCK_P3_CAPSENSE_VERSION, 0
.set CYIPBLOCK_P3_COMP_VERSION, 0
.set CYIPBLOCK_P3_DECIMATOR_VERSION, 0
.set CYIPBLOCK_P3_DFB_VERSION, 0
.set CYIPBLOCK_P3_DMA_VERSION, 0
.set CYIPBLOCK_P3_DRQ_VERSION, 0
.set CYIPBLOCK_P3_DSM_VERSION, 0
.set CYIPBLOCK_P3_EMIF_VERSION, 0
.set CYIPBLOCK_P3_I2C_VERSION, 0
.set CYIPBLOCK_P3_LCD_VERSION, 0
.set CYIPBLOCK_P3_LPF_VERSION, 0
.set CYIPBLOCK_P3_OPAMP_VERSION, 0
.set CYIPBLOCK_P3_PM_VERSION, 0
.set CYIPBLOCK_P3_SCCT_VERSION, 0
.set CYIPBLOCK_P3_TIMER_VERSION, 0
.set CYIPBLOCK_P3_USB_VERSION, 0
.set CYIPBLOCK_P3_VIDAC_VERSION, 0
.set CYIPBLOCK_P3_VREF_VERSION, 0
.set CYIPBLOCK_S8_GPIO_VERSION, 0
.set CYIPBLOCK_S8_IRQ_VERSION, 0
.set CYIPBLOCK_S8_SAR_VERSION, 0
.set CYIPBLOCK_S8_SIO_VERSION, 0
.set CYIPBLOCK_S8_UDB_VERSION, 0
.set DMA_CHANNELS_USED__MASK0, 0x00000000
.set CYDEV_BOOTLOADER_ENABLE, 0
.endif