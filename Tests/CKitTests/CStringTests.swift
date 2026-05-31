//
//  CStringTests.swift
//  c-kit
//
//  Created by Fang Ling on 2026/5/23.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

import Testing

import CKit

@Test
func testCStringConvertUTF8CharactersToUTF32Characters() {
  let utf8Strings = ["", "Hello, world!", "ω", "こんにち", "🌍"]

  for i in utf8Strings {
    for j in utf8Strings {
      for k in 0 ..< 512 {
        let utf8String = Array(repeating: i + j, count: k).joined()
        let utf32String = utf8String.unicodeScalars.map { character in
          CInteger32(character.value)
        }

        var destinationSize = CStringConvertUTF8CharactersToUTF32Characters(
          nil,
          utf8String,
          CInteger(utf8String.utf8.count),
          0
        )
        #expect(destinationSize == utf32String.count)

        var destination = [CInteger32](
          repeating: 0,
          count: Int(destinationSize)
        )
        destinationSize = destination.withUnsafeMutableBufferPointer { buffer in
          CStringConvertUTF8CharactersToUTF32Characters(
            buffer.baseAddress,
            utf8String,
            CInteger(utf8String.utf8.count),
            destinationSize
          )
        }
        #expect(destination == utf32String)
      }
    }
  }
}

@Test
func testCStringConvertUTF32CharactersToUTF8Characters() {
  let utf32Strings = ["", "Hello, world!", "ω", "こんにち", "🌍"].map { string in
    return string.unicodeScalars.map({ CInteger32($0.value) })
  }

  for i in utf32Strings {
    for j in utf32Strings {
      for k in 0 ..< 512 {
        let utf32String = Array(repeating: i + j, count: k).flatMap({ $0 })
        let utf8String = utf32String
          .map({ String(Character(UnicodeScalar(CUnsignedInteger32($0))!)) })
          .reduce("", +)

        var destinationSize = utf32String.withUnsafeBufferPointer { buffer in
          CStringConvertUTF32CharactersToUTF8Characters(
            nil,
            buffer.baseAddress!,
            CInteger(utf32String.count),
            0
          )
        }
        #expect(destinationSize == utf8String.utf8.count)

        var destination = [CInteger8](repeating: 0, count: destinationSize)
        destinationSize = destination.withUnsafeMutableBufferPointer { buffer in
          utf32String.withUnsafeBufferPointer { utf32StringBuffer in
            CStringConvertUTF32CharactersToUTF8Characters(
              buffer.baseAddress,
              utf32StringBuffer.baseAddress!,
              CInteger(utf32String.count),
              destinationSize
            )
          }
        }
        #expect(
          destination == utf8String.utf8.map({ CInteger8(bitPattern: $0) })
        )
      }
    }
  }
}
