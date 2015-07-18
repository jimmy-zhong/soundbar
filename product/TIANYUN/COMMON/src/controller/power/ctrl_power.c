/**
*  @file        ctrl_power.c
*  @brief       Power Controller
*  @author    Bill Wu
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#include "tym_debug.h"
#include "tym_type.h"
#include "tym_memory.h"
#include "config.h"
#include "tym_message.h"


#include "top_event.h"

#include "drv_power.h"
#include "drv_led.h"
#include "srv_led.h"


#include "ctrl_power.h"

#define CTRL_PWR_DEBUG_ENABLEx
#ifdef CTRL_PWR_DEBUG_ENABLE
#define CTRL_PWR_DEBUG(x) TYM_DEBUG(x)
#else
#define CTRL_PWR_DEBUG(x)
#endif

#define BT_POWER_ON_DELAY (300)
#define BT_POWER_ON_HOLD_TIME   (2100)

typedef enum
{
    MESSAGE_BT_POWER_ON = PRIVATE_EVENT_MESSAGE_BASE,
    MESSAGE_BT_POWER_ON_HOLD
} ctrl_power_message_t;

typedef struct
{
    task_data_t task;
} ctrl_power_inst_t;

ctrl_power_inst_t *ctrl_power_inst = NULL;
#define THIS_TASK (&ctrl_power_inst->task)

static void message_handler(message_id_t id);
static void bt_power_button_ind(void);


/**
 *  Init function
 *
 * @return void
 */
void ctrl_power_init(void)
{
    STATIC_MEM_ALLOC(ctrl_power_inst);

    ctrl_power_inst->task.handler = message_handler;

    top_event_subscribe(THIS_TASK,  TOP_EVENT_KICKOFF);
    top_event_subscribe(THIS_TASK,  TOP_EVENT_STARTUP_PHASE_1);
    top_event_subscribe(THIS_TASK,  TOP_EVENT_STARTUP_PHASE_3);
    top_event_subscribe(THIS_TASK,  TOP_EVENT_SHUTDOWN_PHASE_1);
    top_event_subscribe(THIS_TASK,  TOP_EVENT_SHUTDOWN_PHASE_3);
}

/**
 *  Loop message handler
 *
 * @param id Message ID
 * @return void
 */
void message_handler(message_id_t id)
{
    switch(id)
    {
        case TOP_EVENT_KICKOFF:
            drv_led_control(LED1, LED_ON);

            drv_power_set_main_power(POWER_ON);
            drv_power_set_change_output(POWER_ON);
            drv_power_set_accessory_change(POWER_ON);
            CTRL_PWR_DEBUG(("Kickoff\n"));
 //           srv_led_control(BATT_LEVEL1_LED);
            break;

        case TOP_EVENT_STARTUP_PHASE_1:
            drv_led_control(LED2, LED_ON);

            bt_power_button_ind();

            top_event_commit(TOP_EVENT_PHASE_DONE);
            CTRL_PWR_DEBUG(("Power On\n"));
            break;

        case TOP_EVENT_SHUTDOWN_PHASE_1:
            drv_led_control(LED2, LED_OFF);

            bt_power_button_ind();

            top_event_commit(TOP_EVENT_PHASE_DONE);
            CTRL_PWR_DEBUG(("Power Off\n"));
            break;

        case MESSAGE_BT_POWER_ON_HOLD:
            drv_power_set_bt_power(POWER_OFF);
            break;

        case TOP_EVENT_STARTUP_PHASE_3:
            top_event_commit(TOP_EVENT_PHASE_DONE);
            srv_led_control(BATT_LEVEL1_LED);
            break;

        case TOP_EVENT_SHUTDOWN_PHASE_3:
            top_event_commit(TOP_EVENT_PHASE_DONE);
            break;

        default:
            break;
    }

}

static void bt_power_button_ind(void)
{
    drv_power_set_bt_power(POWER_ON);
    tym_message_send_later(THIS_TASK, MESSAGE_BT_POWER_ON_HOLD, BT_POWER_ON_HOLD_TIME);
}


