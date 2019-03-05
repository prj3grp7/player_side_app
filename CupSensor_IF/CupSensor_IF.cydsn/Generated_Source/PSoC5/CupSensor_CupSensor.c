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

void (*CupSensor_status_callback)(uint8_t);
void (*CupSensor_hit_status_callback)(uint8_t);


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
uint8_t CupSensor_cupStatus = 0;
uint8_t CupSensor_hitStatus = 0;

char buffer[256];
CY_ISR(newValueInterruptHandler)
{
    Test_time_pin_Write(1);
    uint8_t regValue = CupSensor_Control_Reg_Led_Read(); 
    if(regValue + 1>5) CupSensor_Control_Reg_Led_Write(0);
    else CupSensor_Control_Reg_Led_Write(regValue + 1);
    
    if(V_sample[0] < 0) V_sample[0] = 0;
    
    uint8_t sampleValue = ((uint8_t)(V_sample[0]>>7)); //MSB is used to for sign, it is therefore not included

    if (regValue == 3){
        CupSensor_VDAC8_SetValue(sampleValue);
    }

    if(CupSensorUnit_insertReading(&(sensors[regValue]), sampleValue))
    {
        //State changed
        switch(sensors[regValue].state){
            case PLACED:
                CupSensor_cupStatus |= 1<<regValue;
                (*CupSensor_status_callback)(CupSensor_cupStatus);
            break;
            case NOT_PLACED:
                CupSensor_cupStatus &= ~(1<<regValue);
                (*CupSensor_status_callback)(CupSensor_cupStatus);
                if(CupSensor_hitStatus & (1<<regValue))
                {
                    CupSensor_hitStatus &= ~(1<<regValue);
                    (*CupSensor_hit_status_callback)(CupSensor_hitStatus);    
                }
            break;
            case HIT:
                CupSensor_hitStatus |= 1<<regValue;
                (*CupSensor_hit_status_callback)(CupSensor_hitStatus);
            break;
            default:
            break;
        }
    }
    
    Test_time_pin_Write(0);
}


void DMA_ADC_Config()
{
    /* Variable declarations for CupSensor_DMA_ADC */
    /* Move these variable declarations to the top of the function */
    uint8_t CupSensor_DMA_ADC_Chan;
    uint8_t CupSensor_DMA_ADC_TD[6];
    
    /* Defines for CupSensor_DMA_ADC */
    #define CupSensor_DMA_ADC_BYTES_PER_BURST 2
    #define CupSensor_DMA_ADC_REQUEST_PER_BURST 1
    #define CupSensor_DMA_ADC_SRC_BASE (CYDEV_PERIPH_BASE)
    #define CupSensor_DMA_ADC_DST_BASE (CYDEV_SRAM_BASE)

    /* DMA Configuration for CupSensor_DMA_ADC */
    CupSensor_DMA_ADC_Chan = CupSensor_DMA_ADC_DmaInitialize(CupSensor_DMA_ADC_BYTES_PER_BURST, CupSensor_DMA_ADC_REQUEST_PER_BURST, 
        HI16(CupSensor_DMA_ADC_SRC_BASE), HI16(CupSensor_DMA_ADC_DST_BASE));
    CupSensor_DMA_ADC_TD[0] = CyDmaTdAllocate();
    CupSensor_DMA_ADC_TD[1] = CyDmaTdAllocate();
    CupSensor_DMA_ADC_TD[2] = CyDmaTdAllocate();
    CupSensor_DMA_ADC_TD[3] = CyDmaTdAllocate();
    CupSensor_DMA_ADC_TD[4] = CyDmaTdAllocate();
    CupSensor_DMA_ADC_TD[5] = CyDmaTdAllocate();
    
    CyDmaTdSetConfiguration(CupSensor_DMA_ADC_TD[0], 2, CupSensor_DMA_ADC_TD[1], 0 );
    CyDmaTdSetConfiguration(CupSensor_DMA_ADC_TD[1], 2, CupSensor_DMA_ADC_TD[2], 0 );
    CyDmaTdSetConfiguration(CupSensor_DMA_ADC_TD[2], 2, CupSensor_DMA_ADC_TD[3], 0 );
    CyDmaTdSetConfiguration(CupSensor_DMA_ADC_TD[3], 2, CupSensor_DMA_ADC_TD[4], 0 );
    CyDmaTdSetConfiguration(CupSensor_DMA_ADC_TD[4], 2, CupSensor_DMA_ADC_TD[5], 0 );
    CyDmaTdSetConfiguration(CupSensor_DMA_ADC_TD[5], 2, CupSensor_DMA_ADC_TD[0], CupSensor_DMA_ADC__TD_TERMOUT_EN );
    
    CyDmaTdSetAddress(CupSensor_DMA_ADC_TD[0], LO16((uint32)CupSensor_ADC_DelSig_DEC_SAMP_PTR/*CupSensor_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(CupSensor_DMA_ADC_TD[1], LO16((uint32)CupSensor_ADC_DelSig_DEC_SAMP_PTR/*CupSensor_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(CupSensor_DMA_ADC_TD[2], LO16((uint32)CupSensor_ADC_DelSig_DEC_SAMP_PTR/*CupSensor_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(CupSensor_DMA_ADC_TD[3], LO16((uint32)CupSensor_ADC_DelSig_DEC_SAMP_PTR/*CupSensor_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(CupSensor_DMA_ADC_TD[4], LO16((uint32)CupSensor_ADC_DelSig_DEC_SAMP_PTR/*CupSensor_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
    CyDmaTdSetAddress(CupSensor_DMA_ADC_TD[5], LO16((uint32)CupSensor_ADC_DelSig_DEC_SAMP_PTR/*CupSensor_Filter_HOLDAH_PTR*/), LO16((uint32)V_sample));
        
    CyDmaChSetInitialTd(CupSensor_DMA_ADC_Chan, CupSensor_DMA_ADC_TD[0]);
    CyDmaChEnable(CupSensor_DMA_ADC_Chan, 1);
   
}



void CupSensor_Start()
{
    for(size_t i = 0; i< 6; i++){
        CupSensorUnit_init(&sensors[i], SAMPLES_PER_SENSOR, 333);
    }
    CupSensor_TIA_Start();
    CupSensor_ADC_DelSig_Start();
    CupSensor_ADC_DelSig_SetCoherency(CupSensor_ADC_DelSig_COHER_MID);
    CupSensor_ADC_DelSig_StartConvert();
    CupSensor_VDAC8_Start();

     DMA_ADC_Config();
    
    CupSensor_isr_DMA_StartEx(newValueInterruptHandler);
}

void CupSensor_statusCallback(void (*callback)(uint8_t))
{
    CupSensor_status_callback=callback;
}

void CupSensor_hitStatusCallback(void (*callback)(uint8_t))
{
    CupSensor_hit_status_callback=callback;
}

uint8_t CupSensor_getStatus()
{
    return CupSensor_cupStatus;
}

uint8_t CupSensor_getHitStatus()
{
    return CupSensor_hitStatus;    
}



/* [] END OF FILE */
