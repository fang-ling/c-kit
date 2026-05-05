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

typedef const char* CString;

#define CStringGetCount strlen

CUnsignedInteger64
CStringConvertUTF8CharactersToUTF32Characters(
  CInteger32* destination,
  CString nonnil * nonnil source,
  CUnsignedInteger64 maximumAllowedSize,
  CUnsignedInteger64 destinationSize
);

CUnsignedInteger64
CStringConvertUTF32CharactersToUTF8Characters(
  CInteger8* destination,
  const CInteger32* nonnil * nonnil source,
  CUnsignedInteger64 maximumAllowedSize,
  CUnsignedInteger64 destinationSize
);

C_ASSUME_NONNULL_END

#endif /* CString_h */
