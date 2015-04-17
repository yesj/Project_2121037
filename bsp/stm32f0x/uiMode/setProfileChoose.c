#include "chandler.h"

static void	F_SetProfileChooseMode(void)
{
		switch(ui_action.Event) 
		{
			case	setRollingHillEventVal:
			F_setProfileRollingHillInit();
				break;
			case	setPeakEventVal:
			F_setProfilePeakInit();
				break;
			case	setPlateauEventVal:
			F_setProfilePlateauInit();
				break;
			case	setClimbEventVal:
			F_setProfileClimbInit();
				break;
			case	setInterval_1_EventVal:
			F_setProfileInterval_1Init();
				break;
			case	setInterval_2_EventVal:
			F_setProfileInterval_2Init();
				break;
		}
}

void F_setProfileChoose(void)
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
					F_SetUserKey(keyCode);
					switch(keyCode)
					{
						case	quick_start_KeyVal:
							bz_short();
							F_ProfileSportInit(ui_action.Event);
							break;
						case	enter_KeyVal:
							bz_short();
							F_SetProfileChooseMode();
							break;
						case	stop_rest_KeyVal:
							bz_short();
							ui_action.ProfileEventSave = ui_action.Event;
							F_setProfileInit(setProfileEventVal);
							break;
						case	resistance_up_KeyVal:
							bz_short();
							ui_action.Event++;
							if(ui_action.Event>setInterval_2_EventVal)
								ui_action.Event = setRollingHillEventVal;
							break;
						case	resistance_down_KeyVal:
							bz_short();
							if(ui_action.Event > setRollingHillEventVal)
								ui_action.Event--;
								else
									ui_action.Event = setInterval_2_EventVal;
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event) 
					{
						case	setRollingHillEventVal:
							F_showRollingHillGraph();
							break;
						case	setPeakEventVal:
							F_showPeakGraph();
							break;
						case	setPlateauEventVal:
							F_showPlateauGraph();
							break;
						case	setClimbEventVal:
							F_showClimbGraph();
							break;
						case	setInterval_1_EventVal:
							F_showInterval_1_Graph();
							break;
						case	setInterval_2_EventVal:
							F_showInterval_2_Graph();
							break;
					}
					F_Display();
				}
				//=====================
			}
}

void F_setProfileChooseInit(rt_uint8_t Event)
{
	ui_action.Status = setProfileChooseVal;
	ui_action.Event = Event;
}

