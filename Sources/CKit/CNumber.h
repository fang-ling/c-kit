/*
 *  CNumber.h
 *  c-kit
 *
 *  Created by Fang Ling on 2026/4/25.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef CNumber_h
#define CNumber_h

#include <stdint.h>

#include "CBase.h"

C_ASSUME_NONNULL_BEGIN

/**
 * A 8-bit signed integer value type.
 */
typedef char CInteger8;

/**
 * A 8-bit unsigned integer value type.
 */
typedef uint8_t CUnsignedInteger8;

/**
 * A 32-bit signed integer value type.
 */
typedef int32_t CInteger32;

/**
 * A 32-bit unsigned integer value type.
 */
typedef uint32_t CUnsignedInteger32;

/**
 * A 64-bit unsigned integer value type.
 */
typedef uint64_t CUnsignedInteger64;

#define CNumberFindMinimum(lhs, rhs) ({ \
  __auto_type _lhs = (lhs);             \
  __auto_type _rhs = (rhs);             \
  _lhs < _rhs ? _lhs : _rhs;            \
})

C_ASSUME_NONNULL_END

#endif /* CNumber_h */
