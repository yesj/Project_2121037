#include "chandler.h"
#include "24lcxx_user.h"

static void F_UeserChooseMode(void)
{
	rt_uint8_t	buf;
	
		switch(ui_action.Event) {
			case setUser_1_EventVal:
			F_eeprom_user_DetectionData(0,setUser_1_EventVal,&buf);	
				break;
			case setUser_2_EventVal:
			F_eeprom_user_DetectionData(0,setUser_2_EventVal,&buf);	
				break;
			case setUser_3_EventVal:
			F_eeprom_user_DetectionData(0,setUser_3_EventVal,&buf);	
				break;
			case setUser_4_EventVal:
			F_eeprom_user_DetectionData(0,setUser_4_EventVal,&buf);	
				break;
			case setUser_5_EventVal:
			F_eeprom_user_DetectionData(0,setUser_5_EventVal,&buf);	
				break;
			case setUser_6_EventVal:
			F_eeprom_user_DetectionData(0,setUser_6_EventVal,&buf);	
				break;
			case setUser_7_EventVal:
			F_eeprom_user_DetectionData(0,setUser_7_EventVal,&buf);	
				break;
			case setUser_8_EventVal:
			F_eeprom_user_DetectionData(0,setUser_8_EventVal,&buf);	
				break;
			case setUser_9_EventVal:

				break;
			case setUser_10_EventVal:

				break;
		}
		ui_action.UsersEventSave = ui_action.Event;
		F_setUsersNoDataInit();
		/*
		if(buf) {
			
		} 
		*/
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
					switch(keyCode)
					{
						case	stop_rest_KeyVal:
							bz_short();
							F_setNoramalInit();
						break;
						case	enter_KeyVal:
							bz_short();
							F_UeserChooseMode();
						break;
						case	resistance_down_KeyVal:
							bz_short();
							ui_action.Event++;
							if(ui_action.Event>setUser_10_EventVal)
								ui_action.Event = setUser_1_EventVal;
							break;
						case	resistance_up_KeyVal:
							bz_short();
							if(ui_action.Event > setUser_1_EventVal)
								ui_action.Event--;
								else
									ui_action.Event = setUser_10_EventVal;
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
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
					F_Display();
				}
				//=====================
			}
}

void F_setUsersInit(void)
{
		ui_action.Status = setUsersVal;
		ui_action.Event = setUser_1_EventVal;
}
