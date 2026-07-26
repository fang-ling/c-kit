/*
 *  CNumber.h
 *  c-kit
 *
 *  Created by Fang Ling on 2026/4/25.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and limitations under the License.
 */

#ifndef CNumber_h
#define CNumber_h

#include <limits.h>
#include <math.h>
#include <stdint.h>

#include "CBase.h"

C_ASSUME_NONNULL_BEGIN

#define yes 1

#define no 0

/**
 * A value type whose instances are either `yes` or `no`.
 */
typedef _Bool CBoolean;

/**
 * A 8-bit signed integer value type.
 */
typedef char CInteger8;

/**
 * A 8-bit unsigned integer value type.
 */
typedef uint8_t CUnsignedInteger8;

/**
 * A 16-bit signed integer value type.
 */
typedef int16_t CInteger16;

/**
 * A 16-bit unsigned integer value type.
 */
typedef uint16_t CUnsignedInteger16;

/**
 * A 32-bit signed integer value type.
 */
typedef int32_t CInteger32;

/**
 * A 32-bit unsigned integer value type.
 */
typedef uint32_t CUnsignedInteger32;

/**
 * A 64-bit signed integer value type.
 */
typedef int64_t CInteger64;

/**
 * A 64-bit unsigned integer value type.
 */
typedef uint64_t CUnsignedInteger64;

/**
 * A signed integer value type.
 *
 * When building 32-bit applications, `CInteger` is a 32-bit integer.
 * A 64-bit application treats `CInteger` as a 64-bit integer.
 */
typedef long CInteger;

/**
 * An unsigned integer value type.
 *
 * When building 32-bit applications, `CUnsignedInteger` is a 32-bit unsigned integer.
 * A 64-bit application treats `CUnsignedInteger` as a 64-bit unsigned integer.
 */
typedef unsigned long CUnsignedInteger;

/**
 * A 32-bit floating point type.
 */
typedef float CFloatingPoint32;

/**
 * A 64-bit floating point type.
 */
typedef double CFloatingPoint64;

#if C_TARGET_ARCHITECTURE_WASM32
#define _C_FLOATING_POINT_TYPE float
#else
#define _C_FLOATING_POINT_TYPE double
#endif

/**
 * The basic type for floating-point scalar values.
 *
 * When building 32-bit applications, `CFloatingPoint` is a 32-bit, IEEE single-precision floating point type.
 * A 64-bit application treats `CFloatingPoint` a 64-bit, IEEE double-precision floating point type.
 */
typedef _C_FLOATING_POINT_TYPE CFloatingPoint;

#define CNumberFindMaximum(x, y)                                                                                                                                                   \
  ({                                                                                                                                                                               \
    __auto_type _x = (x);                                                                                                                                                          \
    __auto_type _y = (y);                                                                                                                                                          \
    _x > _y ? _x : _y;                                                                                                                                                             \
  })

#define CNumberFindMinimum(x, y)                                                                                                                                                   \
  ({                                                                                                                                                                               \
    __auto_type _x = (x);                                                                                                                                                          \
    __auto_type _y = (y);                                                                                                                                                          \
    _x < _y ? _x : _y;                                                                                                                                                             \
  })

#define CNumberCalculateAbsoluteValue(value) ((value) < 0 ? -(value) : (value))

/**
 * The maximum value for a ``CInteger``.
 */
#define CIntegerMaximum LONG_MAX

/**
 * A quiet NaN ("not a number").
 *
 * A NaN compares not equal, not greater than, and not less than every value, including itself.
 * Passing a NaN to an operation generally results in NaN.
 *
 * Because a NaN always compares not equal to itself, to test whether a floating-point value is NaN, use its ``CNumberIsNaN`` function instead of the equal-to operator (==).
 */
extern const CFloatingPoint CFloatingPointNaN;

#define CNumberIsNaN isnan

C_ASSUME_NONNULL_END

#endif /* CNumber_h */
