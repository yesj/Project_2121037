#include "chandler.h"

static	rt_timer_t		sport_timer;
struct rt_event				sport_timer_event;

static rt_uint8_t		time20ms;
static rt_uint8_t		time40ms;
static rt_uint8_t		time100ms;
static rt_uint16_t	time500ms;
static rt_uint16_t	time1s;
static rt_uint16_t	SleepTime1s;

static void sport_time_timeout_callbak(void* parameter)
{
	//rt_event_send(&sport_timer_event, time_10ms);
	rt_uint32_t		temp = 0;
	rt_bool_t			Enterflg = 0;
	
	time20ms++;
	if(time20ms >=2) 
	{
		time20ms = 0;
		Enterflg	=	1;
		temp |= time_20ms_val;
	}
	
	time40ms++;
	if(time40ms >=4) 
	{
		time40ms = 0;
		Enterflg	=	1;
		temp |= time_40ms_val;
	}
	
		time100ms++;
		if(time100ms >=10) 
		{
			time100ms = 0;
			Enterflg	=	1;
			temp |= time_100ms_val;
		}
		
		time500ms++;
		if(time500ms >=50) 
		{
			time500ms = 0;
			Enterflg	=	1;
			temp |= time_500ms_val;
		}
		
			time1s++;
			if(time1s >=100) 
			{
				time1s = 0;
				Enterflg	=	1;
				temp |= time_1s_val;
			}		

		SleepTime1s++;
		if(SleepTime1s >=100) 
		{
			SleepTime1s = 0;
			Enterflg	=	1;
			temp |= sleep_time_1s_val;
		}

	if(Enterflg)
	{		
		rt_event_send(&sport_timer_event, temp);
	}
	
	//F_timer_process_up(&sport_time_data);
	//rt_kprintf("%d : %d\n", sport_time_data.timeH,sport_time_data.timeL);
}

void	F_cleartTimer(void)
{
	//rt_event_init(&sport_timer_event, "timer_event", RT_IPC_FLAG_FIFO);
	time20ms = 0;
	time40ms = 0;
	time100ms = 0;
	time1s = 0;
}

void F_startSportTimerInit(void)
{
	
		rt_event_init(&sport_timer_event, "timer_event", RT_IPC_FLAG_FIFO);
		//rt_event_init(&sleep_timer_event, "timer_event", RT_IPC_FLAG_FIFO);
	
		sport_timer = rt_timer_create("sport_timer",
																	sport_time_timeout_callbak,
																	RT_NULL,
																	10,		// timeout_value
																	RT_TIMER_FLAG_PERIODIC);
	
		if(sport_timer != RT_NULL) rt_timer_start(sport_timer);
}
