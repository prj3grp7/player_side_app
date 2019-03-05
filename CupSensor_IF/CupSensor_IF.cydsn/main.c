#include "project.h"
#include "CupSensor_IF.h"


int placedCount = 0;
int removedCount = 0;
int hitCount = 0;
char buffer[255];

uint8_t oldHitStatus = 0;
uint8_t oldCupStatus = 0;

//Testing more sensors
void updateHitStatus(uint8_t status)
{
    for (int bitNumber = 0; bitNumber < 6; bitNumber++){
        if((status & 1<<bitNumber) && !(oldHitStatus & 1<<bitNumber)){
            hitCount++;
        }
    }
    oldHitStatus = status;
    snprintf(buffer,254,"removedCount: %d, placedCount: %d, hitCount: %d\r\n", removedCount, placedCount, hitCount);
    UART_PutString(buffer);
}

void updateCupStatus(uint8_t status)
{
    for (int bitNumber = 0; bitNumber < 6; bitNumber++){
        if((status & 1<<bitNumber) && !(oldCupStatus & 1<<bitNumber)){
            placedCount++;
        }
        else if((!(status & 1<<bitNumber)) && (oldCupStatus & 1<<bitNumber))
        {
            removedCount++;
        }
    }
    oldCupStatus = status;
    snprintf(buffer,254,"removedCount: %d, placedCount: %d, hitCount: %d\r\n", removedCount, placedCount, hitCount);
    
    UART_PutString(buffer);
   
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    CupSensor_IF_init();
    UART_Start();
    UART_PutString("CupSensor_IF Test Program started\r\n");
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
