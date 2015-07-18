/**
*  @file      drv_button.h
*  @brief    Button driver
*  @author    Victor.Xia
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#ifndef __DRV_BUTTON_H__
#define __DRV_BUTTON_H__

#include "tym_type.h"

#define    BTN_POWER            (uint8)(0x01)
#define    BTN_BATTERY          (uint8)(0x02)
#define    BTN_POWER_BATTERY    (uint8)(0x03)

typedef enum
{
    NOT_PRESSED = 0,
    NONE_EVENT,
    SP,
    LP,
    VLP,
    PRESS_HOLD
} btn_event_t;


typedef void  (*drv_button_callback_t)(uint8 btn, btn_event_t event);

void drv_button_init(void);

void drv_button_reg_callback(drv_button_callback_t handler);
#endif