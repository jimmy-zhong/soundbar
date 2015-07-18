/**
*  @file      io_pio.c
*  @brief    STM8S PIO control and dectect
*  @author    xx
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#include "io_pio.h"
#include "drv_led.h"

#define LED_TYPE         pio_mapping_t

#define LED_TRUN_OFF(X)      io_pio_set_level(X, PIO_LEVEL_HIGH)
#define LED_TRUN_ON(X)       io_pio_set_level(X, PIO_LEVEL_LOW)
#define LED_REGISTER(X) io_pio_config(X, PIO_OUTPUT)


const uint8 led_hardware_mapping[] =
{
    PIO_BATT_LED1,
    PIO_BATT_LED2,
    PIO_BATT_LED3,
    PIO_BATT_LED4,
    PIO_BATT_LED5
};

#define TABLE_LEN  (sizeof(led_hardware_mapping) / sizeof(uint8))

/**
 *  led driver init function. Called at system initialization
 *
 * @return void
 */
void drv_led_init(void)
{
    uint8 i;

    for (i = 0; i < TABLE_LEN; i ++)
    {
        if (led_hardware_mapping[i])
        {
            LED_REGISTER(led_hardware_mapping[i]);
            LED_TRUN_OFF(led_hardware_mapping[i]);
        }
    }
}

/**
 *  led driver control function.turn on or off the led
 * para      led    the led you want to control
 * onOff    on  or off
 * @return void
 */
void drv_led_control(led_t led, led_status_t onOff)
{
    if(led >= TABLE_LEN)
    {
        return;
    }

    if (LED_OFF == onOff)
    {
        LED_TRUN_OFF(led_hardware_mapping[led]);
    }
    else
    {
        LED_TRUN_ON(led_hardware_mapping[led]);
    }
}

