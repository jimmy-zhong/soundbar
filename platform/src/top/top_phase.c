/**
*  @file      top_phase.c
*  @brief    Support a mechanism of feedback collection and event sequence. The sets is seriel.
*  @author    Bill Wu
*  @date      01 -2014
*  @copyright Tymphany Ltd.
*/

#include "tym_assert.h"

#include "tym_event.h"
#include "tym_memory.h"
#include "tym_debug.h"

#include "config.h"
#include "top_event.h"
#include "top_core.h"
#include "top_phase.h"

#define DEBUG_PHASEx
#ifdef DEBUG_PHASE
#define PHASE_DEBUG(x) TYM_DEBUG(x)
#else
#define PHASE_DEBUG(x)
#endif


#define PHASE_SETS_START {
#define PHASE_SET(start, end) {start, end},
#define PHASE_SETS_END PHASE_SET(TOP_EVENT_END, TOP_EVENT_END)}

typedef enum
{
    PHASE_STATE_IDLE,
    PHASE_STATE_WAIT
} top_phase_state_t;

typedef struct
{
    top_phase_state_t state;
    uint16 set;
    uint16 event;
    uint16 expect_count;
    uint16 current_count;
} top_phase_inst_t;

typedef struct
{
    uint16 start;
    uint16 end;
} top_set_t;

static bool phase_filter(uint16 id);
static bool state_idle_handler(uint16 id);
static bool state_wait_handler(uint16 id);
static bool go_to_next_event(void);
static bool get_next_event(uint16 *next_event, uint16 *expect_count);
static void state_switch(top_phase_state_t state);

top_phase_inst_t * top_phase_inst = NULL;
static top_set_t phase_sets[] = TOP_PHASE_SETS;
#define SETS_NUMBER (sizeof(phase_sets) / sizeof(top_set_t))

/**
 *  Init function
 *
 * @return void
 */
void top_phase_init(void)
{
    STATIC_MEM_ALLOC(top_phase_inst);

    TYM_ASSERT(top_phase_inst != NULL);

    top_phase_inst->state = PHASE_STATE_IDLE;

    top_add_filter(phase_filter);
}

/**
 *  Top phase filter
 *
 * @param id Event ID
 * @return bool TRUE: Pass filter. FALSE: Reject by filter
 */
static bool phase_filter(uint16 id)
{
    bool ret;

    switch(top_phase_inst->state)
    {
        case PHASE_STATE_IDLE:
            ret = state_idle_handler(id);
            break;

        case PHASE_STATE_WAIT:
            ret = state_wait_handler(id);
            break;

        default:
            ret = TRUE;
            break;
    }

    return ret;
}

/**
 *  Idel state handler
 *
 * @param id Event ID
 * @return bool TRUE: Pass filter. FALSE: Reject by filter
 */
static bool state_idle_handler(uint16 id)
{
    uint16 i;

    for(i = 0; i < SETS_NUMBER; i++)
    {
        if(id == phase_sets[i].start)
        {
            /* Set start event as current event */
            top_phase_inst->set = i;
            top_phase_inst->event = id;
            top_phase_inst->current_count = 0;
            top_phase_inst->expect_count = tym_event_subscriber_num(id);

            if(top_phase_inst->expect_count == 0) /* If the event without subscriber, go to next event */
            {
                if(go_to_next_event())
                {
                    PHASE_DEBUG(("[TOP PHASE]: New Exp[%d] \r\n", top_phase_inst->expect_count));
                    state_switch(PHASE_STATE_WAIT);
                }
            }
            else
            {
                PHASE_DEBUG(("[TOP PHASE]: New Exp[%d] \r\n", top_phase_inst->expect_count));
                state_switch(PHASE_STATE_WAIT);
            }
        }
    }

    return TRUE;
}

/**
 *  Waiting state handler
 *
 * @param id Event ID
 * @return bool TRUE: Pass filter. FALSE: Reject by filter
 */
static bool state_wait_handler(uint16 id)
{
    if(id == TOP_EVENT_PHASE_DONE)
    {
        top_phase_inst->current_count++;

        PHASE_DEBUG(("[TOP PHASE]: Cur[%d] \r\n", top_phase_inst->current_count));

        if(top_phase_inst->current_count == top_phase_inst->expect_count)
        {
            if(!go_to_next_event())
            {
                state_switch(PHASE_STATE_IDLE);
            }
        }

        return FALSE; /* TOP_EVENT_PHASE_DONE is handled only by phase filter  */
    }

    return TRUE;
}

/**
 *  Go to next event
 *
 * @return bool TRUE: successfully go to next event. FALSE: Reach the end event, has no next event
 */
static bool go_to_next_event(void)
{
    uint16 next_event;
    uint16 expect_count;

    if(get_next_event(&next_event, &expect_count))
    {
        top_phase_inst->expect_count = expect_count;
        top_phase_inst->current_count = 0;
        top_phase_inst->event = next_event;

        PHASE_DEBUG(("[TOP PHASE]: New Exp[%d] \r\n", top_phase_inst->expect_count));
        top_event_commit(next_event);

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 *  Get next event, if the next event has subscribers
 *
 * @param next_event Output next event, if return value is TRUE
 * @param expect_count Output except count, if return value is TRUE
 * @return bool TRUE: Has next event. FALSE: No next event
 */
static bool get_next_event(uint16 *next_event, uint16 *expect_count)
{
    uint16 current_event = top_phase_inst->event;
    uint16 end_event = phase_sets[top_phase_inst->set].end;
    uint16 subscriber_num;

    TYM_ASSERT(current_event <= end_event);

    while(current_event < end_event)
    {
        current_event++;

        subscriber_num = tym_event_subscriber_num(current_event);

        if(subscriber_num != 0) /* If the event without subscriber, go to next event */
        {
            *next_event = current_event;
            *expect_count = subscriber_num;
            return TRUE;
        }
    }

    return FALSE;
}

/**
 *  State switch
 *
 * @param state The target state
 * @return void
 */
static void state_switch(top_phase_state_t state)
{
    if(state != top_phase_inst->state)
    {
        PHASE_DEBUG(("TOP Phase: State switch [%x]->[%x] \r\n", top_phase_inst->state, state));

        top_phase_inst->state = state;
    }
}


