/*
 * File      : speed_control.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

#ifndef __HEART_CONTROL_H__
#define __HEART_CONTROL_H__

#include <rthw.h>
//#include "chandler.h"

extern rt_uint8_t	F_readHandHeartRate(void);

extern rt_uint8_t	F_readwHeartRate(void);

extern void rt_hw_heart_rate_init(void);


#endif
