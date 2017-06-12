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

#if defined(TARGET_K64F)

#define MAIN_LED           LED1
#define SECURE_LED         LED2
#define LED_ON             false
#define LED_OFF            true
#define SECURE_SWITCH      SW2
#define SECURE_SWITCH_PULL PullUp

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

#elif defined(TARGET_EFM32GG_STK3700)

#define MAIN_LED           LED1
#define SECURE_LED         LED2
#define LED_ON             true
#define LED_OFF            false
#define SECURE_SWITCH      SW0
#define SECURE_SWITCH_PULL PullUp

#define MAIN_ACL(acl_list_name) \
    static const UvisorBoxAclItem acl_list_name[] = {     \
        {CMU,                 sizeof(*CMU),    UVISOR_TACLDEF_PERIPH}, \
        {MSC,                 sizeof(*MSC),    UVISOR_TACLDEF_PERIPH}, \
        {GPIO,                sizeof(*GPIO),   UVISOR_TACLDEF_PERIPH}, \
        {TIMER0,              sizeof(*TIMER0), UVISOR_TACLDEF_PERIPH}, \
        {UART0,               sizeof(*UART0),  UVISOR_TACLDEF_PERIPH}, \
        {(void *) 0x0FE08000, 0x1000,          UVISOR_TACLDEF_PERIPH}, \
        {(void *) 0x42000000, 0x2000000,       UVISOR_TACLDEF_PERIPH}, \
    }

#elif defined(TARGET_DISCO_F429ZI)

#define MAIN_LED           LED1
#define SECURE_LED         LED2
#define LED_ON             true
#define LED_OFF            false
#define SECURE_SWITCH      USER_BUTTON
#define SECURE_SWITCH_PULL PullDown

#define MAIN_ACL(acl_list_name) \
    static const UvisorBoxAclItem acl_list_name[] = {     \
        {GPIOA,               sizeof(*GPIOA),  UVISOR_TACLDEF_PERIPH}, \
        {GPIOB,               sizeof(*GPIOB),  UVISOR_TACLDEF_PERIPH}, \
        {GPIOC,               sizeof(*GPIOC),  UVISOR_TACLDEF_PERIPH}, \
        {GPIOD,               sizeof(*GPIOD),  UVISOR_TACLDEF_PERIPH}, \
        {GPIOE,               sizeof(*GPIOE),  UVISOR_TACLDEF_PERIPH}, \
        {RTC,                 sizeof(*RTC),    UVISOR_TACLDEF_PERIPH}, \
        {TIM5,                sizeof(*TIM5),   UVISOR_TACLDEF_PERIPH}, \
        {USART1,              sizeof(*USART1), UVISOR_TACLDEF_PERIPH}, \
        {I2C1,                sizeof(*I2C1),   UVISOR_TACLDEF_PERIPH}, \
        {SPI1,                sizeof(*SPI1),   UVISOR_TACLDEF_PERIPH}, \
        {RCC,                 sizeof(*RCC),    UVISOR_TACLDEF_PERIPH}, \
        {FLASH,               sizeof(*FLASH),  UVISOR_TACLDEF_PERIPH}, \
        {PWR,                 sizeof(*PWR),    UVISOR_TACLDEF_PERIPH}, \
        {EXTI,                sizeof(*EXTI),   UVISOR_TACLDEF_PERIPH}, \
        {GPIOG,               sizeof(*GPIOG),  UVISOR_TACLDEF_PERIPH}, \
        {SYSCFG,              sizeof(*SYSCFG), UVISOR_TACLDEF_PERIPH}, \
        {(void *) 0x42000000, 0x01000000,      UVISOR_TACLDEF_PERIPH}, \
    }

#else /* Target-specific settings */

#error "Unsupported target. Checkout the README.md file for the list of supported targets for this app."

#endif /* Target-specific settings */

#endif /* __UVISOR_HELLOWORLD_MAIN_HW_H__ */
