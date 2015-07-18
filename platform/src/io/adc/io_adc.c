/**
*  @file        io_adc.c
*  @brief       ADC driver
*
*   This is a filtering algorithm support the ADC up to 12 bit
*   Algorithm Description:
*   Ai: Input HW ADC value, 0~4095
*   Ao: Output ADC value
*   Aa: Average ADC value
*
*   Init:    Aa = Ai * 10
*   Update:  Aa = (Aa * 9  + Ai * 10) / 10
*   Output:  Ao = (Aa + 5) / 10
*
*
*  @author    Bill Wu
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#include "stm8s_adc1.h"


#include "tym_debug.h"
#include "tym_message.h"
#include "tym_memory.h"
#include "config.h"

#include "io_adc.h"

/* Debug switch */
#define ADC_DEBUG_ENABLEx
#ifdef ADC_DEBUG_ENABLE
#define ADC_DEBUG(x) TYM_DEBUG(x)
#else
#define ADC_DEBUG(x)
#endif


#define ADC_LOOP_INTERVAL   (100)

#define ADC_WEIGHT_OLD (9)
#define ADC_WEIGHT_NEW (1)
#define ADC_WEIGHT_TOTAL (ADC_WEIGHT_OLD + ADC_WEIGHT_NEW)
#define ADC_ROUND    (5)

typedef struct
{
    task_data_t task;
    uint16 adc_average;
} io_adc_inst_t;

typedef enum
{
    MESSAGE_ADC_UPDATE_LOOP = PRIVATE_EVENT_MESSAGE_BASE
} private_message_t;

static void message_handler(message_id_t id);
static void adc_hw_init(void);
static void update_adc_value(void);


static io_adc_inst_t *io_adc_inst = NULL;


/**
 *  Init function
 *
 * @return void
 */
void io_adc_init(void)
{
    adc_hw_init();

    STATIC_MEM_ALLOC(io_adc_inst);

    io_adc_inst->task.handler = message_handler;
    io_adc_inst->adc_average = ADC1_GetConversionValue() * ADC_WEIGHT_TOTAL;
	ADC_DEBUG(("FIR:[%d]\n", io_adc_inst->adc_average));

    tym_message_send(&io_adc_inst->task, MESSAGE_ADC_UPDATE_LOOP);
}

/**
 *  Get average adc value
 *
 * @return uint16 ADC value
 */
uint16 io_adc_get_value(void)
{
    uint16 adc_out = (io_adc_inst->adc_average + ADC_ROUND) / ADC_WEIGHT_TOTAL;

    return adc_out;
}

/**
 *  Loop message handler
 *
 * @param id Message ID
 * @return void
 */
static void message_handler(message_id_t id)
{
    update_adc_value();

    tym_message_send_later(&io_adc_inst->task, MESSAGE_ADC_UPDATE_LOOP, ADC_LOOP_INTERVAL);
}

/**
 *  ADC HW init
 *
 * @return void
 */
static void adc_hw_init(void)
{
    ADC1_DeInit();

    ADC1_Init(ADC_CHANNEL, ADC_PRESCALER);

    ADC1_Cmd(ENABLE);
}

/**
 *  Update ADC value
 *
 * @return void
 */
static void update_adc_value(void)
{
    uint16 adc_in = ADC1_GetConversionValue() * ADC_WEIGHT_TOTAL;

    io_adc_inst->adc_average = ((uint32)io_adc_inst->adc_average * ADC_WEIGHT_OLD
                              + (uint32)adc_in * ADC_WEIGHT_NEW)
                             / ADC_WEIGHT_TOTAL;

    ADC_DEBUG(("ADC Update Ai[%d] Aa[%d] \n", adc_in, io_adc_inst->adc_average));
}



