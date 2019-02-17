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
 
/*
 * Driver layer to interface with ADF435x devices.  A bit-bang method is used
 * to write the registers of the device. 
 */

// Driver layer
#include "stm32f4xx.h"

// Local includes
#include "adf435x.h"
#include "hal.h"

/*
 * adf435x_init:  Initialise the ADF435x driver.
 */
void adf435x_init()
{
    // Setup GPIO
    gpio_set_output(ADF435X_CLK_PORT, ADF435X_CLK_PIN);
    gpio_set_output(ADF435X_DAT_PORT, ADF435X_DAT_PIN);
    gpio_set_output(ADF435X_LE_PORT, ADF435X_LE_PIN);
    gpio_set_output(ADF435X_CE_PORT, ADF435X_CE_PIN);
}

/*
 * adf435x_write_out:  Shift out 32-bit data on our write port.
 */
void adf435x_write_out(uint32_t data)
{
    
}

/*
 * adf435x_write_reg:  Write register data to register index to ADF435x.
 */
void adf435x_write_reg(uint32_t index, uint32_t reg)
{
    adf435x_write_out((index & _ADF435X_REG_DATA_MASK) | (index & _ADF435X_REG_CTRL_BITS_MASK));
}

/*
 * adf435x_sync:  Sync state to ADF435x device.
 */
void adf435x_sync()
{
    adf435x_write_reg(adf435x_state.r0, ADF435X_R0);
    adf435x_write_reg(adf435x_state.r1, ADF435X_R1);
    adf435x_write_reg(adf435x_state.r2, ADF435X_R2);
    adf435x_write_reg(adf435x_state.r3, ADF435X_R3);
    adf435x_write_reg(adf435x_state.r4, ADF435X_R4);
    adf435x_write_reg(adf435x_state.r5, ADF435X_R5);
}
