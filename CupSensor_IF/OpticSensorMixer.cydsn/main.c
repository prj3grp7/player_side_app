/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

typedef enum   
{
    PLACED,
    NOT_PLACED
} PLACED_STATE;

typedef enum
{
    HIT,
    NOT_HIT
} HIT_STATE;

typedef struct{
    uint8_t OFF_VALUE;
    uint8_t ON_VALUE;

} schmitt_trigger;

HIT_STATE hit_state = NOT_HIT;
PLACED_STATE placed_state = NOT_PLACED;

schmitt_trigger placedTrigger =  {70, 135};
schmitt_trigger hitTrigger =  {125, 185};

uint32_t placedTime = 0;
uint32_t hitTime = 0;

uint8_t newState = 0;

uint8_t value = 0;
uint16 	V_Sample[1];
CY_ISR(newValueInterruptHandler)
{

    
    uint8_t newValue = V_Sample[0];
    if(newValue >= placedTrigger.ON_VALUE && placed_state != PLACED)
    {
        placed_state = PLACED;
        placedTime = 1;
        newState = 1;
    }
    else if (newValue <= placedTrigger.OFF_VALUE && placed_state != NOT_PLACED)
    {
        placed_state = NOT_PLACED;
        newState = 1;
 
    }
    
    if(newValue >= hitTrigger.ON_VALUE && hit_state != HIT)
    {
        if(placedTime > 10000)
        {
            hit_state = HIT;
            hitTime = 1;
            newState = 1;
 
        }
    }else if(newValue <= hitTrigger.OFF_VALUE && hit_state != NOT_HIT)
    {
        if(hitTime > 10000)
        {
            hit_state = NOT_HIT;
            newState = 1;
        }
    }
    
    
    if(placedTime != 0 && placedTime != 0xFFFFFFFF)
    {
        placedTime++;
    }
    if(hitTime != 0 && hitTime != 0xFFFFFFFF)
    {
        hitTime++;
    }
    
}



void DMA_1_Config()
{
    /* Variable declarations for DMA_1 */
    /* Move these variable declarations to the top of the function */
    uint8 DMA_1_Chan;
    uint8 DMA_1_TD[1];

    /* DMA Configuration for DMA_1 */
    #define DMA_1_BYTES_PER_BURST 1
    #define DMA_1_REQUEST_PER_BURST 1
    #define DMA_1_SRC_BASE (CYDEV_PERIPH_BASE)
    #define DMA_1_DST_BASE (CYDEV_PERIPH_BASE)
    DMA_1_Chan = DMA_1_DmaInitialize(DMA_1_BYTES_PER_BURST, DMA_1_REQUEST_PER_BURST, 
        HI16(DMA_1_SRC_BASE), HI16(DMA_1_DST_BASE));
    DMA_1_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_1_TD[0], 1, DMA_INVALID_TD, 0);
<<<<<<< HEAD
    CyDmaTdSetAddress(DMA_1_TD[0], LO16((uint32)ADC_DelSig_1_DEC_SAMP_PTR), LO16((uint32)VDAC8_1_Data_PTR));
=======
    CyDmaTdSetAddress(DMA_1_TD[0], LO16((uint32)ADC_DelSig_1_DEC_SAMP_PTR), LO16((uint32)Filter_1_STAGEAM_PTR));
>>>>>>> fix
    CyDmaChSetInitialTd(DMA_1_Chan, DMA_1_TD[0]);
    CyDmaChEnable(DMA_1_Chan, 1);

}

void DMA_2_Config()
{
<<<<<<< HEAD
    /* Variable declarations for DMA_2 */
    /* Move these variable declarations to the top of the function */
    uint8 DMA_2_Chan;
    uint8 DMA_2_TD[1];

    /* DMA Configuration for DMA_2 */
    #define DMA_2_BYTES_PER_BURST 1
    #define DMA_2_REQUEST_PER_BURST 1
    #define DMA_2_SRC_BASE (CYDEV_PERIPH_BASE)
    #define DMA_2_DST_BASE (CYDEV_PERIPH_BASE)
    
    
    DMA_2_Chan = DMA_2_DmaInitialize(DMA_2_BYTES_PER_BURST, DMA_2_REQUEST_PER_BURST, 
        HI16(DMA_2_SRC_BASE), HI16(DMA_2_DST_BASE));
    DMA_2_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_2_TD[0], 1, DMA_INVALID_TD, DMA_2__TD_TERMOUT_EN);
    CyDmaTdSetAddress(DMA_2_TD[0], LO16((uint32)Filter_1_HOLDAM_PTR), LO16((uint32)VDAC8_1_Data_PTR));
    CyDmaChSetInitialTd(DMA_2_Chan, DMA_2_TD[0]);
    CyDmaChEnable(DMA_2_Chan, 1);
=======
/* Variable declarations for DMA_2 */
/* Move these variable declarations to the top of the function */
uint8 DMA_2_Chan;
uint8 DMA_2_TD[1];

/* DMA Configuration for DMA_2 */
#define DMA_2_BYTES_PER_BURST 1
#define DMA_2_REQUEST_PER_BURST 1
#define DMA_2_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_2_DST_BASE (CYDEV_PERIPH_BASE)
DMA_2_Chan = DMA_2_DmaInitialize(DMA_2_BYTES_PER_BURST, DMA_2_REQUEST_PER_BURST, 
    HI16(DMA_2_SRC_BASE), HI16(DMA_2_DST_BASE));
DMA_2_TD[0] = CyDmaTdAllocate();
CyDmaTdSetConfiguration(DMA_2_TD[0], 1, DMA_INVALID_TD, DMA_2__TD_TERMOUT_EN);
CyDmaTdSetAddress(DMA_2_TD[0], LO16((uint32)Filter_1_HOLDAM_PTR), LO16((uint32)VDAC8_1_Data_PTR));
CyDmaChSetInitialTd(DMA_2_Chan, DMA_2_TD[0]);
CyDmaChEnable(DMA_2_Chan, 1);
>>>>>>> fix

}

void DMA_3_Config()
{
/* Variable declarations for DMA_3 */
/* Move these variable declarations to the top of the function */
uint8 DMA_3_Chan;
uint8 DMA_3_TD[1];

/* DMA Configuration for DMA_3 */
#define DMA_3_BYTES_PER_BURST 2
#define DMA_3_REQUEST_PER_BURST 1
#define DMA_3_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_3_DST_BASE (CYDEV_SRAM_BASE)
DMA_3_Chan = DMA_3_DmaInitialize(DMA_3_BYTES_PER_BURST, DMA_3_REQUEST_PER_BURST, 
    HI16(DMA_3_SRC_BASE), HI16(DMA_3_DST_BASE));
DMA_3_TD[0] = CyDmaTdAllocate();
CyDmaTdSetConfiguration(DMA_3_TD[0], 2, DMA_INVALID_TD,  DMA_3__TD_TERMOUT_EN );
CyDmaTdSetAddress(DMA_3_TD[0], LO16((uint32)Filter_1_HOLDAM_PTR), LO16((uint32)V_Sample));
CyDmaChSetInitialTd(DMA_3_Chan, DMA_3_TD[0]);
CyDmaChEnable(DMA_3_Chan, 1);

}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    TIA_1_Start();
    PWM_1_Start();
    Mixer_1_Start();
    ADC_DelSig_1_Start();
    ADC_DelSig_1_SetCoherency(ADC_DelSig_1_COHER_LOW);
    ADC_DelSig_1_StartConvert();
    VDAC8_1_Start();
    Filter_1_Start();
	Filter_1_SetCoherency(Filter_1_CHANNEL_A, Filter_1_KEY_MID);
    DMA_1_Config();
<<<<<<< HEAD
    //DMA_2_Config();
    //DMA_3_Config();
=======
    DMA_2_Config();
    DMA_3_Config();
>>>>>>> fix
    UART_Start();
    isr_1_StartEx(newValueInterruptHandler);
    UART_PutString("Cup Sensor app started\r\n");
    for(;;)
    {
        CyDelay(300);
        
        if(newState == 1)
        {
            UART_PutString("Der er ");
            switch (placed_state)
            {
                case PLACED:
                break;
                case NOT_PLACED:
                    UART_PutString("IKKE ");
                break;
            }
            UART_PutString("en kop\r\n");
            UART_PutString("Der er ");
            switch (hit_state)
            {
                case HIT:
                break;
                case NOT_HIT:
                    UART_PutString("IKKE ");
                break;
            }
            UART_PutString("en bold\r\n\r\n");
            newState=0;
        }
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
