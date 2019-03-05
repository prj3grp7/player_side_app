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
#include <stdint.h>
#include "project.h"

#define WHITE {255,255,255}
#define RED {255,0,0}
#define GREEN {0,255,0}
#define BLUE {0,0,255}
#define PURPLE {255,255,0}
#define YELLOW {0,255,255}
#define TURQUOISE {255,0,255}


typedef struct color
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} color_t;

//Init the RGBLED with RGB value at start
void initRGBLED();

//Sets the RGB value
void setColor(color_t color);
//Sets the red color to R
void setRed(uint8_t R);
//Sets the green color to G
void setGreen(uint8_t G);
//Sets the blue color to B
void setBlue(uint8_t B);

//Gets the Red color
uint8_t getRed(void);
//Get the green color
uint8_t getGreen(void);
//Gets the blue color
uint8_t getBlue(void);


/* [] END OF FILE */
