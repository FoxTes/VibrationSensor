

/*
    Секция: Включаемые файлы.
*/

#include "spi.h"
#include <xc.h>

/*
    Секция: APIs.
*/

void SPI_Initialize(void)
{
    //SPI setup
    SSP1STAT = 0xC0;
    SSP1CON1 = 0x00;
    SSP1ADD = 0x01;
    TRISAbits.TRISA1 = 0;
    SSP1CON1bits.SSPEN = 1;
}

void SPI_Close(void)
{
    SSP1CON1bits.SSPEN = 0;
}

uint8_t SPI_ExchangeByte(uint8_t data)
{
    SSP1BUF = data;
    while(!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF = 0;
    return SSP1BUF;
}

void SPI_WriteByte(uint8_t byte)
{
    SSPBUF = byte;                                        
    while(!PIR1bits.SSP1IF);                                
    PIR1bits.SSP1IF = 0;                                   
}

uint8_t SPI_ReadByte(void)
{
    return SSP1BUF;
}

/*
    Конец файда.
*/