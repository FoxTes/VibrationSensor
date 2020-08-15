

/*
    Секция: Включаемые файлы.
*/

#include "eusart.h"
#include "device_config.h"

/*
    Секция: APIs.
*/

void EUSART_Initialize(void)
{
    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUDCON = 0x08;
    // SPEN enabled; RX9 8-bit; CREN disabled; ADDEN disabled; SREN disabled; 
    RCSTA = 0x80;
    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TXSTA = 0x24;
    // SPBRGL 25; 76800 Baud Rate
    SPBRGL = 0x19; 
    // SPBRGH 0; 
    SPBRGH = 0x00;

#ifndef DEBUG    
    // TX9 9-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TXSTA = 0x64;
    // SPBRGL 10; 300 Baud Rate
    SPBRGL = 0x0A;
    // SPBRGH 26; 
    SPBRGH = 0x1A;
#endif
}

bool EUSART_is_tx_ready(void)
{
    return (bool)(PIR1bits.TXIF && TXSTAbits.TXEN);
}

bool EUSART_is_tx_done(void)
{
    return TXSTAbits.TRMT;
}

void EUSART_Write(uint8_t txData)
{
    while(0 == PIR1bits.TXIF)
    {
        CLRWDT();
    }
    // Write the data byte to the USART.
    TXREG = txData;         
}

/*
    Конец файда.
*/