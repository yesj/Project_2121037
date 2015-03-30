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
					F_SeatPositionControlAllKey(keyCode,LongKeyStartFlg);
					F_SetUserKey(keyCode);
					switch(keyCode)
					{
						case	quick_start_KeyVal:
						F_SportManualInit();
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
						F_EngMode1_Init();
						bz_short();
						break;
						case	programs_KeyVal:
						F_setProfileInit();
						bz_short();
						break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					F_showNoramal();
					//LCDBuffer[63] = Temp; 
					F_Display();
				}
				//=====================
			}
}

void F_setNoramalInit(void)
{
	ui_action.Status = setNoramalVal;
	sport_data.resistance.number = 0;
	F_vms_control(sport_data.resistance.number);
}

