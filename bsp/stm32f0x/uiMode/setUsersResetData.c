#include "chandler.h"
#include "24lcxx_user.h"

static void	F_ResetDataEnterKey(void)
{
	rt_uint8_t	buf;

	if(ui_action.Event == showUserResetYesEventVal) {
		buf = 0;	// 清除資料記憶
		F_eeprom_user_DetectionData(WriteDataVal,ui_action.UsersEventSave,&buf);	
	}
}

void F_setUsersResetData(void)
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
						case	short_enter_KeyVal:
						bz_short();
						F_ResetDataEnterKey();
						F_setUsersInit(ui_action.UsersEventSave);
							break;
						case	stop_rest_KeyVal:
						bz_short();
						F_setUsersInit(ui_action.UsersEventSave);
							break;
						case	resistance_up_KeyVal:
						if(LongKeyStartFlg == 0)	{
							bz_short();	
							if(ui_action.Event == showUserResetNoEventVal) {
								ui_action.Event = showUserResetYesEventVal;
							} else {
								ui_action.Event = showUserResetNoEventVal;
							}
						}
							break;
						case	resistance_down_KeyVal:
						if(LongKeyStartFlg == 0)	{
							bz_short();
							if(ui_action.Event == showUserResetNoEventVal) {
								ui_action.Event = showUserResetYesEventVal;
							} else {
								ui_action.Event = showUserResetNoEventVal;
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

void F_setUsersResetDataInit(void)
{
		ui_action.Status = setUsersResetDataVal;
		ui_action.Event = showUserResetNoEventVal;
}
