/**
*  @file      tym_memory.h
*  @brief    Memory manager of TYM platform
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/

#ifndef __TYM_MEMORY_H__
#define __TYM_MEMORY_H__

#include "tym_type.h"

/**
 *  Init function.
 *
 * @return void
 */
void tym_memory_init(void);

/**
 *  Allocate static memory
 *
 * @param size Size of memory
 * @return void* Memory address, return NULL if allocate fail
 */
void * tym_static_alloc(uint16 size);

/* Allocate memory for an instance */
#define STATIC_MEM_ALLOC(inst) inst = (inst##_t *) tym_static_alloc(sizeof(inst##_t));


#endif /* __TYM_MEMORY_H__ */

