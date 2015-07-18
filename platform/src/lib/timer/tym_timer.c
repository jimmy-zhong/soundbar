/**
*  @file     tym_timer.c
*  @brief    timer manager of TYM platform
*  @author    Jimmy.Z
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/
#include "stm8s_timer2.h"
#include "tym_timer.h"

#define DISABLE_TIMER_INT()         TIM2_ITConfig(TIM2_IT_UPDATE, DISABLE)
#define ENABLE_TIMER_INT()          TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE)
#define CLEAR_TIMER_INT_FLAG()      TIM2_ClearFlag(TIM2_FLAG_UPDATE)
#define TIMER_HANLDER()
#define CONVERT_MS_TO_TICKER(MS)    10000    /*calculate later*/


static TINY tym_timer_callback_t timer_callback = 0;


static void init_external_timer(unsigned char tick_ms);



/**
 *  timer init
 *
 * @param void
 * @return void
 */
 void tym_timer_init(void)
{}

/**
 *  timer register function for caller
 *
 * @param tickMs    how much time for each tick in MS
 * @param callBack  what caller want to do for each tick
 * @return void
 */
void tym_timer_register(unsigned char tick_ms, tym_timer_callback_t callback)
{
    timer_callback = callback;
    init_external_timer(tick_ms);
}

/**
 *  timer interrupt server function
 *
 * @param void
 * @return void
 */
irq_handler_t tym_timer_irq_handler(void)
{
    DISABLE_TIMER_INT();
    CLEAR_TIMER_INT_FLAG();
    if (timer_callback)
    {
        timer_callback();
    }
    ENABLE_TIMER_INT();
}

/**
 *  timer hardware setting init
 *
 * @param tickMs    tick in MS for hardware timer
 * @return void
 */
static void init_external_timer(unsigned char tick_ms)
{
    DISABLE_TIMER_INT();
    TIM2_TimeBaseInit(TIM2_PRESCALER_2, CONVERT_MS_TO_TICKER(tick_ms));
    TIM2_SetCounter(0x00);
    TIM2_ARRPreloadConfig(ENABLE);
    CLEAR_TIMER_INT_FLAG();
    TIM2_Cmd(ENABLE);
    ENABLE_TIMER_INT();
    _asm("rim");
}








