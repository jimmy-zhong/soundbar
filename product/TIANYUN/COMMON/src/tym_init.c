/**
*  @file      tym_init.c
*  @brief    TYM platform init
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/
#include "io_uart.h"

/* lib */
#include "tym_memory.h"
#include "tym_event.h"
#include "tym_clock.h"
#include "tym_timer.h"

/* framework */
#include "tym_message.h"

/* driver */
#include "drv_power.h"
#include "drv_battery.h"
#include "drv_button.h"
#include "drv_led.h"
#include "srv_led.h"


/* io */
#include "io_pio.h"
#include "io_uart.h"
#include "io_adc.h"


/* top */
#include "top_core.h"
#include "top_phase.h"
#include "top_state.h"
#include "top_event.h"

/* controller */
#include "ctrl_power.h"
#include "ctrl_battery.h"
#include "ctrl_button.h"


#include "tym_init.h"

static void lib_init(void);
static void framework_init(void);
static void io_init(void);
static void driver_init(void);
static void controller_init(void);
static void top_init(void);
static void kickoff(void);

/**
 *  TYM platfrom init function
 *
 * @return void
 */
void tym_init(void)
{
#ifndef RELEASE
    io_uart_init(); /* Init uart for output debug info  */
#endif
    lib_init();

    framework_init();

    io_init();

    driver_init();

    top_init();

    controller_init();
    srv_led_init();

    kickoff();
}

/**
 *  Init lib
 *
 * @return void
 */
static void lib_init(void)
{
    tym_memory_init();

    tym_event_init();

    tym_clock_init();

    tym_timer_init();
}

/**
 *  Init framework
 *
 * @return void
 */
static void framework_init(void)
{
    tym_message_init();
}

/**
 *  Init IO layer
 *
 * @return void
 */
static void io_init(void)
{
    io_pio_init();

    io_adc_init();
}

/**
 *  Init driver layer
 *
 * @return void
 */
static void driver_init(void)
{
    drv_power_init();

    drv_battery_init();

    drv_button_init();

    drv_led_init();
}

/**
 *  Init controllers
 *
 * @return void
 */
static void controller_init(void)
{
    ctrl_power_init();

    ctrl_battery_init();

    ctrl_btn_init();
}

/**
 *  Top layer init function
 *
 * @return void
 */
void top_init(void)
{
    top_core_init();

    top_phase_init();

    top_state_init();
}

/**
 *  After finish system init, commit a kickoff event
 *
 * @return void
 */
static void kickoff(void)
{
    top_event_commit(TOP_EVENT_KICKOFF);
}

