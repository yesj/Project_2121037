#include "chandler.h"

static void	F_SetProfilesChooseMode(void)
{
		bz_short();	
		switch(ui_action.Event) {
			case	setProfileEventVal:
			F_setProfileChooseInit(ui_action.ProfileEventSave);
				break;
			case	setManualEventVal:
			F_setProfilesManualInit(showManualFatBurnEventVal);
				break;
			case	setHeartRateEventVal:

				break;
			case	setFocusEventVal:

				break;
			case	setMetsEventVal:

				break;
			}
}

void F_setProfiles(void)
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
					F_SeatPositionControlAllKey(keyCode,LongKeyStartFlg);
					F_SetUserKey(keyCode);
					switch(keyCode)
					{
						case	stop_rest_KeyVal:
							bz_short();
							F_setNoramalInit();
						break;
						case	enter_KeyVal:
							F_SetProfilesChooseMode();
						break;
						case	resistance_up_KeyVal:
							bz_short();
							if(ui_action.Event > setProfileEventVal)
								ui_action.Event--;
								else
									ui_action.Event = setMetsEventVal;
							break;
						case	resistance_down_KeyVal:
							bz_short();
							ui_action.Event++;
							if(ui_action.Event>setMetsEventVal)
								ui_action.Event = setProfileEventVal;
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event) {
						case	setProfileEventVal:
							F_showProfileReverse();
							break;
						case	setManualEventVal:
							F_showManualReverse();
							break;
						case	setHeartRateEventVal:
							F_showHeartReverse();
							break;
						case	setFocusEventVal:
							F_showFocusReverse();
							break;
						case	setMetsEventVal:
							F_showMetsReverse();
							break;
					}
					F_Display();
				}
				//=====================
			}
}

void F_setProfileInit(rt_uint8_t Event)
{
	ui_action.Status = setProfilesVal;
	ui_action.Event = Event;
}

