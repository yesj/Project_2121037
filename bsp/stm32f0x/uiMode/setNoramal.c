#include "chandler.h"


void F_setNoramal(void)
{
		rt_uint8_t	keyCode = 0;
		rt_bool_t	LongKeyStartFlg = 0;
		rt_uint32_t e;
		static rt_uint32_t	Temp = 1;
	
			if (rt_event_recv(&sport_timer_event, 0xFFFF,
					RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
					RT_WAITING_FOREVER, &e) == RT_EOK)
			{
				if((e & time_20ms_val) == time_20ms_val)
				{
					//rt_kprintf("timer 40ms");
					F_ReadKeyCode(&keyCode,&LongKeyStartFlg);
					if(keyCode != 0 ) 
					{
						rt_kprintf("setNoramalVal:%d\r\n>",keyCode);
					}
					F_SeatPositionControlAllKey(&keyCode,LongKeyStartFlg);
					F_LongRestKey(keyCode);
					F_SetUserKey(keyCode);
					F_SetProgramsKey(keyCode);
					switch(keyCode)
					{
						case	quick_start_KeyVal:
						F_SportNoramalInit();
						bz_short();
						break;
						case	resistance_up_KeyVal:
						Temp = 	Temp << 1;
						rt_kprintf("Temp:%d\r\n",Temp);
						break;
						case	resistance_down_KeyVal:
						Temp = 	Temp >> 1;
						rt_kprintf("Temp:%d\r\n",Temp);
						break;
						case	eng1_KeyVal:
						//F_EngMode1_Init();
						//bz_short();
						break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					if(ui_action.TemporarySeatPositionEvent == TemporarySeatPositionNormalEventVal) {
						F_showNoramal();
					} else {
						F_showSeatPositionStatus(ui_action.TemporarySeatPositionEvent);
					}
					/*
					F_showMatrixProfileWrokOutTime(TimeData);
					F_Menual_LevelCount(20,sport_data.progfileArry,ProgfileDataSizeVal);
					F_ShowProgfileGraph(sport_data.progfileArry,ProgfileDataSizeVal,FlickerModeVal,0,0);
					F_showResistance(sport_data.resistance.number);
					F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
					F_showCal(calor_count.calorie);
					*/
					F_Display();
				}
				//=====================
				if((e & time_1s_val) == time_1s_val)
				{
					F_SwitchingSeatPositionDisplayTimer();
				}
			}
}

void F_setNoramalInit(void)
{
	ui_action.Status = setNoramalVal;
	sport_data.resistance.number = 0;
	F_vms_control(0);
}

