#include "chandler.h"

static	rt_uint8_t	KeyNumber = 0;

void F_setKeyTest(void)
{
		rt_uint8_t	keyCode = 0;
		rt_bool_t	LongKeyStartFlg = 0;
		rt_uint32_t e;
		rt_bool_t		BzOnFlg;
			if (rt_event_recv(&sport_timer_event, 0xFFFF,
					RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
					RT_WAITING_FOREVER, &e) == RT_EOK)
			{
				if((e & time_20ms_val) == time_20ms_val)
				{
					F_ReadKeyCode(&keyCode,&LongKeyStartFlg,&ui_action.SleepTimer);
					BzOnFlg = 0;
					switch(keyCode) {
						case	engineering_KeyVal:
							BzOnFlg = 1;
							F_EngineeringModeInit(KeypadTestEventVal);
							break;
						case	user_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 1;
							break;
						case	focus_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 2;
							break;
						case	view_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 3;
							break;
						case	programs_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 4;
							break;
						case	seat_position_up_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 5;
							break;
						case	quick_start_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 6;
							break;
						case	resistance_up_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 7;
							break;
						case	seat_position_down_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 8;
							break;
						case	enter_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 9;
							break;
						case	stop_rest_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 10;
							break;
						case	resistance_down_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 11;
							break;
						case	seat_position_home_1_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 12;
							break;
						case	fast_seat_position_up_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 13;
							break;
						case	seat_position_home_2_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 14;
							break;
						case	fast_seat_position_down_KeyVal:
							BzOnFlg = 1;
							KeyNumber = 15;
							break;
					}
						if(BzOnFlg) {
							if(LongKeyStartFlg == 0){
								bz_short();
							}
						}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					F_ShowKeyNum(KeyNumber);
					F_Display();
				}
			}
}

void F_setKeyTestInit(void)
{
	ui_action.Status = setKeyTestVal;
	//ui_action.Event = ;
}
