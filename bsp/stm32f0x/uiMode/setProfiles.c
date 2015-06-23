#include "chandler.h"

static void	F_SetProfilesChooseMode(void)
{
		bz_short();	
		switch(ui_action.Event) {
			case	setProfileEventVal:
			F_setProfileChooseInit(ui_action.ProfileEventSave);
				break;
			case	setManualEventVal:
			F_setProfileManualInit();
				break;
			case	setHeartRateEventVal:
			F_setProfilesHeartRateInit(showHeartRateFatBurnEventVal);			
				break;
			case	setFocusEventVal:
			F_setProfilesFocusInit(FocusTotalBodyEventVal);
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
					F_ReadKeyCode(&keyCode,&LongKeyStartFlg,&ui_action.SleepTimer);
					F_LongRestKey(keyCode);
					F_SeatPositionControlAllKey(&keyCode,LongKeyStartFlg);
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
						if(LongKeyStartFlg == 0)	{
							bz_short();
							if(ui_action.Event > setProfileEventVal)
								ui_action.Event--;
								else
									ui_action.Event = setFocusEventVal;
							}
							break;
						case	resistance_down_KeyVal:
						if(LongKeyStartFlg == 0)	{
							bz_short();
							ui_action.Event++;
							if(ui_action.Event>setFocusEventVal)
								ui_action.Event = setProfileEventVal;
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
								//F_showMetsReverse();
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

void F_setProfileInit(rt_uint8_t Event)
{
	ui_action.Status = setProfilesVal;
	ui_action.Event = Event;
}

