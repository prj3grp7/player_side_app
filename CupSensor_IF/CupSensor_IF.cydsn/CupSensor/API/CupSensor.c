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
#include <stdio.h>
#include <project.h>

#define SAMPLES_PER_SENSOR 90 // Number of samples to make from sensor before changing to the next.

void (*`$INSTANCE_NAME`_status_callback)(uint8_t);
void (*`$INSTANCE_NAME`_hit_status_callback)(uint8_t);


struct CupSensorUnit sensors[6] = 
{
    {
    .placed_trigger = 11, // The value above baseline where the sensor changes to PLACED state
    .removed_trigger = 8, // The value above baseline where the sensor shanges to NOT_PLACED state
    .hit_trigger = 1.9f, //(hit trigger value)/(placed_baseline).
    .hit_lower_threshold = 1.0f   
    },
    {
    .placed_trigger = 11, // The value above baseline where the sensor changes to PLACED state
    .removed_trigger = 8, // The value above baseline where the sensor shanges to NOT_PLACED state
    .hit_trigger = 1.9f, //(hit trigger value)/(placed_baseline).
    .hit_lower_threshold = 1.0f   
    },
    {
    .placed_trigger = 11, // The value above baseline where the sensor changes to PLACED state
    .removed_trigger = 8, // The value above baseline where the sensor shanges to NOT_PLACED state
    .hit_trigger = 1.9f, //(hit trigger value)/(placed_baseline).
    .hit_lower_threshold = 1.0f   
    },
    {
    .placed_trigger = 11, // The value above baseline where the sensor changes to PLACED state
    .removed_trigger = 8, // The value above baseline where the sensor shanges to NOT_PLACED state
    .hit_trigger = 1.9f, //(hit trigger value)/(placed_baseline).
    .hit_lower_threshold = 1.0f   
    },
    {
    .placed_trigger = 11, // The value above baseline where the sensor changes to PLACED state
    .removed_trigger = 8, // The value above baseline where the sensor shanges to NOT_PLACED state
    .hit_trigger = 1.9f, //(hit trigger value)/(placed_baseline).
    .hit_lower_threshold = 1.0f   
    },
    {
    .placed_trigger = 11, // The value above baseline where the sensor changes to PLACED state
    .removed_trigger = 8, // The value above baseline where the sensor shanges to NOT_PLACED state
    .hit_trigger = 1.9f, //(hit trigger value)/(placed_baseline).
    .hit_lower_threshold = 1.0f   
    }
};



int16_t V_sample[1];
uint8_t `$INSTANCE_NAME`_cupStatus = 0;
uint8_t `$INSTANCE_NAME`_hitStatus = 0;

char buffer[256];
CY_ISR(newValueInterruptHandler)
{
    Test_time_pin_Write(1);
    uint8_t regValue = `$INSTANCE_NAME`_Control_Reg_Led_Read(); 
    if(regValue + 1>5) `$INSTANCE_NAME`_Control_Reg_Led_Write(0);
    else `$INSTANCE_NAME`_Control_Reg_Led_Write(regValue + 1);
    
    if(V_sample[0] < 0) V_sample[0] = 0;
    
    uint8_t sampleValue = ((uint8_t)(V_sample[0]>>7)); //MSB is used to for sign, it is therefore not included

    if (regValue == 3){
        `$INSTANCE_NAME`_VDAC8_SetValue(sampleValue);
    }

    if(CupSensorUnit_insertReading(&(sensors[regValue]), sampleValue))
    {
        //State changed
        switch(sensors[regValue].state){
            case PLACED:
                `$INSTANCE_NAME`_cupStatus |= 1<<regValue;
                (*`$INSTANCE_NAME`_status_callback)(`$INSTANCE_NAME`_cupStatus);
            break;
            case NOT_PLACED:
                `$INSTANCE_NAME`_cupStatus &= ~(1<<regValue);
                (*`$INSTANCE_NAME`_status_callback)(`$INSTANCE_NAME`_cupStatus);
                if(`$INSTANCE_NAME`_hitStatus & (1<<regValue))
                {
                    `$INSTANCE_NAME`_hitStatus &= ~(1<<regValue);
                    (*`$INSTANCE_NAME`_hit_status_callback)(`$INSTANCE_NAME`_hitStatus);    
                }
            break;
            case HIT:
                `$INSTANCE_NAME`_hitStatus |= 1<<regValue;
                (*`$INSTANCE_NAME`_hit_status_callback)(`$INSTANCE_NAME`_hitStatus);
            break;
            default:
            break;
        }
    }
    
    Test_time_pin_Write(0);
}


void DMA_ADC_Config()
{
    /* Variable declarations for `$INSTANCE_NAME`_DMA_ADC */
    /* Move these variable declarations to the top of the function */
    uint8_t `$INSTANCE_NAME`_DMA_ADC_Chan;
    uint8_t `$INSTANCE_NAME`_DMA_ADC_TD[6];
    
    /* Defines for `$INSTANCE_NAME`_DMA_ADC */
    #define `$INSTANCE_NAME`_DMA_ADC_BYTES_PER_BURST 2
    #define `$INSTANCE_NAME`_DMA_ADC_REQUEST_PER_BURST 1
    #define `$INSTANCE_NAME`_DMA_ADC_SRC_BASE (CYDEV_PERIPH_BASE)
    #define `$INSTANCE_NAME`_DMA_ADC_DST_BASE (CYDEV_SRAM_BASE)

    /* DMA Configuration for `$INSTANCE_NAME`_DMA_ADC */
    `$INSTANCE_NAME`_DMA_ADC_Chan = `$INSTANCE_NAME`_DMA_ADC_DmaInitialize(`$INSTANCE_NAME`_DMA_ADC_BYTES_PER_BURST, `$INSTANCE_NAME`_DMA_ADC_REQUEST_PER_BURST, 
        HI16(`$INSTANCE_NAME`_DMA_ADC_SRC_BASE), HI16(`$INSTANCE_NAME`_DMA_ADC_DST_BASE));
    `$INSTANCE_NAME`_DMA_ADC_TD[0] = CyDmaTdAllocate();
    `$INSTANCE_NAME`_DMA_ADC_TD[1] = CyDmaTdAllocate();
    `$INSTANCE_NAME`_DMA_ADC_TD[2] = CyDmaTdAllocate();
    `$INSTANCE_NAME`_DMA_ADC_TD[3] = CyDmaTdAllocate();
    `$INSTANCE_NAME`_DMA_ADC_TD[4] = CyDmaTdAllocate();
    `$INSTANCE_NAME`_DMA_ADC_TD[5] = CyDmaTdAllocate();
    
    CyDmaTdSetConfiguration(`$INSTANCE_NAME`_DMA_ADC_TD[0], 2, `$INSTANCE_NAME`_DMA_ADC_TD[1], 0 );
    CyDmaTdSetConfiguration(`$INSTANCE_NAME`_DMA_ADC_TD[1], 2, `$INSTANCE_NAME`_DMA_ADC_TD[2], 0 );
    CyDmaTdSetConfiguration(`$INSTANCE_NAME`_DMA_ADC_TD[2], 2, `$INSTANCE_NAME`_DMA_ADC_TD[3], 0 );
    CyDmaTdSetConfiguration(`$INSTANCE_NAME`_DMA_ADC_TD[3], 2, `$INSTANCE_NAME`_DMA_ADC_TD[4], 0 );
    CyDmaTdSetConfiguration(`$INSTANCE_NAME`_DMA_ADC_TD[4], 2, `$INSTANCE_NAME`_DMA_ADC_TD[5], 0 );
    CyDmaTdSetConfiguration(`$INSTANCE_NAME`_DMA_ADC_TD[5], 2, `$INSTANCE_NAME`_DMA_ADC_TD[0], `$INSTANCE_NAME`_DMA_ADC__TD_TERMOUT_EN );
    
    CyDmaTdSetAddress(`$INSTANCE_NAME`_DMA_ADC_TD[0], LO16((uint32)`$INSTANCE_NAME`_ADC_DelSig_DEC_SAMP_PTR/*`$INSTANCE_NAME`_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(`$INSTANCE_NAME`_DMA_ADC_TD[1], LO16((uint32)`$INSTANCE_NAME`_ADC_DelSig_DEC_SAMP_PTR/*`$INSTANCE_NAME`_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(`$INSTANCE_NAME`_DMA_ADC_TD[2], LO16((uint32)`$INSTANCE_NAME`_ADC_DelSig_DEC_SAMP_PTR/*`$INSTANCE_NAME`_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(`$INSTANCE_NAME`_DMA_ADC_TD[3], LO16((uint32)`$INSTANCE_NAME`_ADC_DelSig_DEC_SAMP_PTR/*`$INSTANCE_NAME`_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(`$INSTANCE_NAME`_DMA_ADC_TD[4], LO16((uint32)`$INSTANCE_NAME`_ADC_DelSig_DEC_SAMP_PTR/*`$INSTANCE_NAME`_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(`$INSTANCE_NAME`_DMA_ADC_TD[5], LO16((uint32)`$INSTANCE_NAME`_ADC_DelSig_DEC_SAMP_PTR/*`$INSTANCE_NAME`_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
        
    CyDmaChSetInitialTd(`$INSTANCE_NAME`_DMA_ADC_Chan, `$INSTANCE_NAME`_DMA_ADC_TD[0]);
    CyDmaChEnable(`$INSTANCE_NAME`_DMA_ADC_Chan, 1);
   
}



void `$INSTANCE_NAME`_Start()
{
    for(size_t i = 0; i< 6; i++){
        CupSensorUnit_init(&sensors[i], SAMPLES_PER_SENSOR, 333);
    }
    `$INSTANCE_NAME`_TIA_Start();
    `$INSTANCE_NAME`_ADC_DelSig_Start();
    `$INSTANCE_NAME`_ADC_DelSig_SetCoherency(`$INSTANCE_NAME`_ADC_DelSig_COHER_MID);
    `$INSTANCE_NAME`_ADC_DelSig_StartConvert();
    `$INSTANCE_NAME`_VDAC8_Start();

     DMA_ADC_Config();
    
    `$INSTANCE_NAME`_isr_DMA_StartEx(newValueInterruptHandler);
}

void `$INSTANCE_NAME`_statusCallback(void (*callback)(uint8_t))
{
    `$INSTANCE_NAME`_status_callback=callback;
}

void `$INSTANCE_NAME`_hitStatusCallback(void (*callback)(uint8_t))
{
    `$INSTANCE_NAME`_hit_status_callback=callback;
}

uint8_t `$INSTANCE_NAME`_getStatus()
{
    return `$INSTANCE_NAME`_cupStatus;
}

uint8_t `$INSTANCE_NAME`_getHitStatus()
{
    return `$INSTANCE_NAME`_hitStatus;    
}



/* [] END OF FILE */
