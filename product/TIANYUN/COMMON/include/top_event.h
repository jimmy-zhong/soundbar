/**
*  @file      top_event.h
*  @brief    Top layer event define
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/

#ifndef __TOP_EVENT_H__
#define __TOP_EVENT_H__

#include "config.h"
#include "top_core.h"

typedef enum
{
    /* System init and deinit */
    TOP_EVENT_KICKOFF = TOP_EVENT_MESSAGE_BASE,
    TOP_EVENT_PHASE_DONE,

    TOP_EVENT_STARTUP_PHASE_1,
    TOP_EVENT_STARTUP_PHASE_2,
    TOP_EVENT_STARTUP_PHASE_3,

    TOP_EVENT_SHUTDOWN_PHASE_1,
    TOP_EVENT_SHUTDOWN_PHASE_2,
    TOP_EVENT_SHUTDOWN_PHASE_3,

    TOP_EVENT_STATE_CHANGED,

    /* System Event */
    TOP_EVENT_POWER_BUTTON,
    TOP_EVENT_AUTO_POWER_OFF,

    TOP_EVENT_BATTERY_LEVEL_CHANGE,
    TOP_EVENT_BATTERY_LEVEL_SHOW,
    TOP_EVENT_BATTERY_CRITICAL_LOW,

    TOP_EVENT_CHARGER_PLUGGED,
    TOP_EVENT_CHARGER_UNPLUGGED,

    TOP_EVENT_BUTT
} top_event_t;


#define TOP_EVENT_BEGIN  TOP_EVENT_MESSAGE_BASE
#define TOP_EVENT_END    TOP_EVENT_BUTT

#endif /* __TOP_EVENT_H__ */


