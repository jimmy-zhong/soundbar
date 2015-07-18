/**
*  @file      top_state.c
*  @brief    Top layer state machine
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/

#include "tym_assert.h"
#include "tym_message.h"
#include "tym_memory.h"
#include "tym_debug.h"
#include "config.h"
#include "top_event.h"

#include "top_state.h"


/* Debug switch */
#define TOP_STATE_DEBUG_ENABLEx
#ifdef TOP_STATE_DEBUG_ENABLE
#define TOP_STATE_DEBUG(x) TYM_DEBUG(x)
#else
#define TOP_STATE_DEBUG(x)
#endif


typedef bool (* state_handler_f)(uint16 event_id, top_state_id_t * next);


typedef struct
{
    state_handler_f handler;
} top_state_t;

typedef struct
{
    task_data_t task;
    top_state_id_t cur_state;
    bool is_phase_finished;
} top_state_inst_t;


static bool handler_state_off(uint16 event_id, top_state_id_t * next);
static bool handler_state_on(uint16 event_id, top_state_id_t * next);
static bool state_filter(uint16 id);
static void top_state_switch(top_state_id_t next);


static const top_state_t state[TOP_STATE_BUTT] =
{
    {handler_state_off},
    {handler_state_on},
};

static top_state_inst_t *top_state_inst = NULL;


/**
 *  Init function
 *
 * @return void
 */
void top_state_init(void)
{
    STATIC_MEM_ALLOC(top_state_inst);

    top_state_inst->cur_state = TOP_STATE_OFF;
    top_state_inst->is_phase_finished = TRUE;

    top_add_filter(state_filter);
}

/**
 *  Get current Top state
 *
 * @return top_state_id_t State
 */
top_state_id_t top_state_get(void)
{
    TYM_ASSERT(top_state_inst != NULL);

    return top_state_inst->cur_state;
}

/**
 *  State filter callback function. This fuction filter top event, using current state handler.
 *
 * @param id Event ID
 * @return void
 */
static bool state_filter(uint16 id)
{
    top_state_id_t next_state = TOP_STATE_BUTT;
    bool ret;

    TYM_ASSERT(top_state_inst != NULL);

    /* Call the handler of current state */
    ret = (* state[top_state_inst->cur_state].handler)(id, &next_state);

    /* State switch */
    top_state_switch(next_state);

    return ret;
}

/**
 *  Switch state
 *
 * @param next Next state
 * @return void
 */
static void top_state_switch(top_state_id_t next)
{
    if((next >= TOP_STATE_BUTT) || (next == top_state_inst->cur_state))
    {
        return;
    }

    TOP_STATE_DEBUG(("State switch [%x]->[%x]\r\n", top_state_inst->cur_state, next));

    top_state_inst->cur_state = next;

    top_event_commit(TOP_EVENT_STATE_CHANGED);
}

/**
 *  Filter handler of the state OFF
 *
 * @param event_id Event ID
 * @param next Next state
 * @return bool Return TRUE if this event pass filter, otherwise return FALSE
 */
static bool handler_state_off(uint16 event_id, top_state_id_t * next)
{
    bool ret = TRUE;

    switch(event_id)
    {
        case TOP_EVENT_KICKOFF:
        case TOP_EVENT_POWER_BUTTON:
            if(top_state_inst->is_phase_finished)
            {
                top_state_inst->is_phase_finished = FALSE;

                *next = TOP_STATE_ON;
                top_event_commit(TOP_EVENT_STARTUP_PHASE_1);
            }
            else
            {
                ret = FALSE;
                TOP_STATE_DEBUG(("Top State: Ignore OFF \r\n"));
            }
            break;

        case TOP_EVENT_SHUTDOWN_PHASE_3:
            top_state_inst->is_phase_finished = TRUE;
            break;

        /* Events Passed are enumerated here */
//        case TOP_EVENT_KICKOFF:
        case TOP_EVENT_BATTERY_LEVEL_CHANGE:
        case TOP_EVENT_SHUTDOWN_PHASE_1:
        case TOP_EVENT_SHUTDOWN_PHASE_2:
        case TOP_EVENT_PHASE_DONE:
        case TOP_EVENT_STATE_CHANGED:
        case TOP_EVENT_CHARGER_PLUGGED:
        case TOP_EVENT_CHARGER_UNPLUGGED:
            break;

        default:
            /* Other events are Rejected */
            ret = FALSE;
            break;
    }

    TOP_STATE_DEBUG(("handler_state_off id[0x%02x] pass[%x] \r\n", event_id, ret));

    return ret;
}

/**
 *  Filter handler of the state ON
 *
 * @param event_id Event ID
 * @param next Next state
 * @return bool Return TRUE if this event pass filter, otherwise return FALSE
 */
static bool handler_state_on(uint16 event_id, top_state_id_t * next)
{
    bool ret = TRUE;

    switch(event_id)
    {
        case TOP_EVENT_BATTERY_CRITICAL_LOW:
            if (TRUE) /* TODO: Check AC if AC is plugged */
            {
                if(top_state_inst->is_phase_finished)
                {
                    top_state_inst->is_phase_finished = FALSE;

                    *next = TOP_STATE_OFF;
                    top_event_commit(TOP_EVENT_SHUTDOWN_PHASE_1);
                }
                else
                {
                    ret = FALSE;
                    TOP_STATE_DEBUG(("Top State: Ignore ON \r\n"));
                }
            }
            else
            {
                ret = FALSE;
            }
            break;

        case TOP_EVENT_POWER_BUTTON:
            if(top_state_inst->is_phase_finished)
            {
                top_state_inst->is_phase_finished = FALSE;

                *next = TOP_STATE_OFF;
                top_event_commit(TOP_EVENT_SHUTDOWN_PHASE_1);
            }
            else
            {
                ret = FALSE;
                TOP_STATE_DEBUG(("Top State: Ignore ON \r\n"));
            }
            break;

        case TOP_EVENT_STARTUP_PHASE_3:
            top_state_inst->is_phase_finished = TRUE;
            break;

        default:
            /* Other events are Passed */
            ret = TRUE;
            break;
    }

    TOP_STATE_DEBUG(("handler_state_on id[0x%02x] pass[%x] \r\n", event_id, ret));

    return ret;
}

