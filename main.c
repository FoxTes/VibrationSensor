

/*
    ������: ���������� �����.
*/

#include "mcc_generated_files/mcc.h"
#include "adxl_library/adxl372.h"

/*
    ������: ����������.
*/

// ������� ���������� ��� �������� � �������� ������.
volatile bool     needCalcData = false, needSendData = false, 
                  needSendAttemp = false;
// ��������� ��� �������� ������.
volatile uint8_t  countTickTimer = 0x00, countAttemptSend = 0x00, 
                  countSendByte = 0x00,  dataTimeSend = TIME_WAIT_SEND_FIRST;
// ���������� ��� �������� �������� �������� � ��������������.
#ifdef FUNC_AVERAGING_A
volatile uint16_t dataMaximal_X = 0x00, dataMaximal_Y = 0x00,
                  tempMaximal_X = 0x00, tempMaximal_Y = 0x00;
volatile uint32_t dataAverage_X = 0x00, dataAverage_Y = 0x00,
                  tempAverage_X = 0x00, tempAverage_Y = 0x00;              
#endif

// ����������.
Accel_Data_t accel_data;
// ��� ������ UART.
UART_MSG     data_uart;

#ifdef SEND_TO_PC
    UART_MSG_TEST data_uart_test;
#endif

/*
    ��������� �������.
*/

void GetDataAccel(void);
void CheckDataAndRead(void);
void ConvertDataAndSend(void);

/*
    ������� ���������.
*/

void main(void)
{
    // ��������������� ����������.
    uint8_t i;
    
    // ������������� ���������.
    SYSTEM_Initialize();
    // ������������� �������������.
    ADXL372_Initialize();
    
    // ������ �������� device_config.h.
#ifdef SEND_TO_PC
    while (1)
    {
        // �������. �������� ������ �� ��.
        if (!IO_INT_GetValue())
        {
            ConvertDataAndSend();
        }
        // �� �������� �������� �������.
        CLRWDT();
    }   
#endif
    
    // ��������� ������ ������ ���� ������.
    data_uart.frame.byte_0 = START_BYTE;

    //*** ������� ���� ***//
    while (1)
    {   
        //*** ��������. ������ ������ ��� ������? ***//
        if (!IO_INT_GetValue())
        {
            // �������� �� - ������ ���������� ������ 2.5 �� ��� ODR400.
            GetDataAccel();
        }
        //*** �������� ��������� ����������. ������ 250 �� ***//
        else if (PIR1bits.TMR1IF)
        {
            PIR1bits.TMR1IF = 0;
            TMR1_Reload(); 
            // �������� ������� ������ 250 ��.
            CLRWDT();
            
            if (++countTickTimer > dataTimeSend)
            {
                countTickTimer = 0x00;
                needCalcData = true;
                // ��������� �������� �� ��������� ����������.
                tempMaximal_X = dataMaximal_X;
                tempMaximal_Y = dataMaximal_Y;
                tempAverage_X = dataAverage_X;
                tempAverage_Y = dataAverage_Y;
                // ������� ��������� ��� ��������.
                dataMaximal_X = 0x00;
                dataMaximal_Y = 0x00;
                dataAverage_X = 0x00;
                dataAverage_Y = 0x00;
                // ���������� �������� ����� ��� ��������� ������������ ��������.
                if (dataTimeSend == TIME_WAIT_SEND_FIRST)
                {
                    // �����������. ������� �� 6000. 7/47
                    tempAverage_X >>= 7;
                    tempAverage_X /= 47;
                    CheckDataAndRead();
                    
                    tempAverage_Y >>= 7;
                    tempAverage_Y /= 47;
                }
                else
                {
                    // �����������. ������� �� 12000. 8/47
                    tempAverage_X >>= 8;
                    tempAverage_X /= 47;
                    CheckDataAndRead();
                    
                    tempAverage_Y >>= 8;
                    tempAverage_Y /= 47;
                }
                CheckDataAndRead();
            }
            else if (countAttemptSend != 0)
            {
                // *�� ���������� ���������, ����� �� ������� ������ � �����.
                // *��� ����������� ������������ countTickTimer%TIME_BETTWEN_SEND == 0.
                if ((countTickTimer == TIME_BETTWEN_SEND) || (countTickTimer == TIME_BETTWEN_SEND * 2))
                {
                    needSendAttemp = true;
                }
            }
        }
        //*** ���������� ��������� �������� � �� �������� ***//
        else if (needCalcData)
        {
            // ������������� �������� � G.
            float temp[4];
            temp[0] = tempAverage_X * ADXL_SCALE_LSB;
            CheckDataAndRead();
            temp[1] = tempAverage_Y * ADXL_SCALE_LSB;
            CheckDataAndRead();
            temp[2] = tempMaximal_X * ADXL_SCALE_LSB;
            CheckDataAndRead();
            temp[3] = tempMaximal_Y * ADXL_SCALE_LSB;
            CheckDataAndRead();
            // ��������� �����.
            data_uart.frame.byte_1 = (uint8_t)temp[0];
            data_uart.frame.byte_2 = (uint8_t)temp[2];
            data_uart.frame.byte_3 = (uint8_t)temp[1];
            data_uart.frame.byte_4 = (uint8_t)temp[3];
            data_uart.frame.byte_5 = 0x00;
            data_uart.frame.byte_6 = 0x00; 
            
            for (i = 1; i < 5; i++) 
            {
                // ����������� ����, ���������� ��������������� ������ ���������� 4� ���� ��� ����� ������������.
                data_uart.frame.byte_5 += data_uart.array[i];
                // ����������� ����, ���������� ��������������� ��������� ������������ ��� ��� �� 4� ���� ������.
                data_uart.frame.byte_6 ^= data_uart.array[i];
            }
            // ���������� ��������������.
            data_uart.frame.byte_5 = ~data_uart.frame.byte_5;
            data_uart.frame.byte_6 = ~data_uart.frame.byte_6;

            needCalcData = false;
            needSendData = true;         
        }
        //*** �������� ������ �� UART ***//
        else if (needSendData || needSendAttemp)
        {
            // ���������, �������� �� �����.
            if (EUSART_is_tx_done())
            {
#ifndef DEBUG   
                // ������ ���� - 9 ��� ��� 1.
                if (countSendByte == 0x00)
                {
                    TXSTAbits.TX9D = 1;
                }
                else
                {
                    TXSTAbits.TX9D = 0;
                }
#endif
                EUSART_Write(data_uart.array[countSendByte++]);
                // �������� ������ ���������.
                if (countSendByte == 0x07)
                {
                    countSendByte = 0x00;
                    needSendData = false;
                    needSendAttemp = false;
                    // �� ������ �������� ������ �� UART.
                    if (++countAttemptSend > SEND_ATTEMPS)
                    {
                        countAttemptSend = 0x00;
                        dataTimeSend = TIME_WAIT_SEND_SECOND;
                    }
                }
            }
        }            
    }
}

void GetDataAccel(void)
{
    #define ABS(x) x = (0x0FFF - x)

    ADXL372_Get_Accel_Data(&accel_data);
    // ������������� ������ �� ������.
    if (accel_data.x > 0x07FF)
    {
        ABS(accel_data.x);
    }
    if (accel_data.y > 0x07FF)
    {
        ABS(accel_data.y);
    }   
    // ���� ������������ ��������������� ��������.
    if (accel_data.x > dataMaximal_X)
    {
        dataMaximal_X = accel_data.x;
    }
    if (accel_data.y > dataMaximal_Y)
    {
        dataMaximal_Y = accel_data.y;
    }
    // ���������� ������� �� ���� ����.
    dataAverage_X += accel_data.x;
    dataAverage_Y += accel_data.y;
}

void CheckDataAndRead(void)
{
    if (!IO_INT_GetValue())
    {
        GetDataAccel();
    }
}

#ifdef SEND_TO_PC
    void ConvertDataAndSend(void)
    {     
        ADXL372_Get_Accel_Data(&accel_data);
        // ����������� ������. ������ ���� (���������) ����� 8-�� ��� ������ ���. 1, ��������� - ���. 0.
        data_uart_test.frame.byte_0 = 0xFF;
        data_uart_test.frame.byte_1 = (uint8_t)accel_data.x & 0b01111111;
        data_uart_test.frame.byte_2 = (accel_data.x >> 7)   & 0b01111111;
        data_uart_test.frame.byte_3 = (uint8_t)accel_data.y & 0b01111111;
        data_uart_test.frame.byte_4 = (accel_data.y >> 7)   & 0b01111111;
        data_uart_test.frame.byte_5 = (uint8_t)accel_data.z & 0b01111111;
        data_uart_test.frame.byte_6 = (accel_data.z >> 7)   & 0b01111111;

        uint8_t i;
        for (i = 0; i < 7; i++)
        {
            // �������� ������ ������������� � ������� ������.
            EUSART_Write(data_uart_test.array[i]);
        }
    }
#endif

/*
   ����� �����.
*/