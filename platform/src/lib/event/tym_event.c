/**
*  @file      tym_event.c
*  @brief    An event mechanism support Subscribe/Publish
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/
#include <string.h>

/* TYM head files */
#include "tym_type.h"
#include "tym_debug.h"
#include "tym_assert.h"
#include "config.h"
#include "tym_memory.h"
#include "tym_message.h"

#include "tym_event.h"

/* Debug switch */
#define TYM_EVENT_DEBUG_ENABLEx
#ifdef TYM_EVENT_DEBUG_ENABLE
#define TYM_EVENT_DEBUG(x) TYM_DEBUG(x)
#else
#define TYM_EVENT_DEBUG(x)
#endif

#define MAP_BIT_NUM 32  /* Bit mumber of per map unit */
#define MAX_EVENT_ID (EVENT_MAP_UNIT * MAP_BIT_NUM - 1)      /* Max event ID */

#define EX_TO_IN(id) ((id) - TOP_EVENT_MESSAGE_BASE)
#define IN_TO_EX(id) ((id) + TOP_EVENT_MESSAGE_BASE)

typedef struct
{
    task_t task;
    uint32 map[EVENT_MAP_UNIT];
} event_map_t;


typedef struct
{
    event_map_t event_map[EVENT_MAP_MAX_TASK];
} event_inst_t;


static void map_set(uint32 map[EVENT_MAP_UNIT], uint16 id);
static bool map_check(uint32 map[EVENT_MAP_UNIT], uint16 id);

static event_inst_t * event_inst = NULL;

/**
 *  Init function.
 *
 * @return void
 */
void tym_event_init(void)
{
    STATIC_MEM_ALLOC(event_inst);

    TYM_ASSERT(event_inst != NULL);

    memset(event_inst, 0, sizeof(event_inst_t));
}

/**
 *  Subscribe an event. This function should be called at initialization phase.
 *
 * @param task The task of obsever, that receive event message
 * @param id Event ID
 * @return void
 */
void tym_event_subscribe(task_t task, uint16 id)
{
    uint16 i;

    id = EX_TO_IN(id);

    if(event_inst == NULL || task == NULL || id > MAX_EVENT_ID)
    {
        TYM_ASSERT(0);
        return;
    }

    for(i = 0; i < EVENT_MAP_MAX_TASK; i++)
    {
        if(event_inst->event_map[i].task == task || event_inst->event_map[i].task == NULL)
        {
            event_inst->event_map[i].task = task;
            map_set(event_inst->event_map[i].map , id);
            break;
        }
    }

    TYM_ASSERT(i != EVENT_MAP_MAX_TASK); /* Subscribe task is more than EVENT_MAP_MAX_TASK */
}

/**
 *  Publish an event. Every task that subscribe this event will recevie this event
 *
 * @param id Event ID
 * @return void
 */
void tym_event_publish(uint16 id)
{
    uint16 i;

    id = EX_TO_IN(id);

    if(event_inst == NULL || id > MAX_EVENT_ID)
    {
        TYM_ASSERT(0);
        return;
    }

    for(i = 0; i < EVENT_MAP_MAX_TASK; i++)
    {
        if((event_inst->event_map[i].task != NULL) && map_check(event_inst->event_map[i].map, id))
        {
            TYM_EVENT_DEBUG(("EVENT SEND [0x%02x]\n", IN_TO_EX(id)));
            tym_message_send(event_inst->event_map[i].task, IN_TO_EX(id));
        }
    }
}

/**
 *  Get subscriber number of the event
 *
 * @param id Event ID
 * @return uint16 Number of subscriber
 */
uint16 tym_event_subscriber_num(uint16 id)
{
    uint16 num = 0;
    uint16 i;

    id = EX_TO_IN(id);

    if(event_inst == NULL || id > MAX_EVENT_ID)
    {
        TYM_ASSERT(0);
        return 0;
    }

    for(i = 0; i < EVENT_MAP_MAX_TASK; i++)
    {
        if((event_inst->event_map[i].task != NULL) && map_check(event_inst->event_map[i].map, id))
        {
            num++;
        }
    }

    return num;
}

/**
 *  Set event map
 *
 * @param map Array of event map
 * @param id Event ID
 * @return void
 */
static void map_set(uint32 map[EVENT_MAP_UNIT], uint16 id)
{
    if(id >= (EVENT_MAP_UNIT * MAP_BIT_NUM))
    {
        return;
    }

    map[id / MAP_BIT_NUM] |= (((uint32)1) <<(id % MAP_BIT_NUM));
}

/**
 *  Check the event id if exit in event map
 *
 * @param map Array of event map
 * @param id Event ID
 * @return bool Return TRUE if this id exit in map, otherwise return FALSE
 */
static bool map_check(uint32 map[EVENT_MAP_UNIT], uint16 id)
{
    if(id >= (EVENT_MAP_UNIT * MAP_BIT_NUM))
    {
        return FALSE;
    }

    if(map[id / MAP_BIT_NUM] & (((uint32)1) <<(id % MAP_BIT_NUM)))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

