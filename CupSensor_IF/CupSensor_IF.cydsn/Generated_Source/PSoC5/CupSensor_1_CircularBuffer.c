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
#include "CupSensor_1_CircularBuffer.h"

void CircularBuffer_calculateMinMax(struct CircularBuffer* buffer)
{
    buffer->min = 0xFF;
    buffer->max = 0x00;
    int countSize = buffer->size;
    if(buffer->reset == 1)
    {
        countSize = buffer->index;
    }
    for(size_t i = 0; i < countSize; i++)
    {
        if(buffer->min > buffer->data[i]) buffer->min = buffer->data[i]; 
        if(buffer->max < buffer->data[i]) buffer->max = buffer->data[i];    
    }
    
}

void CircularBuffer_insertReading(struct CircularBuffer* buffer, uint8_t reading)
{
    if(buffer->reset){
        buffer->sum += reading;
        buffer->data[buffer->index++] = reading;
        buffer->average = (float)buffer->sum/buffer->index;
        if(buffer->index >= buffer->size)
        {
            //just filled up the buffer
            buffer->reset = 0;
        } 
    }
    else
    {
        uint8_t oldData = buffer->data[buffer->index];
        buffer->data[buffer->index++] = reading;
        buffer->sum += reading-oldData;
        buffer->average = (((float)buffer->sum)/buffer->size);
    }
    
    if(buffer->index >= buffer->size)
    {
        buffer->index = 0;
    }
}

int8_t CircularBuffer_getLastReading(struct CircularBuffer* buffer, uint8_t * reading)
{
    if(buffer->index == 0)
    {
        if(buffer->reset == 0)
        {
            *reading = buffer->data[buffer->size - 1];
            return 0; //No error
        }
        else
        {
            return -1; //Error
        }
    }
    else
    {
        *reading = buffer->data[buffer->index - 1]; 
        return 0; //No error
    }
}


void CircularBuffer_init(struct CircularBuffer* buffer, uint16_t size)
{
    if(size > BUFFER_SIZE) size = BUFFER_SIZE;
    buffer->size = size;
    CircularBuffer_resetBuffer(buffer);
}

void CircularBuffer_resetBuffer(struct CircularBuffer* buffer)
{
    buffer->index = 0;
    buffer->average = -1;
    buffer->min = 0xFF;
    buffer->max = 0;
    buffer->reset = 1;
    buffer->sum = 0;
}

/* [] END OF FILE */
