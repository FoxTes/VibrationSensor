

#ifndef DEVICE_CONFIG_H
#define	DEVICE_CONFIG_H

/*
    ������: ����������� ������� (���������).
*/

// ��� ������ �������.
#define DEBUG
// ���������� ������ �� ��.
#define SEND_TO_PC
// ������� EEPROM ��� ������.
// #define EEPROM_CLEAR         
// ������� ������ (��� ��������).
#define _XTAL_FREQ                      8000000
// ����� ������� �������� ���������, �.
#define TIME_WAIT_SEND_FIRST            0x0Fu * 4
// ����� ������� �������� ���������, �.
#define TIME_WAIT_SEND_SECOND           0x1Eu * 4
// ����� ����� �����������, �.
#define TIME_BETTWEN_SEND               0x02u * 4
// ���������� ���������� ���������.
#define SEND_ATTEMPS                    0x02u 

//*** ��������� ���������� �������� ***//

// ���������� �������.
// #define FUNC_AVERAGING_MA
// C������ ��������.
#define FUNC_AVERAGING_A
// ������������������.
// #define FUNC_AVERAGING_RMS

//*** ��������� UART ***//

// ��������� ���� ������ �������.
#define START_BYTE                      0x55

#endif

/*
    ����� �����. 
*/
