/**
*  @file        io_uart.c
*  @brief    UART driver
*  @author    Bill Wu
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#include <stdio.h>
#include "stm8s_uart1.h"

#include "config.h"

#include "io_uart.h"

/**
 *  Init function
 *
 * @return void
 */
void io_uart_init(void)
{
    /* DeInit UART */
    UART1_DeInit();

    /* Init UART */
    UART1_Init(UART_BAUDRATE,
               UART1_WORDLENGTH_8D,
               UART1_STOPBITS_1,
               UART1_PARITY_NO,
               UART1_SYNCMODE_CLOCK_DISABLE,
               UART1_MODE_TX_ENABLE);

    /* Enable UART */
    UART1_Cmd(ENABLE);
}

/**
 *  Redefine putchar function
 *
 * @param c Data sent to UART
 * @return void
 */
char putchar (char c)
{
    /* put '\r' to hardware here */
    if (c == '\n')
    {
        /* Wait transmission is completed : otherwise the first data is not sent */
        while (!UART1_GetFlagStatus(UART1_FLAG_TC));

        /* Send '\r' */
        UART1_SendData8('\r');

        /* Wait transmission is completed */
        while (!UART1_GetFlagStatus(UART1_FLAG_TC));
    }

    /* Wait transmission is completed : otherwise the first data is not sent */
    while (!UART1_GetFlagStatus(UART1_FLAG_TC));

    /* Send Data */
    UART1_SendData8(c);

    /* Wait transmission is completed */
    while (!UART1_GetFlagStatus(UART1_FLAG_TC));
}

