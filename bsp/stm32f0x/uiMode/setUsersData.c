#include "chandler.h"
#include "24lcxx_user.h"

static	rt_time_data_t	TimeTest;

void F_setUsersData(void)
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
					switch(keyCode) {
						case	stop_rest_KeyVal:
						bz_short();
						F_setUsersInit(ui_action.UsersEventSave);
							break;
						case	resistance_up_KeyVal:
						if(LongKeyStartFlg == 0)	{
							bz_short();	
							if(ui_action.Event < showUserDataEventVal) {
								ui_action.Event++;
							} else {
								ui_action.Event = showUserNameEventVal;
							}
						}
							break;
						case	resistance_down_KeyVal:
						if(LongKeyStartFlg == 0)	{
							bz_short();
							if(ui_action.Event > showUserNameEventVal) {
								ui_action.Event--;
							} else {
								ui_action.Event = showUserDataEventVal;
							}
						}
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event) {
						case showUserNameEventVal:
							F_showUserName(set_user_data.UserNaume,10);
							break;
						case showUserDataEventVal:
							F_showTimeMilesCal(TimeTest,set_user_data.SportCal,set_user_data.SportKm);
							break;
					}
					F_Display();
				}
				//=====================
			}
}

void F_setUsersDataInit(void)
{
	rt_uint16_t	TempMin;
		ui_action.Status = setUsersDataVal;
		ui_action.Event = showUserNameEventVal;
		F_eeprom_user_name(ReadDataVal,ui_action.UsersEventSave,set_user_data.UserNaume,0);
		F_eeprom_user_time(ReadDataVal,ui_action.UsersEventSave,&set_user_data.SportTimeSec);
		F_eeprom_user_cal(ReadDataVal,ui_action.UsersEventSave,&set_user_data.SportCal);
		F_eeprom_user_km(ReadDataVal,ui_action.UsersEventSave,&set_user_data.SportKm);
		TempMin =  set_user_data.SportTimeSec / 60;
		TimeTest.timeH = (TempMin / 60);
		TimeTest.timeL = (TempMin % 60);
}
