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

void (*CupSensor_1_status_callback)(uint8_t);
void (*CupSensor_1_hit_status_callback)(uint8_t);

const struct CupSensorUnit sensorTemplate =
{
    .placed_trigger = 40, // The value above baseline where the sensor changes to PLACED state
    .removed_trigger = 10, // The value above baseline where the sensor shanges to NOT_PLACED state
    .hit_trigger = 2.5f, //(hit trigger value)/(placed_baseline).
    .hit_lower_threshold = 1.0f   
};

struct CupSensorUnit sensors[6] = 
{
    {
    .placed_trigger = 15, // The value above baseline where the sensor changes to PLACED state
    .removed_trigger = 8, // The value above baseline where the sensor shanges to NOT_PLACED state
    .hit_trigger = 2.0f, //(hit trigger value)/(placed_baseline).
    .hit_lower_threshold = 1.0f   
    },
    {
    .placed_trigger = 15, // The value above baseline where the sensor changes to PLACED state
    .removed_trigger = 8, // The value above baseline where the sensor shanges to NOT_PLACED state
    .hit_trigger = 2.0f, //(hit trigger value)/(placed_baseline).
    .hit_lower_threshold = 1.0f   
    },
    {
    .placed_trigger = 15, // The value above baseline where the sensor changes to PLACED state
    .removed_trigger = 8, // The value above baseline where the sensor shanges to NOT_PLACED state
    .hit_trigger = 2.0f, //(hit trigger value)/(placed_baseline).
    .hit_lower_threshold = 1.0f   
    },
    {
    .placed_trigger = 15, // The value above baseline where the sensor changes to PLACED state
    .removed_trigger = 8, // The value above baseline where the sensor shanges to NOT_PLACED state
    .hit_trigger = 2.0f, //(hit trigger value)/(placed_baseline).
    .hit_lower_threshold = 1.0f   
    },
    {
    .placed_trigger = 15, // The value above baseline where the sensor changes to PLACED state
    .removed_trigger = 8, // The value above baseline where the sensor shanges to NOT_PLACED state
    .hit_trigger = 2.0f, //(hit trigger value)/(placed_baseline).
    .hit_lower_threshold = 1.0f   
    },
    {
    .placed_trigger = 15, // The value above baseline where the sensor changes to PLACED state
    .removed_trigger = 8, // The value above baseline where the sensor shanges to NOT_PLACED state
    .hit_trigger = 2.0f, //(hit trigger value)/(placed_baseline).
    .hit_lower_threshold = 1.0f   
    }
};



int16_t V_sample[1];
uint8_t CupSensor_1_cupStatus = 0;
uint8_t CupSensor_1_hitStatus = 0;

char buffer[256];
CY_ISR(newValueInterruptHandler)
{
    Test_time_pin_Write(1);
    
    uint8_t regValue = CupSensor_1_Control_Reg_Led_Read(); 
    if(V_sample[0] < 0) V_sample[0] = 0;
    
    uint8_t sampleValue = ((uint8_t)(V_sample[0]>>7)); //MSB is used to for sign, it is therefore not included
    
    if (regValue == 0){
        CupSensor_1_VDAC8_SetValue(sampleValue);
    }
    



    if(CupSensorUnit_insertReading(&(sensors[regValue]), sampleValue))
    {
        //State changed
        switch(sensors[regValue].state){
            case PLACED:
                CupSensor_1_cupStatus |= 1<<regValue;
                (*CupSensor_1_status_callback)(CupSensor_1_cupStatus);
            break;
            case NOT_PLACED:
                CupSensor_1_cupStatus &= ~(1<<regValue);
                (*CupSensor_1_status_callback)(CupSensor_1_cupStatus);
                if(CupSensor_1_hitStatus & (1<<regValue))
                {
                    CupSensor_1_hitStatus &= ~(1<<regValue);
                    (*CupSensor_1_hit_status_callback)(CupSensor_1_hitStatus);    
                }
            break;
            case HIT:
                CupSensor_1_hitStatus |= 1<<regValue;
                (*CupSensor_1_hit_status_callback)(CupSensor_1_hitStatus);
            break;
            default:
            break;
        }
    }
    
    regValue++;
    if(regValue>5) regValue = 0;
    CupSensor_1_Control_Reg_Led_Write(regValue);  
    Test_time_pin_Write(0);
}


void DMA_Filter_Config()
{
    /* Variable declarations for CupSensor_1_DMA_Filter */
    /* Move these variable declarations to the top of the function */
    uint8_t CupSensor_1_DMA_Filter_Chan;
    uint8_t CupSensor_1_DMA_Filter_TD[6];
    
    /* Defines for CupSensor_1_DMA_Filter */
    #define CupSensor_1_DMA_Filter_BYTES_PER_BURST 2
    #define CupSensor_1_DMA_Filter_REQUEST_PER_BURST 1
    #define CupSensor_1_DMA_Filter_SRC_BASE (CYDEV_PERIPH_BASE)
    #define CupSensor_1_DMA_Filter_DST_BASE (CYDEV_SRAM_BASE)

    /* DMA Configuration for CupSensor_1_DMA_Filter */
    CupSensor_1_DMA_Filter_Chan = CupSensor_1_DMA_Filter_DmaInitialize(CupSensor_1_DMA_Filter_BYTES_PER_BURST, CupSensor_1_DMA_Filter_REQUEST_PER_BURST, 
        HI16(CupSensor_1_DMA_Filter_SRC_BASE), HI16(CupSensor_1_DMA_Filter_DST_BASE));
    CupSensor_1_DMA_Filter_TD[0] = CyDmaTdAllocate();
    CupSensor_1_DMA_Filter_TD[1] = CyDmaTdAllocate();
    CupSensor_1_DMA_Filter_TD[2] = CyDmaTdAllocate();
    CupSensor_1_DMA_Filter_TD[3] = CyDmaTdAllocate();
    CupSensor_1_DMA_Filter_TD[4] = CyDmaTdAllocate();
    CupSensor_1_DMA_Filter_TD[5] = CyDmaTdAllocate();
    
    CyDmaTdSetConfiguration(CupSensor_1_DMA_Filter_TD[0], 2, CupSensor_1_DMA_Filter_TD[1], 0 );
    CyDmaTdSetConfiguration(CupSensor_1_DMA_Filter_TD[1], 2, CupSensor_1_DMA_Filter_TD[2], 0 );
    CyDmaTdSetConfiguration(CupSensor_1_DMA_Filter_TD[2], 2, CupSensor_1_DMA_Filter_TD[3], 0 );
    CyDmaTdSetConfiguration(CupSensor_1_DMA_Filter_TD[3], 2, CupSensor_1_DMA_Filter_TD[4], 0 );
    CyDmaTdSetConfiguration(CupSensor_1_DMA_Filter_TD[4], 2, CupSensor_1_DMA_Filter_TD[5], 0 );
    CyDmaTdSetConfiguration(CupSensor_1_DMA_Filter_TD[5], 2, CupSensor_1_DMA_Filter_TD[0], CupSensor_1_DMA_Filter__TD_TERMOUT_EN );
    
    CyDmaTdSetAddress(CupSensor_1_DMA_Filter_TD[0], LO16((uint32)CupSensor_1_ADC_DelSig_DEC_SAMP_PTR/*CupSensor_1_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(CupSensor_1_DMA_Filter_TD[1], LO16((uint32)CupSensor_1_ADC_DelSig_DEC_SAMP_PTR/*CupSensor_1_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(CupSensor_1_DMA_Filter_TD[2], LO16((uint32)CupSensor_1_ADC_DelSig_DEC_SAMP_PTR/*CupSensor_1_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(CupSensor_1_DMA_Filter_TD[3], LO16((uint32)CupSensor_1_ADC_DelSig_DEC_SAMP_PTR/*CupSensor_1_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(CupSensor_1_DMA_Filter_TD[4], LO16((uint32)CupSensor_1_ADC_DelSig_DEC_SAMP_PTR/*CupSensor_1_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(CupSensor_1_DMA_Filter_TD[5], LO16((uint32)CupSensor_1_ADC_DelSig_DEC_SAMP_PTR/*CupSensor_1_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
        
    CyDmaChSetInitialTd(CupSensor_1_DMA_Filter_Chan, CupSensor_1_DMA_Filter_TD[0]);
    CyDmaChEnable(CupSensor_1_DMA_Filter_Chan, 1);
   
}



void CupSensor_1_Start()
{
    for(size_t i = 0; i< 6; i++){
        CupSensorUnit_init(&sensors[i], SAMPLES_PER_SENSOR, 333);
    }
    CupSensor_1_TIA_Start();
    CupSensor_1_ADC_DelSig_Start();
    CupSensor_1_ADC_DelSig_SetCoherency(CupSensor_1_ADC_DelSig_COHER_MID);
    CupSensor_1_ADC_DelSig_StartConvert();
    CupSensor_1_VDAC8_Start();

     DMA_Filter_Config();
    
    CupSensor_1_isr_1_StartEx(newValueInterruptHandler);
}

void CupSensor_1_statusCallback(void (*callback)(uint8_t))
{
    CupSensor_1_status_callback=callback;
}

void CupSensor_1_hitStatusCallback(void (*callback)(uint8_t))
{
    CupSensor_1_hit_status_callback=callback;
}

uint8_t CupSensor_1_getStatus()
{
    return CupSensor_1_cupStatus;
}

uint8_t CupSensor_1_getHitStatus()
{
    return CupSensor_1_hitStatus;    
}



/* [] END OF FILE */
