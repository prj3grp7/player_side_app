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
#ifndef _GAME_CONTROLLER
#define _GAME_CONTROLLER
#include "RPI_IF.h"
#include "project.h"
    
enum GameState{IDLE,STARTING,PLAYING,WON,LOST}currentState;

typedef struct color
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
}color_t;


void setState(enum GameState state);
void setMyColor(color_t c);
void setOpponentColor(color_t c);
void updateCupStatus(uint8_t status);
void updateHitStatus(uint8_t status);   
void ControlLights(uint8_t cupstatus);
void ControlAllColor(color_t color);
uint8_t getCupStatus();
void Controller();
void controlLight(uint8_t index,color_t color);
void Interrupt_LED();

#endif
/* [] END OF FILE */
