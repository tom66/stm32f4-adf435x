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

#ifndef ___ADF435X_H___
#define ___ADF435X_H___

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdbool.h>

/*
 * ADF435x definitions
 */
#define _ADF435X_R0_INT_MASK            0xffff
#define _ADF435X_R0_INT_SHIFT           15

#define _ADF435X_R0_FRAC_MASK           0x0fff
#define _ADF435X_R0_FRAC_SHIFT          3

#define ADF435X_R1_PHASE_ADJ_OFF        (0 << 28)
#define ADF435X_R1_PHASE_ADJ_ON         (1 << 28)
#define ADF435X_R1_PRESCALER_4_5        (0 << 27)
#define ADF435X_R1_PRESCALER_8_9        (1 << 27)

#define _ADF435X_R1_PHASE_MASK          0x0fff
#define _ADF435X_R1_PHASE_SHIFT         15

#define _ADF435X_R1_MOD_MASK            0x0fff
#define _ADF435X_R1_MOD_SHIFT           3

#define _ADF435X_R2_LNLS_SHIFT          29
#define ADF435X_R2_LOW_NOISE_MODE       (0x00 << _ADF435X_R2_LNLS_SHIFT)
#define ADF435X_R2_LOW_SPUR_MODE        (0x03 << _ADF435X_R2_LNLS_SHIFT)

#define _ADF435X_R2_MUX_SHIFT           26
#define ADF435X_R2_MUX_3STATE           (0x00 << _ADF435X_R2_MUX_SHIFT)
#define ADF435X_R2_MUX_DVDD             (0x01 << _ADF435X_R2_MUX_SHIFT)
#define ADF435X_R2_MUX_DGND             (0x02 << _ADF435X_R2_MUX_SHIFT)
#define ADF435X_R2_MUX_RCTR             (0x03 << _ADF435X_R2_MUX_SHIFT)
#define ADF435X_R2_MUX_NDIV             (0x04 << _ADF435X_R2_MUX_SHIFT)
#define ADF435X_R2_MUX_ALOCK            (0x05 << _ADF435X_R2_MUX_SHIFT)
#define ADF435X_R2_MUX_DLOCK            (0x06 << _ADF435X_R2_MUX_SHIFT)

#define ADF435X_R2_REF_DOUBLER          (1 << 25)
#define ADF435X_R2_REF_DIVIDE_BY_2      (1 << 24)

#define _ADF435X_R2_RCOUNTER_MASK       0x03ff
#define _ADF435X_R2_RCOUNTER_SHIFT      14

#define ADF435X_R2_DOUBLE_BUFF          (1 << 13)

#define _ADF435X_R2_CHARGEPUMP_MASK     0x000f
#define _ADF435X_R2_CHARGEPUMP_SHIFT    9

#define ADF435X_R2_LDF_FRAC_N           (0 << 8)
#define ADF435X_R2_LDF_INT_N            (1 << 8)
#define ADF435X_R2_LDP_10NS             (0 << 7)
#define ADF435X_R2_LDP_6NS              (1 << 7)
#define ADF435X_R2_PD_POL_NEG           (0 << 6)
#define ADF435X_R2_PD_POL_POS           (1 << 6)
#define ADF435X_R2_POWERDOWN_DIS        (0 << 5)
#define ADF435X_R2_POWERDOWN_ENA        (1 << 5)
#define ADF435X_R2_CP_3STATE_DIS        (0 << 4)
#define ADF435X_R2_CP_3STATE_ENA        (1 << 4)
#define ADF435X_R2_CP_CTR_RESET_ENA     (0 << 3)
#define ADF435X_R2_CP_CTR_RESET_DIS     (1 << 3)

#define ADF435X_R3_BAND_SEL_LOW         (0 << 23)
#define ADF435X_R3_BAND_SEL_HIGH        (1 << 23)
#define ADF435X_R3_ANTIBACKLASH_6NS     (0 << 22)
#define ADF435X_R3_ANTIBACKLASH_3NS     (1 << 22)
#define ADF435X_R3_CHARGE_CANCEL_DIS    (0 << 21)
#define ADF435X_R3_CHARGE_CANCEL_ENA    (1 << 21)
#define ADF435X_R3_CYCLE_SLIP_RED_DIS   (0 << 18)
#define ADF435X_R3_CYCLE_SLIP_RED_ENA   (1 << 18)

#define _ADF435X_R3_CLOCK_DIV_SHIFT     15
#define ADF435X_R3_CLOCK_DIV_OFF        (0x00 << _ADF435X_R3_CLOCK_DIV_SHIFT)
#define ADF435X_R3_CLOCK_DIV_FASTLOCK   (0x01 << _ADF435X_R3_CLOCK_DIV_SHIFT)
#define ADF435X_R3_CLOCK_DIV_RESYNC     (0x02 << _ADF435X_R3_CLOCK_DIV_SHIFT)

#define _ADF435X_R3_CLOCK_DIV_VAL_MASK  0x0fff
#define _ADF435X_R3_CLOCK_DIV_VAL_SHIFT 3

#define ADF435X_R4_FBACK_DIVIDED        (0 << 23)
#define ADF435X_R4_FBACK_FUNDAMENTAL    (1 << 23)

#define _ADF435X_R4_RFDIV_SEL_SHIFT     20
#define ADF435X_R4_RFDIV_SEL_1          (0x00 << _ADF435X_R4_RFDIV_SEL_SHIFT)
#define ADF435X_R4_RFDIV_SEL_2          (0x01 << _ADF435X_R4_RFDIV_SEL_SHIFT)
#define ADF435X_R4_RFDIV_SEL_4          (0x02 << _ADF435X_R4_RFDIV_SEL_SHIFT)
#define ADF435X_R4_RFDIV_SEL_8          (0x03 << _ADF435X_R4_RFDIV_SEL_SHIFT)
#define ADF435X_R4_RFDIV_SEL_16         (0x04 << _ADF435X_R4_RFDIV_SEL_SHIFT)
#define ADF435X_R4_RFDIV_SEL_32         (0x05 << _ADF435X_R4_RFDIV_SEL_SHIFT)
#define ADF435X_R4_RFDIV_SEL_64         (0x06 << _ADF435X_R4_RFDIV_SEL_SHIFT)

#define _ADF435X_R4_BSEL_CLK_DIV_MASK   0x00ff
#define _ADF435X_R4_BSEL_CLK_DIV_SHIFT  3

#define ADF435X_R4_VCO_POWERED_UP       (0 << 11)
#define ADF435X_R4_VCO_POWERED_DOWN     (1 << 11)
#define ADF435X_R4_MUTE_DISABLED        (0 << 10)
#define ADF435X_R4_MUTE_ENABLED         (1 << 10)
#define ADF435X_R4_AUX_DIV_OUT          (0 << 9)
#define ADF435X_R4_AUX_FUNDAMENTAL      (1 << 9)
#define ADF435X_R4_AUX_OUT_ENABLED      (0 << 8)
#define ADF435X_R4_AUX_OUT_DISABLED     (1 << 8)

#define _ADF435X_R4_AUX_POWER_SHIFT     6
#define ADF435X_R4_AUX_POWER_NEG_4DBM   (0x00 << _ADF435X_R4_AUX_POWER_SHIFT)
#define ADF435X_R4_AUX_POWER_NEG_1DBM   (0x01 << _ADF435X_R4_AUX_POWER_SHIFT)
#define ADF435X_R4_AUX_POWER_POS_2DBM   (0x02 << _ADF435X_R4_AUX_POWER_SHIFT)
#define ADF435X_R4_AUX_POWER_POS_5DBM   (0x03 << _ADF435X_R4_AUX_POWER_SHIFT)

#define ADF435X_R4_RF_OUT_ENABLED       (0 << 5)
#define ADF435X_R4_RF_OUT_DISABLED      (1 << 5)

#define _ADF435X_R4_RF_POWER_SHIFT      3
#define ADF435X_R4_RF_POWER_NEG_4DBM    (0x00 << _ADF435X_R4_RF_POWER_SHIFT)
#define ADF435X_R4_RF_POWER_NEG_1DBM    (0x01 << _ADF435X_R4_RF_POWER_SHIFT)
#define ADF435X_R4_RF_POWER_POS_2DBM    (0x02 << _ADF435X_R4_RF_POWER_SHIFT)
#define ADF435X_R4_RF_POWER_POS_5DBM    (0x03 << _ADF435X_R4_RF_POWER_SHIFT)

#define _ADF435X_R5_LD_PIN_MODE_SHIFT   22
#define ADF435X_R5_LD_PIN_LOW1          (0x00 << _ADF435X_R5_LD_PIN_MODE_SHIFT)
#define ADF435X_R5_LD_PIN_DIGITAL       (0x01 << _ADF435X_R5_LD_PIN_MODE_SHIFT)
#define ADF435X_R5_LD_PIN_LOW2          (0x02 << _ADF435X_R5_LD_PIN_MODE_SHIFT)
#define ADF435X_R5_LD_PIN_HIGH          (0x03 << _ADF435X_R5_LD_PIN_MODE_SHIFT)

#define ADF435X_R0                      0
#define ADF435X_R1                      1
#define ADF435X_R2                      2
#define ADF435X_R3                      3
#define ADF435X_R4                      4
#define ADF435X_R5                      5
 
#define _ADF435X_REG_DATA_MASK          0xfffffff8
#define _ADF435X_REG_CTRL_BITS_MASK     0x00000007

/*
 * Struct that represents state of ADF435x.
 */
struct adf435x_state_t {
    // Six 29-bit registers.  Control bits are always unused.
    uint32_t r0, r1, r2, r3, r4, r5;
};

struct adf435x_state_t adf435x_state;

/*
 * Port/pin combinations for ADF435X on STM32F4-Discovery board.
 *
 * CLK      Serial clock            PD0  
 * DAT      Serial data             PD1
 * LE       Latch signal            PD2
 * CE       Chip enable             PD3
 * LD       Lock detect (unused)
 * MUX      Mux input (unused)
 */
#define ADF435X_CLK_PORT            GPIOD
#define ADF435X_CLK_PIN             0
#define ADF435X_DAT_PORT            GPIOD
#define ADF435X_DAT_PIN             1
#define ADF435X_LE_PORT             GPIOD
#define ADF435X_LE_PIN              2
#define ADF435X_CE_PORT             GPIOD
#define ADF435X_CE_PIN              3

void adf435x_init(void);
void adf435x_write_out(uint32_t data);
void adf435x_write_reg(uint32_t index, uint32_t reg);
void adf435x_sync(void);

#endif // ___ADF435X_H___
