/*===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CAtomicity.h
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

#ifndef CAtomicity_h
#define CAtomicity_h

#include "CBase.h"
#include "CNumber.h"

C_ASSUME_NONNULL_BEGIN

CUnsignedInteger64 CAtomicityIncrease(CUnsignedInteger64* value);

CUnsignedInteger64 CAtomicityDecrease(CUnsignedInteger64* value);

void CAtomicityAcquireMemoryBarrier();

void CAtomicityReleaseMemoryBarrier();

C_ASSUME_NONNULL_END

#endif /* CAtomicity_h */
