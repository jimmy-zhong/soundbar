/**
*  @file      drv_button.c
*  @brief    Button driver
*  @author    Victor.Xia
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/
#include <string.h>

#include "tym_memory.h"
#include "tym_debug.h"
#include "tym_assert.h"
#include "tym_message.h"
#include "config.h"
#include "io_pio.h"
#include "drv_button.h"

/* Debug switch */
#define DRV_BTN_DEBUG_ENABLE
#ifdef DRV_BTN_DEBUG_ENABLE
#define DRV_BTN_DEBUG(x) TYM_DEBUG(x)
#else
#define DRV_BTN_DEBUG(x)
#endif


#define     PIO_POWER               (uint8)(1<<0)
#define     PIO_BATTERY             (uint8)(1<<1)
#define     PIO_POLLING_TIMER       10
#define     PIO_POLLING_MSG         0xF0
#define     BUTTON_DETECT_MININUM   60      /*ms*/
#define     BUTTON_DETECT_SP        1500    /*ms*/
#define     BUTTON_DETECT_LP        3000    /*ms*/
#define     BUTTON_DETECT_VLP_START 5000    /*ms*/
#define     BUTTON_DETECT_VLP       8000    /*ms*/


typedef struct
{
    task_data_t task;
    drv_button_callback_t cb_func;      /*cb function handler*/
    uint16 counter_power;               /*pio detection ticker*/
    uint16 counter_battery;             /*pio detection ticker*/
    bool flag_power;                    /*High/Low flag of pio*/
    bool flag_battery;                  /*High/Low flag of pio*/
    uint8 pio_mark;                     /*Which pio is set to high*/
    btn_event_t curr_power_event;       /*power pio to btn event*/
    btn_event_t curr_battery_event;     /*battery pio to btn event*/
} drv_btn_inst_t;


static drv_btn_inst_t *drv_btn_inst = NULL;

static void drv_buttion_detect(void);
static void drv_button_message_handler(message_id_t id);
static btn_event_t drv_button_convert_event(uint16 time_duration);
static void drv_button_power_pio_detect(void);
static void drv_button_battery_pio_detect(void);

void drv_button_init(void)
{
    STATIC_MEM_ALLOC(drv_btn_inst);

    memset(drv_btn_inst, 0, sizeof(drv_btn_inst_t));

    io_pio_config(PIO_KEY_PWR_ON, PIO_INPUT);
    io_pio_config(PIO_KEY_BAT_IND, PIO_INPUT);

    drv_btn_inst->task.handler = drv_button_message_handler;
    drv_btn_inst->cb_func = NULL;
}

void drv_button_reg_callback(drv_button_callback_t handler)
{
    TYM_ASSERT(handler!= NULL);

    drv_btn_inst->cb_func = handler;

    tym_message_send_later(&drv_btn_inst->task, PIO_POLLING_MSG, PIO_POLLING_TIMER);
}

static void drv_buttion_detect(void)
{
    drv_button_power_pio_detect();

    drv_button_battery_pio_detect();
}


static void drv_button_power_pio_detect(void)
{
    if (PIO_LEVEL_LOW == io_pio_get_level(PIO_KEY_PWR_ON))
    {
        if (drv_btn_inst->flag_power)
        {
            drv_btn_inst->counter_power++;
        }
        else
        {
            drv_btn_inst->flag_power = TRUE;

            drv_btn_inst->counter_power = 0;
            drv_btn_inst->pio_mark |= PIO_POWER;
            drv_btn_inst->curr_power_event = NOT_PRESSED;

            DRV_BTN_DEBUG(("power pio start detection\r\n"));
        }
    }
    else
    {
        /*stop counting*/
        if (drv_btn_inst->flag_power)
        {
            DRV_BTN_DEBUG(("power pio stop detection\r\n"));

            drv_btn_inst->flag_power = FALSE;
            drv_btn_inst->curr_power_event = drv_button_convert_event(drv_btn_inst->counter_power*PIO_POLLING_TIMER);

            if (!drv_btn_inst->flag_battery)
            {
                /*Now we can deliver event to callback func*/
                if (drv_btn_inst->curr_power_event > NONE_EVENT)
                {
                    if (drv_btn_inst->curr_battery_event == NOT_PRESSED || drv_btn_inst->curr_power_event == drv_btn_inst->curr_battery_event)
                    {
                        DRV_BTN_DEBUG(("send to cb\r\n"));

                        drv_btn_inst->cb_func(drv_btn_inst->pio_mark, drv_btn_inst->curr_power_event);

                        drv_btn_inst->pio_mark = 0;

                        drv_btn_inst->curr_battery_event = NOT_PRESSED;
                    }
                }


            }
        }
    }
}


static void drv_button_battery_pio_detect(void)
{
    if (PIO_LEVEL_LOW == io_pio_get_level(PIO_KEY_BAT_IND))
    {
        if (drv_btn_inst->flag_battery)
        {
            drv_btn_inst->counter_battery++;
        }
        else
        {
            /*start counting*/
            drv_btn_inst->flag_battery = TRUE;

            drv_btn_inst->counter_battery = 0;
            drv_btn_inst->pio_mark |= PIO_BATTERY;
            drv_btn_inst->curr_battery_event = NOT_PRESSED;

            DRV_BTN_DEBUG(("battery pio start detection\r\n"));
        }
    }
    else
    {
        /*stop counting*/
        if (drv_btn_inst->flag_battery)
        {
            DRV_BTN_DEBUG(("battery pio stop detection\r\n"));

            drv_btn_inst->flag_battery = FALSE;
            drv_btn_inst->curr_battery_event = drv_button_convert_event(drv_btn_inst->counter_battery*PIO_POLLING_TIMER);

            if (!drv_btn_inst->flag_power)
            {
                /*Now we can deliver event to callback func*/
                if (drv_btn_inst->curr_battery_event > NONE_EVENT)
                {
                    if (drv_btn_inst->curr_power_event == drv_btn_inst->curr_battery_event || drv_btn_inst->curr_power_event == NOT_PRESSED)
                    {
                        DRV_BTN_DEBUG(("send to cb\r\n"));

                        drv_btn_inst->cb_func(drv_btn_inst->pio_mark, drv_btn_inst->curr_battery_event);

                        drv_btn_inst->pio_mark = 0;

                        drv_btn_inst->curr_power_event = NOT_PRESSED;
                    }
                }

            }
        }
    }
}

static btn_event_t drv_button_convert_event(uint16 time_duration)
{
    btn_event_t event = NONE_EVENT;

    if (time_duration > BUTTON_DETECT_MININUM &&
        time_duration < BUTTON_DETECT_SP)
    {
        event = SP;
    }
    else if (time_duration >= BUTTON_DETECT_SP &&
             time_duration <= BUTTON_DETECT_LP)
    {
        event = LP;
    }
    else if (time_duration >= BUTTON_DETECT_VLP_START &&
             time_duration < BUTTON_DETECT_VLP)
    {
        event = VLP;
    }
    else if (time_duration >= BUTTON_DETECT_VLP)
    {
        event = PRESS_HOLD;
    }

    return event;
}

static void drv_button_message_handler(message_id_t id)
{
    switch (id)
    {
        case PIO_POLLING_MSG:
            drv_buttion_detect();

            tym_message_send_later(&drv_btn_inst->task, PIO_POLLING_MSG, PIO_POLLING_TIMER);
            break;
        default:
            break;
    }
}

