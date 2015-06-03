#include "chandler.h"
#include "24lcxx_user.h"

static rt_user_name_data_t	user_name_data;

static	void	F_ReadUser_1_Name(void)
{
	rt_uint8_t	buf;
	F_eeprom_user_DetectionData(ReadDataVal,setUser_1_EventVal,&buf);	
	if(buf) {
		F_eeprom_user_name(ReadDataVal,setUser_1_EventVal,user_name_data.user_1.UserName,0);
		user_name_data.user_1.User_DetectionFlg = 1;
	} else {
		user_name_data.user_1.User_DetectionFlg = 0;
	}
}

static	void	F_ReadUser_2_Name(void)
{
	rt_uint8_t	buf;
	F_eeprom_user_DetectionData(ReadDataVal,setUser_2_EventVal,&buf);	
	if(buf) {
		F_eeprom_user_name(ReadDataVal,setUser_2_EventVal,user_name_data.user_2.UserName,0);
		user_name_data.user_2.User_DetectionFlg = 1;
	} else {
		user_name_data.user_2.User_DetectionFlg = 0;
	}
}

static	void	F_ReadUser_3_Name(void)
{
	rt_uint8_t	buf;
	F_eeprom_user_DetectionData(ReadDataVal,setUser_3_EventVal,&buf);	
	if(buf) {
		F_eeprom_user_name(ReadDataVal,setUser_3_EventVal,user_name_data.user_3.UserName,0);
		user_name_data.user_3.User_DetectionFlg = 1;
	} else {
		user_name_data.user_3.User_DetectionFlg = 0;
	}
}

static	void	F_ReadUser_4_Name(void)
{
	rt_uint8_t	buf;
	F_eeprom_user_DetectionData(ReadDataVal,setUser_4_EventVal,&buf);	
	if(buf) {
		F_eeprom_user_name(ReadDataVal,setUser_4_EventVal,user_name_data.user_4.UserName,0);
		user_name_data.user_4.User_DetectionFlg = 1;
	} else {
		user_name_data.user_4.User_DetectionFlg = 0;
	}
}

static	void	F_ReadUser_5_Name(void)
{
	rt_uint8_t	buf;
	F_eeprom_user_DetectionData(ReadDataVal,setUser_5_EventVal,&buf);	
	if(buf) {
		F_eeprom_user_name(ReadDataVal,setUser_5_EventVal,user_name_data.user_5.UserName,0);
		user_name_data.user_5.User_DetectionFlg = 1;
	} else {
		user_name_data.user_5.User_DetectionFlg = 0;
	}
}

static	void	F_ReadUser_6_Name(void)
{
	rt_uint8_t	buf;
	F_eeprom_user_DetectionData(ReadDataVal,setUser_6_EventVal,&buf);	
	if(buf) {
		F_eeprom_user_name(ReadDataVal,setUser_6_EventVal,user_name_data.user_6.UserName,0);
		user_name_data.user_6.User_DetectionFlg = 1;
	} else {
		user_name_data.user_6.User_DetectionFlg = 0;
	}
}

static	void	F_ReadUser_7_Name(void)
{
	rt_uint8_t	buf;
	F_eeprom_user_DetectionData(ReadDataVal,setUser_7_EventVal,&buf);	
	if(buf) {
		F_eeprom_user_name(ReadDataVal,setUser_7_EventVal,user_name_data.user_7.UserName,0);
		user_name_data.user_7.User_DetectionFlg = 1;
	} else {
		user_name_data.user_7.User_DetectionFlg = 0;
	}
}

static	void	F_ReadUser_8_Name(void)
{
	rt_uint8_t	buf;
	F_eeprom_user_DetectionData(ReadDataVal,setUser_8_EventVal,&buf);	
	if(buf) {
		F_eeprom_user_name(ReadDataVal,setUser_8_EventVal,user_name_data.user_8.UserName,0);
		user_name_data.user_8.User_DetectionFlg = 1;
	} else {
		user_name_data.user_8.User_DetectionFlg = 0;
	}
}

static	void	F_ReadUser_9_Name(void)
{
	rt_uint8_t	buf;
	F_eeprom_user_DetectionData(ReadDataVal,setUser_9_EventVal,&buf);	
	if(buf) {
		F_eeprom_user_name(ReadDataVal,setUser_9_EventVal,user_name_data.user_9.UserName,0);
		user_name_data.user_9.User_DetectionFlg = 1;
	} else {
		user_name_data.user_9.User_DetectionFlg = 0;
	}
}

static	void	F_ReadUser_10_Name(void)
{
	rt_uint8_t	buf;
	F_eeprom_user_DetectionData(ReadDataVal,setUser_10_EventVal,&buf);	
	if(buf) {
		F_eeprom_user_name(ReadDataVal,setUser_10_EventVal,user_name_data.user_10.UserName,0);
		user_name_data.user_10.User_DetectionFlg = 1;
	} else {
		user_name_data.user_10.User_DetectionFlg = 0;
	}
}

static	void	F_ReadUserName(rt_uint8_t Event)
{
		switch(Event) {
			case setUser_1_EventVal:
			case setUser_2_EventVal:
			case setUser_3_EventVal:
			F_ReadUser_1_Name();
			F_ReadUser_2_Name();
			F_ReadUser_3_Name();
				break;
			case setUser_4_EventVal:
			F_ReadUser_2_Name();
			F_ReadUser_3_Name();
			F_ReadUser_4_Name();
				break;
			case setUser_5_EventVal:
			F_ReadUser_3_Name();
			F_ReadUser_4_Name();
			F_ReadUser_5_Name();
				break;
			case setUser_6_EventVal:
			F_ReadUser_4_Name();
			F_ReadUser_5_Name();
			F_ReadUser_6_Name();
				break;
			case setUser_7_EventVal:
			F_ReadUser_5_Name();
			F_ReadUser_6_Name();
			F_ReadUser_7_Name();
				break;
			case setUser_8_EventVal:
			F_ReadUser_6_Name();
			F_ReadUser_7_Name();
			F_ReadUser_8_Name();
				break;
			case setUser_9_EventVal:
			F_ReadUser_7_Name();
			F_ReadUser_8_Name();
			F_ReadUser_9_Name();
				break;
			case setUser_10_EventVal:
			F_ReadUser_8_Name();
			F_ReadUser_9_Name();
			F_ReadUser_10_Name();
				break;
		}
}

static void F_UeserEnterKeyChooseMode(void)
{
		rt_uint8_t	buf;
		F_eeprom_user_DetectionData(ReadDataVal,ui_action.Event,&buf);	
		ui_action.UsersEventSave = ui_action.Event;
		if(buf) {
			F_setUsersDataInit(showUserStartEventVal);
		} else {
			buf = 1;
			F_eeprom_user_DetectionData(WriteDataVal,ui_action.Event,&buf);	
			F_setUsersNoDataInit();
		}
}

static void F_UeserStartKeyChooseMode(void)
{
		rt_uint8_t	buf;
		F_eeprom_user_DetectionData(ReadDataVal,ui_action.Event,&buf);	
		ui_action.UsersEventSave = ui_action.Event;
		if(buf) {
			F_setUsersSportInit();
		} else {
			buf = 1;
			F_eeprom_user_DetectionData(WriteDataVal,ui_action.Event,&buf);	
			F_setUsersNoDataInit();
		}					
}

void F_setUsers(void)
{
		rt_uint8_t	keyCode = 0;
		rt_bool_t	LongKeyStartFlg = 0;
		rt_uint32_t e;
	
			if (rt_event_recv(&sport_timer_event, 0xFFFF,
					RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
					RT_WAITING_FOREVER, &e) == RT_EOK)
			{
				if((e & time_20ms_val) == time_20ms_val)
				{
					F_ReadKeyCode(&keyCode,&LongKeyStartFlg);
					F_LongRestKey(keyCode);
					F_SeatPositionControlAllKey(&keyCode,LongKeyStartFlg);
					F_SetProgramsKey(keyCode);
					switch(keyCode)
					{
						case	quick_start_KeyVal:
							bz_short();
							F_UeserStartKeyChooseMode();
						break;
						case	stop_rest_KeyVal:
							bz_short();
							F_setNoramalInit();
						break;
						case	enter_KeyVal:
							bz_short();
							F_UeserEnterKeyChooseMode();
						break;
						case	resistance_down_KeyVal:
							if(LongKeyStartFlg == 0)	{
								bz_short();
								ui_action.Event++;
								if(ui_action.Event>setUser_10_EventVal)
									ui_action.Event = setUser_1_EventVal;
								F_ReadUserName(ui_action.Event);
							}
							break;
						case	resistance_up_KeyVal:
							if(LongKeyStartFlg == 0)	{
								bz_short();
								if(ui_action.Event > setUser_1_EventVal)
									ui_action.Event--;
									else
										ui_action.Event = setUser_10_EventVal;
								F_ReadUserName(ui_action.Event);
							}
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					if(ui_action.TemporarySeatPositionEvent == TemporarySeatPositionNormalEventVal) {
						switch(ui_action.Event) {
							case setUser_1_EventVal:
								F_showUsers_1(user_name_data.user_1,user_name_data.user_2,user_name_data.user_3);
								break;
							case setUser_2_EventVal:
								F_showUsers_2(user_name_data.user_1,user_name_data.user_2,user_name_data.user_3);
								break;
							case setUser_3_EventVal:
								F_showUsers_3(user_name_data.user_1,user_name_data.user_2,user_name_data.user_3);
								break;
							case setUser_4_EventVal:
								F_showUsers_4(user_name_data.user_2,user_name_data.user_3,user_name_data.user_4);
								break;
							case setUser_5_EventVal:
								F_showUsers_5(user_name_data.user_3,user_name_data.user_4,user_name_data.user_5);
								break;
							case setUser_6_EventVal:
								F_showUsers_6(user_name_data.user_4,user_name_data.user_5,user_name_data.user_6);
								break;
							case setUser_7_EventVal:
								F_showUsers_7(user_name_data.user_5,user_name_data.user_6,user_name_data.user_7);
								break;
							case setUser_8_EventVal:
								F_showUsers_8(user_name_data.user_6,user_name_data.user_7,user_name_data.user_8);
								break;
							case setUser_9_EventVal:
								F_showUsers_9(user_name_data.user_7,user_name_data.user_8,user_name_data.user_9);
								break;
							case setUser_10_EventVal:
								F_showUsers_10(user_name_data.user_8,user_name_data.user_9,user_name_data.user_10);
								break;
						}
					} else {
						F_showSeatPositionStatus(ui_action.TemporarySeatPositionEvent);
					}
					F_Display();
				}
				//=====================
				if((e & time_1s_val) == time_1s_val)
				{
					F_SwitchingSeatPositionDisplayTimer();
				}
			}
}

void F_setUsersInit(rt_uint8_t UserEvent)
{
		ui_action.Status = setUsersVal;
		ui_action.Event = UserEvent;
		F_ReadUserName(ui_action.Event);
}
