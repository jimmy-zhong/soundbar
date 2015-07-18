/**
*  @file      config_product_pio.h
*  @brief    PIO configuration file of CA10
*  @author    Bill Wu
*  @date      01-2014
*  @copyright Tymphany Ltd.
*/

#ifndef __CONFIG_PRODUCT_PIO_H__
#define __CONFIG_PRODUCT_PIO_H__


/*****************************
 *   PIO mapping config
 *
 *****************************/
typedef enum
{
    PIO_EN_5V               = 0xA1,
    PIO_EN_3V7              = 0xA2,
    PIO_EN_BT_AMP           = 0xA3,
    PIO_ACC_DET             = 0xB4,
    PIO_CHARGE_DET          = 0xB5,
    PIO_BATT_LED1           = 0xC3,
    PIO_BT2MCU_1            = 0xC4,
    PIO_BATT_LED2           = 0xC5,
    PIO_KEY_PWR_ON          = 0xC6,
    PIO_BATT_LED5           = 0xC7,
    PIO_EN_5V_TO_ACC        = 0xD1,
    PIO_KEY_BAT_IND         = 0xD3,
    PIO_BT2MCU_2            = 0xD4,
    PIO_BATT_LED3           = 0xD5,
    PIO_BATT_LED4           = 0xD6
} pio_mapping_t;

#endif  /* __CONFIG_PRODUCT_PIO_H__ */

