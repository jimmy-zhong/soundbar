/**
*  @file      tym_clock.c
*  @brief    Clock API
*  @author    Bill Wu
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#include "stm8s_clk.h"

#include "tym_clock.h"

/**
 *  Init function
 *
 * @return void
 */
void tym_clock_init(void)
{
    CLK_DeInit();
}

