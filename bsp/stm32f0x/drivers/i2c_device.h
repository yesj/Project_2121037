/*
 * File      : i2c_device.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-15     
 */

#ifndef __I2C_DEVICE_H__
#define __I2C_DEVICE_H__

#include <rtdevice.h>

typedef enum
{
    Error = 0,
    Success = !Error
}Status;

extern void  F_InitialEEPROM_GPIO(void);

extern void EE_WriteData(rt_uint8_t* pBuffer, rt_off_t WriteAddr, rt_size_t NumByteToWrite);

extern void EE_ReadData(rt_uint8_t* pBuffer, rt_off_t ReadAddr, rt_size_t NumByteToRead);

#endif
