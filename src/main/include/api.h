/**
 * \file api.h
 *
 * PROS API header provides high-level user functionality
 *
 * Contains declarations for use by typical VEX programmers using PROS.
 *
 * This file should not be modified by users, since it gets replaced whenever
 * a kernel upgrade occurs.
 *
 * Copyright (c) 2017-2019, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_API_H_
#define _PROS_API_H_

#ifdef __cplusplus
#include <cerrno>
#include <cmath>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#else /* (not) __cplusplus */
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#endif /* __cplusplus */

#define PROS_VERSION_MAJOR 3
#define PROS_VERSION_MINOR 2
#define PROS_VERSION_PATCH 0
#define PROS_VERSION_STRING "3.2.0"

#define PROS_ERR (INT32_MAX)
#define PROS_ERR_F (INFINITY)

#include "../../../libraries/pros/adi.h"
#include "../../../libraries/pros/colors.h"
#include "../../../libraries/pros/llemu.h"
#include "../../../libraries/pros/misc.h"
#include "../../../libraries/pros/motors.h"
#include "../../../libraries/pros/rtos.h"
#include "../../../libraries/pros/vision.h"

#ifdef __cplusplus
#include "../../../libraries/pros/adi.hpp"
#include "../../../libraries/pros/llemu.hpp"
#include "../../../libraries/pros/misc.hpp"
#include "../../../libraries/pros/motors.hpp"
#include "../../../libraries/pros/rtos.hpp"
#include "../../../libraries/pros/vision.hpp"
#endif

#endif  // _PROS_API_H_