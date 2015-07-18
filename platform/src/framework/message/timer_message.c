/**
*  @file      timer_message.c
*  @brief    timer Message Framework
*  @author    Jimmy.Z
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/
#include <string.h>

#include "tym_assert.h"

#include "config.h"
#include "tym_timer.h"
#include "timer_message.h"

#define ERROR_ID        0xFF

/* timer message node define */
typedef struct
{
    task_t task;
    message_id_t id;
    uint16 delay_ticker;
} timer_msg_node_t;

static void timer_message_handler(void);

static TINY timer_msg_node_t timer_msg_node[TIMER_MSG_MAX_NUM]; /* timer message */
static TINY volatile uint8 msg_time_out_counter = 0;

/**
 *  init time message manager
 * @param void
 * @return void
 */
void timer_message_init(void)
{
    memset(timer_msg_node, 0, sizeof(timer_msg_node));

    tym_timer_register(TIME_FOR_EACH_TICKER, timer_message_handler);
}

/**
 *  Put message and the delay time into timer message buffer
 *
 * @param task The task receive message
 * @param id Message ID
 * @delay_ms the time to delay
 * @return void
 */
void timer_message_in(task_t task, message_id_t id, uint16 delay_ms)
{
    uint8 i;

    if (delay_ms < TIME_FOR_EACH_TICKER)
    {   //minimum time to set is TIME_FOR_EACH_TICKER
        delay_ms = TIME_FOR_EACH_TICKER;
        TYM_ASSERT(FALSE);
    }

    for (i = 0; i < TIMER_MSG_MAX_NUM; i ++)
    {
        if (( NULL == timer_msg_node[i].task) && (0 == timer_msg_node[i].delay_ticker))
        {
            timer_msg_node[i].delay_ticker  = delay_ms / TIME_FOR_EACH_TICKER;
            timer_msg_node[i].task      = task;
            timer_msg_node[i].id        = id;
            break;
        }
    }

    TYM_ASSERT((i != TIMER_MSG_MAX_NUM));
}

/**
 *  clear the task and event in the message buffer
 *
 * @param task The task receive message
 * @param id Message ID
 * @return void
 */
void timer_message_cancel(task_t task, message_id_t id)
{
    uint8 i;
    TYM_ASSERT(NULL != task);

    for (i = 0; i < TIMER_MSG_MAX_NUM; i ++)
    {
        if (task == timer_msg_node[i].task)
        {
            if (!timer_msg_node[i].delay_ticker)
            {/*for the evens that already in the buffer but haven't message out*/
                msg_time_out_counter --;
            }
            timer_msg_node[i].delay_ticker  = 0;
            timer_msg_node[i].task      = NULL;
            timer_msg_node[i].id        = ERROR_ID;
            return;
        }
    }
}

/**
 *  send meesage out to handler if
 *  tick time out
 * @param void
 * @return void
 */
void timer_message_out(void)
{
    uint8 i;

    if (msg_time_out_counter)
    {
        for (i = 0; i < TIMER_MSG_MAX_NUM; i ++)
        {
            if (( NULL != timer_msg_node[i].task) && (!timer_msg_node[i].delay_ticker))
            {
                timer_msg_node[i].task->handler(timer_msg_node[i].id);
                timer_msg_node[i].task      = NULL;
                timer_msg_node[i].id        = ERROR_ID;
                msg_time_out_counter --;
                return;
            }
        }
    }
}

/**
 *  check the timer message buffer every tick
 *  this handler should be called in irq
 * @param void
 * @return void
 */
static void timer_message_handler(void)
{
    uint8 i;

    for (i = 0; i < TIMER_MSG_MAX_NUM; i ++)
    {
        if(NULL == timer_msg_node[i].task) continue;

        if(timer_msg_node[i].delay_ticker > 0)
        {
            timer_msg_node[i].delay_ticker  --;
            if(timer_msg_node[i].delay_ticker == 0)  msg_time_out_counter ++;
        }
    }
}
