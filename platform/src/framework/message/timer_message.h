/**
*  @file      timer_message.h
*  @brief    timer Message Framework
*  @author    Jimmy.Z
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/
#ifndef __TIMER_MESSAGE_H__
#define __TIMER_MESSAGE_H__

#include "tym_message.h"
#include "tym_type.h"

/**
 *  init time message manager
 * @param void
 * @return void
 */
void timer_message_init(void);

/**
 *  send meesage out to handler if
 *  tick time out
 * @param void
 * @return void
 */
void timer_message_out(void);

/**
 *  Put message and the delay time into timer message buffer
 *
 * @param task The task receive message
 * @param id Message ID
 * @delay_ms the time to delay
 * @return void
 */
void timer_message_in(task_t task, message_id_t id, uint16 delay_ms);

/**
 *  clear the task and event in the message buffer
 *
 * @param task The task receive message
 * @param id Message ID
 * @return void
 */
void timer_message_cancel(task_t task, message_id_t id);

void timer_message_cancel_all(void);

#endif