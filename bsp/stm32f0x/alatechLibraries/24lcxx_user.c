#include "24lcxx_user.h"

#define WriteDelayTimeVal	6

#define EepromVer_1				0xA0
#define EepromVer_2				0x10
#define EepromVer_3				0x34
#define EepromVer_4				0x01
//============
#define EE_Unit						0x05
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
#define EE_UserNameDataAdr						0x0E
#define EE_User1_Name			EE_UserNameDataAdr
#define EE_User2_Name			(EE_UserNameDataAdr + 10)
#define EE_User3_Name			(EE_UserNameDataAdr + 20)
#define EE_User4_Name			(EE_UserNameDataAdr + 30)
#define EE_User5_Name			(EE_UserNameDataAdr + 40)
#define EE_User6_Name			(EE_UserNameDataAdr + 50)
#define EE_User7_Name			(EE_UserNameDataAdr + 60)
#define EE_User8_Name			(EE_UserNameDataAdr + 70)
#define EE_User9_Name			(EE_UserNameDataAdr + 80)
#define EE_User10_Name		(EE_UserNameDataAdr + 90)

#define EE_UserDataAdr		(EE_UserNameDataAdr + 100)
#define EE_User1_age			EE_UserDataAdr
#define EE_User2_age			(EE_UserDataAdr + 1)
#define EE_User3_age			(EE_UserDataAdr + 2)
#define EE_User4_age			(EE_UserDataAdr + 3)
#define EE_User5_age			(EE_UserDataAdr + 4)
#define EE_User6_age			(EE_UserDataAdr + 5)
#define EE_User7_age			(EE_UserDataAdr + 6)
#define EE_User8_age			(EE_UserDataAdr + 7)
#define EE_User9_age			(EE_UserDataAdr + 8)
#define EE_User10_age			(EE_UserDataAdr + 9)

#define EE_User1_wigeht		(EE_UserDataAdr + 10)
#define EE_User2_wigeht		(EE_UserDataAdr + 11)
#define EE_User3_wigeht		(EE_UserDataAdr + 12)
#define EE_User4_wigeht		(EE_UserDataAdr + 13)
#define EE_User5_wigeht		(EE_UserDataAdr + 14)
#define EE_User6_wigeht		(EE_UserDataAdr + 15)
#define EE_User7_wigeht		(EE_UserDataAdr + 16)
#define EE_User8_wigeht		(EE_UserDataAdr + 17)
#define EE_User9_wigeht		(EE_UserDataAdr + 18)
#define EE_User10_wigeht	(EE_UserDataAdr + 19)

#define EE_User1_seat_position		(EE_UserDataAdr + 20)
#define EE_User2_seat_position		(EE_UserDataAdr + 21)
#define EE_User3_seat_position		(EE_UserDataAdr + 22)
#define EE_User4_seat_position		(EE_UserDataAdr + 23)
#define EE_User5_seat_position		(EE_UserDataAdr + 24)
#define EE_User6_seat_position		(EE_UserDataAdr + 25)
#define EE_User7_seat_position		(EE_UserDataAdr + 26)
#define EE_User8_seat_position		(EE_UserDataAdr + 27)
#define EE_User9_seat_position		(EE_UserDataAdr + 28)
#define EE_User10_seat_position		(EE_UserDataAdr + 29)

#define EE_User_gender_1		(EE_UserDataAdr + 30)
#define EE_User_gender_2		(EE_UserDataAdr + 31)

#define EE_User_sport_data_adr		(EE_User_gender_2 + 1)

#define EE_User1_time				(EE_User_sport_data_adr)
#define EE_User2_time				(EE_User_sport_data_adr + (3 * 1))
#define EE_User3_time				(EE_User_sport_data_adr + (3 * 2))
#define EE_User4_time				(EE_User_sport_data_adr + (3 * 3))
#define EE_User5_time				(EE_User_sport_data_adr + (3 * 4))
#define EE_User6_time				(EE_User_sport_data_adr + (3 * 5))
#define EE_User7_time				(EE_User_sport_data_adr + (3 * 6))
#define EE_User8_time				(EE_User_sport_data_adr + (3 * 7))
#define EE_User9_time				(EE_User_sport_data_adr + (3 * 8))
#define EE_User10_time				(EE_User_sport_data_adr + (3 * 9))

#define EE_User1_cal				(EE_User_sport_data_adr + (3 * 10))
#define EE_User2_cal				(EE_User_sport_data_adr + (3 * 11))
#define EE_User3_cal				(EE_User_sport_data_adr + (3 * 12))
#define EE_User4_cal				(EE_User_sport_data_adr + (3 * 13))
#define EE_User5_cal				(EE_User_sport_data_adr + (3 * 14))
#define EE_User6_cal				(EE_User_sport_data_adr + (3 * 15))
#define EE_User7_cal				(EE_User_sport_data_adr + (3 * 16))
#define EE_User8_cal				(EE_User_sport_data_adr + (3 * 17))
#define EE_User9_cal				(EE_User_sport_data_adr + (3 * 18))
#define EE_User10_cal				(EE_User_sport_data_adr + (3 * 19))

#define EE_User_km_adr		(EE_User_sport_data_adr + (3 * 20))
#define EE_User1_km			EE_User_km_adr
#define EE_User2_km			(EE_User_km_adr + (2 * 1))
#define EE_User3_km			(EE_User_km_adr + (2 * 2))
#define EE_User4_km			(EE_User_km_adr + (2 * 3))
#define EE_User5_km			(EE_User_km_adr + (2 * 4))
#define EE_User6_km			(EE_User_km_adr + (2 * 5))
#define EE_User7_km			(EE_User_km_adr + (2 * 6))
#define EE_User8_km			(EE_User_km_adr + (2 * 7))
#define EE_User9_km			(EE_User_km_adr + (2 * 8))
#define EE_User10_km			(EE_User_km_adr + (2 * 9))

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
	rt_uint8_t	DetectionDataTemp;
	rt_uint8_t	DataAdr;

	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	
		switch(Num) {
			case	setUser_1_EventVal:
				DetectionDataTemp = EE_DetectionData_1;
				DataAdr = 0x01;
				break;
			case	setUser_2_EventVal:
				DetectionDataTemp = EE_DetectionData_1;
				DataAdr = 0x02;
				break;
			case	setUser_3_EventVal:
				DetectionDataTemp = EE_DetectionData_1;
				DataAdr = 0x04;
				break;
			case	setUser_4_EventVal:
				DetectionDataTemp = EE_DetectionData_1;
				DataAdr = 0x08;
				break;
			case	setUser_5_EventVal:
				DetectionDataTemp = EE_DetectionData_1;
				DataAdr = 0x10;
				break;
			case	setUser_6_EventVal:
				DetectionDataTemp = EE_DetectionData_1;
				DataAdr = 0x20;
				break;
			case	setUser_7_EventVal:
				DetectionDataTemp = EE_DetectionData_1;
				DataAdr = 0x40;
				break;
			case	setUser_8_EventVal:
				DetectionDataTemp = EE_DetectionData_1;
				DataAdr = 0x80;
				break;
			case	setUser_9_EventVal:
				DetectionDataTemp = EE_DetectionData_2;
				DataAdr = 0x01;
				break;
			case	setUser_10_EventVal:
				DetectionDataTemp = EE_DetectionData_2;
				DataAdr = 0x02;
				break;
		}
		
	switch(status) {
		case	ReadDataVal:
			rt_device_read(dev, DetectionDataTemp , data, 1);
			*data &= DataAdr;	
			if(*data) {
				*data = 1;
			} else {
				*data = 0;
			}
			break;
		//===========
		case	WriteDataVal:
		rt_device_read(dev, DetectionDataTemp , &buf, 1);
		if(*data) {
			buf |= DataAdr;
		} else {
			buf &= ~DataAdr;
		}
		rt_device_write(dev, DetectionDataTemp, &buf, 1);
			break;
		//===========
		case	InitDataVal:
		rt_device_write(dev, EE_DetectionData_1, data, 1);	
		rt_device_write(dev, EE_DetectionData_2, data, 1);	
			break;		
	}
	rt_device_close(dev);
}

void	F_eeprom_user_name(rt_uint8_t status,rt_uint8_t Num,rt_uint8_t *data,rt_uint8_t Adr)
{
	rt_uint8_t	DetectionDataTemp;
	rt_uint8_t	i,buf;
	
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	
		switch(Num) {
			case	setUser_1_EventVal:
				DetectionDataTemp = EE_User1_Name;
				break;
			case	setUser_2_EventVal:
				DetectionDataTemp = EE_User2_Name;
				break;
			case	setUser_3_EventVal:
				DetectionDataTemp = EE_User3_Name;
				break;
			case	setUser_4_EventVal:
				DetectionDataTemp = EE_User4_Name;
				break;
			case	setUser_5_EventVal:
				DetectionDataTemp = EE_User5_Name;
				break;
			case	setUser_6_EventVal:
				DetectionDataTemp = EE_User6_Name;
				break;
			case	setUser_7_EventVal:
				DetectionDataTemp = EE_User7_Name;
				break;
			case	setUser_8_EventVal:
				DetectionDataTemp = EE_User8_Name;
				break;
			case	setUser_9_EventVal:
				DetectionDataTemp = EE_User9_Name;
				break;
			case	setUser_10_EventVal:
				DetectionDataTemp = EE_User10_Name;
				break;
		}
		
	switch(status) {
		case	ReadDataVal:
			for(i=0;i<10;i++) {
				rt_device_read(dev, DetectionDataTemp+i , &buf, 1);
				*(data + i) = buf;
			}
			break;
		//===========
		case	WriteDataVal:
			for(i=0;i<10;i++) {
				buf = *(data+i);
				rt_device_write(dev, DetectionDataTemp+i, &buf, 1);
			}
			break;
		//===========
		case	ReadSpecificDataAdrVal:
		rt_device_read(dev, DetectionDataTemp+Adr , &buf, 1);
		*(data + Adr) = buf;
			break;		
		//===========
		case	WriteSpecificDataAdrVal:
		buf = *(data+Adr);
		rt_device_write(dev, DetectionDataTemp+Adr, &buf, 1);
			break;	
	}
	rt_device_close(dev);
}

void	F_eeprom_user_age(rt_uint8_t status,rt_uint8_t Num,rt_uint8_t *data)
{
	rt_uint8_t	DetectionDataTemp;
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	
		switch(Num) {
			case	setUser_1_EventVal:
				DetectionDataTemp = EE_User1_age;
				break;
			case	setUser_2_EventVal:
				DetectionDataTemp = EE_User2_age;
				break;
			case	setUser_3_EventVal:
				DetectionDataTemp = EE_User3_age;
				break;
			case	setUser_4_EventVal:
				DetectionDataTemp = EE_User4_age;
				break;
			case	setUser_5_EventVal:
				DetectionDataTemp = EE_User5_age;
				break;
			case	setUser_6_EventVal:
				DetectionDataTemp = EE_User6_age;
				break;
			case	setUser_7_EventVal:
				DetectionDataTemp = EE_User7_age;
				break;
			case	setUser_8_EventVal:
				DetectionDataTemp = EE_User8_age;
				break;
			case	setUser_9_EventVal:
				DetectionDataTemp = EE_User9_age;
				break;
			case	setUser_10_EventVal:
				DetectionDataTemp = EE_User10_age;
				break;
		}
		
	switch(status) {
		case	ReadDataVal:
			rt_device_read(dev, DetectionDataTemp , data, 1);
			break;
		//===========
		case	WriteDataVal:
			rt_device_write(dev, DetectionDataTemp, data, 1);
			break;
	}
	rt_device_close(dev);
}

void	F_eeprom_user_wigeht(rt_uint8_t status,rt_uint8_t Num,rt_uint8_t *data)
{
	rt_uint8_t	DetectionDataTemp;
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	
		switch(Num) {
			case	setUser_1_EventVal:
				DetectionDataTemp = EE_User1_wigeht;
				break;
			case	setUser_2_EventVal:
				DetectionDataTemp = EE_User2_wigeht;
				break;
			case	setUser_3_EventVal:
				DetectionDataTemp = EE_User3_wigeht;
				break;
			case	setUser_4_EventVal:
				DetectionDataTemp = EE_User4_wigeht;
				break;
			case	setUser_5_EventVal:
				DetectionDataTemp = EE_User5_wigeht;
				break;
			case	setUser_6_EventVal:
				DetectionDataTemp = EE_User6_wigeht;
				break;
			case	setUser_7_EventVal:
				DetectionDataTemp = EE_User7_wigeht;
				break;
			case	setUser_8_EventVal:
				DetectionDataTemp = EE_User8_wigeht;
				break;
			case	setUser_9_EventVal:
				DetectionDataTemp = EE_User9_wigeht;
				break;
			case	setUser_10_EventVal:
				DetectionDataTemp = EE_User10_wigeht;
				break;
		}
	switch(status) {
		case	ReadDataVal:
			rt_device_read(dev, DetectionDataTemp , data, 1);
			break;
		//===========
		case	WriteDataVal:
			rt_device_write(dev, DetectionDataTemp, data, 1);
			break;
	}
	rt_device_close(dev);
}

void	F_eeprom_user_seat_position(rt_uint8_t status,rt_uint8_t Num,rt_uint8_t *data)
{
	rt_uint8_t	DetectionDataTemp;
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	
		switch(Num) {
			case	setUser_1_EventVal:
				DetectionDataTemp = EE_User1_seat_position;
				break;
			case	setUser_2_EventVal:
				DetectionDataTemp = EE_User2_seat_position;
				break;
			case	setUser_3_EventVal:
				DetectionDataTemp = EE_User3_seat_position;
				break;
			case	setUser_4_EventVal:
				DetectionDataTemp = EE_User4_seat_position;
				break;
			case	setUser_5_EventVal:
				DetectionDataTemp = EE_User5_seat_position;
				break;
			case	setUser_6_EventVal:
				DetectionDataTemp = EE_User6_seat_position;
				break;
			case	setUser_7_EventVal:
				DetectionDataTemp = EE_User7_seat_position;
				break;
			case	setUser_8_EventVal:
				DetectionDataTemp = EE_User8_seat_position;
				break;
			case	setUser_9_EventVal:
				DetectionDataTemp = EE_User9_seat_position;
				break;
			case	setUser_10_EventVal:
				DetectionDataTemp = EE_User10_seat_position;
				break;
		}
	switch(status) {
		case	ReadDataVal:
			rt_device_read(dev, DetectionDataTemp , data, 1);
			break;
		//===========
		case	WriteDataVal:
			rt_device_write(dev, DetectionDataTemp, data, 1);
			break;
	}
	rt_device_close(dev);
}

void	F_eeprom_user_gender(rt_uint8_t status,rt_uint8_t Num,rt_uint8_t *data)
{
	rt_uint8_t	DetectionDataTemp,DataAdr;

	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);

		switch(Num) {
			case	setUser_1_EventVal:
				DetectionDataTemp = EE_User_gender_1;
				DataAdr = 0x01;
				break;
			case	setUser_2_EventVal:
				DetectionDataTemp = EE_User_gender_1;
				DataAdr = 0x02;
				break;
			case	setUser_3_EventVal:
				DetectionDataTemp = EE_User_gender_1;
				DataAdr = 0x04;
				break;
			case	setUser_4_EventVal:
				DetectionDataTemp = EE_User_gender_1;
				DataAdr = 0x08;
				break;
			case	setUser_5_EventVal:
				DetectionDataTemp = EE_User_gender_1;
				DataAdr = 0x10;
				break;
			case	setUser_6_EventVal:
				DetectionDataTemp = EE_User_gender_1;
				DataAdr = 0x20;
				break;
			case	setUser_7_EventVal:
				DetectionDataTemp = EE_User_gender_1;
				DataAdr = 0x40;
				break;
			case	setUser_8_EventVal:
				DetectionDataTemp = EE_User_gender_1;
				DataAdr = 0x80;
				break;
			case	setUser_9_EventVal:
				DetectionDataTemp = EE_User_gender_2;
				DataAdr = 0x01;
				break;
			case	setUser_10_EventVal:
				DetectionDataTemp = EE_User_gender_2;
				DataAdr = 0x02;
				break;
		}
		
	switch(status) {
		case	ReadDataVal:
			rt_device_read(dev, DetectionDataTemp , data, 1);
			*data &= DataAdr;	
			if(*data) {
				*data = 1;
			} else {
				*data = 0;
			}
			break;
		//===========
		case	WriteDataVal:
			rt_device_read(dev, DetectionDataTemp , &buf, 1);
			if(*data) {
				buf |= DataAdr;
			} else {
				buf &= ~DataAdr;
			}
			rt_device_write(dev, DetectionDataTemp, &buf, 1);
			break;
		//===========
		case	InitDataVal:
		rt_device_write(dev, EE_User_gender_1, data, 1);	
		rt_device_write(dev, EE_User_gender_2, data, 1);	
			break;		
	}
	rt_device_close(dev);
}

void	F_eeprom_user_time(rt_uint8_t status,rt_uint8_t Num,rt_uint32_t *TimeSec)
{
	rt_uint8_t	DetectionDataTemp1,DetectionDataTemp2,DetectionDataTemp3;
	rt_uint8_t	TimeSecByte_3,TimeSecByte_2,TimeSecByte_1;
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	
		switch(Num) {
			case	setUser_1_EventVal:
				DetectionDataTemp1 = EE_User1_time;
				DetectionDataTemp2 = EE_User1_time + 1;
				DetectionDataTemp3 = EE_User1_time + 2;
				break;
			case	setUser_2_EventVal:
				DetectionDataTemp1 = EE_User2_time;
				DetectionDataTemp2 = EE_User2_time + 1;
				DetectionDataTemp3 = EE_User2_time + 2;
				break;
			case	setUser_3_EventVal:
				DetectionDataTemp1 = EE_User3_time;
				DetectionDataTemp2 = EE_User3_time + 1;
				DetectionDataTemp3 = EE_User3_time + 2;
				break;
			case	setUser_4_EventVal:
				DetectionDataTemp1 = EE_User4_time;
				DetectionDataTemp2 = EE_User4_time + 1;
				DetectionDataTemp3 = EE_User4_time + 2;
				break;
			case	setUser_5_EventVal:
				DetectionDataTemp1 = EE_User5_time;
				DetectionDataTemp2 = EE_User5_time + 1;
				DetectionDataTemp3 = EE_User5_time + 2;
				break;
			case	setUser_6_EventVal:
				DetectionDataTemp1 = EE_User6_time;
				DetectionDataTemp2 = EE_User6_time + 1;
				DetectionDataTemp3 = EE_User6_time + 2;
				break;
			case	setUser_7_EventVal:
				DetectionDataTemp1 = EE_User7_time;
				DetectionDataTemp2 = EE_User7_time + 1;
				DetectionDataTemp3 = EE_User7_time + 2;
				break;
			case	setUser_8_EventVal:
				DetectionDataTemp1 = EE_User8_time;
				DetectionDataTemp2 = EE_User8_time + 1;
				DetectionDataTemp3 = EE_User8_time + 2;
				break;
			case	setUser_9_EventVal:
				DetectionDataTemp1 = EE_User9_time;
				DetectionDataTemp2 = EE_User9_time + 1;
				DetectionDataTemp3 = EE_User9_time + 2;
				break;
			case	setUser_10_EventVal:
				DetectionDataTemp1 = EE_User10_time;
				DetectionDataTemp2 = EE_User10_time + 1;
				DetectionDataTemp3 = EE_User10_time + 2;
				break;
		}
	switch(status) {
		case	ReadDataVal:
			rt_device_read(dev, DetectionDataTemp3 , &TimeSecByte_3, 1);
			rt_device_read(dev, DetectionDataTemp2 , &TimeSecByte_2, 1);
			rt_device_read(dev, DetectionDataTemp1 , &TimeSecByte_1, 1);
			*TimeSec = (TimeSecByte_3 << 16) + (TimeSecByte_2 << 8) + TimeSecByte_1;
			break;
		//===========
		case	WriteDataVal:
			TimeSecByte_3 = ((*TimeSec & 0x00FF0000) >> 16);
			TimeSecByte_2 = ((*TimeSec & 0x0000FF00) >> 8);
			TimeSecByte_1 = (*TimeSec & 0x000000FF);
			rt_device_write(dev, DetectionDataTemp3, &TimeSecByte_3, 1);
			rt_device_write(dev, DetectionDataTemp2, &TimeSecByte_2, 1);
			rt_device_write(dev, DetectionDataTemp1, &TimeSecByte_1, 1);
			break;
	}
	rt_device_close(dev);
}

void	F_eeprom_user_cal(rt_uint8_t status,rt_uint8_t Num,rt_uint32_t *cal)
{
	rt_uint8_t	DetectionDataTemp1,DetectionDataTemp2,DetectionDataTemp3;
	rt_uint8_t	TimeSecByte_3,TimeSecByte_2,TimeSecByte_1;
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	
		switch(Num) {
			case	setUser_1_EventVal:
				DetectionDataTemp1 = EE_User1_cal;
				DetectionDataTemp2 = EE_User1_cal + 1;
				DetectionDataTemp3 = EE_User1_cal + 2;
				break;
			case	setUser_2_EventVal:
				DetectionDataTemp1 = EE_User2_cal;
				DetectionDataTemp2 = EE_User2_cal + 1;
				DetectionDataTemp3 = EE_User2_cal + 2;
				break;
			case	setUser_3_EventVal:
				DetectionDataTemp1 = EE_User3_cal;
				DetectionDataTemp2 = EE_User3_cal + 1;
				DetectionDataTemp3 = EE_User3_cal + 2;
				break;
			case	setUser_4_EventVal:
				DetectionDataTemp1 = EE_User4_cal;
				DetectionDataTemp2 = EE_User4_cal + 1;
				DetectionDataTemp3 = EE_User4_cal + 2;
				break;
			case	setUser_5_EventVal:
				DetectionDataTemp1 = EE_User5_cal;
				DetectionDataTemp2 = EE_User5_cal + 1;
				DetectionDataTemp3 = EE_User5_cal + 2;
				break;
			case	setUser_6_EventVal:
				DetectionDataTemp1 = EE_User6_cal;
				DetectionDataTemp2 = EE_User6_cal + 1;
				DetectionDataTemp3 = EE_User6_cal + 2;
				break;
			case	setUser_7_EventVal:
				DetectionDataTemp1 = EE_User7_cal;
				DetectionDataTemp2 = EE_User7_cal + 1;
				DetectionDataTemp3 = EE_User7_cal + 2;
				break;
			case	setUser_8_EventVal:
				DetectionDataTemp1 = EE_User8_cal;
				DetectionDataTemp2 = EE_User8_cal + 1;
				DetectionDataTemp3 = EE_User8_cal + 2;
				break;
			case	setUser_9_EventVal:
				DetectionDataTemp1 = EE_User9_cal;
				DetectionDataTemp2 = EE_User9_cal + 1;
				DetectionDataTemp3 = EE_User9_cal + 2;
				break;
			case	setUser_10_EventVal:
				DetectionDataTemp1 = EE_User10_cal;
				DetectionDataTemp2 = EE_User10_cal + 1;
				DetectionDataTemp3 = EE_User10_cal + 2;
				break;
		}
	switch(status) {
		case	ReadDataVal:
			rt_device_read(dev, DetectionDataTemp3 , &TimeSecByte_3, 1);
			rt_device_read(dev, DetectionDataTemp2 , &TimeSecByte_2, 1);
			rt_device_read(dev, DetectionDataTemp1 , &TimeSecByte_1, 1);
			*cal = (TimeSecByte_3 << 16) + (TimeSecByte_2 << 8) + TimeSecByte_1;
			break;
		//===========
		case	WriteDataVal:
			TimeSecByte_3 = ((*cal & 0x00FF0000) >> 16);
			TimeSecByte_2 = ((*cal & 0x0000FF00) >> 8);
			TimeSecByte_1 = (*cal & 0x000000FF);
			rt_device_write(dev, DetectionDataTemp3, &TimeSecByte_3, 1);
			rt_device_write(dev, DetectionDataTemp2, &TimeSecByte_2, 1);
			rt_device_write(dev, DetectionDataTemp1, &TimeSecByte_1, 1);
			break;
	}
	rt_device_close(dev);
}

void	F_eeprom_user_km(rt_uint8_t status,rt_uint8_t Num,rt_uint16_t *km)
{
	rt_uint8_t	DetectionDataTemp1,DetectionDataTemp2;
	rt_uint8_t	TimeSecByte_2,TimeSecByte_1;
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	
		switch(Num) {
			case	setUser_1_EventVal:
				DetectionDataTemp1 = EE_User1_km;
				DetectionDataTemp2 = EE_User1_km + 1;
				break;
			case	setUser_2_EventVal:
				DetectionDataTemp1 = EE_User2_km;
				DetectionDataTemp2 = EE_User2_km + 1;
				break;
			case	setUser_3_EventVal:
				DetectionDataTemp1 = EE_User3_km;
				DetectionDataTemp2 = EE_User3_km + 1;
				break;
			case	setUser_4_EventVal:
				DetectionDataTemp1 = EE_User4_km;
				DetectionDataTemp2 = EE_User4_km + 1;
				break;
			case	setUser_5_EventVal:
				DetectionDataTemp1 = EE_User5_km;
				DetectionDataTemp2 = EE_User5_km + 1;
				break;
			case	setUser_6_EventVal:
				DetectionDataTemp1 = EE_User6_km;
				DetectionDataTemp2 = EE_User6_km + 1;
				break;
			case	setUser_7_EventVal:
				DetectionDataTemp1 = EE_User7_km;
				DetectionDataTemp2 = EE_User7_km + 1;
				break;
			case	setUser_8_EventVal:
				DetectionDataTemp1 = EE_User8_km;
				DetectionDataTemp2 = EE_User8_km + 1;
				break;
			case	setUser_9_EventVal:
				DetectionDataTemp1 = EE_User9_km;
				DetectionDataTemp2 = EE_User9_km + 1;
				break;
			case	setUser_10_EventVal:
				DetectionDataTemp1 = EE_User10_km;
				DetectionDataTemp2 = EE_User10_km + 1;
				break;
		}
	switch(status) {
		case	ReadDataVal:
			rt_device_read(dev, DetectionDataTemp2 , &TimeSecByte_2, 1);
			rt_device_read(dev, DetectionDataTemp1 , &TimeSecByte_1, 1);
			*km = (TimeSecByte_2 << 8) + TimeSecByte_1;
			break;
		//===========
		case	WriteDataVal:
			TimeSecByte_2 = ((*km & 0xFF00) >> 8);
			TimeSecByte_1 = (*km & 0x00FF);
			rt_device_write(dev, DetectionDataTemp2, &TimeSecByte_2, 1);
			rt_device_write(dev, DetectionDataTemp1, &TimeSecByte_1, 1);
			break;
	}
	rt_device_close(dev);
}

void	F_eeprom_uint(rt_uint8_t status,rt_bool_t *data)
{
	dev = rt_device_find("eeprom");
	rt_device_open(dev , RT_DEVICE_OFLAG_RDWR);
	if(status) {
		rt_device_write(dev, EE_Unit, data, 1);
	} else {
		rt_device_read(dev, EE_Unit , data, 1);
	}
	rt_device_close(dev);
}

