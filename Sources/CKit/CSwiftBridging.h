/*===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CSwiftBridging.h
 *  c-kit
 *
 *  Created by Fang Ling on 2026/8/1.
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

#ifndef CSwiftBridging_h
#define CSwiftBridging_h

#include "CBase.h"

C_ASSUME_NONNULL_BEGIN

#define _CXX_INTEROP_STRINGIFY(_x) #_x

#define C_SWIFT_SHARED_REFERENCE(_retain, _release)                                                                                                                                \
  __attribute__((swift_attr("import_reference")))                                                                                                                                  \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(retain:_retain))))                                                                                                              \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(release:_release))))

#define C_SWIFT_RETURNS_RETAINED __attribute__((swift_attr("returns_retained")))

#define C_SWIFT_NAME(_name) __attribute__((swift_name(#_name)))

C_ASSUME_NONNULL_END

#endif /* CSwiftBridging_h */
