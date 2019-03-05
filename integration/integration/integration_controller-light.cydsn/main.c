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


void handleByteReceived(uint8_t byteReceived);

CY_ISR(blinking_LED)
{
    Timer_ReadStatusRegister();
    Interrupt_LED();
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
    initShiftRegPWM();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_1_StartEx(ISR_UART_rx_handler);
    RPI_IF_init();
    CyDelay(2000);
    isr_StartEx(blinking_LED);
    //sendCupStatus(0x41);
    for(;;)
    {
       RPi_IF_handleData();
       //CyDelay(1000);
       Controller();
    }
}


void handleByteReceived(uint8_t byteReceived)
{
    switch(byteReceived)
    {
        case 'q' :
        {
            updateCupStatus(0b00000000);
            updateHitStatus(0b00000000);
        }
        break;
        case 'w' :
        {
            updateCupStatus(0b00000001);
            updateHitStatus(0b00000000);
        }
        break;
        case 'e':
        {
            updateCupStatus(0b00000001);
            updateHitStatus(0b00000001);
        }
        break;
    }
}
/*void I2C_ISR_EntryCallback()
{
   UART_PutString("hey");
    RPi_IF_handleData();
}*/


/* [] END OF FILE */
