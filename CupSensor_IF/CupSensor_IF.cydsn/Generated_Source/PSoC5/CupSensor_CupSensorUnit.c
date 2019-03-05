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

#include <project.h>

void CupSensorUnit_init(struct CupSensorUnit* sensorUnit, uint16_t bufferSize, uint16_t averageSize)
{
    CircularBuffer_init(&(sensorUnit->averageBuffer), averageSize);
    CircularBuffer_init(&(sensorUnit->buffer), bufferSize);
    sensorUnit->state = NOT_PLACED;
    
    sensorUnit->baseline = -1;
    sensorUnit->placed_baseline = -1;

}

void CupSensorUnit_calculateBaselines(struct CupSensorUnit* sensorUnit)
{
    switch (sensorUnit->state)
    {
        case NOT_PLACED:
        {
            if (sensorUnit->averageBuffer.reset == 0)
            {
                if(sensorUnit->averageBuffer.average >= 0)
                {
                    sensorUnit->baseline = sensorUnit->averageBuffer.average;
                }
            }
            sensorUnit->placed_baseline = -1;
        }    
        break;
        
        case PLACED:
        {
            if (sensorUnit->averageBuffer.reset == 0 || sensorUnit->averageBuffer.index > 70)
            {
                if(sensorUnit->averageBuffer.average)
                {
                    sensorUnit->placed_baseline = sensorUnit->averageBuffer.average - sensorUnit->baseline;
                }
            }
            else
            {
                sensorUnit->placed_baseline = -1;
            }
        }
        break;
        default:
        break;
    }
}


uint8_t CupSensorUnit_updateState(struct CupSensorUnit* sensorUnit)
{
    CUP_STATE oldState = sensorUnit->state;
    uint8_t lastReading;
    int8_t error = CircularBuffer_getLastReading(&(sensorUnit->averageBuffer), &lastReading);
    if(error == 0){
        if ((sensorUnit->baseline > 0))
        {
            switch (sensorUnit->state)
            {
                case NOT_PLACED:
                {
                    if((lastReading - sensorUnit->baseline) > sensorUnit->placed_trigger)
                    {
                        sensorUnit->state = VALIDATING_PLACED;
                        CircularBuffer_resetBuffer(&(sensorUnit->averageBuffer));
                    }
                }
                break;
                case VALIDATING_PLACED:
                {
                    if((lastReading - sensorUnit->baseline) < sensorUnit->removed_trigger)
                    {
                        sensorUnit->state = NOT_PLACED;
                        CircularBuffer_resetBuffer(&(sensorUnit->averageBuffer));
                    }
                    if(sensorUnit->averageBuffer.index >= 25)
                    {
                        sensorUnit->state = PLACED;
                        CircularBuffer_resetBuffer(&(sensorUnit->averageBuffer));    
                    }
                }
                break;
                
                case PLACED:
                {
                    if(((lastReading - sensorUnit->baseline) > (sensorUnit->hit_trigger * sensorUnit->placed_baseline)) && (sensorUnit->placed_baseline > 0))
                    {
                        sensorUnit->state = HIT;
                        CircularBuffer_resetBuffer(&(sensorUnit->averageBuffer));
                    }
                    if((lastReading - sensorUnit->baseline) < sensorUnit->removed_trigger)
                    {
                        sensorUnit->state = NOT_PLACED;
                        CircularBuffer_resetBuffer(&(sensorUnit->averageBuffer));
                    }
                }
                break;
                case HIT:
                {
                    if((lastReading - sensorUnit->baseline) < sensorUnit->removed_trigger)
                    {
                        sensorUnit->state = NOT_PLACED;
                        CircularBuffer_resetBuffer(&(sensorUnit->averageBuffer));
                    }
                }
                break;
            }
        }
    }
    if(oldState == sensorUnit->state)
    {
        return 0;    
    }
    else
    {
        if(oldState == VALIDATING_PLACED && sensorUnit->state == NOT_PLACED)
        {
            return 0;    
        }
        else
        {
            return 1;   
        }
    }
}

uint8_t CupSensorUnit_insertReading(struct CupSensorUnit* sensorUnit, uint8_t reading)
{
    
    CircularBuffer_insertReading(&(sensorUnit->averageBuffer), reading);
    CircularBuffer_calculateMinMax(&(sensorUnit->averageBuffer));
    uint8_t stateChanged = CupSensorUnit_updateState(sensorUnit);
    CupSensorUnit_calculateBaselines(sensorUnit);
    return stateChanged;

    
}

/* [] END OF FILE */
