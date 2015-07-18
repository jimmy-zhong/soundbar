/**
*  @file      fifo_message.h
*  @brief    FIFO Message Framework
*  @author    Bill Wu
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#include "tym_message.h"

/**
 *  Init function
 *
 * @return void
 */
void fifo_message_init(void);

/**
 *  Message in to FIFO
 *
 * @param task The task receive message
 * @param id Message ID
 * @return void
 */
void fifo_message_in(task_t task, message_id_t id);

/**
 *  Message out of FIFO
 *
 * @return void
 */
void fifo_message_out(void);

/**
 *  Check FIFO is empty
 *
 * @return bool TRUE: FIFO is empty; FALSE: FIFO is not empty
 */
bool fifo_message_is_empty(void);

