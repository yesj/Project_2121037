#include "chandler.h"


void F_SysUiStart(void)
{
		rt_uint8_t	keyCode = 0;
		rt_bool_t	LongKeyStartFlg = 0;
		rt_uint32_t e;
		static rt_uint8_t	TimeTemp = 0;
	
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
						rt_kprintf(" sysUiStartVal:%d \r\n",keyCode);
					}
				}
				if((e & time_1s_val) == time_1s_val)
				{
					F_SetDisplayRam(1);
					F_Display();
					TimeTemp++;
					if(TimeTemp > 2)
					{
						TimeTemp = 0;
						F_setNoramalInit();
					}
					//rt_event_detach(&sport_timer_event);
					//F_cleartTimer();
				}
			}
}

