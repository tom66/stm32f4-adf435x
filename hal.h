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

#ifndef ___HAL_H___
#define ___HAL_H___

#include "stm32f4xx.h"

#include <stdint.h>

#define UART_DEBUG_PORT                 GPIOA
#define UART_DEBUG_TX_PIN               GPIO_Pin_2
#define UART_DEBUG_RX_PIN               GPIO_Pin_3
#define UART_DEBUG_TX_PIN_SRC           GPIO_PinSource2
#define UART_DEBUG_RX_PIN_SRC           GPIO_PinSource3
#define UART_DEBUG_PERIPH               USART2
#define UART_DEBUG_PERIPH_RCC           RCC_APB1Periph_USART2

#define LED_0_PIN                       GPIO_Pin_12
#define LED_1_PIN                       GPIO_Pin_13
#define LED_2_PIN                       GPIO_Pin_14
#define LED_3_PIN                       GPIO_Pin_15

#define LED_0_PORT                      GPIOD
#define LED_1_PORT                      GPIOD
#define LED_2_PORT                      GPIOD
#define LED_3_PORT                      GPIOD

#define GPIO_FAST_SET_PIN(port, pin)    ((port)->BSRRL = (1 << pin)) ;
#define GPIO_FAST_CLR_PIN(port, pin)    ((port)->BSRRH = (1 << pin)) ;

void hal_init();
void uart_putsraw(char *str);
void gpio_set_output(GPIO_TypeDef *gpio_port, uint32_t gpio_pin);
void gpio_set_input(GPIO_TypeDef *gpio_port, uint32_t gpio_pin);

#endif // ___HAL_H___