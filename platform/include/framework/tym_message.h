/**
*  @file      tym_message.h
*  @brief    Mini Message Framework API
*  @author    Bill Wu
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#ifndef __TYM_MESSAGE_H__
#define __TYM_MESSAGE_H__

#include "tym_type.h"

/* Message ID type define */
typedef uint8 message_id_t;

/* Message delay type define */
typedef uint16 message_delay_t;

/* Task type define */
typedef struct
{
    void (*handler)(message_id_t id);   /* Message handler */
} *task_t, task_data_t;

/**
 *  Init function
 *
 * @return void
 */
void tym_message_init(void);

/**
 *  Message loop start function
 *
 * @return void
 */
void tym_message_loop(void);

/**
 *  Message send function
 *
 * @param task The task receive message
 * @param id Message ID
 * @return void
 */
void tym_message_send(task_t task, message_id_t id);

/**
 *  Message send function with delay
 *
 * @param task The task receive message
 * @param id Message ID
 * @param delay The task will receive this message (delay * ms) later
 * @return void
 */
void tym_message_send_later(task_t task, message_id_t id, message_delay_t delay);

/**
 *  Cancel the message sent by tym_message_send_later()
 *
 * @param task The task receive message
 * @param id Message ID
 * @return void
 */
void tym_message_cancel(task_t task, message_id_t id);

#endif /* __TYM_MESSAGE_H__ */

