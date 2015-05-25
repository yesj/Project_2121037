#include "chandler.h"
/*
static	void	F_ChooseFocusData(void)
{
	
}
*/

void F_setProfilesFocus(void)
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
					switch(keyCode)
					{
						case	quick_start_KeyVal:
						bz_short();
						ui_action.FocusEventSave = ui_action.Event;
						F_FocusSportInit();
							break;
						case	stop_rest_KeyVal:
						bz_short();
						F_setProfileInit(setFocusEventVal);
							break;
						case	enter_KeyVal:
						bz_short();
						ui_action.FocusEventSave = ui_action.Event;
						F_setProfilesFocusDataInit();
							break;
						case	resistance_up_KeyVal:
						if(LongKeyStartFlg == 0)	{
							bz_short();
							if(ui_action.Event > FocusTotalBodyEventVal)
								ui_action.Event--;
								else
									ui_action.Event = FocusLegsEventVal;
						}
							break;
						case	resistance_down_KeyVal:
						if(LongKeyStartFlg == 0)	{
							bz_short();
							ui_action.Event++;
							if(ui_action.Event>FocusLegsEventVal)
								ui_action.Event = FocusTotalBodyEventVal;
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
							case	FocusTotalBodyEventVal:
								F_ShowChooseTotalBody();
								break;
							case	FocusArmsEventVal:
								F_ShowChooseArms();
								break;
							case	FocusLegsEventVal:
								F_ShowChooseLegs();
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

void F_setProfilesFocusInit(rt_uint8_t Event)
{
	ui_action.Status = setProfilesFocusVal;
	ui_action.Event = Event;
	
}
