/*
 * File      : ht1625.h
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
 
#include <rthw.h>

#define C_LCDRamSize 				64

extern void F_SetDisplayRam(rt_uint8_t SetClear);

extern void F_Display(void);

extern rt_uint32_t LCDBuffer[C_LCDRamSize];
