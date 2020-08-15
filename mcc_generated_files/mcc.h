

#ifndef MCC_H
#define	MCC_H

/*
    Секция: Включаемые файлы.
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>

#include "device_config.h"
#include "pin_manager.h"
#include "spi.h"
#include "tmr1.h"
#include "eusart.h"

/*
    Секция: APIs.
*/

/*
    @Param
        none.
  
    @Returns
        none.
  
    @Description
        Initializes the device to the default states configured in the MCC GUI.
 
    @Example
        SYSTEM_Initialize(void);
*/
void SYSTEM_Initialize(void);

/*
    @Param
        none.
 
    @Returns
        none.
  
    @Description
        Initializes the oscillator to the default states configured in the MCC GUI.
  
    @Example
        OSCILLATOR_Initialize(void);
*/
void OSCILLATOR_Initialize(void);

/*
    @Param
        none.
  
    @Returns
        none.

    @Description
        Initializes the WDT module to the default states configured in the MCC GUI.
 
   @Example
        WDT_Initialize(void);
*/
void WDT_Initialize(void);

#endif

/*
    Конец файда.
*/