/*
 *  CBase.h
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

#ifndef CBase_h
#define CBase_h

#define C_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#define C_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")

#define let      __auto_type
#define nonnil   _Nonnull
#define nillable _Nullable

#define null (void*)0

#define C_INITIALIZER __attribute__((constructor))

/* Apple platforms. */
#if defined(__APPLE__)
#  define C_TARGET_OS_APPLE 1
#else
#  define C_TARGET_OS_APPLE 0
#endif

/* Linux. */
#if defined(__linux__)
#  define C_TARGET_OS_LINUX 1
#else
#  define C_TARGET_OS_LINUX 0
#endif

/* FreeBSD. */
#if defined(__FreeBSD__)
#  define C_TARGET_OS_FREEBSD 1
#else
#  define C_TARGET_OS_FREEBSD 0
#endif

/* WASI. */
#if defined(__wasi__)
#  define C_TARGET_OS_WASI 1
#else
#  define C_TARGET_OS_WASI 0
#endif

/* Online Judge platforms. */
#if defined(ONLINE_JUDGE)
#  define C_TARGET_OS_ONLINE_JUDGE 1
#else
#  define C_TARGET_OS_ONLINE_JUDGE 0
#endif

/* ARM64 architecture. */
#if defined(__arm64__)
#  define C_TARGET_ARCHITECTURE_ARM64 1
#else
#  define C_TARGET_ARCHITECTURE_ARM64 0
#endif

/* x86_64 architecture. */
#if defined(__x86_64__)
#  define C_TARGET_ARCHITECTURE_X86_64 1
#else
#  define C_TARGET_ARCHITECTURE_X86_64 0
#endif

/* WebAssembly 32-bit architecture. */
#if defined(__wasm32__)
#  define C_TARGET_ARCHITECTURE_WASM32 1
#else
#  define C_TARGET_ARCHITECTURE_WASM32 0
#endif

#endif /* CBase_h */
