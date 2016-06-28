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

#ifndef FUN_BAG_H
#define FUN_BAG_H

#include "uvisor-lib/uvisor-lib.h"
#include <stdint.h>

/* This file contains abstract functions for oft-repeated patterns in our
 * example. */

/* Allocate a memory region of a given size, wait the specified length of time
 * (if non-zero), and then free the memory region. If any operations fail, call
 * uvisor_halt. */
UVISOR_EXTERN void alloc_wait_free(size_t size, uint32_t wait_ms);

#endif
