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
#include "light_control.h"

CY_ISR_PROTO(ISR_UART_rx_handler);
void handleByteReceived(uint8_t byteReceived);
int globalRed = 0;
int globalGreen = 0;
int globalBlue = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    UART_1_Start();
    UART_1_PutString("Program started\r\n"); 
    initLedControl();
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
            controlLight(0,(color_t)RED);
            UART_1_PutString("Red\r\n");
        }
        break;
        case 'w' :
        {
            controlLight(0,(color_t)GREEN);
            UART_1_PutString("Green\r\n");
        }
        break;
        case 'e' :
        {
            controlLight(0,(color_t)BLUE);
            UART_1_PutString("Blue\r\n");
        }
        break;
        case'a':
        {
            controlLight(1,(color_t)PURPLE);
            UART_1_PutString("Purple\r\n");
        }
        break;
        case's':
        {
            controlLight(1,(color_t)YELLOW);
            UART_1_PutString("Yellowish\r\n");
        }
        break;
        case'd':
        {
            controlLight(1,(color_t)TURQUOISE);
            UART_1_PutString("Turqish\r\n");
        }
        break;
        case'z':
        {
            globalRed+=5;
            controlLight(6,(color_t){globalRed,globalGreen,globalBlue});
        }
        break;
        case'x':
        {
            globalGreen+=5;
            controlLight(6,(color_t){globalRed,globalGreen,globalBlue});
        }
        break;
        case'c':
        {
            globalBlue+=5;
            controlLight(6,(color_t){globalRed,globalGreen,globalBlue});
        }
        break;
        default :
        {
            // nothing
        }
        break;
    }
}