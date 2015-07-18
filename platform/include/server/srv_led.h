/**
*  @file      srv_led.h
*  @brief    led blink mode control
*  @author    xx
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#ifndef __SRV_LED_H__
#define __SRV_LED_H__

typedef enum
{
    BATT_CHARGING_LED = 0,
    BATT_LEVEL1_LED,
    BATT_LEVEL2_LED,
    BATT_LEVEL3_LED,
    BATT_LEVEL4_LED,
    BATT_LEVEL5_LED,
    BATT_LOW_LED
/*end of the bettery led*/

}led_mode_t;

void srv_led_init(void);
/**
 *  led server control function
 * para      mode    for controller to set led display mode
 * @return void
 */
void  srv_led_control(led_mode_t mode);

#endif
