/**
*  @file      top_core.h
*  @brief    The core of Top. Receive input events, filter them, and publish to subscribers
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/

#ifndef __TOP_CORE_H__
#define __TOP_CORE_H__

#include "tym_type.h"
#include "tym_message.h"

/**
 *  Top core init function
 *
 * @return void
 */
void top_core_init(void);

/**
 *  Subscribe TOP event
 *
 * @param task Task of the subscriber
 * @param id Event id
 * @return void
 */
void top_event_subscribe(task_t task, uint16 id);

/**
 *  Commit event to TOP
 *
 * @param id Event id
 * @return void
 */
void top_event_commit(uint16 id);

/* Prototype of filter callback function */
typedef bool (* top_event_filter_f)(uint16 id);

/**
 *  Add filter. The filters running sequence is the same as adding sequence.
 *
 * @param filter Filter callback function
 * @return void
 */
void top_add_filter(top_event_filter_f filter);

#endif /* __TOP_CORE_H__ */

