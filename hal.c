/**
 * This file is part of YAOS and licenced under the MIT licence.
 * Copyright (c) 2019 Thomas Oldbury
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "hal.h"

#include <stdio.h>
#include <stdarg.h>

/*
 * Layer to interface with STM32F4 processor.  This layer is likely to be replaced 
 * when we move to the STM32F0/F1 processor for the final design.
 */

char vsnprint_buffer[1024];
    
/*
 * hal_init:  Initialise key hardware resources
 */
void hal_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef UART_InitStructure;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    RCC_APB1PeriphClockCmd(UART_DEBUG_PERIPH_RCC, ENABLE);
    
    SystemInit();
    SystemCoreClockUpdate();
    
    // Set sys clock output on PC9 per STM32 example
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO2Div_4);
    
    // Set diagnostic LED on
    GPIO_InitStructure.GPIO_Pin = LED_1_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(LED_1_PORT, &GPIO_InitStructure);
    GPIO_WriteBit(LED_1_PORT, LED_1_PIN, 1);
    
    // Initialise our debug UART port
    GPIO_InitStructure.GPIO_Pin = UART_DEBUG_TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(UART_DEBUG_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = UART_DEBUG_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(UART_DEBUG_PORT, &GPIO_InitStructure);
    
    GPIO_PinAFConfig(UART_DEBUG_PORT, UART_DEBUG_TX_PIN_SRC, GPIO_AF_USART2);
    GPIO_PinAFConfig(UART_DEBUG_PORT, UART_DEBUG_RX_PIN_SRC, GPIO_AF_USART2);
    
    UART_InitStructure.USART_BaudRate = 115200;
    UART_InitStructure.USART_WordLength = USART_WordLength_8b;
    UART_InitStructure.USART_Parity = USART_Parity_No;
    UART_InitStructure.USART_StopBits = USART_StopBits_1;
    UART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    
    USART_Init(UART_DEBUG_PERIPH, &UART_InitStructure);
    USART_Cmd(UART_DEBUG_PERIPH, ENABLE);
    
    uart_putsraw("\r\n\r\n");
    uart_putsraw("STM32-ADF435x Test Application\r\n");
    uart_putsraw("hal: ready\r\n");
}

/*
 * uart_putsraw:  Put debug string without any formatting.
 *
 * @param   string      String to print
 */
void uart_putsraw(char *str)
{
    do {
        while(USART_GetFlagStatus(UART_DEBUG_PERIPH, USART_FLAG_TXE) == RESET);
        USART_SendData(UART_DEBUG_PERIPH, *str);
    } while(*str++) ;
}

/*
 * uart_printf:  Put debug string with printf formatting.
 *
 * @note    buffer size limit enforced by vsnprintf
 *
 * @param   fmt         Format string
 * @param   ...         Zero or more arguments for format string
 */
void uart_printf(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    
    vsnprintf(vsnprint_buffer, sizeof(vsnprint_buffer), fmt, args);
    uart_putsraw(vsnprint_buffer);
    
    va_end(args);
}

/*
 * gpio_set_output:  Set a GPIO port/pin combination to push-pull output.
 *
 * @param   gpio_port   GPIO_TypeDef pointer to the port base
 * @param   gpio_pin    GPIO_Pin_xx or bit-shifted representation of pin number
 */
void gpio_set_output(GPIO_TypeDef *gpio_port, uint32_t gpio_pin)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin = gpio_pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    GPIO_Init(gpio_port, &GPIO_InitStructure);
}

/*
 * gpio_set_input:  Set a GPIO port/pin combination to an unpulled input.
 *
 * @param   gpio_port   GPIO_TypeDef pointer to the port base
 * @param   gpio_pin    GPIO_Pin_xx or bit-shifted representation of pin number
 */
void gpio_set_input(GPIO_TypeDef *gpio_port, uint32_t gpio_pin)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin = gpio_pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    
    GPIO_Init(gpio_port, &GPIO_InitStructure);
}
