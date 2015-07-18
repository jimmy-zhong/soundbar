/**
*  @file     tym_memory.c
*  @brief    Memory manager of TYM platform
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/

#include <string.h>

#include "tym_assert.h"
#include "tym_debug.h"

#include "tym_type.h"
#include "config.h"

#include "tym_memory.h"


#define MEM_DEBUG_ENABLE

#ifdef MEM_DEBUG_ENABLE
#define MEM_DEBUG(x) TYM_DEBUG(x)
#else
#define MEM_DEBUG(x)
#endif

#define CONTENT_INIT_VALUE (0x0)

static NEAR uint8 static_memory[STATIC_MEMORY_SIZE];
static NEAR uint16 pool_idx = 0;

/**
 *  Init function.
 *
 * @return void
 */
void tym_memory_init(void)
{
    memset(static_memory, CONTENT_INIT_VALUE, STATIC_MEMORY_SIZE);

    pool_idx = 0;

    MEM_DEBUG(("Mem Init\n"));
}

/**
 *  Allocate static memory
 *
 * @param size Size of memory
 * @return void* Memory address, return NULL if allocate fail
 */
void * tym_static_alloc(uint16 size)
{
    uint8 * content;

    if((size > STATIC_MEMORY_SIZE) || ((size + pool_idx) > STATIC_MEMORY_SIZE))
    {
        TYM_ASSERT(FALSE);
        return NULL;
    }

    /* Get block content address */
    content = &(static_memory[pool_idx]);

    /* Move pool index */
    pool_idx += size;

    MEM_DEBUG(("Mem:A[%d] R[%d]\n", size, (STATIC_MEMORY_SIZE - pool_idx)));

    return content;
}


