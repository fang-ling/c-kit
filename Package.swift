// swift-tools-version: 6.3

//===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//
//
//  Package.swift
//  c-kit
//
//  Created by Fang Ling on 2026/4/25.
//
//  This source file is part of the CKit open source project
//
//  Copyright (c) 2026 Fang Ling <fangling@fangl.ing>
//  Licensed under Apache License v2.0
//
//  See LICENSE for license information
//
//  SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//

import PackageDescription

let package = Package(
  name: "c-kit",
  products: [
    .library(name: "CKit", targets: ["CKit"])
  ],
  targets: [
    .target(name: "CKit", publicHeadersPath: "Includes"),
    .testTarget(name: "CKitTests", dependencies: ["CKit"])
  ],
  cLanguageStandard: .c89
)
