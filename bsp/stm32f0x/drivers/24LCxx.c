/*
 * File      : 24LCxx.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-21     JoyChen      First version, support 24LC024H eeprom device
 */

#include <rtthread.h>
#include <stdlib.h>
#include <string.h>
//#include "i2c.h"
#include "i2c_device.h"

#define EE_Address 0xA0

#define EE24LC024H

/*
	Note: If eeprom size lager then EE_MEM_SIZE byte, you must define EE_ADDR_SIZE == I2C_MEM_2Bytes
*/
#ifdef EE24LC024H
#define EE_ADDR_SIZE I2C_MEM_1Byte
#define EE_MEM_SIZE	256
#define EE_PageSize	16
#endif

static struct rt_device ee_dev;

rt_uint32_t EE_ReadBuffer(void *pBuffer, rt_off_t ReadAddr, rt_size_t NumByteToRead)
{
	//return I2C_IORW(I2C1, (uint8_t *)pBuffer, (uint16_t)NumByteToRead, (uint16_t)ReadAddr, EE_Address | 0x01, I2C_MEM_1Byte );
	//rt_uint8_t data;
	//rt_uint8_t* i2c_buf;
	
	//*(rt_uint8_t *)pBuffer = EE_Read(ReadAddr);
	
	EE_ReadData((rt_uint8_t *)pBuffer,ReadAddr,NumByteToRead);

	return 0;
}

Status EE_WriteBuffer(const void *pBuffer, rt_off_t WriteAddr, rt_size_t NumByteToWrite)
{
	//rt_uint8_t NumOfPage = 0, NumOfSingle = 0;
	rt_uint16_t Addr = 0,count = 0;
	rt_uint8_t *ptr = (rt_uint8_t *)pBuffer;
	
	Addr = (rt_uint16_t)(WriteAddr&0xFFFF);

	count = (rt_uint16_t)(NumByteToWrite&0xFFFF);
	
	if ((WriteAddr + NumByteToWrite) > EE_MEM_SIZE)
		return Error;

	EE_WriteData(ptr,Addr,count);
	
	rt_thread_delay(50);
	
	return Success; 
}

static rt_err_t ee24LCxx_init(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t ee24LCxx_read(rt_device_t dev, rt_off_t pos, void *buf, rt_size_t size)
{
	EE_ReadBuffer(buf, pos, size);
	return size;
}

static rt_size_t ee24LCxx_write(rt_device_t dev, rt_off_t pos, const void *buf, rt_size_t size)
{
	EE_WriteBuffer(buf, pos, size);
	return size;
}

static rt_err_t ee24LCxx_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t ee24LCxx_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_err_t ee24LCxx_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	return RT_EOK;
}

int	 ee24LCxx_hw_init(void)
{
	//rt_uint32_t delay, i;
	F_InitialEEPROM_GPIO();
	
	ee_dev.init 	= ee24LCxx_init;
	ee_dev.open 	= ee24LCxx_open;
	ee_dev.close	= ee24LCxx_close;
	ee_dev.read 	= ee24LCxx_read;
	ee_dev.write	= ee24LCxx_write;
	ee_dev.control	= ee24LCxx_control;
	ee_dev.type 	= RT_Device_Class_Unknown;

	rt_device_register(&ee_dev, "eeprom", RT_DEVICE_FLAG_RDWR);
	
	return 0;
}

INIT_DEVICE_EXPORT(ee24LCxx_hw_init);

/*
int ee_read_all(int argc , char** argv)
{
	rt_device_t dev;
	rt_uint8_t buf[256],i;
	
	
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	//rt_device_read(dev, atoi(argv[1]), buf, 1 );
	
	rt_device_read(dev, 0, buf, (sizeof(buf)-1));
	//sizeof(buf)
	for (i = 0; i < (sizeof(buf)-1) ; i++)
	{
		rt_kprintf("adr = %d data = %d\n", i,buf[i]);
	}
	rt_device_close(dev);

	return 0;
}
*/

int ee_read_adr(int argc , char** argv)
{
	rt_device_t dev;
	rt_uint8_t buf,adr;

	adr = atoi(argv[1]);
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	rt_device_read(dev, adr , &buf, 1);
	rt_kprintf("adr = %d data = %d\n", adr ,buf);
	rt_device_close(dev);

	return 0;
}
/*
int ee_write_all(int argc , char** argv)
{
	rt_device_t dev;
	rt_uint8_t buf[256];
	
	memset(buf , atoi(argv[1]) , sizeof(buf));
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	rt_device_write(dev, 0, buf, (sizeof(buf)-1));
	rt_device_close(dev);
	
	return 0;
}
*/

int ee_write_adr(int argc , char** argv)
{
	rt_device_t dev;
	rt_uint8_t buf,adr;

	adr = atoi(argv[1]);
	buf = atoi(argv[2]);
	
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	rt_device_write(dev, adr, &buf, 1);
	rt_device_close(dev);

	return 0;
}


#include <finsh.h>
//MSH_CMD_EXPORT(ee_read_all, do test eeprom read);
MSH_CMD_EXPORT(ee_read_adr, do test eeprom read);
//MSH_CMD_EXPORT(ee_write_all, do test eeprom write);
MSH_CMD_EXPORT(ee_write_adr, do test eeprom write);

/*
void dump_ee(void)
{
	rt_device_t dev;
	char buf[EE_MEM_SIZE];
	int i, j;

	dev = rt_device_find("eeprom");
	rt_device_read(dev, 0, buf, EE_MEM_SIZE );

	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			rt_kprintf("0x%02X ", buf[ i*16+ j]);
		}
		rt_kprintf("\n");
	}
}

void ee_reset(void)
{
	char buf[EE_MEM_SIZE], read[EE_MEM_SIZE];
	int i;
	rt_device_t dev = rt_device_find("eeprom");

	for (i = 0; i < EE_MEM_SIZE; i++)
	{
		buf[i] = 0xFF;
		read[i] = 0;
	}
	if (rt_device_write(dev, 0, buf, EE_MEM_SIZE ) == EE_MEM_SIZE)
		rt_kprintf("Write Success\n");

	rt_device_read(dev, 0, read, EE_MEM_SIZE );

	for (i = 0; i < EE_MEM_SIZE; i++)
	{
		if (buf[i] != read[i])
			rt_kprintf("EE Failed %X != %X at %d\n", buf[i], read[i], i);
	}
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(ee_reset, test system);
FINSH_FUNCTION_EXPORT(dump_ee, test system);
#endif
*/
