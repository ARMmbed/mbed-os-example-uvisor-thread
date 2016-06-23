/*
 * Copyright (c) 2016, ARM Limited, All Rights Reserved
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
#include "fun_bag.h"
#include "mbed.h"
#include "rtos.h"
#include <stdio.h>

/* Polynomial selected from Koopman's list of Maximal Length LFSR Feedback
 * Terms <https://users.ece.cmu.edu/~koopman/lfsr/16.txt>. */
static const uint16_t polynomial = 0x822B;

/* Given the state of an LFSR (with the specific LFSR specified by the feedback
 * polynomial), output the next state. */
static uint16_t lfsr_next(uint16_t state, uint16_t poly)
{
    /* This code block is adapted from:
     * https://en.wikipedia.org/wiki/Linear-feedback_shift_register#Galois_LFSRs
     * https://en.wikipedia.org/wiki/Wikipedia:Text_of_Creative_Commons_Attribution-ShareAlike_3.0_Unported_License
     */
    uint16_t lsb = state & 1;
    state >>= 1;
    state ^= (-lsb) & poly;
    return state;
}

/* Fill the memory region with a 16-bit pseudo-random number (PRN) sequence. */
static void prn_fill(void * mem, uint16_t seed, size_t len)
{
    size_t i;
    uint16_t state = seed;
    uint8_t * m = (uint8_t *) mem;

    for (i = 0; i < len; ++i) {
        /* Just use the bottom byte. */
        m[i] = state & 0xFF;
        state = lfsr_next(state, polynomial);
    }
}

/* Check that the memory region has the specified 16-bit PRN sequence. */
/* Return non-zero if the region matches. Return zero if the region doesn't
 * entirely match. */
static int prn_verify(const void * mem, uint16_t seed, size_t len)
{
    size_t i;
    uint16_t state = seed;
    uint8_t * m = (uint8_t *) mem;
    bool matches = true;

    /* Check all of the bytes, even if we find a match sooner. This tests that
     * we can read all of the memory (and that it hasn't been securely taken
     * over by another box. */
    for (i = 0; i < len; ++i) {
        if (m[i] != (state & 0xFF)) {
            matches = false;
        }
        state = lfsr_next(state, polynomial);
    }

    return matches;
}

UVISOR_EXTERN void alloc_fill_wait_verify_free(size_t size, uint16_t seed, uint32_t wait_ms)
{
    void * memory;

    /* Allocate a memory region. */
    memory = malloc(size);
    if (!memory) {
        printf("malloc failed: %s:%u\n", __FILE__, __LINE__);
        uvisor_error(USER_NOT_ALLOWED);
    }

    /* Fill the entire memory region with a with PRN sequence. */
    prn_fill(memory, seed, size);

    /* Optionally wait. */
    if (wait_ms > 0) {
        Thread::wait(wait_ms);
    }

    /* Verify the data we wrote is still there. */
    if (!prn_verify(memory, seed, size)) {
        printf("Verification failed: %s:%u\n", __FILE__, __LINE__);
        uvisor_error(USER_NOT_ALLOWED);
    }

    /* Free the memory region. */
    free(memory);
}

UVISOR_EXTERN void specific_alloc_fill_wait_verify_free(SecureAllocator allocator,
                                                        size_t size, uint16_t seed, uint32_t wait_ms)
{
    void * memory;

    /* Allocate a memory region using the provided allocator. */
    memory = secure_malloc(allocator, size);
    if (!memory) {
        printf("malloc failed: %s:%u\n", __FILE__, __LINE__);
        uvisor_error(USER_NOT_ALLOWED);
    }

    /* Fill the entire memory region with a with PRN sequence. */
    prn_fill(memory, seed, size);

    /* Optionally wait. */
    if (wait_ms > 0) {
        Thread::wait(wait_ms);
    }

    /* Verify the data we wrote is still there. */
    if (!prn_verify(memory, seed, size)) {
        printf("Verification failed: %s:%u\n", __FILE__, __LINE__);
        uvisor_error(USER_NOT_ALLOWED);
    }

    /* Free the memory region. */
    secure_free(allocator, memory);
}
