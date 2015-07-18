/**
*  @file      io_pio.h
*  @brief    STM8S PIO control and dectect
*  @author    xx
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#ifndef __IO_PIO_H__
#define __IO_PIO_H__

#include "tym_type.h"
#include "config.h"

typedef enum
{
    PIO_LEVEL_LOW,
    PIO_LEVEL_HIGH
} pio_level_t;

typedef enum
{
    PIO_INPUT,
    PIO_OUTPUT
}pio_mode_t;

/**
 *  PIO init function. Called at system initialization
 *
 * @return void
 */
void io_pio_init(void);

/**
 *  Set PIO mode. input or output.
 *
 * @param pio PIO to be set
 * @param mode   input or output
 * @return void
 */
void io_pio_config(pio_mapping_t pio, pio_mode_t mode);
/**
 *  Set PIO level. Only output pio can be set.
 *
 * @param pio PIO to be set
 * @param level PIO level
 * @return void
 */
void io_pio_set_level(pio_mapping_t pio, pio_level_t level);

/**
 *  Get PIO level. Only input pio can be read.
 *
 * @param pio PIO to be read
 * @return void
 */
pio_level_t io_pio_get_level(pio_mapping_t pio);

#endif /* __IO_PIO_H__ */

