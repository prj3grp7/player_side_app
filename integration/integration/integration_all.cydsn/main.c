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

//#include "cyapicallbacks.h"
#include "project.h"
#include "RPI_IF.h"
#include "string.h"
#include "GameController.h"

#define I2C_ISR_ENTRY_CALLBACK
#define I2C_ISR_EXIT_CALLBACK

void handleByteReceived(uint8_t byteReceived);

CY_ISR(blinking_LED)
{
    Timer_ReadStatusRegister();
    interruptBlink();
}

CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_ReadRxData();
        UART_WriteTxData(byteReceived); // echo back
        
        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Start();
    UART_PutString("Program started\n\r");
    isr_UART_StartEx(ISR_UART_rx_handler);
    
    initShiftRegPWM();
    CupSensor_IF_init();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    RPI_IF_init();
    isr_BLINK_TIMER_StartEx(blinking_LED);
    //sendCupStatus(0x41);
    setState(PLAYING);
    CyDelay(2000);
    //test_LED_Write(1);
    for(;;)
    {
       Controller();
    }
}

void I2C_ISR_EntryCallback()
{
    test_LED_Write(1);
}

void I2C_ISR_ExitCallback()
{
    test_LED_Write(0);
}

void handleByteReceived(uint8_t byteReceived)
{
    switch(byteReceived)
    {
        case '0' : 
        {
            updateCupStatus(0b00000000);
        }
        break;
        case '1' :
        {
            updateCupStatus(0b00000001);
        }
        break;
        case '2' :
        {
            updateCupStatus(0b00000011);
        }
        break;
        case '3':
        {
            updateCupStatus(0b00000111);
        }
        break;
        case '4':
        {
            updateCupStatus(0b00001111);
        }
        break;
        case '5':
        {
            updateCupStatus(0b00011111);
        }
        break;
        case '6':
        {
            updateCupStatus(0b00111111);
        }
        break;
    }
}
/* [] END OF FILE */
