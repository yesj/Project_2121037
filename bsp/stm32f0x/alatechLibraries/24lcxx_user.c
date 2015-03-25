#include "24lcxx_user.h"

#define WriteDelayTimeVal	6

#define EepromVer_1				0xA0
#define EepromVer_2				0x10
#define EepromVer_3				0x34
#define EepromVer_4				0x00


//============
#define EE_IncMax					0x06
#define EE_IncUpDown			0x07
#define EE_IncMaxAd				0x08
#define EE_IncMinAd				0x09
//============
#define EE_Home1Data			0x0A
#define EE_Home2Data			0x0B
//============
#define EE_DetectionData_1	0x0C
#define EE_DetectionData_2	0x0D

//============
#define EE_Ver_1					0xFA
#define EE_Ver_2					0xFB
#define EE_Ver_3					0xFC
#define EE_Ver_4					0xFD

static		rt_device_t	dev;
static		rt_uint8_t	buf;

rt_uint8_t	F_eeprom_test(void)
{
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	buf = 0x5A;
	rt_device_write(dev, 0xFF, &buf, 1);
	rt_thread_delay(WriteDelayTimeVal);
	
	buf = 0xA5;
	rt_device_write(dev, 0xFE, &buf, 1);
	rt_thread_delay(WriteDelayTimeVal);
	
	rt_device_read(dev, 0xFF , &buf, 1);
	if(buf == 0x5A)
	{
		rt_device_read(dev, 0xFE , &buf, 1);
		if(buf == 0xA5)
		{
			rt_device_close(dev);
			return RT_EOK;
		}
	}
	rt_device_close(dev);
	
	return RT_ERROR;
}

rt_uint8_t	F_eeprom_whether_init(void)
{
		rt_uint8_t	TempByte1,TempByte2,TempByte3,TempByte4;

		dev = rt_device_find("eeprom");
		rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
		rt_device_read(dev, EE_Ver_1 , &buf, 1);
		TempByte1 = buf;
		rt_device_read(dev, EE_Ver_2 , &buf, 1);
		TempByte2 = buf;
		rt_device_read(dev, EE_Ver_3 , &buf, 1);
		TempByte3 = buf;
		rt_device_read(dev, EE_Ver_4 , &buf, 1);
		TempByte4 = buf;
		if((TempByte1==EepromVer_1) && (TempByte2==EepromVer_2) && (TempByte3==EepromVer_3) && (TempByte4==EepromVer_4))
		{
			rt_device_close(dev);
			return RT_EOK;
		}

	rt_device_close(dev);
	return RT_ERROR;
}

void	F_eeprom_write_init(void)
{
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	buf = EepromVer_1;
	rt_device_write(dev, EE_Ver_1, &buf, 1);
	rt_thread_delay(WriteDelayTimeVal);
	buf = EepromVer_2;
	rt_device_write(dev, EE_Ver_2, &buf, 1);
	rt_thread_delay(WriteDelayTimeVal);
	buf = EepromVer_3;
	rt_device_write(dev, EE_Ver_3, &buf, 1);
	rt_thread_delay(WriteDelayTimeVal);
	buf = EepromVer_4;
	rt_device_write(dev, EE_Ver_4, &buf, 1);
	rt_thread_delay(WriteDelayTimeVal);
	rt_device_close(dev);
}

void	F_eeprom_incline_data(rt_uint8_t status,rt_incline_eeprom_data_t *data)
{
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	if(status) 
	{
		rt_thread_delay(WriteDelayTimeVal);
		rt_device_write(dev, EE_IncUpDown, &(data ->incUpDownFlg), 1);
		rt_thread_delay(WriteDelayTimeVal);
		rt_device_write(dev, EE_IncMaxAd, &(data ->incMaxAd), 1);
		rt_thread_delay(WriteDelayTimeVal);
		rt_device_write(dev, EE_IncMinAd, &(data ->incMinAd), 1);
		rt_thread_delay(WriteDelayTimeVal);
	}
	else
	{
		rt_device_read(dev, EE_IncUpDown , &(data ->incUpDownFlg), 1);
		rt_device_read(dev, EE_IncMaxAd , &(data ->incMaxAd), 1);
		rt_device_read(dev, EE_IncMinAd , &(data ->incMinAd), 1);
	}
	rt_device_close(dev);
}

void	F_eeprom_home1_data(rt_uint8_t status,rt_uint8_t *data)
{
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	if(status) 
	{
		rt_device_write(dev, EE_Home1Data, data, 1);
	}
	else
	{
		rt_device_read(dev, EE_Home1Data , data, 1);
	}
	rt_device_close(dev);
}

void	F_eeprom_home2_data(rt_uint8_t status,rt_uint8_t *data)
{
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	if(status) 
	{
		rt_device_write(dev, EE_Home2Data, data, 1);
	}
	else
	{
		rt_device_read(dev, EE_Home2Data , data, 1);
	}
	rt_device_close(dev);
}

void	F_eeprom_user_DetectionData(rt_uint8_t status,rt_uint8_t Num,rt_uint8_t *data)
{
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	if(status) 
	{
		rt_device_read(dev, EE_DetectionData_1 , data, 1);
		switch(Num) {
			case	setUser_1_EventVal:
				*data |= 0x01;
				break;
			case	setUser_2_EventVal:
				*data |= 0x02;
				break;
			case	setUser_3_EventVal:
				*data |= 0x04;
				break;
			case	setUser_4_EventVal:
				*data |= 0x08;
				break;
			case	setUser_5_EventVal:
				*data |= 0x10;
				break;
			case	setUser_6_EventVal:
				*data |= 0x20;
				break;
			case	setUser_7_EventVal:
				*data |= 0x40;
				break;
			case	setUser_8_EventVal:
				*data |= 0x80;
				break;
		}
		rt_device_write(dev, EE_DetectionData_1, data, 1);
	}
	else
	{
		rt_device_read(dev, EE_DetectionData_1 , data, 1);
		switch(Num) {
			case	setUser_1_EventVal:
				*data &= ~0x01;	
				break;
			case	setUser_2_EventVal:
				*data &= ~0x02;	
				break;
			case	setUser_3_EventVal:
				*data &= ~0x04;	
				break;
			case	setUser_4_EventVal:
				*data &= ~0x08;	
				break;
			case	setUser_5_EventVal:
				*data &= ~0x10;	
				break;
			case	setUser_6_EventVal:
				*data &= ~0x20;	
				break;
			case	setUser_7_EventVal:
				*data &= ~0x40;	
				break;
			case	setUser_8_EventVal:
				*data &= ~0x80;	
				break;
		}
			if(*data) {
				*data = 1;
			} else {
				*data = 0;
			}
	}
	rt_device_close(dev);
}
