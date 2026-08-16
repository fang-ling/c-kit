/*===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CDebugging.h
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
 *===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*/

#ifndef CDebugging_h
#define CDebugging_h

#include "CBase.h"

C_ASSUME_NONNULL_BEGIN

#define CDebuggingHaltWithMessage(message) \
  do {                                     \
    __builtin_trap();                      \
  } while (0)

/**
 * Checks a necessary condition for making forward progress.
 *
 * - Parameters:
 *   - condition: The condition to test.
 *   - message: A string to print if `condition` is evaluated to `no`.
 */
#define CDebuggingPrecondition(condition, message) \
  do {                                             \
    if (!(condition)) {                            \
      CDebuggingHaltWithMessage((message));        \
    }                                              \
  } while (0)

C_ASSUME_NONNULL_END

#endif /* CDebugging_h */
