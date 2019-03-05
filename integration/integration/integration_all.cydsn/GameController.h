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
#include "CupLight_IF.h"
#include "CupSensor_IF.h"

//#define STUB
//#define HIT_ANIMATION
    
enum GameState{IDLE,STARTING,PLAYING,WON,LOST}currentState;


void setState(enum GameState state);
void setMyColor(color_t c);
void setOpponentColor(color_t c);
void updateCupStatus(uint8_t status);
void updateHitStatus(uint8_t status);   
void ControlLights();
uint8_t getCupStatus();
void Controller();
void interruptBlink();

#endif
/* [] END OF FILE */
