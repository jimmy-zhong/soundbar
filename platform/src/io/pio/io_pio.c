/**
*  @file      io_pio.c
*  @brief    STM8S PIO control and dectect
*  @author    xx
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/
#include "tym_assert.h"
#include "stm8s_gpio.h"
#include "io_pio.h"

typedef enum
{
    GROUP_A = 0x0A,
    GROUP_B = 0x0B,
    GROUP_C = 0x0C,
    GROUP_D = 0x0D
}pio_group_t;

typedef struct
{
    uint8   pin_number  : 4;
    uint8   group       : 4;
}pio_t;

/**
 *  PIO init function. Called at system initialization
 *
 * @return void
 */
void io_pio_init(void)
{
    
}

/**
 *  Set PIO mode. input or output.
 *
 * @param pio PIO to be set
 * @param mode   input or output
 * @return void
 */
void io_pio_config(pio_mapping_t pio, pio_mode_t mode)
{
    GPIO_TypeDef * pio_group;

    switch((uint8)((pio_t *)&pio)->group)
    {
        case GROUP_A:
            pio_group = GPIOA;
            break;

        case GROUP_B:
            pio_group = GPIOB;
            break;

        case GROUP_C:
            pio_group = GPIOC;
            break;

        case GROUP_D:
            pio_group = GPIOD;
            break;

        default:
            TYM_ASSERT(FALSE);
            break;
    }
    GPIO_Init(pio_group, (1 << (((pio_t *)&pio)->pin_number)), (mode == PIO_INPUT)?GPIO_MODE_IN_PU_NO_IT:GPIO_MODE_OUT_PP_LOW_FAST);
}
/**
 *  Set PIO level. Only output pio can be set.
 *
 * @param pio PIO to be set
 * @param level PIO level
 * @return void
 */
void io_pio_set_level(pio_mapping_t pio, pio_level_t level)
{
    GPIO_TypeDef * pio_group;

    switch((uint8)((pio_t *)&pio)->group)
    {
        case GROUP_A:
            pio_group = GPIOA;
            break;

        case GROUP_B:
            pio_group = GPIOB;
            break;

        case GROUP_C:
            pio_group = GPIOC;
            break;

        case GROUP_D:
            pio_group = GPIOD;
            break;

        default:
            TYM_ASSERT(FALSE);
            break;
    }

    if(level == PIO_LEVEL_LOW)
    {
        GPIO_WriteLow(pio_group, (1 << (((pio_t *)&pio)->pin_number)));
    }
    else
    {
        GPIO_WriteHigh(pio_group, (1 << (((pio_t *)&pio)->pin_number)));
    }
}

/**
 *  Get PIO level. Only input pio can be read.
 *
 * @param pio PIO to be read
 * @return void
 */
pio_level_t io_pio_get_level(pio_mapping_t pio)
{
    bool pinStatus = FALSE;
    GPIO_TypeDef * pio_group;

    switch((uint8)((pio_t *)&pio)->group)
    {
        case GROUP_A:
            pio_group = GPIOA;
            break;

        case GROUP_B:
            pio_group = GPIOB;
            break;

        case GROUP_C:
            pio_group = GPIOC;
            break;

        case GROUP_D:
            pio_group = GPIOD;
            break;

        default:
            TYM_ASSERT(FALSE);
            break;
    }

    pinStatus = GPIO_ReadInputPin(pio_group, (1 << (((pio_t *)&pio)->pin_number)));

    return ((pio_level_t)pinStatus);
}





