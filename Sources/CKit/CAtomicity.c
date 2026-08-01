/*===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CAtomicity.c
 *  c-kit
 *
 *  Created by Fang Ling on 2026/4/25.
 *
 *  This source file is part of the CKit open source project
 *
 *  Copyright (c) 2026 Fang Ling <fangling@fangl.ing>
 *  Licensed under Apache License v2.0
 *
 *  See LICENSE for license information
 *
 *  SPDX-License-Identifier: Apache-2.0
 *
 *===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*/

#include "CAtomicity.h"

C_ASSUME_NONNULL_BEGIN

CUnsignedInteger64 CAtomicityIncrease(CUnsignedInteger64* value) {
  return __atomic_add_fetch(value, 1, __ATOMIC_RELAXED);
}

CUnsignedInteger64 CAtomicityDecrease(CUnsignedInteger64* value) {
  return __atomic_sub_fetch(value, 1, __ATOMIC_RELAXED);
}

void CAtomicityAcquireMemoryBarrier() {
  __atomic_thread_fence(__ATOMIC_ACQUIRE);
}

void CAtomicityReleaseMemoryBarrier() {
  __atomic_thread_fence(__ATOMIC_RELEASE);
}

C_ASSUME_NONNULL_END
