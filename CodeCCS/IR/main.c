#include "lib/IRrecv.h"

//#define DEBUG


int main(void)
{
    Config_stop_WDT();
    Clock_Init();
    GPIO_Init();
    Timer_Init();
    while(1)
    {

    }

}


