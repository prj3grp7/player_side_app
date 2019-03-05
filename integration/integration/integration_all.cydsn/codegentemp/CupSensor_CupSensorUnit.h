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

#if !defined(CupSensor_CUP_SESNOR_UNIT_H)
#define CupSensor_CUP_SESNOR_UNIT_H
    
#include <project.h>
//#include "CupSensor_CircularBuffer.h"


typedef enum {
    NOT_PLACED, //No cup on sensor
    VALIDATING_PLACED, // Validating if cup is placed
    PLACED,     //A cup on sensor
    VALIDATING_HIT, // Validating if cup has bin hit
    HIT         //A cup on sensor which has been hit
} CUP_STATE; 

struct CupSensorUnit {
    CUP_STATE state;
    int16_t baseline; // The "offset" of the sensor, ie. the average reading when no cup is on the sensor. Is set automaticly
    int16_t placed_baseline; // The average reading minus baseline when a cup is on the sensor. Is set automaticly
    uint8_t placed_trigger; // The value above baseline where the sensor changes to PLACED state
    uint8_t removed_trigger; // The value above baseline where the sensor shanges to NOT_PLACED state
    float hit_trigger; //(hit trigger value)/(placed_baseline).
    float hit_lower_threshold;
    struct CircularBuffer buffer;
    struct CircularBuffer averageBuffer;
    uint8_t removedCount;
};

void CupSensorUnit_init(struct CupSensorUnit* sensorUnit, uint16_t bufferSize, uint16_t averageSize);

void CupSensorUnit_calculateBaselines(struct CupSensorUnit* sensorUnit);

uint8_t CupSensorUnit_updateState(struct CupSensorUnit* sensorUnit);

uint8_t CupSensorUnit_insertReading(struct CupSensorUnit* sensorUnit, uint8_t reading);

#endif /* CUP_SESNOR_UNIT_H */
/* [] END OF FILE */
