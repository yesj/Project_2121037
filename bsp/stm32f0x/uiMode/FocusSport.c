#include "chandler.h"

void F_FocusSport(void)
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
						F_setProfilesFocusInit(ui_action.FocusEventSave);
						break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					F_show8Time(TimeData);
					F_showResistance(sport_data.resistance.number);
					F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
					F_ShowHandlesUp();
					F_ShowHandlesDown();
					F_ShowFeetOnPedals();
					F_ShowFeetOnPegs();
					F_Display();
				}
				//=====================
				if((e & time_1s_val) == time_1s_val)
				{
					F_timer_process_down(&TimeData);
					if(TimeData.timeH != 0 || TimeData.timeL != 0) {
						distance_data.rpm = F_readRpm();
						F_VmsDetection(distance_data.rpm,sport_data.resistance.number);
						
					} else {
						F_setProfilesFocusInit(ui_action.FocusEventSave);
					}
				}
			}
}

void F_FocusSportInit(void)
{
		ui_action.Status = FocusSportVal;
	//ui_action.Event = ;
		TimeData.timeH = set_focus_data.FocusWorkoutMinTime.number;
		TimeData.timeL = 0;
		sport_data.resistance.number = 1;
		F_setVmsDetectionVal(30);
}
