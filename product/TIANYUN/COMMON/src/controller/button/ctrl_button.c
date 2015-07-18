/**
*  @file      ctrl_button.c
*  @brief    Button controller
*  @author    Victor.Xia
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/
#include <string.h>

#include "tym_debug.h"
#include "tym_assert.h"
#include "tym_type.h"
#include "tym_memory.h"
#include "config.h"
#include "tym_message.h"
#include "top_event.h"
#include "drv_button.h"
#include "ctrl_button.h"

/* Debug switch */
#define CTRL_BTN_DEBUG_ENABLEx
#ifdef CTRL_BTN_DEBUG_ENABLE
#define CTRL_BTN_DEBUG(x) TYM_DEBUG(x)
#else
#define CTRL_BTN_DEBUG(x)
#endif


typedef struct
{
    task_data_t ctrl_btn_task;
} ctrl_button_inst_t;

static ctrl_button_inst_t *ctrl_button_inst = NULL;


static void ctrl_btn_message_handler (message_id_t id);
static void ctrl_button_notify(uint8 btn, btn_event_t event);

/**
 *  Init function
 *
 * @return void
 */
void ctrl_btn_init(void)
{
    STATIC_MEM_ALLOC(ctrl_button_inst);
    TYM_ASSERT(ctrl_button_inst != NULL);

    memset(ctrl_button_inst, 0, sizeof(ctrl_button_inst_t));

    ctrl_button_inst->ctrl_btn_task.handler = ctrl_btn_message_handler;    

    top_event_subscribe(&ctrl_button_inst->ctrl_btn_task, TOP_EVENT_KICKOFF);

    drv_button_reg_callback(ctrl_button_notify);
}

static void ctrl_button_notify(uint8 btn, btn_event_t event)
{
    CTRL_BTN_DEBUG(("ctrl_button_notify: btn[%d], event[%d]\r\n", btn, event));
    
    switch (btn)
    {
        case BTN_POWER:
            if (SP == event)
            {
                top_event_commit(TOP_EVENT_POWER_BUTTON);
            }
            break;
        case BTN_BATTERY:
            if (SP == event)
            {
                top_event_commit(TOP_EVENT_BATTERY_LEVEL_SHOW);
            }
            break;
        case BTN_POWER_BATTERY:
            break;
        default:
            break;
    }
}

/**
 *  Message handler of button controller
 *
 * @param task Task
 * @param id Message ID
 * @param msg Message body
 * @return void
 */
static void ctrl_btn_message_handler (message_id_t id)
{
    switch(id)
    {
        case TOP_EVENT_KICKOFF:
            break;
        default:
            break;
    }
}
