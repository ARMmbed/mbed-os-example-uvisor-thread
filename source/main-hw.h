/*
 * Copyright (c) 2013-2016, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __UVISOR_HELLOWORLD_MAIN_HW_H__
#define __UVISOR_HELLOWORLD_MAIN_HW_H__

/* The vector containing the challenge is shared with the push-button ISR, so
 * that it can attempt to access it from an IRQ context. */

#define LED_ON  true
#define LED_OFF false

#define MAIN_LED LED_BLUE
#define HALT_LED LED_RED

#define MAIN_BTN SW2
#define MAIN_BTN_PUPD PullUp

#define MAIN_ACL(acl_list_name) \
    static const UvisorBoxAclItem acl_list_name[] = {     \
        {SIM,    sizeof(*SIM),    UVISOR_TACLDEF_PERIPH}, \
        {OSC,    sizeof(*OSC),    UVISOR_TACLDEF_PERIPH}, \
        {MCG,    sizeof(*MCG),    UVISOR_TACLDEF_PERIPH}, \
        {PORTA,  sizeof(*PORTA),  UVISOR_TACLDEF_PERIPH}, \
        {PORTB,  sizeof(*PORTB),  UVISOR_TACLDEF_PERIPH}, \
        {PORTC,  sizeof(*PORTC),  UVISOR_TACLDEF_PERIPH}, \
        {PORTD,  sizeof(*PORTD),  UVISOR_TACLDEF_PERIPH}, \
        {PORTE,  sizeof(*PORTE),  UVISOR_TACLDEF_PERIPH}, \
        {RTC,    sizeof(*RTC),    UVISOR_TACLDEF_PERIPH}, \
        {LPTMR0, sizeof(*LPTMR0), UVISOR_TACLDEF_PERIPH}, \
        {PIT,    sizeof(*PIT),    UVISOR_TACLDEF_PERIPH}, \
        {SMC,    sizeof(*SMC),    UVISOR_TACLDEF_PERIPH}, \
        {UART0,  sizeof(*UART0),  UVISOR_TACLDEF_PERIPH}, \
        {I2C0,   sizeof(*I2C0),   UVISOR_TACLDEF_PERIPH}, \
        {SPI0,   sizeof(*SPI0),   UVISOR_TACLDEF_PERIPH}, \
    }

#endif /* __UVISOR_HELLOWORLD_MAIN_HW_H__ */
