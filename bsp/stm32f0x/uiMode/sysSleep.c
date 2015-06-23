#include "chandler.h"
#include "24lcxx_user.h"
#include "led.h"

void F_SysSleep(void)
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
					//rt_kprintf("timer 40ms");
					F_ReadKeyCode(&keyCode,&LongKeyStartFlg,&ui_action.SleepTimer);	
					if(keyCode != 0 ) 
					{
							IWDG_Config(0);	
							while(1);
					}
				}
				if((e & time_1s_val) == time_1s_val)
				{
					F_SetDisplayRam(0);
					F_Display();
				}
			}
}

void	F_SysSleepInit(void)
{
	ui_action.Status = sleepVal;
	rt_hw_led_off();
	F_SetDisplayRam(0);
	F_Display();
}
