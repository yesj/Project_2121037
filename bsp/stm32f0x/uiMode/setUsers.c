#include "chandler.h"
#include "24lcxx_user.h"

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
					F_SeatPositionControlAllKey(keyCode,LongKeyStartFlg);
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
							}
							break;
						case	resistance_up_KeyVal:
							if(LongKeyStartFlg == 0)	{
								bz_short();
								if(ui_action.Event > setUser_1_EventVal)
									ui_action.Event--;
									else
										ui_action.Event = setUser_10_EventVal;
							}
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					if(ui_action.TemporaryEventFlg == 0) {
						switch(ui_action.Event) {
							case setUser_1_EventVal:
								F_showUsers_1();
								break;
							case setUser_2_EventVal:
								F_showUsers_2();
								break;
							case setUser_3_EventVal:
								F_showUsers_3();
								break;
							case setUser_4_EventVal:
								F_showUsers_4();
								break;
							case setUser_5_EventVal:
								F_showUsers_5();
								break;
							case setUser_6_EventVal:
								F_showUsers_6();
								break;
							case setUser_7_EventVal:
								F_showUsers_7();
								break;
							case setUser_8_EventVal:
								F_showUsers_8();
								break;
							case setUser_9_EventVal:
								F_showUsers_9();
								break;
							case setUser_10_EventVal:
								F_showUsers_10();
								break;
						}
					} else {
						F_showSeatPositionMove();
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
}
