

#ifndef SPI_H
#define SPI_H

/*
    Секция: Включаемые файлы.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*
    Секция: APIs.
*/

void SPI_Initialize(void);
void SPI_Close(void);
uint8_t SPI_ExchangeByte(uint8_t data);
void SPI_WriteByte(uint8_t byte);
uint8_t SPI_ReadByte(void);

#endif

/*
    Конец файда.
*/