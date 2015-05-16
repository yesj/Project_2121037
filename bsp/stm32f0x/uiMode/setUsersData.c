#include "chandler.h"
#include "24lcxx_user.h"

static	rt_time_data_t	TimeTest;

static void	F_ResetUserData(void)
{
	rt_uint8_t	buf;

		buf = 0;	// 清除資料記憶
		F_eeprom_user_DetectionData(WriteDataVal,ui_action.UsersEventSave,&buf);	
}

static void	F_setChooseUserKey(rt_uint8_t keyCode,rt_bool_t LongKeyStartFlg)
{
		switch(keyCode) {
			case	quick_start_KeyVal:
				bz_short();
				F_setUsersSportInit();
				break;
			case	stop_rest_KeyVal:
				bz_short();
				F_setUsersInit(ui_action.UsersEventSave);
				break;
			case	resistance_up_KeyVal:
				if(LongKeyStartFlg == 0)	{
					bz_short();
					if(ui_action.Event > showUserStartEventVal) {
						ui_action.Event--;
					} else {
						ui_action.Event = showUserTotalEventVal;
					}
				}
				break;
			case	resistance_down_KeyVal:
				if(LongKeyStartFlg == 0)	{
					bz_short();	
					if(ui_action.Event < showUserTotalEventVal) {
						ui_action.Event++;
					} else {
						ui_action.Event = showUserStartEventVal;
					}
				}
				break;
			}
}

static void	F_setUserStartEnter(rt_uint8_t keyCode)
{
		switch(keyCode) {
			case	enter_KeyVal:
				bz_short();
				F_setUsersSportInit();
				break;	
		}
}

static void	F_setUserSeetingsEnterKey(rt_uint8_t keyCode)
{
		switch(keyCode) {
			case	enter_KeyVal:
				bz_short();

				break;	
		}
}

static void	F_setChooseUserTotalEnterKey(rt_uint8_t keyCode)
{
		switch(keyCode) {
			case	enter_KeyVal:
				bz_short();
				ui_action.Event = showUserDataEventVal;
				break;	
		}
}

static void	F_setUserDataKey(rt_uint8_t keyCode)
{
		switch(keyCode) {
			case	stop_rest_KeyVal:
				bz_short();
				ui_action.Event = showUserTotalEventVal;
				break;	
			case	long_enter_KeyVal:
				bz_short();
				ui_action.Event = showUserResetNoEventVal;
				break;
		}
}

static void	F_setUserResetNoKey(rt_uint8_t keyCode,rt_bool_t LongKeyStartFlg)
{
		switch(keyCode) {
			case	short_enter_KeyVal:
			bz_short();
			ui_action.Event = showUserDataEventVal;
				break;
			case	stop_rest_KeyVal:
			bz_short();
			ui_action.Event = showUserDataEventVal;
				break;
			case	resistance_up_KeyVal:
			case	resistance_down_KeyVal:
			if(LongKeyStartFlg == 0)	{
				bz_short();	
				ui_action.Event = showUserResetYesEventVal;
			}
				break;
		}
}

static void	F_setUserResetYesKey(rt_uint8_t keyCode,rt_bool_t LongKeyStartFlg)
{
		switch(keyCode) {
			case	short_enter_KeyVal:
			bz_short();
			F_ResetUserData();
			F_setUsersInit(ui_action.UsersEventSave);
				break;
			case	stop_rest_KeyVal:
			bz_short();
			ui_action.Event = showUserDataEventVal;
				break;
			case	resistance_up_KeyVal:
			case	resistance_down_KeyVal:
			if(LongKeyStartFlg == 0)	{
				bz_short();	
				ui_action.Event = showUserResetNoEventVal;
			}
				break;
		}
}

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
					switch(ui_action.Event) {
						case showUserStartEventVal:
						F_setChooseUserKey(keyCode,LongKeyStartFlg);
						F_setUserStartEnter(keyCode);
							break;	
						case showUserSeetingsEventVal:
						F_setChooseUserKey(keyCode,LongKeyStartFlg);
						F_setUserSeetingsEnterKey(keyCode);
							break;
						case showUserTotalEventVal:
						F_setChooseUserKey(keyCode,LongKeyStartFlg);
						F_setChooseUserTotalEnterKey(keyCode);
							break;
						case showUserDataEventVal:
						F_setUserDataKey(keyCode);
							break;
						case	showUserResetNoEventVal:
						F_setUserResetNoKey(keyCode,LongKeyStartFlg);
							break;
						case	showUserResetYesEventVal:
						F_setUserResetYesKey(keyCode,LongKeyStartFlg);
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event) {
						//case showUserNameEventVal:
						//	F_showUserName(set_user_data.UserNaume,10);
						//	break;
						case showUserStartEventVal:
							F_ShowStartReverse();
							break;
						case showUserSeetingsEventVal:
							F_ShowSettingsReverse();
							break;
						case showUserTotalEventVal:
							F_ShowUserTotalReverse();
							break;
						case showUserDataEventVal:
							F_showTimeMilesCal(TimeTest,set_user_data.SportCal,set_user_data.SportKm);
							break;
						case	showUserResetNoEventVal:
						F_showResetDataNo();	
							break;
						case	showUserResetYesEventVal:
						F_showResetDataYes();
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
		ui_action.Event = showUserStartEventVal;
		F_eeprom_user_name(ReadDataVal,ui_action.UsersEventSave,set_user_data.UserNaume,0);
		F_eeprom_user_time(ReadDataVal,ui_action.UsersEventSave,&set_user_data.SportTimeSec);
		F_eeprom_user_cal(ReadDataVal,ui_action.UsersEventSave,&set_user_data.SportCal);
		F_eeprom_user_km(ReadDataVal,ui_action.UsersEventSave,&set_user_data.SportKm);
		TempMin =  set_user_data.SportTimeSec / 60;
		TimeTest.timeH = (TempMin / 60);
		TimeTest.timeL = (TempMin % 60);
}
