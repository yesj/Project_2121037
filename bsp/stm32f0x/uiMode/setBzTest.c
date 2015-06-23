#include "chandler.h"

static void	F_ChooseBzControl(void)
{
		switch(ui_action.Event) {
			case	BzTest1EventVal:
			bz_short();
				break;
			case	BzTest2EventVal:
			bz_long();
				break;
			case	BzTest3EventVal:
			bz_short3bz();
				break;
		}
}

void F_setBzTest(void)
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
						F_EngineeringModeInit(BeeperTestEventVal);
							break;
						case	enter_KeyVal:
						F_ChooseBzControl();
							break;
						case	resistance_up_KeyVal:
						if(LongKeyStartFlg == 0)	{
							bz_short();
							if(ui_action.Event > BzTest1EventVal)
								ui_action.Event--;
								else
									ui_action.Event = BzTest3EventVal;
						}
							break;
						case	resistance_down_KeyVal:
						if(LongKeyStartFlg == 0)	{
							bz_short();
							ui_action.Event++;
							if(ui_action.Event>BzTest3EventVal)
								ui_action.Event = BzTest1EventVal;
						}
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event) {
						case	BzTest1EventVal:
							F_ShowChooseBz1();
							break;
						case	BzTest2EventVal:
							F_ShowChooseBz2();
							break;
						case	BzTest3EventVal:
							F_ShowChooseBz3();
							break;
					}
					F_Display();
				}
			}
}

void F_setBzTestInit(void)
{
	ui_action.Status = setBzTestVal;
	ui_action.Event = BzTest1EventVal;
}
