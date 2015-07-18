/**
*  @file      top_core.c
*  @brief    The core of Top. Receive input events, filter them, and publish to subscribers
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/
#include "tym_assert.h"

#include "tym_memory.h"
#include "tym_debug.h"
#include "tym_event.h"

#include "config.h"
#include "top_event.h"
#include "top_core.h"


typedef struct
{
    task_data_t top_core_task;
    top_event_filter_f top_filters[TOP_CORE_MAX_FILTER];
} top_core_inst_t;

static bool run_filters(uint16 id);
static void message_handler (message_id_t id);

static top_core_inst_t * top_core_inst = NULL;


/**
 *  TOP core init function
 *
 * @return void
 */
void top_core_init(void)
{
    uint16 i;

    STATIC_MEM_ALLOC(top_core_inst);

    TYM_ASSERT(top_core_inst != NULL);

    top_core_inst->top_core_task.handler = message_handler;

    for(i = 0; i < TOP_CORE_MAX_FILTER; i++)
    {
        top_core_inst->top_filters[i] = NULL;
    }
}

/**
 *  Subscribe TOP event
 *
 * @param task Task of the subscriber
 * @param id Event id
 * @return void
 */
void top_event_subscribe(task_t task,uint16 id)
{
    tym_event_subscribe(task, id);
}

/**
 *  Commit event to TOP
 *
 * @param id Event id
 * @return void
 */
void top_event_commit(uint16 id)
{
    TYM_ASSERT(top_core_inst != NULL);

    /* Asynchronous commit */
    tym_message_send(&top_core_inst->top_core_task, id);
}

/**
 *  Add filter. The filters running sequence is the same as adding sequence.
 *
 * @param filter Filter callback function
 * @return void
 */
void top_add_filter(top_event_filter_f filter)
{
    uint16 i;

    TYM_ASSERT(top_core_inst != NULL);

    for(i = 0; i < TOP_CORE_MAX_FILTER; i++)
    {
        if(top_core_inst->top_filters[i] == NULL)
        {
            top_core_inst->top_filters[i] = filter;
            break;
        }
    }

    TYM_ASSERT(i != TOP_CORE_MAX_FILTER); /* No enough filters, increase TOP_CORE_MAX_FILTER */
}

/**
 *  Go throught all the filters. Only the event passing all the filters can be published.
 *
 * @param event_id Event id
 * @return bool TRUE: Event can be published;  FALSE: Event can not be published
 */
static bool run_filters(uint16 event_id)
{
    uint16 i;

    TYM_ASSERT(top_core_inst != NULL);

    for(i = 0; i < TOP_CORE_MAX_FILTER; i++)
    {
        if((top_core_inst->top_filters[i] != NULL)
           && ((* top_core_inst->top_filters[i])(event_id) == FALSE))
        {
            return FALSE;
        }
    }

    return TRUE;
}

/**
 *  Message handler of TOP core. Support asynchronous commit.
 *
 * @param task Task
 * @param id Message ID
 * @param msg Message body
 * @return void
 */
static void message_handler (message_id_t id)
{
    if(run_filters(id))
    {
        tym_event_publish(id);
    }
}

