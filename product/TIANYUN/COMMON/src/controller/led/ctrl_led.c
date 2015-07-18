/**
*  @file        ctrl_led.h
*  @brief       led Controller
*  @author    JZ
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#include "tym_debug.h"
#include "tym_message.h"
#include "tym_memory.h"

#include "top_event.h"

#include "srv_led.h"

#include "ctrl_led.h"

#define THIS_TASK (&ctrl_led_inst->task)

typedef struct
{
    task_data_t task;
} ctrl_led_inst_t;

static void message_handler(message_id_t id);

ctrl_led_inst_t * ctrl_led_inst = NULL;


/**
 *  Init function
 *
 * @return void
 */
void ctrl_led_init(void)
{
    STATIC_MEM_ALLOC(ctrl_led_inst);

    ctrl_led_inst->task.handler = message_handler;

    top_event_subscribe(THIS_TASK, TOP_EVENT_KICKOFF);
}

/**
 *  Loop message handler
 *
 * @param id Message ID
 * @return void
 */
static void message_handler(message_id_t id)
{
    
}
