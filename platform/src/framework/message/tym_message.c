/**
*  @file      tym_message.c
*  @brief    Mini Message Framework
*  @author    Bill Wu
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#include "tym_type.h"

#include "fifo_message.h"

#include "timer_message.h"

#include "tym_message.h"

/**
 *  Init function
 *
 * @return void
 */
void tym_message_init(void)
{
    fifo_message_init();

    timer_message_init();
}

/**
 *  Message loop start function
 *
 * @return void
 */
void tym_message_loop(void)
{

    /* System while loop */
    while(1)
    {
        if(!fifo_message_is_empty())
        {
            fifo_message_out();
        }
        else
        {
            timer_message_out();
        }
    }
}

/**
 *  Message send function
 *
 * @param task The task receive message
 * @param id Message ID
 * @return void
 */
void tym_message_send(task_t task, message_id_t id)
{
    fifo_message_in(task, id);
}

/**
 *  Message send function with delay
 *
 * @param task The task receive message
 * @param id Message ID
 * @param delay The task will receive this message (delay * ms) later
 * @return void
 */
void tym_message_send_later(task_t task, message_id_t id, message_delay_t delay)
{
    timer_message_in(task, id, delay);
}

/**
 *  Cancel the message sent by tym_message_send_later()
 *
 * @param task The task receive message
 * @param id Message ID
 * @return void
 */
void tym_message_cancel(task_t task, message_id_t id)
{
    timer_message_cancel(task, id);
}

