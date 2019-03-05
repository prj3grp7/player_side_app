
#include <stdbool.h>
#include "project.h"
#include "ShiftRegPWM.h"
#include "CupLight_IF.h"

#define LEDTOTEST 2

CY_ISR_PROTO(ISR_UART_rx_handler);
void handleByteReceived(uint8_t byteReceived);

uint8_t globalRed = 0;
uint8_t globalGreen = 0;
uint8_t globalBlue = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    UART_1_Start();
    UART_1_PutString("Program started\r\n"); 
    initShiftRegPWM();
    for(;;)
    {
    }
}

CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_1_GetRxBufferSize();    
    //Read bytes
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_1_ReadRxData();
        UART_1_WriteTxData(byteReceived); // echo back
        
        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}

void handleByteReceived(uint8_t byteReceived)
{
    switch(byteReceived)
    {
        case 'q' :
        {
            globalRed = 255;
            controlLight(LEDTOTEST,(color_t){globalRed,globalGreen,globalBlue});
        }
        break;
        case 'w' :
        {
            globalGreen = 255;
            controlLight(LEDTOTEST,(color_t){globalRed,globalGreen,globalBlue});
        }
        break;
        case 'e' :
        {
            globalBlue = 255;
            controlLight(LEDTOTEST,(color_t){globalRed,globalGreen,globalBlue});
        }
        break;
        case 'a' :
        {
            globalRed += 5;
            controlLight(LEDTOTEST,(color_t){globalRed,globalGreen,globalBlue});
        }
        break;
        case 's' :
        {
            globalGreen += 5;
            controlLight(LEDTOTEST,(color_t){globalRed,globalGreen,globalBlue});
        }
        break;
        case 'd' :
        {
            globalBlue += 5;
            controlLight(LEDTOTEST,(color_t){globalRed,globalGreen,globalBlue});
        }
        break;
        break;
        default :
        {
            // nothing
        }
        break;
    }
}