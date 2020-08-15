

/*
    Секция: Включаемые файлы.
*/

#include "adxl372.h"
#include "../mcc_generated_files/eusart.h"

/*
    Секция: APIs.
*/

void SPI_Write_Then_Read(uint8_t *txbuf, uint8_t n_tx,
                         uint8_t *rxbuf, uint8_t n_rx)
{
    volatile uint8_t count;

    IO_CS_SetLow();
    for (count = 0; count < n_tx; count++)
    {
        SPI_WriteByte((uint8_t)txbuf[count]);
    }
    for (count = 0; count < n_rx; count++)
    {
        rxbuf[count] = SPI_ExchangeByte(0x00);
    }
    IO_CS_SetHigh();
}

static void ADXL_Read_Reg_Multiple(uint8_t reg, uint8_t count, uint8_t *val)
{
    reg = reg << 1 | ADXL_SPI_RNW;
    SPI_Write_Then_Read(&reg, 1, val, count);
}

void ADXL_Read_Reg(uint8_t reg, uint8_t *val)
{
    ADXL_Read_Reg_Multiple(reg, 1, val);
}

void ADXL_Write_Reg(uint8_t reg, uint8_t val)
{
    uint8_t tmp[2];
    tmp[0] = reg << 1;
    tmp[1] = val;

    SPI_Write_Then_Read(tmp, 2, NULL, 0);  
}

static void ADXL_Update_Reg(uint8_t reg, uint8_t mask, uint8_t shift, uint8_t val)
{
    uint8_t tmp;

    ADXL_Read_Reg(reg, &tmp);
    
    tmp &= mask;
    tmp |= (val << shift) & ~mask;

    ADXL_Write_Reg(reg, tmp);
}

void ADXL372_Set_Op_Mode(ADXL372_OP_MODE mode)
{
    ADXL_Update_Reg(ADI_ADXL372_POWER_CTL, PWRCTRL_OPMODE_MASK, 0, mode);
}

void ADXL372_Set_ODR(ADXL372_ODR odr)
{
    ADXL_Update_Reg(ADI_ADXL372_TIMING, TIMING_ODR_MASK, TIMING_ODR_POS, odr);
}

//int16_t ADXL372_Set_WakeUp_Rate(struct ADXL372_Device *dev, ADXL372_WUR wur)
//{
//    return adxl_update_reg(dev->spi, ADI_ADXL372_TIMING, 
//                           TIMING_WUR_MASK, TIMING_WUR_POS, wur);
//}

void ADXL372_Set_BandWidth(ADXL372_BW bw)
{
    ADXL_Update_Reg(ADI_ADXL372_MEASURE, MEASURE_BANDWIDTH_MASK, 0, bw);
}

void ADXL372_Set_HighFilter(ADXL372_HPF hpf)
{
    ADXL_Update_Reg(ADI_ADXL372_HPF, MEASURE_BANDWIDTH_MASK, 0, hpf);
}

void ADXL372_Set_AutoSleep(bool enable)
{
    return ADXL_Update_Reg(ADI_ADXL372_MEASURE, MEASURE_AUTOSLEEP_MASK, MEASURE_AUTOSLEEP_POS, enable);
}

//int16_t ADXL372_Set_Act_Proc_Mode(struct ADXL372_Device *dev,
//                              ADXL372_ACT_PROC_MODE mode)
//{
//    return adxl_update_reg(dev->spi, ADI_ADXL372_MEASURE, 
//                           MEASURE_ACTPROC_MASK,
//                           MEASURE_ACTPROC_POS, mode);
//}
//
//int16_t ADXL372_Set_InstaOn_Thresh(struct ADXL372_Device *dev,
//                               ADXL_INSTAON_THRESH mode)
//{
//    return adxl_update_reg(dev->spi, ADI_ADXL372_POWER_CTL,
//                           PWRCTRL_INSTON_THRESH_MASK, 
//                           INSTAON_THRESH_POS, mode);
//}
//
//int16_t ADXL372_Set_Activity_Threshold(struct ADXL372_Device *dev,
//                                    uint16_t thresh, bool referenced, bool enable)
//{
//    int16_t err = ADXL372_Set_Op_Mode(dev, STAND_BY); /* FIXME ? */
//    if (err < 0)
//        return err;
//
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_X_THRESH_ACT_H, thresh >> 3);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_X_THRESH_ACT_L,
//                   (thresh << 5) | (referenced << 1) | enable);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_Y_THRESH_ACT_H, thresh >> 3);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_Y_THRESH_ACT_L, (thresh << 5) | enable);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_Z_THRESH_ACT_H, thresh >> 3);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_Z_THRESH_ACT_L, (thresh << 5) | enable);
//
//    return err;
//}
//
//int16_t ADXL372_Set_Activity2_Threshold(struct ADXL372_Device *dev,
//                                        uint16_t thresh, bool referenced, bool enable)
//{
//    int16_t err = ADXL372_Set_Op_Mode(dev, STAND_BY); /* FIXME ? */
//    if (err < 0)
//        return err;
//
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_X_THRESH_ACT2_H, thresh >> 3);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_X_THRESH_ACT2_L,
//                   (thresh << 5) | (referenced << 1) | enable);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_Y_THRESH_ACT2_H, thresh >> 3);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_Y_THRESH_ACT2_L, (thresh << 5) | enable);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_Z_THRESH_ACT2_H, thresh >> 3);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_Z_THRESH_ACT2_L, (thresh << 5) | enable);
//
//    return err;
//}
//
//int16_t ADXL372_Set_Inactivity_Threshold(struct ADXL372_Device *dev,
//                                        uint16_t thresh, bool referenced, bool enable)
//{
//    int err = ADXL372_Set_Op_Mode(dev, STAND_BY); /* FIXME ? */
//    if (err < 0)
//        return err;
//
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_X_THRESH_INACT_H, thresh >> 3);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_X_THRESH_INACT_L,
//                   (thresh << 5) | (referenced << 1) | enable);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_Y_THRESH_INACT_H, thresh >> 3);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_Y_THRESH_INACT_L, (thresh << 5) | enable);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_Z_THRESH_INACT_H, thresh >> 3);
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_Z_THRESH_INACT_L, (thresh << 5) | enable);
//
//    return err;
//}
//
//int16_t ADXL372_Set_Activity_Time(struct ADXL372_Device *dev, uint8_t time)
//{
//    return ADXL_Write_Reg(dev->spi, ADI_ADXL372_TIME_ACT, time);
//}
//
//int16_t ADXL372_Set_Inactivity_Time(struct ADXL372_Device *dev, uint16_t time)
//{
//    ADXL_Write_Reg(dev->spi, ADI_ADXL372_TIME_INACT_H, time >> 8);
//
//    return ADXL_Write_Reg(dev->spi, ADI_ADXL372_TIME_INACT_L, time & 0xFF);
//}
//
//int16_t ADXL372_Set_Filter_Settle(struct ADXL372_Device *dev,
//                                    ADXL372_Filter_Settle mode)
//{
//    return adxl_update_reg(dev->spi, ADI_ADXL372_POWER_CTL,
//                           PWRCTRL_FILTER_SETTLE_MASK, 
//                           PWRCTRL_FILTER_SETTLE_POS, mode);
//}

void ADXL372_Get_DevID(uint8_t *DevID)
{
    ADXL_Read_Reg_Multiple(ADI_ADXL372_ADI_DEVID, 1, DevID);
}

void ADXL372_Get_Status_Register(uint8_t *adxl_status)
{
    ADXL_Read_Reg(ADI_ADXL372_STATUS_1, adxl_status);
}

void ADXL372_Get_ActivityStatus_Register(uint8_t *adxl_status)
{
    ADXL_Read_Reg(ADI_ADXL372_STATUS_2, adxl_status);
}

#define SWAP16(x) ((x) = (((x) & 0x00FF) << 8) | (((x) & 0xFF00) >> 8))
#define SHIFT4(x) ((x) = (x) >> 4)

#ifdef ADXL372_USE_FIFO_FUNCTION  
    void ADXL372_Get_Highest_Peak_Accel_data(Accel_Data_t *max_peak)
    {
        uint8_t buffer[6];
        uint8_t status;

        do
        {
            ADXL372_Get_Status_Register(&status);
        }
        while (!(status & DATA_RDY));

        ADXL_Read_Reg_Multiple(ADI_ADXL372_X_MAXPEAK_H, 6, buffer);

#ifdef L_ENDIAN
        max_peak->x = (buffer[0] << 4) | (buffer[1] >> 4);
        max_peak->y = (buffer[2] << 4) | (buffer[3] >> 4);
        max_peak->y = (buffer[5] << 4) | (buffer[5] >> 4);
#endif
        SHIFT4(max_peak->x);
        SHIFT4(max_peak->y);
        SHIFT4(max_peak->z);
    }
#endif  

void ADXL372_Get_Accel_Data(Accel_Data_t *accel_data)
{
    uint8_t status;
    do
    {
        ADXL372_Get_Status_Register(&status);
    }
    while (!(status & DATA_RDY));

    ADXL_Read_Reg_Multiple(ADI_ADXL372_X_DATA_H, 6, (uint8_t *) accel_data);

#ifdef L_ENDIAN
    SWAP16(accel_data->x);
    SWAP16(accel_data->y);
    SWAP16(accel_data->z);
#endif
    SHIFT4(accel_data->x);
    SHIFT4(accel_data->y);
    SHIFT4(accel_data->z);
}

bool ADXL372_Get_Status_Data(void)
{
    uint8_t status;
    ADXL372_Get_Status_Register(&status);
    // Use mask.
    return (status & DATA_RDY);
}

void ADXL372_Reset()
{
    ADXL_Write_Reg(ADI_ADXL372_SRESET, 0x52);
    __delay_ms(1);
}

void ADXL372_Configure_FIFO(uint16_t fifo_samples, ADXL372_FIFO_MODE fifo_mode, ADXL372_FIFO_FORMAT fifo_format)
{
    ADXL372_Set_Op_Mode(STAND_BY);
    fifo_samples -= 1;
    
    uint8_t config = ((uint8_t) fifo_mode << FIFO_CRL_MODE_POS) |
                     ((uint8_t) fifo_format << FIFO_CRL_FORMAT_POS) |
                     ((fifo_samples > 0xFF) << FIFO_CRL_SAMP8_POS);

    ADXL_Write_Reg(ADI_ADXL372_FIFO_SAMPLES, fifo_samples & 0xFF);
    ADXL_Write_Reg(ADI_ADXL372_FIFO_CTL, config);
}

#ifdef ADXL372_USE_FIFO_FUNCTION 
    void ADXL372_Get_FIFO_Data(int16_t count, int16_t *samples)
    {
        int16_t i;

        ADXL_Read_Reg_Multiple(ADI_ADXL372_FIFO_DATA, count * 2, (uint8_t *) samples);

#ifdef L_ENDIAN
        for (i = 0; i < count; i++)
        {
            SWAP16(samples[i]);
        }
#endif
    }
#endif 

void ADXL372_Set_Interrupts()
{
    ADXL_Write_Reg(ADI_ADXL372_INT1_MAP, 0b10000001);
}

void ADXL372_Set_ActiveTime(uint8_t count) 
{
    ADXL_Write_Reg(ADI_ADXL372_TIME_ACT, count);
}

bool ADXL372_Self_Test(void)
{
    // В стадии разработки.
    return true;
}

void ADXL372_Initialize(void)
{
    __delay_ms(500);
    ADXL372_Set_ODR(ODR_400Hz);
    ADXL372_Set_BandWidth(BW_200Hz);
    ADXL372_Set_HighFilter(HPF_CORNER3);
    ADXL372_Set_Interrupts();
    ADXL372_Set_Op_Mode(FULL_BW_MEASUREMENT);
}

/*
    Конец файда.
*/
