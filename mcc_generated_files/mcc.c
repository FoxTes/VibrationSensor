

/*
    Секция: Включаемые файлы.
*/

#include "mcc.h"

/*
    Секция: APIs.
*/

void SYSTEM_Initialize(void)
{
    OSCILLATOR_Initialize();
    PIN_MANAGER_Initialize();
    WDT_Initialize();
    SPI_Initialize();
    TMR1_Initialize();
    EUSART_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // SCS FOSC; SPLLEN disabled; IRCF 8MHz_HF; 
    OSCCON = 0x70;
    // TUN 0; 
    OSCTUNE = 0x00;
    // SBOREN enabled; BORFS disabled; 
    BORCON = 0x80;
}

void WDT_Initialize(void)
{
    // WDTPS 1:32768; SWDTEN OFF; 
    WDTCON = 0x14;
}

/*
    Конец файда.
*/
