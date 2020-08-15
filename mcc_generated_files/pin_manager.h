

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/*
    Секция: Включаемые файлы.
*/

#include <xc.h>

/*
    Секция: Определения.
*/

#define INPUT                   1
#define OUTPUT                  0

#define HIGH                    1
#define LOW                     0

#define ANALOG                  1
#define DIGITAL                 0

#define PULL_UP_ENABLED         1
#define PULL_UP_DISABLED        0

// get/set RA0 procedures.
#define RA0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define RA0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define RA0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define RA0_GetValue()           PORTAbits.RA0
#define RA0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define RA0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define RA0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define RA0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define RA0_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define RA0_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set RA1 procedures.
#define RA1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define RA1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define RA1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define RA1_GetValue()           PORTAbits.RA1
#define RA1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define RA1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define RA1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define RA1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define RA1_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define RA1_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set RA2 procedures.
#define RA2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define RA2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define RA2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define RA2_GetValue()           PORTAbits.RA2
#define RA2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define RA2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define RA2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define RA2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define RA2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define RA2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set IO_INT aliases
#define IO_INT_TRIS                 TRISAbits.TRISA3
#define IO_INT_PORT                 PORTAbits.RA3
#define IO_INT_WPU                  WPUAbits.WPUA3
#define IO_INT_GetValue()           PORTAbits.RA3
#define IO_INT_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define IO_INT_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define IO_INT_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define IO_INT_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)

// get/set RA4 procedures
#define RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RA4_GetValue()           PORTAbits.RA4
#define RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define RA4_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define RA4_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set IO_CS aliases.
#define IO_CS_TRIS               TRISAbits.TRISA5
#define IO_CS_LAT                LATAbits.LATA5
#define IO_CS_PORT               PORTAbits.RA5
#define IO_CS_WPU                WPUAbits.WPUA5
#define IO_CS_SetHigh()          do { LATAbits.LATA5 = 1; } while(0)
#define IO_CS_SetLow()           do { LATAbits.LATA5 = 0; } while(0)
#define IO_CS_Toggle()           do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define IO_CS_GetValue()         PORTAbits.RA5
#define IO_CS_SetDigitalInput()  do { TRISAbits.TRISA5 = 1; } while(0)
#define IO_CS_SetDigitalOutput() do { TRISAbits.TRISA5 = 0; } while(0)
#define IO_CS_SetPullup()        do { WPUAbits.WPUA5 = 1; } while(0)
#define IO_CS_ResetPullup()      do { WPUAbits.WPUA5 = 0; } while(0)

/*
    Секция: APIs.
*/

/*
    @Param
        none.

    @Returns
        none.

    @Description
        GPIO and peripheral I/O initialization.

    @Example
        PIN_MANAGER_Initialize();
*/
void PIN_MANAGER_Initialize (void);

/*
    @Param
        none.

    @Returns
        none.

    @Description
        Interrupt on Change Handling routine.

    @Example
        PIN_MANAGER_IOC();
*/
void PIN_MANAGER_IOC(void);

#endif

/*
    Конец файда.
*/