//==================================================================
//
//==================================================================
#include "sleeping.h"
#include <rthw.h>
//#include <stm32f0xx.h>
#include "chandler.h"

static struct rt_thread			rt_sleeping_thread;
static rt_uint8_t						sleeping_stack[256];

static void	F_SleepTimerCount(void)
{
	ui_action.SleepTimer++;
	if(ui_action.SleepTimer >= 600) {
		
		F_SysSleepInit();
	}
}

static void sleeping_thread_entry(void* parameter)
{
		rt_uint32_t e;
		while(1)
		{
			if (rt_event_recv(&sport_timer_event, sleep_time_1s_val,
					RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
					RT_WAITING_FOREVER, &e) == RT_EOK)
			{
				if((e & sleep_time_1s_val) == sleep_time_1s_val)
				{
					F_SleepTimerCount();
				}	
			}
		}
}

void  rt_sleeping_init(void)
{
		rt_err_t result;

		result = rt_thread_init(&rt_sleeping_thread,"sleep", sleeping_thread_entry, RT_NULL,
						(rt_uint8_t*)&sleeping_stack[0], sizeof(sleeping_stack),3,2);
		
		if(result == RT_EOK) 
		{
			rt_thread_startup(&rt_sleeping_thread); 
		}
}

