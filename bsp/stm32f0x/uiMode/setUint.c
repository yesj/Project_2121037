#include "chandler.h"


void F_setUint(void)
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
					switch(keyCode)
					{
						case	stop_rest_KeyVal:
						bz_short();
						F_EngineeringModeInit(UnitEventVal);
							break;
						case	enter_KeyVal:

							break;
						case	resistance_up_KeyVal:
						if(LongKeyStartFlg == 0)	{
							bz_short();
							ui_action.Event++;
							if(ui_action.Event>EnglishEventVal)
								ui_action.Event = MetricEventVal;
						}
							break;
						case	resistance_down_KeyVal:
						if(LongKeyStartFlg == 0)	{
							bz_short();
							if(ui_action.Event > MetricEventVal)
								ui_action.Event--;
								else
									ui_action.Event = EnglishEventVal;
						}
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event) {
						case	MetricEventVal:
							F_ShowChooseMetric();
							break;
						case	EnglishEventVal:
							F_ShowChooseEnglish();
							break;
					}
					F_Display();
				}
			}
}

void F_setUintInit(void)
{
	ui_action.Status = setUintVal;
	ui_action.Event = MetricEventVal;
}
