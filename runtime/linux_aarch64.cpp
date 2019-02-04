/*
 * Copyright (c) 2017 Trail of Bits, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define ADDRESS_SIZE_BITS 64
#define KLEEMILL_RUNTIME_AARCH64 64
#define KLEEMILL_RUNTIME

#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64

#include <algorithm>
#include <cassert>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-alignof-expression"

#include "FreeStanding/FreeStanding.cpp"
#include "Intrinsic/Intrinsics.cpp"
#include "remill/Arch/Runtime/Intrinsics.h"
#include "remill/Arch/Runtime/Intrinsics.cpp"
#include "remill/Arch/AArch64/Runtime/State.h"
#include "Native/Task.h"
#include "Native/AArch64.cpp"
#include "Native/Task.cpp"

#pragma clang diagnostic pop