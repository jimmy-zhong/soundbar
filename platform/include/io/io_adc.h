/**
*  @file        io_adc.h
*  @brief       ADC driver
*  @author    Bill Wu
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#ifndef __IO_ADC_H__
#define __IO_ADC_H__

/**
 *  Init function
 *
 * @return void
 */
void io_adc_init(void);

/**
 *  Get average adc value
 *
 * @return uint16 ADC value
 */
uint16 io_adc_get_value(void);

#endif  /* __IO_ADC_H__ */

