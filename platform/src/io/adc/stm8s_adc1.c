/**
  ******************************************************************************
  * @file stm8s_adc1.c
  * @brief This file contains all the functions/macros for the ADC1 peripheral.
  * @author STMicroelectronics - MCD Application Team
  * @version V1.1.1
  * @date 06/05/2009
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  * @image html logo.bmp
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8s_adc1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
  * @addtogroup ADC1_Public_Functions
  * @{
  */

/**
  * @brief Deinitializes the ADC1 peripheral registers to their default reset
  * values.
  * @par Parameters:
  * None
  * @retval None
  */
void ADC1_DeInit(void)
{
    ADC1->CSR  = ADC1_CSR_RESET_VALUE;
    ADC1->CR1  = ADC1_CR1_RESET_VALUE;
    ADC1->CR2  = ADC1_CR2_RESET_VALUE;
    ADC1->CR3  = ADC1_CR3_RESET_VALUE;
    ADC1->TDRH = ADC1_TDRH_RESET_VALUE;
    ADC1->TDRL = ADC1_TDRL_RESET_VALUE;
    ADC1->HTRH = ADC1_HTRH_RESET_VALUE;
    ADC1->HTRL = ADC1_HTRL_RESET_VALUE;
    ADC1->LTRH = ADC1_LTRH_RESET_VALUE;
    ADC1->LTRL = ADC1_LTRL_RESET_VALUE;
    ADC1->AWCRH = ADC1_AWCRH_RESET_VALUE;
    ADC1->AWCRL = ADC1_AWCRL_RESET_VALUE;
}


/**
  * @brief Initializes the ADC1 peripheral according to the specified parameters
  * @param[in] ADC1_ConversionMode: specifies the conversion mode
  * can be one of the values of @ref ADC1_ConvMode_TypeDef.
  * @param[in] ADC1_Channel: specifies the channel to convert
  * can be one of the values of @ref ADC1_Channel_TypeDef.
  * @param[in] ADC1_PrescalerSelection: specifies the ADC1 prescaler
  * can be one of the values of @ref ADC1_PresSel_TypeDef.
  * @param[in] ADC1_ExtTrigger: specifies the external trigger
  * can be one of the values of @ref ADC1_ExtTrig_TypeDef.
  * @param[in] ADC1_ExtTriggerState: specifies the external trigger new state
  * can be one of the values of @ref FunctionalState.
  * @param[in] ADC1_Align: specifies the converted data alignement
  * can be one of the values of @ref ADC1_Align_TypeDef.
  * @param[in] ADC1_SchmittTriggerChannel: specifies the schmitt trigger channel
  * can be one of the values of @ref ADC1_SchmittTrigg_TypeDef.
  * @param[in] ADC1_SchmittTriggerState: specifies the schmitt trigger state
  * can be one of the values of @ref FunctionalState.
  * @retval None
  */
void ADC1_Init(ADC1_Channel_TypeDef ADC1_Channel, ADC1_PresSel_TypeDef ADC1_PrescalerSelection)
{
    /* Set the continuous coversion mode */
    ADC1->CR1 |= ADC1_CR1_CONT;

    /* Select the ADC1 channel */
    ADC1->CSR &= (u8)(~ADC1_CSR_CH);
    ADC1->CSR |= (u8)(ADC1_Channel);

    /* Select the prescaler division factor according to ADC1_PrescalerSelection values */
    ADC1->CR1 &= (u8)(~ADC1_CR1_SPSEL);
    ADC1->CR1 |= (u8)(ADC1_PrescalerSelection);

    /* Configure the data RIGHT alignment */
    ADC1->CR2 &= (u8)(~ADC1_CR2_ALIGN);
    ADC1->CR2 |= (u8)(ADC1_ALIGN_RIGHT);

    /* Disable external Tigger */
    ADC1->CR2 &= (u8)(~ADC1_CR2_EXTSEL);
    ADC1->CR2 &= (u8)(~ADC1_CR2_EXTTRIG);

    /* Disable Schmitt Trigger */
    ADC1->TDRL |= (u8)((u8)0x01 << (u8)ADC1_Channel);

    /* Enable the ADC1 peripheral */
    ADC1->CR1 |= ADC1_CR1_ADON;

}


/**
  * @brief Enables or Disables the ADC1 peripheral.
  * @param[in] NewState: specifies the peripheral enabled or disabled state.
  * @retval None
  */
void ADC1_Cmd(FunctionalState NewState)
{

    /* Check the parameters */
    assert_param(IS_FUNCTIONALSTATE_OK(NewState));

    if (NewState != DISABLE)
    {
        ADC1->CR1 |= ADC1_CR1_ADON;
    }
    else /* NewState == DISABLE */
    {
        ADC1->CR1 &= (u8)(~ADC1_CR1_ADON);
    }

}

/**
  * @brief Get one sample of measured signal.
  * @par Parameters:
  * None
  * @retval ConversionValue:  value of the measured signal.
  * @par Required preconditions:
  * ADC1 conversion finished.
  */
u16 ADC1_GetConversionValue(void)
{
    u16 temph = 0;
    u8 templ = 0;

    /* Read LSB first */
    templ = ADC1->DRL;
    /* Then read MSB */
    temph = ADC1->DRH;

    temph = (u16)(templ | (u16)(temph << (u8)8));

    return ((u16)temph);
}


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
