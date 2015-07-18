/**
*  @file      tym_event.h
*  @brief    An event mechanism support Subscribe/Publish
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/

#ifndef __TYM_EVENT_H__
#define __TYM_EVENT_H__

#include "tym_message.h"

/**
 *  Init function.
 *
 * @return void
 */
void tym_event_init(void);

/**
 *  Subscribe an event.
 *
 * @param task The task of obsever, that receive event message
 * @param id Event ID
 * @return void
 */
void tym_event_subscribe(task_t task, uint16 id);

/**
 *  Publish an event. Every task that subscribe this event will recevie this event
 *
 * @param id Event ID
 * @return void
 */
void tym_event_publish(uint16 id);

/**
 *  Get subscriber number of the event
 *
 * @param id Event ID
 * @return uint16 Number of subscriber
 */
uint16 tym_event_subscriber_num(uint16 id);

#endif /* __TYM_EVENT_H__ */

