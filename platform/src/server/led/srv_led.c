/**
*  @file      srv_led.h
*  @brief    led blink mode control
*  @author    xx
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/
#include "tym_type.h"
#include "tym_memory.h"
#include "tym_message.h"

#include "drv_led.h"

#include "srv_led.h"

typedef void (*handler_t)(uint8);

typedef enum
{
    MSG_BLINKING_ON_START = 0,
    MSG_BLINKING_ON_DONE,
    MSG_BLINKING_OFF_START,
    MSG_BLINKING_OFF_DONE
}led_blinking_msg_t;

typedef enum
{
    LED_BLINKING_ON_STATE = 0,
    LED_BLINKING_OFF_STATE,
    LED_BLINKING_DONE
}led_blinking_state_t;

typedef struct
{
    led_t                       led;
    uint16                      ledOnTime;
    uint16                      ledOffTime;
    led_blinking_state_t        ledState;
    task_data_t                 ledTask;
    bool                        isRepeat;
}led_blinking_t;

typedef struct
{
    led_blinking_t                  led_blinking;
}srv_led_inst_t;

srv_led_inst_t  * srv_led_inst = NULL;

static void srv_led_handler(led_mode_t mode);
static void battery_led_handler(led_mode_t mode);
static void led_blinking_start(led_t led, uint16 onTime, uint16 offTime, bool isRepeat);
static void led_blinking_handler(uint8 event);


void srv_led_init(void)
{
    STATIC_MEM_ALLOC(srv_led_inst);
}
/**
 *  led server control function
 * para      mode    for controller to set led display mode
 * @return void
 */
void srv_led_control(led_mode_t mode)
{
   srv_led_handler(mode);
   led_blinking_start(LED1, 1000, 1000, TRUE);
}

/**
 *  handle led display mode function
 * para      mode    for controller to set led display mode
 * @return void
 */
static void srv_led_handler(led_mode_t mode)
{
    if (mode < BATT_LOW_LED)
    {
        battery_led_handler(mode);
    }

}

/**
 *  handle led battery status display mode function
 * para      mode    for controller to set led display mode
 * @return void
 */
static void battery_led_handler(led_mode_t mode)
{
    switch (mode)
    {
        case BATT_CHARGING_LED:
            
            break;

        case BATT_LEVEL1_LED:
        case BATT_LEVEL2_LED:
        case BATT_LEVEL3_LED:
        case BATT_LEVEL4_LED:
        case BATT_LEVEL5_LED:
            
            break;

        case BATT_LOW_LED:
            
            break;

        default:
            break;
    }
}

static void led_blinking_start(led_t led, uint16 onTime, uint16 offTime, bool isRepeat)
{
    srv_led_inst->led_blinking.ledOnTime = onTime;
    srv_led_inst->led_blinking.ledOffTime = offTime;
    srv_led_inst->led_blinking.isRepeat = isRepeat;
    srv_led_inst->led_blinking.led = led;
    srv_led_inst->led_blinking.ledState = LED_BLINKING_ON_STATE;
    srv_led_inst->led_blinking.ledTask.handler = led_blinking_handler;
    led_blinking_handler(MSG_BLINKING_ON_START);
}

static void led_blinking_handler(uint8 event)
{
    switch(srv_led_inst->led_blinking.ledState)
    {
         case LED_BLINKING_DONE:
            if (srv_led_inst->led_blinking.isRepeat)
            {
                led_blinking_start(srv_led_inst->led_blinking.led, 1000, 1000, TRUE);
            }
            break;

        case LED_BLINKING_ON_STATE:
            switch (event)
            {
                case MSG_BLINKING_ON_START:
                    drv_led_control(srv_led_inst->led_blinking.led, LED_ON);
                    drv_led_control(srv_led_inst->led_blinking.led + 1, LED_OFF);
                    tym_message_send_later(&srv_led_inst->led_blinking.ledTask, MSG_BLINKING_ON_DONE, 1000);
                    break;
                    
                case MSG_BLINKING_ON_DONE:
                    srv_led_inst->led_blinking.ledState = LED_BLINKING_OFF_STATE;
                    tym_message_send(&srv_led_inst->led_blinking.ledTask, MSG_BLINKING_OFF_START);
                    break;
                default:
                    break;
            }
            break;

        case LED_BLINKING_OFF_STATE:
            switch (event)
            {
                case MSG_BLINKING_OFF_START:
                    drv_led_control(srv_led_inst->led_blinking.led, LED_OFF);
                     drv_led_control(srv_led_inst->led_blinking.led + 1, LED_ON);
                    tym_message_send_later(&srv_led_inst->led_blinking.ledTask, MSG_BLINKING_OFF_DONE, 1000);
                    break;
                    
                case MSG_BLINKING_OFF_DONE:
                    srv_led_inst->led_blinking.ledState = LED_BLINKING_DONE;
                    tym_message_send(&srv_led_inst->led_blinking.ledTask, LED_BLINKING_DONE);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}