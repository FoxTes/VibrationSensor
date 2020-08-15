

/*
    Секция: Включаемые файлы.
*/

#include "pin_manager.h"

/*
    Секция: APIs.
*/

void PIN_MANAGER_Initialize(void)
{
    // LATx registers.
    LATA = 0x20;
    // TRISx registers.
    TRISA = 0x1C;
    // ANSELx registers.
    ANSELA = 0x00;
    // WPUx registers.
    WPUA = 0x00;
    OPTION_REGbits.nWPUEN = 1;
    // APFCONx registers.
    APFCON = 0x04;  
}
  
void PIN_MANAGER_IOC(void)
{   
}

/*
    Конец файда.
*/