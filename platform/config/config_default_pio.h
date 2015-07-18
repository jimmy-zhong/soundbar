/**
*  @file      config_default_pio.h
*  @brief    Configuration file of BT platform. Every product can define private value of this parameters in
                its product_config.h, otherwise use the value from config_default.h
*  @author    Bill Wu
*  @date      01-2014
*  @copyright Tymphany Ltd.
*/

#ifndef __CONFIG_DEFAULT_PIO_H__
#define __CONFIG_DEFAULT_PIO_H__

/*****************************
 *   PIO mapping config
 *
 *****************************/
typedef enum
{
    PIO_A1              = 0xA1,
    PIO_A2              = 0xA2,
    PIO_A3              = 0xA3
} pio_mapping_t;


#endif  /* __CONFIG_DEFAULT_PIO_H__ */

