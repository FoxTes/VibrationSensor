

#ifndef ADXL372_H
#define	ADXL372_H

/*
    Секция: Включаемые файлы.
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "../mcc_generated_files/spi.h"
#include "../mcc_generated_files/device_config.h"
#include "../mcc_generated_files/pin_manager.h"

/*
    Секция: Определения.
*/

// Указывает порядок расположения байтов в посылке.
#define L_ENDIAN
// Использовать функции с буфером.
// #define ADXL372_USE_FIFO_FUNCTION 

// Адресс для регистров.
#define ADI_ADXL372_ADI_DEVID           0x00u   /* Analog Devices, Inc., accelerometer ID */
#define ADI_ADXL372_MST_DEVID          	0x01u   /* Analog Devices MEMS device ID */
#define ADI_ADXL372_DEVID               0x02u   /* Device ID */
#define ADI_ADXL372_REVID               0x03u   /* product revision ID*/
#define ADI_ADXL372_STATUS_1            0x04u   /* Status register 1 */
#define ADI_ADXL372_STATUS_2            0x05u   /* Status register 2 */
#define ADI_ADXL372_FIFO_ENTRIES_2      0x06u   /* Valid data samples in the FIFO */
#define ADI_ADXL372_FIFO_ENTRIES_1      0x07u   /* Valid data samples in the FIFO */
#define ADI_ADXL372_X_DATA_H            0x08u   /* X-axis acceleration data [11:4] */
#define ADI_ADXL372_X_DATA_L            0x09u   /* X-axis acceleration data [3:0] | dummy LSBs */
#define ADI_ADXL372_Y_DATA_H            0x0Au   /* Y-axis acceleration data [11:4] */
#define ADI_ADXL372_Y_DATA_L            0x0Bu   /* Y-axis acceleration data [3:0] | dummy LSBs */
#define ADI_ADXL372_Z_DATA_H            0x0Cu   /* Z-axis acceleration data [11:4] */
#define ADI_ADXL372_Z_DATA_L            0x0Du   /* Z-axis acceleration data [3:0] | dummy LSBs */
#define ADI_ADXL372_X_MAXPEAK_H         0x15u   /* X-axis MaxPeak acceleration data [15:8] */
#define ADI_ADXL372_X_MAXPEAK_L         0x16u   /* X-axis MaxPeak acceleration data [7:0] */
#define ADI_ADXL372_Y_MAXPEAK_H        	0x17u   /* X-axis MaxPeak acceleration data [15:8] */
#define ADI_ADXL372_Y_MAXPEAK_L         0x18u   /* X-axis MaxPeak acceleration data [7:0] */
#define ADI_ADXL372_Z_MAXPEAK_H         0x19u   /* X-axis MaxPeak acceleration data [15:8] */
#define ADI_ADXL372_Z_MAXPEAK_L         0x1Au   /* X-axis MaxPeak acceleration data [7:0] */
#define ADI_ADXL372_OFFSET_X 	        0x20u   /* X axis offset */
#define ADI_ADXL372_OFFSET_Y            0x21u   /* Y axis offset */
#define ADI_ADXL372_OFFSET_Z	        0x22u   /* Z axis offset */
#define ADI_ADXL372_X_THRESH_ACT_H      0x23u   /* X axis Activity Threshold [15:8] */
#define ADI_ADXL372_X_THRESH_ACT_L      0x24u   /* X axis Activity Threshold [7:0] */
#define ADI_ADXL372_Y_THRESH_ACT_H      0x25u   /* Y axis Activity Threshold [15:8] */
#define ADI_ADXL372_Y_THRESH_ACT_L      0x26u   /* Y axis Activity Threshold [7:0] */
#define ADI_ADXL372_Z_THRESH_ACT_H      0x27u   /* Z axis Activity Threshold [15:8] */
#define ADI_ADXL372_Z_THRESH_ACT_L      0x28u   /* Z axis Activity Threshold [7:0] */
#define ADI_ADXL372_TIME_ACT	        0x29u   /* Activity Time */
#define ADI_ADXL372_X_THRESH_INACT_H    0x2Au   /* X axis Inactivity Threshold [15:8] */
#define ADI_ADXL372_X_THRESH_INACT_L	0x2Bu   /* X axis Inactivity Threshold [7:0] */
#define ADI_ADXL372_Y_THRESH_INACT_H    0x2Cu   /* Y axis Inactivity Threshold [15:8] */
#define ADI_ADXL372_Y_THRESH_INACT_L    0x2Du   /* Y axis Inactivity Threshold [7:0] */
#define ADI_ADXL372_Z_THRESH_INACT_H	0x2Eu   /* Z axis Inactivity Threshold [15:8] */
#define ADI_ADXL372_Z_THRESH_INACT_L	0x2Fu   /* Z axis Inactivity Threshold [7:0] */
#define ADI_ADXL372_TIME_INACT_H        0x30u   /* Inactivity Time [15:8] */
#define ADI_ADXL372_TIME_INACT_L        0x31u   /* Inactivity Time [7:0] */
#define ADI_ADXL372_X_THRESH_ACT2_H     0x32u   /* X axis Activity2 Threshold [15:8] */
#define ADI_ADXL372_X_THRESH_ACT2_L     0x33u   /* X axis Activity2 Threshold [7:0] */
#define ADI_ADXL372_Y_THRESH_ACT2_H     0x34u   /* Y axis Activity2 Threshold [15:8] */
#define ADI_ADXL372_Y_THRESH_ACT2_L     0x35u   /* Y axis Activity2 Threshold [7:0] */
#define ADI_ADXL372_Z_THRESH_ACT2_H     0x36u   /* Z axis Activity2 Threshold [15:8] */
#define ADI_ADXL372_Z_THRESH_ACT2_L     0x37u   /* Z axis Activity2 Threshold [7:0] */
#define ADI_ADXL372_HPF                 0x38u   /* High Pass Filter */
#define ADI_ADXL372_FIFO_SAMPLES        0x39u   /* FIFO Samples */
#define ADI_ADXL372_FIFO_CTL	        0x3Au   /* FIFO Control */
#define ADI_ADXL372_INT1_MAP            0x3Bu   /* Interrupt 1 mapping control */
#define ADI_ADXL372_INT2_MAP            0x3Cu   /* Interrupt 2 mapping control */
#define ADI_ADXL372_TIMING              0x3Du   /* Timing */
#define ADI_ADXL372_MEASURE             0x3Eu   /* Measure */
#define ADI_ADXL372_POWER_CTL           0x3Fu   /* Power control */
#define ADI_ADXL372_SELF_TEST           0x40u   /* Self Test */
#define ADI_ADXL372_SRESET              0x41u   /* Reset */
#define ADI_ADXL372_FIFO_DATA           0x42u   /* FIFO Data */

#define ADI_ADXL372_ADI_DEVID_VAL       0xADu   /* Analog Devices, Inc., accelerometer ID */
#define ADI_ADXL372_MST_DEVID_VAL       0x1Du   /* Analog Devices MEMS device ID */
#define ADI_ADXL372_DEVID_VAL           0xFAu   /* Device ID */
#define ADI_ADXL372_REVID_VAL           0x02u   /* product revision ID*/

#define MEASURE_AUTOSLEEP_MASK          0xBF
#define MEASURE_BANDWIDTH_MASK          0xF8
#define MEASURE_ACTPROC_MASK            0xCF
#define TIMING_ODR_MASK                 0x1F
#define TIMING_WUR_MASK                 0xE3
#define PWRCTRL_OPMODE_MASK             0xFC
#define PWRCTRL_INSTON_THRESH_MASK      0xDF
#define PWRCTRL_INSTON_THRESH_MASK      0xDF
#define PWRCTRL_FILTER_SETTLE_MASK      0xEF

#define MEASURE_AUTOSLEEP_POS           6
#define MEASURE_ACTPROC_POS             4
#define TIMING_ODR_POS                  5
#define TIMING_WUR_POS                  2
#define INSTAON_THRESH_POS              5
#define FIFO_CRL_SAMP8_POS              0
#define FIFO_CRL_MODE_POS               1
#define FIFO_CRL_FORMAT_POS             3
#define PWRCTRL_FILTER_SETTLE_POS       4

#define DATA_RDY                        1
#define FIFO_RDY                        2
#define FIFO_FULL                       4
#define FIFO_OVR                        8

#define ADXL_SPI_RNW                    1

#define ADXL_SCALE_LSB                  0.1f

typedef enum 
{
    STAND_BY = 0,
    WAKE_UP,
    INSTANT_ON,
    FULL_BW_MEASUREMENT
} ADXL372_OP_MODE;

typedef enum 
{
    ODR_400Hz = 0,
    ODR_800Hz,
    ODR_1600Hz,
    ODR_3200Hz,
    ODR_6400Hz
} ADXL372_ODR;

typedef enum 
{
    BW_200Hz = 0,
    BW_400Hz,
    BW_800Hz,
    BW_1600Hz,
    BW_3200Hz
} ADXL372_BW;

typedef enum 
{
    HPF_CORNER0 = 0,
    HPF_CORNER1,
    HPF_CORNER2,
    HPF_CORNER3,
} ADXL372_HPF;

typedef enum 
{
    WUR_52ms = 0,
    WUR_104ms,
    WUR_208ms,
    WUR_512ms,
    WUR_2048ms,
    WUR_4096ms,
    WUR_8192ms,
    WUR_24576ms
} ADXL372_WUR;

typedef enum 
{
    DEF = 0,
    LINKED,
    LOOPED
} ADXL372_ACT_PROC_MODE;

typedef enum 
{
    XYZ_FIFO = 0,
    X_FIFO,
    Y_FIFO,
    XY_FIFO,
    Z_FIFO,
    XZ_FIFO,
    YZ_FIFO,
    XYZ_PEAK_FIFO
} ADXL372_FIFO_FORMAT;

typedef enum 
{
    BYPASSED = 0,
    STREAMED,
    TRIGGERED,
    OLDEST_SAVED
} ADXL372_FIFO_MODE;

typedef struct 
{
    uint16_t            samples;
    ADXL372_FIFO_MODE   mode;
    ADXL372_FIFO_FORMAT format;
} fifo_config_t;

typedef enum 
{
    ADXL_INSTAON_LOW_THRESH = 0,
    ADXL_INSTAON_HIGH_THRESH
} ADXL_INSTAON_THRESH;

typedef enum 
{
    FILTER_SETTLE_16 = 0,
    FILTER_SETTLE_370
} ADXL372_Filter_Settle;

typedef struct 
{
    uint16_t x;
    uint16_t y;
    uint16_t z;
} Accel_Data_t; 

typedef struct 
{
    float x;
    float y;
    float z;
} Accel_G_t;

void ADXL_Read_Reg(uint8_t reg, uint8_t *val);
void ADXL_Write_Reg(uint8_t reg, uint8_t val);

void ADXL372_Set_Op_Mode(ADXL372_OP_MODE mode);
void ADXL372_Set_ODR(ADXL372_ODR odr);
//int16_t ADXL372_Set_WakeUp_Rate(struct ADXL372_Device *dev, ADXL372_WUR wur);
void ADXL372_Set_BandWidth(ADXL372_BW bw);
void ADXL372_Set_HighFilter(ADXL372_HPF hpf);
void ADXL372_Set_AutoSleep(bool enable);
//int16_t ADXL372_Set_Act_Proc_Mode(struct ADXL372_Device *dev, ADXL372_ACT_PROC_MODE mode);
//int16_t ADXL372_Set_InstaOn_Thresh(struct ADXL372_Device *dev, ADXL_INSTAON_THRESH mode);
//int16_t ADXL372_Set_Activity_Threshold(struct ADXL372_Device *dev, uint16_t thresh, bool referenced, bool enable);
//int16_t ADXL372_Set_Inactivity_Threshold(struct ADXL372_Device *dev, uint16_t thresh, bool referenced, bool enable);
//int16_t ADXL372_Set_Activity_Time(struct ADXL372_Device *dev, uint8_t time);
//int16_t ADXL372_Set_Inactivity_Time(struct ADXL372_Device *dev, uint16_t time);
//int16_t ADXL372_Set_Filter_Settle(struct ADXL372_Device *dev, ADXL372_Filter_Settle mode);
void ADXL372_Get_DevID(uint8_t *DevID);
void ADXL372_Get_Status_Register(uint8_t *adxl_status);
void ADXL372_Get_ActivityStatus_Register(uint8_t *adxl_status);

#ifdef ADXL372_USE_FIFO_FUNCTION 
    void ADXL372_Get_Highest_Peak_Accel_data(Accel_Data_t *max_peak);
    void ADXL372_Get_FIFO_Data(int16_t count, int16_t *samples);
#endif

void ADXL372_Get_Accel_Data(Accel_Data_t *accel_data);
bool ADXL372_Get_Status_Data(void);
void ADXL372_Reset(void);
void ADXL372_Configure_FIFO(uint16_t fifo_samples, ADXL372_FIFO_MODE fifo_mode, ADXL372_FIFO_FORMAT fifo_format);
void ADXL372_Get_FIFO_Data(int16_t count, int16_t *samples);
void ADXL372_Set_Interrupts(void);
void ADXL372_Set_ActiveTime(uint8_t count);
bool ADXL372_Self_Test(void);

// Инициализация акселерометра.
void ADXL372_Initialize(void);

#endif

/*
    Конец файда.
*/