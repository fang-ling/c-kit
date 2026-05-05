/*
 *  CString.c
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
 *
 *  Portions of this file are derived from the FreeBSD libc implementation.
 *
 *  Original sources:
 *    freebsd-src/lib/libc/locale/utf8.c
 *      - Commit hash: 1d386b48a555f61cb7325543adbbb5c3f3407a66
 *
 *  Copyright 2013 Garrett D'Amore <garrett@damore.org>
 *  Copyright 2011 Nexenta Systems, Inc.  All rights reserved.
 *  Copyright (c) 2002-2004 Tim J. Robbins
 *  All rights reserved.
 *
 *  Copyright (c) 2011 The FreeBSD Foundation
 *
 *  Portions of this software were developed by David Chisnall
 *  under sponsorship from the FreeBSD Foundation.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 */

#include "CString.h"

C_ASSUME_NONNULL_BEGIN

typedef struct CStringUTF8StateMachine {
  CInteger32 leastValidCodePoint;
  CInteger32 currentCodePoint;
  CInteger32 remainingByteCount;
} CStringUTF8StateMachine;

CUnsignedInteger64
CStringConvertUTF8CharacterToUTF32Character(
  CInteger32* destination,
  CString source,
  CUnsignedInteger64 n,
  CStringUTF8StateMachine* stateMachine
) {
  if (stateMachine->remainingByteCount < 0 ||
      stateMachine->remainingByteCount > 6) {
    return -1;
  }

  if (source == NULL) {
    source = "";
    n = 1;
    destination = NULL;
  }

  /* Incomplete multibyte sequence */
  if (n == 0) {
    return -2;
  }

  let remainingByteCount = 0;
  let leastValidCodePoint = 0;
  let mask = 0;
  if (stateMachine->remainingByteCount == 0) {
    /*
     * Determine the number of octets that make up this character from the first
     * octet, and a mask that extracts the interesting bits of the first octet.
     * We already know the character is at least two bytes long.
     *
     * We also specify a lower bound for the character code to detect redundant,
     * non-"shortest form" encodings. For example, the sequence C0 80 is _not_ a
     * legal representation of the null character. This enforces a 1-to-1
     * mapping between character codes and their multibyte representations.
     */
    let newCharacter = (CInteger32)((CUnsignedInteger8)*source);
    if ((newCharacter & 0x80) == 0) {
      /* Fast path for plain ASCII characters. */
      if (destination != NULL) {
        *destination = newCharacter;
      }

      return newCharacter != '\0' ? 1 : 0;
    }

    if ((newCharacter & 0xe0) == 0xc0) {
      mask = 0x1f;
      remainingByteCount = 2;
      leastValidCodePoint = 0x80;
    } else if ((newCharacter & 0xf0) == 0xe0) {
      mask = 0x0f;
      remainingByteCount = 3;
      leastValidCodePoint = 0x800;
    } else if ((newCharacter & 0xf8) == 0xf0) {
      mask = 0x07;
      remainingByteCount = 4;
      leastValidCodePoint = 0x10000;
    } else {
      /*
       * Malformed input; input is not UTF-8.
       */
      return -1;
    }
  } else {
    remainingByteCount = stateMachine->remainingByteCount;
    leastValidCodePoint = stateMachine->leastValidCodePoint;
  }

  /*
   * Decode the octet sequence representing the character in chunks of 6 bits,
   * most significant first.
   */
  let currentCodePoint = 0;
  if (stateMachine->remainingByteCount == 0) {
    currentCodePoint = (CUnsignedInteger8)*source++ & mask;
  } else {
    currentCodePoint = stateMachine->currentCodePoint;
  }

  let i = 0;
  for (i = (stateMachine->remainingByteCount == 0) ? 1 : 0;
       i < CNumberFindMinimum(remainingByteCount, n);
       i += 1) {
    if ((*source & 0xc0) != 0x80) {
      /* Malformed input; bad characters in the middle of a character. */
      return -1;
    }
    currentCodePoint <<= 6;
    currentCodePoint |= *source++ & 0x3f;
  }

  if (i < remainingByteCount) {
    /* Incomplete multibyte sequence. */
    stateMachine->remainingByteCount = remainingByteCount - i;
    stateMachine->leastValidCodePoint = leastValidCodePoint;
    stateMachine->currentCodePoint = currentCodePoint;

    return -2;
  }

  if (currentCodePoint < leastValidCodePoint) {
    /* Malformed input; redundant encoding. */
    return -1;
  }

  if ((currentCodePoint >= 0xd800 && currentCodePoint <= 0xdfff) ||
      currentCodePoint > 0x10ffff) {
    /* Malformed input; invalid code points. */
    return -1;
  }

  if (destination != NULL) {
    *destination = currentCodePoint;
  }
  stateMachine->remainingByteCount = 0;

  return currentCodePoint == '\0' ? 0 : remainingByteCount;
}

CUnsignedInteger64
CStringConvertUTF8CharactersToUTF32Characters(
  CInteger32* destination,
  CString* source,
  CUnsignedInteger64 maximumAllowedSize,
  CUnsignedInteger64 destinationSize
) {
  let stateMachine = (CStringUTF8StateMachine){ 0 };
  let string = *source;

  /*
   * The fast path in the loop below is not safe if an ASCII character appears
   * as anything but the first byte of a multibyte sequence. Check now to avoid
   * doing it in the loop.
   */
  if (maximumAllowedSize > 0 &&
      destinationSize > 0 &&
      stateMachine.remainingByteCount > 0 &&
      (CInteger8)*string > 0) {
    return -1;
  }

  let unicodeCharacterCount = 0ull;
  let utf8CharacterCount = 0ull;
  while (destinationSize-- > 0) {
    if (maximumAllowedSize > 0 && (CInteger8)*string > 0) {
      /* Fast path for plain ASCII characters excluding NULL. */
      *destination = (CInteger32)*string;
      utf8CharacterCount = 1;
    } else {
      utf8CharacterCount =
        CStringConvertUTF8CharacterToUTF32Character(
          destination,
          string,
          maximumAllowedSize,
          &stateMachine
        );

      if (utf8CharacterCount == -1) {
        *source = string;

        return -1;
      } else if (utf8CharacterCount == -2) {
        *source = string + maximumAllowedSize;

        return unicodeCharacterCount;
      } else if (utf8CharacterCount == 0) {
        *source = NULL;

        return unicodeCharacterCount;
      }
    }

    string += utf8CharacterCount;
    maximumAllowedSize -= utf8CharacterCount;
    unicodeCharacterCount += 1;
    destination += 1;
  }

  *source = string;

  return unicodeCharacterCount;
}

CUnsignedInteger64
CStringConvertUTF32CharacterToUTF8Character(
  CInteger8* destination,
  CInteger32 source,
  CStringUTF8StateMachine* stateMachine
) {
  if (stateMachine->remainingByteCount != 0) {
    return -1;
  }

  if (destination == NULL) {
    /* Reset to initial shift state (no-op). */
    return 1;
  }

  /*
   * Determine the number of octets needed to represent this character.
   * We always output the shortest sequence possible. Also specify the first few
   * bits of the first octet, which contains the information about the sequence
   * length.
   */
  let mask = (CInteger8)0;
  let codePointLength = 0;
  if ((source & ~0x7f) == 0) {
    /* Fast path for plain ASCII characters. */
    *destination = (CInteger8)source;
    return 1;
  } else if ((source & ~0x7ff) == 0) {
    mask = 0xc0;
    codePointLength = 2;
  } else if ((source & ~0xffff) == 0) {
    if (source >= 0xd800 && source <= 0xdfff) {
      return -1;
    }
    mask = 0xe0;
    codePointLength = 3;
  } else if (source >= 0 && source <= 0x10ffff) {
    mask = 0xf0;
    codePointLength = 4;
  } else {
    return -1;
  }

  /*
   * Output the octets representing the character in chunks of 6 bits, least
   * significant last. The first octet is a special case because it contains the
   * sequence length information.
   */
  let i = codePointLength - 1;
  for (; i > 0; i -= 1) {
    destination[i] = (source & 0x3f) | 0x80;
    source >>= 6;
  }
  *destination = (source & 0xff) | mask;

  return codePointLength;
}

CUnsignedInteger64
CStringConvertUTF32CharactersToUTF8Characters(
  CInteger8* destination,
  const CInteger32** source,
  CUnsignedInteger64 maximumAllowedSize,
  CUnsignedInteger64 destinationSize
) {
  let stateMachine = (CStringUTF8StateMachine){ 0 };
  CInteger8 buffer[4];

  if (stateMachine.remainingByteCount != 0) {
    return -1;
  }

  let string = *source;
  let utf8CharacterCount = 0ull;

  while (destinationSize > 0 && maximumAllowedSize-- > 0) {
    let utf8CodePointLength = 0ull;

    if (0 <= *string && *string < 0x80) {
      /* Fast path for plain ASCII characters. */
      utf8CodePointLength = 1;
      *destination = *string;
    } else if (destinationSize > 4) {
      /* Enough space to translate in-place. */
      utf8CodePointLength = CStringConvertUTF32CharacterToUTF8Character(
        destination,
        *string,
        &stateMachine
      );
      if (utf8CodePointLength == -1) {
        *source = string;

        return -1;
      }
    } else {
      /* May not be enough space; use temporary buffer. */
      utf8CodePointLength = CStringConvertUTF32CharacterToUTF8Character(
        buffer,
        *string,
        &stateMachine
      );
      if (utf8CodePointLength == -1) {
        *source = string;

        return -1;
      }
      if (utf8CodePointLength > (CInteger32)destinationSize) {
        /* MB sequence for character won't fit. */
        break;
      }
      memcpy(destination, buffer, utf8CodePointLength);
    }
    if (*string == '\0') {
      *source = NULL;

      return (utf8CharacterCount + utf8CodePointLength - 1);
    }
    string += 1;
    destination += utf8CodePointLength;
    destinationSize -= utf8CodePointLength;
    utf8CharacterCount += utf8CodePointLength;
  }
  *source = string;

  return utf8CharacterCount;
}

C_ASSUME_NONNULL_END
