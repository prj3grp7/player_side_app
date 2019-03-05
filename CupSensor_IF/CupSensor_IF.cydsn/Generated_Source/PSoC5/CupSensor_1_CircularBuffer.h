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

#if !defined(CIRCULAR_BUFFER_H)
#define CIRCULAR_BUFFER_H

#include <stdio.h>

#define BUFFER_SIZE 1024

struct CircularBuffer {
    uint8_t data[BUFFER_SIZE];
    uint16_t index;
    float  average;
    uint8_t min;
    uint8_t max;
    int8_t reset;
    uint32_t sum;
    uint16_t size;
};

void CircularBuffer_insertReading(struct CircularBuffer* buffer, uint8_t reading);

int8_t CircularBuffer_getLastReading(struct CircularBuffer* buffer, uint8_t * reading);

void CircularBuffer_init(struct CircularBuffer* buffer, uint16_t size);

void CircularBuffer_resetBuffer(struct CircularBuffer* buffer);

void CircularBuffer_calculateMinMax(struct CircularBuffer* buffer);

#endif /* CIRCULAR_BUFFER_H */

/* [] END OF FILE */
