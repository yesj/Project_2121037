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

#ifndef __SPEED_CONTROL_H__
#define __SPEED_CONTROL_H__

#include "chandler.h"

/*
struct speed_control
{
	rt_uint8_t	setSpeed;
};

typedef struct speed_control speed_control_t;
*/
struct rt_speed_init_data
{
		rt_uint16_t	wheelSize;
		rt_uint16_t	pwmLowSpeed;
		rt_uint8_t setSpeed;
		rt_uint8_t	speedMax;
		rt_uint8_t	speedMin;
		rt_bool_t		changeUnit;
		app_err_treadmill_handler_t		err_treadmill_handler;
};

typedef struct rt_speed_init_data rt_speed_init_data_t;

extern void	rt_hw_speed_control_init(rt_speed_init_data_t speed_data_init);

extern void	rt_speed_control_start(rt_uint8_t set_speed);

extern void	rt_speed_control_auto_init(void);

#endif
