/**
*  @file      drv_led.h
*  @brief    led control
*  @author    xx
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#ifndef __DRV_LED_H__
#define __DRV_LED_H__

typedef enum
{
    LED1,
    LED2,
    LED3,
    LED4,
    LED5,
    LED6,
    LED7
}led_t;

typedef enum
{
    LED_OFF = 0,
    LED_ON
}led_status_t;

/**
 *  led driver init function. Called at system initialization
 *
 * @return void
 */
void drv_led_init(void);

/**
 *  led driver control function.turn on or off the led
 * para      led    the led you want to control
 * onOff    on  or off
 * @return void
 */
void drv_led_control(led_t led, led_status_t onOff);


#endif