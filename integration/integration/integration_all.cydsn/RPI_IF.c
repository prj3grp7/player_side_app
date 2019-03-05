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

#include "RPI_IF.h"
#include <string.h>
#include <stdio.h>
//#include "GameController.h"
//static uint8_t Cup_status_ready = 0;
//static uint8_t Cup_status_requested = 1;
//static uint8_t Data_Ready=0b00000000;
//static uint8_t Data_not_Ready=0b11111111;
//static uint8_t buf[2];

#define IDLE_DATA 0x0A
#define STARTING_DATA 0x0B
#define PLAYING_DATA 0x0C
#define LOST_DATA 0x0D
#define WON_DATA 0x0E
#define COLOR_MSG 0x21
#define OPPONENT_COLOR 0x02
#define OWN_COLOR 0x01


void resetReadBuffer();
void resetWriteBuffer();

static char buf[50];
int n;
volatile int timer_run_out=0;

uint8_t readBuffer[256];
uint8_t writeBuffer[256];

/*void setState(uint8_t a)
{
    n=sprintf(buf,"Modstanders farver: %d\n\r",a);
    UART_PutString(buf);
}*/



void RPI_IF_init()
{
    I2C_Start();
    I2C_EnableInt();
    
    
    I2C_SlaveInitReadBuf((uint8_t*)readBuffer,1);
    I2C_SlaveInitWriteBuf((uint8_t*)writeBuffer,255);
    
    resetReadBuffer();

}

void resetReadBuffer()
{
    for(int i = 0; i < 255; i++)
    {
        readBuffer[i] = 0xFF;
    }
 
}


void sendCupStatus(uint8_t status)
{
    resetReadBuffer();
    readBuffer[0] = status;
    I2C_SlaveClearReadBuf();
    Interrupt_Write(0);
    CyDelay(1);
    Interrupt_Write(1);
}

void RPi_IF_handleData()
{
    if(I2C_SlaveClearWriteStatus() & I2C_SSTAT_WR_CMPLT)
    {
        for(int i = 0; i < I2C_SlaveGetWriteBufSize(); i++)
        {
            switch (writeBuffer[i])
            {
                case IDLE_DATA:{
                    setState(IDLE);
                    break;}
                case STARTING_DATA:{
                    setState(STARTING);
                    break;}
                case PLAYING_DATA:{
                    setState(PLAYING);
                    break;} 
                case LOST_DATA:{
                    setState(LOST);
                    break;} 
                case WON_DATA:{
                    setState(WON);
                    break;}
                case COLOR_MSG:
                {
                    ++i;
                    color_t color;
                    if(writeBuffer[i]==OWN_COLOR)
                    {
                        color.Red = writeBuffer[++i];
                        color.Green = writeBuffer[++i];
                        color.Blue = writeBuffer[++i];
                        n=sprintf(buf,"Egen farve: %d%d%d\n\r",
                        color.Red,color.Green,color.Blue);
                        setMyColor(color);
                        UART_PutString(buf);
                        
                    }
                    else if(writeBuffer[i]==OPPONENT_COLOR)
                    {
                        color.Red = writeBuffer[++i];
                        color.Green = writeBuffer[++i];
                        color.Blue = writeBuffer[++i];
                        n=sprintf(buf,"Modstanders farver: %d%d%d\n\r",
                            color.Red,
                            color.Green,
                            color.Blue);
                        setOpponentColor(color);
                        UART_PutString(buf);
                    }
                    break;
                }   
            }
        }
        I2C_SlaveClearWriteBuf();
    }
}






/* [] END OF FILE */
