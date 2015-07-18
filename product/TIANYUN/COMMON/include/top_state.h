/**
*  @file      top_state.h
*  @brief    Top layer state machine
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/

#ifndef __TOP_STATE_H__
#define __TOP_STATE_H__

typedef enum
{
    TOP_STATE_OFF,
    TOP_STATE_ON,

    TOP_STATE_BUTT
} top_state_id_t;

/**
 *  Init function
 *
 * @return void
 */
void top_state_init(void);

/**
 *  Get current Top state
 *
 * @return top_state_id_t State
 */
top_state_id_t top_state_get(void);

#endif /* __TOP_STATE_H__ */

