/**
*  @file     tym_timer.h
*  @brief    timer manager of TYM platform
*  @author    Jimmy.Z
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/
#ifndef __TYM_TIMER_H__
#define __TYM_TIMER_H__

typedef void  (*tym_timer_callback_t)(void);
typedef @far @interrupt void    irq_handler_t;


/**
 *  timer init
 *
 * @param void
 * @return void
 */
 void tym_timer_init(void);

/**
 *  timer register function for caller
 *
 * @param tickMs    how much time for each tick in MS
 * @param callBack  what caller want to do for each tick
 * @return void
 */
void tym_timer_register(unsigned char tick_ms, tym_timer_callback_t callback);

/**
 *  timer interrupt server function
 *
 * @param void
 * @return void
 */
irq_handler_t tym_timer_irq_handler(void);

#endif