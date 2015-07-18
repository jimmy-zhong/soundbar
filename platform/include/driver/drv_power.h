/**
*  @file        drv_power.h
*  @brief       Power driver
*  @author    Bill Wu
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#ifndef __DRV_POWER_H__
#define __DRV_POWER_H__

typedef enum
{
    POWER_OFF,
    POWER_ON
} drv_power_status_t;

/**
 *  Init function
 *
 * @return void
 */
void drv_power_init(void);

/**
 *  Main power switch
 *
 * @param switch Set switch to ON or OFF
 * @return void
 */
void drv_power_set_main_power(drv_power_status_t sw);

/**
 *  BT power switch
 *
 * @param switch Set switch to ON or OFF
 * @return void
 */
void drv_power_set_bt_power(drv_power_status_t sw);

/**
 *  Get BT module power status
 *
 * @return drv_power_status_t   BT module status
 */
drv_power_status_t drv_power_get_bt_status(void);

/**
 *  Power switch of 5V changging output
 *
 * @param switch Set switch to ON or OFF
 * @return void
 */
void drv_power_set_change_output(drv_power_status_t sw);

/**
 *  Power switch of 5V accessory changging output
 *
 * @param switch Set switch to ON or OFF
 * @return void
 */
void drv_power_set_accessory_change(drv_power_status_t sw);

#endif /* __DRV_POWER_H__ */

