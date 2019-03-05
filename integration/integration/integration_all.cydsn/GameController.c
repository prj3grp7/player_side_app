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
#include <stdio.h>

static int blinking =0;
static color_t turnedOffColor={.Red=0,.Green=0,.Blue=0,};
static color_t myColor={.Red=0,.Green=255,.Blue=0,};
static color_t opponentColor={.Red=255,.Green=0,.Blue=255,};
static color_t missingCupColor={.Red=255,.Green=255,.Blue=0,};
static color_t placedCupColor={.Red=0,.Green=0,.Blue=255,};
static uint8_t CupStatus;
static uint8_t hitStatus;
static char game_buf[256];
static uint8_t LED_states[8];
static uint8_t CupStatus_latest=0b11000000;

//#define STUB
//#define HIT_ANIMATION

void setState(enum GameState state)
{
   switch(state)
    {
        case IDLE:
        {
                currentState=state;
                UART_PutString("State==IDLE\n\r");
                controlAllLights(turnedOffColor);
        }
        break;
        case STARTING:
        {
                currentState=state;
                #ifdef STUB
                    CupStatus = 0;
                #else
                    CupStatus=getStatus();
                #endif
                ControlLights();
                sendCupStatus(CupStatus);
                UART_PutString("State==STARTING\n\r");
        }
        break;
        case PLAYING:
        {
                currentState=state;
                CupStatus=getStatus();
                #ifdef STUB
                    CupStatus = 0b00111111;
                #else
                    CupStatus=getStatus();
                #endif
                ControlLights();
                sendCupStatus(CupStatus);
                UART_PutString("State==PLAYING\n\r");
        }
        break;
        case WON:
        {
                currentState=state;
                controlAllLights(myColor);
                UART_PutString("state==WON\n\r");
        }
        break;
        case LOST:
        {
                currentState=state;
                controlAllLights(opponentColor);
                UART_PutString("state==LOST\n\r");
        }  
         break;
    }
}
 void setMyColor(color_t c)
{
    myColor=c;
    ControlLights();
}
 void setOpponentColor(color_t c)
{
    opponentColor=c;
     ControlLights();
}
 void updateCupStatus(uint8_t status)
{
    //if(!(status & 1<<1) && (CupStatus & 1<<1)) test_LED_Write(0);
    //else test_LED_Write(0);
    
    if((currentState==STARTING || currentState==PLAYING) )
    {
        CupStatus=status;
        //sprintf(game_buf,"Sending cupstatus. Updating cupstatus with cupstatus:%x\n\r",CupStatus);
        //UART_PutString(game_buf);
        //sendCupStatus(CupStatus);
    }
    
}
 void updateHitStatus(uint8_t status)
{
    if(currentState==PLAYING && (status == getHitStatus()))
    {
        #ifdef HIT_ANIMATION
        if(status != hitStatus)
        {
            if((status^hitStatus)&(1<<0) && (status&(1<<0)))
            {
                controlLight(0,opponentColor);
                CyDelay(50);
                controlLight(0,myColor);
                controlLight(1,opponentColor);
                controlLight(2,opponentColor);
                CyDelay(50);
                controlLight(1,myColor);
                controlLight(2,myColor);
                controlLight(3,opponentColor);
                controlLight(4,opponentColor);
                controlLight(5,opponentColor);
                CyDelay(50);
                controlLight(3,myColor);
                controlLight(4,myColor);
                controlLight(5,myColor);
                
                
            }
            else if((status^hitStatus)&(1<<1) && (status&(1<<1)))
            {
                controlLight(1,opponentColor);
                CyDelay(50);
                controlLight(1,myColor);
                
                controlLight(0,opponentColor);
                controlLight(2,opponentColor);
                controlLight(3,opponentColor);
                controlLight(4,opponentColor);
                CyDelay(50);
                controlLight(0,myColor);
                controlLight(2,myColor);
                controlLight(3,myColor);
                controlLight(4,myColor);
                
                controlLight(5,opponentColor);
                CyDelay(50);
                controlLight(5,myColor);
            }else if((status^hitStatus)&(1<<2) && (status&(1<<2)))
            {
                controlLight(2,opponentColor);
                CyDelay(50);
                controlLight(2,myColor);
                
                controlLight(0,opponentColor);
                controlLight(1,opponentColor);
                controlLight(5,opponentColor);
                controlLight(4,opponentColor);
                CyDelay(50);
                controlLight(0,myColor);
                controlLight(1,myColor);
                controlLight(5,myColor);
                controlLight(4,myColor);
                
                controlLight(3,opponentColor);
                CyDelay(50);
                controlLight(3,myColor);
            }else if((status^hitStatus)&(1<<3) && (status&(1<<3)))
            {
                controlLight(3,opponentColor);
                CyDelay(50);
                controlLight(3,myColor);
                
                controlLight(1,opponentColor);
                controlLight(4,opponentColor);
                CyDelay(50);
                controlLight(1,myColor);
                controlLight(4,myColor);
                
                controlLight(0,opponentColor);
                controlLight(2,opponentColor);
                controlLight(5,opponentColor);
                CyDelay(50);
                controlLight(0,myColor);
                controlLight(2,myColor);
                controlLight(5,myColor);
            }else if((status^hitStatus)&(1<<4) && (status&(1<<4)))
            {
                controlLight(4,opponentColor);
                CyDelay(50);
                controlLight(4,myColor);
                
                controlLight(1,opponentColor);
                controlLight(2,opponentColor);
                controlLight(3,opponentColor);
                controlLight(5,opponentColor);
                CyDelay(50);
                controlLight(1,myColor);
                controlLight(2,myColor);
                controlLight(3,myColor);
                controlLight(5,myColor);
                
                controlLight(0,opponentColor);
                CyDelay(50);
                controlLight(0,myColor);
            }else if((status^hitStatus)&(1<<5) && (status&(1<<5)))
            {
                controlLight(5,opponentColor);
                CyDelay(50);
                controlLight(5,myColor);
                
                controlLight(2,opponentColor);
                controlLight(4,opponentColor);
                CyDelay(50);
                controlLight(2,myColor);
                controlLight(4,myColor);
                
                controlLight(0,opponentColor);
                controlLight(1,opponentColor);
                controlLight(3,opponentColor);
                CyDelay(50);
                controlLight(0,myColor);
                controlLight(1,myColor);
                controlLight(3,myColor);
            }
        }
        #endif
        hitStatus=status;
        //UART_PutString("Sending Hitstatus. Updating Hitstatus\n\r"); 
        
    }
}

void ControlLights()
{
    if(currentState==STARTING){
        UART_PutString("Controlling lights\n\r");
        for(int i=0;i<6;i++)
        {
            if(((~CupStatus)>>i) & 1)
                controlLight(i,missingCupColor);
            else
                controlLight(i,placedCupColor);
        }
    }else if( currentState==PLAYING){
        UART_PutString("Controlling lights\n\r");
        for(int i=0;i<6;i++)
        {
            if(((~CupStatus)>>i) & 1)
                controlLight(i,opponentColor);
            else
                controlLight(i,myColor);
        }
    }
}

void Controller()
{
    RPi_IF_handleData();
    //CupStatus = getStatus();
    if(currentState==STARTING || currentState==PLAYING){
        if(CupStatus!=CupStatus_latest){
            CupStatus_latest=CupStatus;
            ControlLights();
            sprintf(game_buf,"Cupstatus change:%d\n\r",CupStatus);
            UART_PutString(game_buf);
        }
    if(currentState==PLAYING)
    {
        if(hitStatus && !blinking)
        {
            UART_PutString("Starting timer\n\r");
            Timer_Start();
            blinking=1;
        }
        else if(!hitStatus && blinking)
        {
            UART_PutString("Stopping timer\n\r");
            Timer_Stop(); 
            blinking=0;
        }
    }
    }
    else
    {
        if(blinking){
            Timer_Stop();
            blinking=0;
        }
    }
}


void interruptBlink()
{ 
    if(currentState==PLAYING)
        for(uint8_t i=0;i<6;i++)
        {
            if((hitStatus>>i) & 1){
                if(LED_states[i]){
                    controlLight(i,myColor);
                    LED_states[i]=0;}
                else{
                    controlLight(i,opponentColor);
                    LED_states[i]=1;}
                    
             }
        }
}


/* [] END OF FILE */
