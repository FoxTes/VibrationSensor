

#ifndef EUSART_H
#define EUSART_H

/*
    Секция: Включаемые файлы.
*/

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

/*
    Секция: Определения.
*/

typedef union 
{
    struct 
    {
        uint8_t byte_0;
        uint8_t byte_1;
        uint8_t byte_2;
        uint8_t byte_3;
        uint8_t byte_4;
        uint8_t byte_5;
        uint8_t byte_6;
    } frame;
    uint8_t array[7];
} UART_MSG;

typedef union 
{
    struct 
    {
        uint8_t byte_0;
        uint8_t byte_1;
        uint8_t byte_2;
        uint8_t byte_3;
        uint8_t byte_4;
        uint8_t byte_5;
        uint8_t byte_6;
    } frame;
    uint8_t array[5];
} UART_MSG_TEST;

/*
    Секция: APIs.
*/

/*
    @Summary
        Initialization routine that takes inputs from the EUSART GUI.

    @Description
        This routine initializes the EUSART driver.
        This routine must be called before any other EUSART routine is called.

    @Preconditions
        None

    @Param
        None

    @Returns
        None

    @Comment
    
*/
void EUSART_Initialize(void);

/*
    @Summary
        Checks if the EUSART transmitter is ready to transmit data

    @Description
        This routine checks if EUSART transmitter is ready 
        to accept and transmit data byte

    @Preconditions
        EUSART_Initialize() function should have been called
        before calling this function.
        EUSART transmitter should be enabled before calling 
        this function

    @Param
        None

    @Returns
        Status of EUSART transmitter
        TRUE: EUSART transmitter is ready
        FALSE: EUSART transmitter is not ready

    @Example
        <code>
        void main(void)
        {
            volatile uint8_t rxData;

            // Initialize the device
            SYSTEM_Initialize();

            while(1)
            {
                // Logic to echo received data
                if(EUSART_is_rx_ready())
                {
                    rxData = UART1_Read();
                    if(EUSART_is_tx_ready())
                    {
                        EUSARTWrite(rxData);
                    }
                }
            }
        }
        </code>
*/
bool EUSART_is_tx_ready(void);

/*
    @Summary
        Checks if EUSART data is transmitted

    @Description
        This function return the status of transmit shift register

    @Preconditions
        EUSART_Initialize() function should be called
        before calling this function
        EUSART transmitter should be enabled and EUSART_Write
        should be called before calling this function

    @Param
        None

    @Returns
        Status of EUSART receiver
        TRUE: Data completely shifted out if the USART shift register
        FALSE: Data is not completely shifted out of the shift register

    @Example
        <code>
        void main(void)
        {
            volatile uint8_t rxData;

            // Initialize the device
            SYSTEM_Initialize();

            while(1)
            {
                if(EUSART_is_tx_ready())
                {
                    LED_0_SetHigh();
                    EUSARTWrite(rxData);
                }
                if(EUSART_is_tx_done()
                {
                    LED_0_SetLow();
                }
            }
        }
        </code>
*/
bool EUSART_is_tx_done(void);

 /*
    @Summary
        Writes a byte of data to the EUSART.

    @Description
        This routine writes a byte of data to the EUSART.

    @Preconditions
        EUSART_Initialize() function should have been called
        before calling this function. The transfer status should be checked to see
        if transmitter is not busy before calling this function.

    @Param
        txData  - Data byte to write to the EUSART

    @Returns
        None
*/
void EUSART_Write(uint8_t txData);

#endif

/*
    Конец файда.
*/
