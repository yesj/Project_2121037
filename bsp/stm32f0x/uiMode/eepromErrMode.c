#include "chandler.h"


void F_eepromErrMode(void)
{
		rt_uint32_t e;
	
			if (rt_event_recv(&sport_timer_event, 0xFFFF,
					RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
					RT_WAITING_FOREVER, &e) == RT_EOK)
			{
				if((e & time_20ms_val) == time_20ms_val)
				{
					
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					F_ShowEepromErr();
					F_Display();
				}
			}
}

void F_eepromErrModeInit(void)
{
	ui_action.Status = eepromErrVal;
	//ui_action.Event = ;
}
