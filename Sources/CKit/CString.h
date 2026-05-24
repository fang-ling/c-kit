/*
 *  CString.h
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

#ifndef CString_h
#define CString_h

#include <string.h>

#include "CBase.h"
#include "CNumber.h"

C_ASSUME_NONNULL_BEGIN

/**
 * A null-terminated sequence of UTF-8 code units.
 */
typedef const char* CString;

#define CStringGetCount strlen

#define CStringInitializeWithFormat sprintf

/**
 * Converts a UTF-8 string to its UTF-32 representation.
 *
 * - Parameters:
 *   - destination: The buffer where the UTF-32 string will be stored. If
 *     destination is `null`, `destinationSize` is ignored, and the conversion
 *     still proceeds, except that the converted string is not written to
 *     memory, and no destination size limit exists.
 *   - source: A `null`-terminated UTF-8 string to convert.
 *   - maximumAllowedSize: The maximum number of UTF-8 characters to convert.
 *   - destinationSize: The size of the `destination`. At most `destinationSize`
 *     characters are written to the `destination`.
 *
 * - Returns: The number of UTF-8 character that make up the converted part of
 *   the string, not including the terminating `null` byte. If a UTF-32
 *   character is encountered that could not be converted, `-1ull` is returned.
 */
CUnsignedInteger64
CStringConvertUTF8CharactersToUTF32Characters(
  CInteger32* nillable destination,
  CString source,
  CUnsignedInteger64 maximumAllowedSize,
  CUnsignedInteger64 destinationSize
);

/**
 * Converts a UTF-32 string to its UTF-8 representation.
 *
 * - Parameters:
 *   - destination: The buffer where the UTF-8 string will be stored. If
 *     destination is `null`, `destinationSize` is ignored, and the conversion
 *     still proceeds, except that the converted string is not written to
 *     memory, and no destination size limit exists.
 *   - source: A `null`-terminated UTF-32 string to convert.
 *   - maximumAllowedSize: The maximum number of UTF-32 characters to convert.
 *   - destinationSize: The size of the `destination`. At most `destinationSize`
 *     characters are written to the `destination`.
 *
 * - Returns: The number of UTF-32 character that make up the converted part of
 *   the string, not including the terminating `null` byte. If a UTF-8 character
 *   is encountered that could not be converted, `-1ull` is returned.
 */
CUnsignedInteger64
CStringConvertUTF32CharactersToUTF8Characters(
  CInteger8* nillable destination,
  const CInteger32* source,
  CUnsignedInteger64 maximumAllowedSize,
  CUnsignedInteger64 destinationSize
);

C_ASSUME_NONNULL_END

#endif /* CString_h */
