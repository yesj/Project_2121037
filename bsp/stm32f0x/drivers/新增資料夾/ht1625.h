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

#define	segLengthVal       56

extern void F_WriteHT1625(rt_uint8_t *buf,rt_uint8_t bufLength);
