/**
*  @file      fifo_message.c
*  @brief    FIFO Message Framework
*  @author    Bill Wu
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/
#include <string.h>

#include "tym_assert.h"

#include "config.h"

#include "fifo_message.h"


/* FIFO node define */
typedef struct
{
    task_t task;
    message_id_t id;
} fifo_node_t;

static TINY fifo_node_t fifo[FIFO_MAX_NUM]; /* FIFO */
static TINY uint8 head; /* HEAD of FIFO */
static TINY uint8 tail; /* TAIL of FIFO */
static TINY uint8 num;  /* Node number of FIFO */

/* Ring forward */
#define MOVE_FORWARD(a) (a = ((a + 1) == FIFO_MAX_NUM) ? 0 : (a + 1) )

/**
 *  Init function
 *
 * @return void
 */
void fifo_message_init(void)
{
    /* Init FIFO */
    memset(fifo, 0, sizeof(fifo));
    head = 0;
    tail = 0;
    num = 0;
}

/**
 *  Put message into FIFO
 *
 * @param task The task receive message
 * @param id Message ID
 * @return void
 */
void fifo_message_in(task_t task, message_id_t id)
{
    /* If FIFO is not full */
    if(num < FIFO_MAX_NUM)
    {
        /* Store info in FIFO */
        fifo[tail].task = task;
        fifo[tail].id = id;

        /* Move TAIL node forward */
        MOVE_FORWARD(tail);

        /* Node number +1 */
        num++;
    }
    else
    {
        /* FIFO is not long enough, need to increase FIFO_MAX_NUM */
        TYM_ASSERT(FALSE);
    }
}

/**
 *  Move message out of FIFO and call the handler callback
 *
 * @return void
 */
void fifo_message_out(void)
{
    uint8 node_handle;

    /* If FIFO is not empty */
    if(num > 0)
    {
        /* Record the node to handle its callback function */
        node_handle = head;

        /* Node number -1 */
        num--;

        /* Move HEAD node forward */
        MOVE_FORWARD(head);

        /* Call the callback function of node to be handled */
        (*fifo[node_handle].task->handler)(fifo[node_handle].id);
    }
}

/**
 *  Check FIFO is empty
 *
 * @return bool TRUE: FIFO is empty; FALSE: FIFO is not empty
 */
bool fifo_message_is_empty(void)
{
    return (num == 0);
}

