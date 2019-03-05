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

#include "GameController.h"
#include <stdint.h>

/*typedef struct color
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
}color_t;*/

enum GameState{IDLE,STARTING,PLAYING,WON,LOST}currentState;
static color_t turnedOffColor;
static color_t missingCupColor;
static color_t placedCupColor;
static color_t myColor;
static color_t opponentColor;
static uint8_t CupStatus;
static uint8_t hitStatus;

void setState(enum GameState state)
{
   switch(state)
    {
        case IDLE:
        {
            if(currentState==WON || currentState==LOST)
            {
                currentState=state;
                UART_Putstring("turnedOffColor turns On. State==IDLE\n");
            }
            break;
        }
        case STARTING:
        {
            if(currentState==IDLE)
            {
                currentState=state;
                UART_Putstring("get cupstatus\n");
                sendCupStatus(CupStatus);
                UART_Putstring("State==STARTING\n");
            }
            break;
        }
        case PLAYING:
        {
            if(currentState==PLAYING)
            {
                currentState=state;
                UART_Putstring("get cupstatus\n");
                sendCupStatus(CupStatus);
                UART_Putstring("State==PLAYING\n");
            }
            break;
        }
        case WON:
        {
            if(currentState==PLAYING)
            {
                currentState=state;
                UART_Putstring("You won and wining lights turn on\n");
                UART_Putstring("state==WON\n");
            }
            break;
        }
        case LOST:
        {
            if(currentState==PLAYING)
            {
                currentState=state;
                UART_Putstring("You won and losing lights turn on\n");
                UART_Putstring("state==WON\n");
            }
            break;
        }    
    }
}
 void setMyColor(color_t c)
{
    myColor=c;
}
 void setOpponentClor(color_t c)
{
    opponentColor=c;
}
 void updateCupStatus(uint8_t status)
{
    CupStatus=status;
    if(currentState==STARTING || currentState==PLAYING)
    {
        CupStatus=status;
        UART_Putstring("Sending cupstatus. Updating cupstatus\n");
        sendCupStatus(CupStatus);
    }
    
}
 void updateHitStatus(uint8_t status)
{
    if(currentState==PLAYING)
    {
        hitStatus=status;
        UART_Putstring("Sending Hitstatus. Updating Hitstatus\n");
        sendCupStatus(hitStatus); 
    }
}

/* [] END OF FILE */
