

/*
    Секция: Включаемые файлы.
*/

#include <xc.h>
#include "tmr1.h"

/*
    Секция: APIs.
*/

void TMR1_Initialize(void)
{
    //T1GSS T1G_pin; TMR1GE disabled; T1GTM disabled; T1GPOL low; T1GGO done; T1GSPM disabled; 
    T1GCON = 0x00;
    //TMR1H 11; 
    TMR1H = 0x0B;
    //TMR1L 220; 
    TMR1L = 0xDC;
    // Clearing IF flag.
    PIR1bits.TMR1IF = 0;
    // T1CKPS 1:8; T1OSCEN disabled; nT1SYNC do_not_synchronize; TMR1CS FOSC/4; TMR1ON enabled; 
    T1CON = 0x35;
}

void TMR1_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 1;
}

void TMR1_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 0;
}

uint16_t TMR1_ReadTimer(void)
{
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;
    
    readValLow = TMR1L;
    readValHigh = TMR1H;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;
    return readVal;
}

void TMR1_WriteTimer(uint16_t timerVal)
{
    if (T1CONbits.nT1SYNC == 1)
    {
        // Stop the Timer by writing to TMRxON bit.
        T1CONbits.TMR1ON = 0;
        // Write to the Timer1 register.
        TMR1H = (timerVal >> 8);
        TMR1L = timerVal;
        // Start the Timer after writing to the register.
        T1CONbits.TMR1ON =1;
    }
    else
    {
        // Write to the Timer1 register.
        TMR1H = (timerVal >> 8);
        TMR1L = timerVal;
    }
}

void TMR1_Reload(void)
{
    //TMR1H 11; 
    TMR1H = 0x0B;
    //TMR1L 220; 
    TMR1L = 0xDC;
}

void TMR1_StartSinglePulseAcquisition(void)
{
    T1GCONbits.T1GGO = 1;
}

uint8_t TMR1_CheckGateValueStatus(void)
{
    return (T1GCONbits.T1GVAL);
}

bool TMR1_HasOverflowOccured(void)
{
    // Check if  overflow has occurred by checking the TMRIF bit.
    return(PIR1bits.TMR1IF);
}

/*
    Конец файда.
*/
