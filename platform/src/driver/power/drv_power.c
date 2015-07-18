/**
*  @file        drv_power.c
*  @brief       Power driver
*  @author    Bill Wu
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#include "io_pio.h"

#include "drv_power.h"

#define MAIN_POWER_PIO  PIO_EN_3V7
#define BT_POWER_PIO    PIO_EN_BT_AMP
#define BT_STATUS_PIO   PIO_BT2MCU_1
#define CHARGE_OUT_PIO   PIO_EN_5V
#define ACCESSORY_CHARGE_OUT_PIO PIO_EN_5V_TO_ACC

/**
 *  Init function
 *
 * @return void
 */
void drv_power_init(void)
{
    /* Main Power */
    io_pio_config(MAIN_POWER_PIO, PIO_OUTPUT);
    io_pio_set_level(MAIN_POWER_PIO, PIO_LEVEL_LOW);

    /* BT Power */
    io_pio_config(BT_POWER_PIO, PIO_OUTPUT);
    io_pio_set_level(BT_POWER_PIO, PIO_LEVEL_LOW);

    /* BT Status */
    io_pio_config(BT_STATUS_PIO, PIO_INPUT);

    /* Change Out */
    io_pio_config(CHARGE_OUT_PIO, PIO_OUTPUT);
    io_pio_set_level(CHARGE_OUT_PIO, PIO_LEVEL_LOW);

    /* Accessory Change Out */
    io_pio_config(ACCESSORY_CHARGE_OUT_PIO, PIO_OUTPUT);
    io_pio_set_level(ACCESSORY_CHARGE_OUT_PIO, PIO_LEVEL_LOW);

}

/**
 *  Main power switch
 *
 * @param switch Set switch to ON or OFF
 * @return void
 */
void drv_power_set_main_power(drv_power_status_t sw)
{
    if(sw == POWER_ON)
    {
        io_pio_set_level(MAIN_POWER_PIO, PIO_LEVEL_HIGH);
    }
    else
    {
        io_pio_set_level(MAIN_POWER_PIO, PIO_LEVEL_LOW);
    }
}

/**
 *  BT power switch
 *
 * @param switch Set switch to ON or OFF
 * @return void
 */
void drv_power_set_bt_power(drv_power_status_t sw)
{
    if(sw == POWER_ON)
    {
        io_pio_set_level(BT_POWER_PIO, PIO_LEVEL_HIGH);
    }
    else
    {
        io_pio_set_level(BT_POWER_PIO, PIO_LEVEL_LOW);
    }
}

/**
 *  Get BT module power status
 *
 * @return drv_power_status_t   BT module status
 */
drv_power_status_t drv_power_get_bt_status(void)
{
    if(io_pio_get_level(BT_STATUS_PIO) == PIO_LEVEL_LOW)
    {
        return POWER_OFF;
    }
    else
    {
        return POWER_ON;
    }
}


/**
 *  Power switch of 5V changging output
 *
 * @param switch Set switch to ON or OFF
 * @return void
 */
void drv_power_set_change_output(drv_power_status_t sw)
{
    if(sw == POWER_ON)
    {
        io_pio_set_level(CHARGE_OUT_PIO, PIO_LEVEL_HIGH);
    }
    else
    {
        io_pio_set_level(CHARGE_OUT_PIO, PIO_LEVEL_LOW);
    }
}

/**
 *  Power switch of 5V accessory changging output
 *
 * @param switch Set switch to ON or OFF
 * @return void
 */
void drv_power_set_accessory_change(drv_power_status_t sw)
{
    if(sw == POWER_ON)
    {
        io_pio_set_level(ACCESSORY_CHARGE_OUT_PIO, PIO_LEVEL_HIGH);
    }
    else
    {
        io_pio_set_level(ACCESSORY_CHARGE_OUT_PIO, PIO_LEVEL_LOW);
    }
}

