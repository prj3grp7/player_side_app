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
static color_t myColor={.Red=0,.Green=255,.Blue=255,};
static color_t opponentColor={.Red=255,.Green=0,.Blue=255,};
static color_t missingCupColor={.Red=255,.Green=255,.Blue=0,};
static color_t placedCupColor={.Red=0,.Green=0,.Blue=255,};
static uint8_t CupStatus;
static uint8_t hitStatus;
static char game_buf[256];
static int nn;
static uint8_t LED_states[8];
static uint8_t CupStatus_latest=0;

void setState(enum GameState state)
{
   switch(state)
    {
        case IDLE:
        {
                currentState=state;
                UART_PutString("State==IDLE\n\r");
                ControlAllColor(turnedOffColor); //alle kopholder lys slukkes
        }
        break;
        case STARTING:
        {
                currentState=state;
                CupStatus=getCupStatus();   //CupStatus fås fra CupSensor_IF
                ControlLights(CupStatus);   //kopholder lys opdateres efter CupStatus med missingCupColor eller placedCupColor
                sendCupStatus(CupStatus);   //Cupstatus sendes til RPI
                UART_PutString("State==STARTING\n\r");
            break;
        }
        case PLAYING:
        {
                currentState=state;
                CupStatus=getCupStatus();
                ControlLights(CupStatus);   //kopholder lys opdateres efter CupStatus med myColor eller opponentColor
                sendCupStatus(CupStatus);   //Cupstatus sendes til RPI
                UART_PutString("State==PLAYING\n\r");
        }
        break;
        case WON:
        {
                currentState=state;
                ControlAllColor(myColor);   //Denne playerside har vundet og alle kopholder lys skal lyse med myColor
                UART_PutString("state==WON\n\r");
        }
        break;
        case LOST:
        {
                currentState=state;
                ControlAllColor(opponentColor); //Denne playerside har tabt og alle kopholder lys skal lyse med opponentColor
                UART_PutString("state==LOST\n\r");
        }  
         break;
    }
}
 void setMyColor(color_t c)
{
    myColor=c;
}
 void setOpponentColor(color_t c)
{
    opponentColor=c;
}
 void updateCupStatus(uint8_t status)
{
    CupStatus=status;
    if(currentState==STARTING || currentState==PLAYING)
    {
        CupStatus=status;
        sprintf(game_buf,"Sending cupstatus. Updating cupstatus with cupstatus:%x\n\r",CupStatus);
        UART_PutString(game_buf);
        sendCupStatus(CupStatus); //cupstatus sendes til RPI
    }
    
}
 void updateHitStatus(uint8_t status)
{
    if(currentState==PLAYING)
    {
        hitStatus=status;
        UART_PutString("Sending Hitstatus. Updating Hitstatus\n\r"); 
    }
}

void ControlLights(uint8_t cupstatus)
{
    if(currentState==STARTING){
        UART_PutString("Controlling lights\n\r");
        for(int i=0;i<8;i++) //ale bits i cupstatus løbes i gennem med dette loop
        {
            if((~cupstatus)>>i & 1) //Hvis et bit er 0 vil det tilhørende index(index 1 er fx bit nr 1)
                                   //blive brugt til at kalde controlLight med missingcupColor farven
                controlLight(i,missingCupColor);
            else                               //hvis det tilhørende index ikke er nul(det er 1), så vil controllight
                                               //blive kaldt med placedCupColor istedet for missingCupColor
                controlLight(i,placedCupColor);
        }
    }else if( currentState==PLAYING){      
        UART_PutString("Controlling lights\n\r");
        for(int i=0;i<8;i++)
        {
            if((~cupstatus)>>i & 1)             //samme princip som i state STARTING dog vil controllight blive                                              //kaldt med 
                controlLight(i,opponentColor);  //kaldt med opponentColor og MyColor istedet.
            else
                controlLight(i,myColor);
        }
    }
}

void ControlAllColor(color_t color)
{
   
       if(currentState==IDLE){
                nn=sprintf(game_buf,"turned off colors: Red:%d Green:%d Blue:%d\n\r",
                            color.Red,
                            color.Green,
                            color.Blue);
                UART_PutString(game_buf);
        }
        else if (currentState==WON){
            nn=sprintf(game_buf,"Winning lights with colors: Red:%d Green:%d Blue:%d\n\r",
                            color.Red,
                            color.Green,
                            color.Blue);
                UART_PutString(game_buf);
        }
        else if(currentState==LOST){
            nn=sprintf(game_buf,"Losing lights with colors: Red:%d Green:%d Blue:%d\n\r",
                            color.Red,
                            color.Green,
                            color.Blue);
                UART_PutString(game_buf);
        }

}
void Controller()
{
    if(currentState==STARTING || currentState==PLAYING){
        if(CupStatus!=CupStatus_latest){  //kun hvis CupStatus har ændret sig vil dette if statement eksekveres
            CupStatus_latest=CupStatus;
            ControlLights(CupStatus);
            sprintf(game_buf,"Cupstatus change:%d\n\r",CupStatus);
            UART_PutString(game_buf);
        }
    if(currentState==PLAYING)
    {
        if(hitStatus && !blinking)  //Når bare en af hitStatus bits er sat skal og blinking varibale er 0
        {                           //altså timeren er ikke startet allerede, hvilket er det blinking holder styr på.
            UART_PutString("Starting timer\n\r");
            Timer_Start();
            blinking=1;
        }
        else if(!hitStatus && blinking) // Ingen bits i hitStatus er sat længere og den blinkes
        {
            UART_PutString("Stopping timer\n\r");
            Timer_Stop(); 
            blinking=0;
        }
    }
    }
    else
    {
        if(blinking){           //Hvis systemet ikke er i state PLAYING eller STARTING, så skal timer stoppes
            Timer_Stop();       //og blinking sættes til 0 
            blinking=0;
        }
    }
}

void controlLight(uint8_t index,color_t color)
{
    sprintf(game_buf,"light for index %d with color: Red:%d Green:%d Blue:%d\n\r",index,color.Red,color.Green,color.Blue);
    UART_PutString(game_buf);
}
uint8_t getCupStatus(){
    UART_PutString("get cupstatus\n\r");
    return CupStatus;
}

void Interrupt_LED()
{ 
    if(currentState==PLAYING)
        for(uint8_t i=0;i<8;i++)  //i er bit nummer(fra LSB) og index i LED_states  
        {
            if((hitStatus>>i) & 1){ //Her håndteres blink for alle de satte bits i hitStatus
                if(LED_states[i]){  //hvis det tilhørende index i LED_states er sat vil controllight kaldes med myColor
                    controlLight(i,myColor);
                    LED_states[i]=0;}
                else{
                    controlLight(i,opponentColor); //når det tilhørende index er 0, så vil controllight kaldes med opponentColor
                    LED_states[i]=1;}
                    
             }
        }
}


/* [] END OF FILE */
