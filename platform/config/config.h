/**
*  @file      config.h
*  @brief    Configuration file. Every product can define private value of this parameters in
                its product_config.h, otherwise use the value from config_default.h
*  @author    Bill Wu
*  @date      10-2014
*  @copyright Tymphany Ltd.
*/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "config_product.h"

#ifndef NEAR
#define NEAR
#endif

#ifndef TINY
#define TINY
#endif

#ifndef FIFO_MAX_NUM
#define FIFO_MAX_NUM 30
#endif

#ifndef TIME_FOR_EACH_TICKER
#define TIME_FOR_EACH_TICKER   10        /*time for each ticker in ms*/
#endif

#ifndef TIMER_MSG_MAX_NUM
#define TIMER_MSG_MAX_NUM   20
#endif

#ifndef UART_BAUDRATE
#define UART_BAUDRATE (57600)
#endif

/* ADC PIN */
#ifndef ADC_CHANNEL
#define ADC_CHANNEL ADC1_CHANNEL_3
#endif

/* ADC PRESCALER */
#ifndef ADC_PRESCALER
#define ADC_PRESCALER ADC1_PRESSEL_FCPU_D2
#endif

/* Battery level table define */
#ifndef BATTERY_LEVEL_TABLE_MAX
#define BATTERY_LEVEL_TABLE_MAX (6)
#endif

#ifndef BATTERY_LEVEL
#define BATTERY_LEVEL
/* Battery level define */
typedef enum
{
    BATTERY_LEVEL_1,    /* 0% ~ 5% */
    BATTERY_LEVEL_2,    /* 5% ~ 10% */
    BATTERY_LEVEL_3,    /* 10% ~ 20% */
    BATTERY_LEVEL_4,    /* 20% ~ 40% */
    BATTERY_LEVEL_5,    /* 40% ~ 60% */
    BATTERY_LEVEL_6,    /* 60% ~ 80% */
    BATTERY_LEVEL_7     /* 80% ~ 100% */
} drv_battery_level_t;
#endif


/* Controller private message ID rang: 0x0~0xF */
#ifndef PRIVATE_EVENT_MESSAGE_BASE
#define PRIVATE_EVENT_MESSAGE_BASE (0x0)
#endif

/* TOP message ID rang: 0x10~0xFE */
#ifndef TOP_EVENT_MESSAGE_BASE
#define TOP_EVENT_MESSAGE_BASE (0x10)
#endif

/* Max number of task */
#ifndef EVENT_MAP_MAX_TASK
#define EVENT_MAP_MAX_TASK (5)
#endif

/* Number of event map unit, per unit include 32 events. Total event number = 32 * EVENT_MAP_UNIT.*/
#ifndef EVENT_MAP_UNIT
#define EVENT_MAP_UNIT (1)
#endif

/* Number of TOP filters */
#ifndef TOP_CORE_MAX_FILTER
#define TOP_CORE_MAX_FILTER (2)
#endif

/* The event IDs in one set must be continuous */
#ifndef TOP_PHASE_SETS
#define TOP_PHASE_SETS \
PHASE_SETS_START \
    PHASE_SET(TOP_EVENT_STARTUP_PHASE_1,    TOP_EVENT_STARTUP_PHASE_3) \
    PHASE_SET(TOP_EVENT_SHUTDOWN_PHASE_1,   TOP_EVENT_SHUTDOWN_PHASE_3) \
PHASE_SETS_END
#endif

#endif  /* __CONFIG_H__ */
