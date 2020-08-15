

#ifndef DEVICE_CONFIG_H
#define	DEVICE_CONFIG_H

/*
    Секция: Программнын макросы (настройки).
*/

// Для режима отладки.
#define DEBUG
// Отправлять данные на ПК.
#define SEND_TO_PC
// Очищать EEPROM при записи.
// #define EEPROM_CLEAR         
// Частоты кварца (для задержек).
#define _XTAL_FREQ                      8000000
// Время периода отправки сообщений, с.
#define TIME_WAIT_SEND_FIRST            0x0Fu * 4
// Время периода отправки сообщений, с.
#define TIME_WAIT_SEND_SECOND           0x1Eu * 4
// Время между сообщениями, с.
#define TIME_BETTWEN_SEND               0x02u * 4
// Количество повторений сообщений.
#define SEND_ATTEMPS                    0x02u 

//*** Настройки усреднения значений ***//

// Скользящая средняя.
// #define FUNC_AVERAGING_MA
// Cреднее значения.
#define FUNC_AVERAGING_A
// Среднеквадратичное.
// #define FUNC_AVERAGING_RMS

//*** Настройки UART ***//

// Стартовый байт фрейма послыки.
#define START_BYTE                      0x55

#endif

/*
    Конец файла. 
*/
