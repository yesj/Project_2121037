/*
 * File      : bz.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-15     bright       the first version
 */

#include "bz.h"
#include <rthw.h>
#include <stm32f0xx.h>

/*
#define P_BZ_PIN						GPIO_Pin_15
#define P_BZ_GPIO_PORT			GPIOA
#define P_BZ_GPIO_CLK				RCC_AHBPeriph_GPIOA
*/
#define P_BZ_PIN						GPIO_Pin_2
#define P_BZ_GPIO_PORT			GPIOB
#define P_BZ_GPIO_CLK				RCC_AHBPeriph_GPIOB

#define rt_hw_bz_on()   GPIO_SetBits(P_BZ_GPIO_PORT, P_BZ_PIN)
#define rt_hw_bz_off()  GPIO_ResetBits(P_BZ_GPIO_PORT, P_BZ_PIN)

static rt_uint8_t bz_stack[256];
static struct rt_thread bz_thread;
struct rt_event bz_event;


static void bz_thread_entry(void* parameter)
{
	rt_uint32_t e;
	
	while(1)
	{
			if (rt_event_recv(&bz_event, 0x01 | 0x02 | 0x04,
					RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
					RT_WAITING_FOREVER, &e) == RT_EOK)
			//RT_WAITING_NO   RT_WAITING_FOREVER
			{
				//rt_kprintf("bz_event: AND recv event 0x%x\n", e);
				switch(e) 
				{
					case 0x01:
					rt_hw_bz_on();
					rt_thread_delay(500);
					rt_hw_bz_off();
					break;
					case 0x02:
					rt_hw_bz_on();
					rt_thread_delay(40);
					rt_hw_bz_off();
					break;
					case 0x04:
					rt_hw_bz_on();
					rt_thread_delay(40);
					rt_hw_bz_off();
					rt_thread_delay(40);
					rt_hw_bz_on();
					rt_thread_delay(40);
					rt_hw_bz_off();
					break;
				}
			}

			//rt_thread_delay(100);
	}
}


int	rt_hw_bz_init(void)
{
		rt_err_t result;
    GPIO_InitTypeDef  GPIO_InitStructure;
		
    /* Enable the GPIO_LED Clock */
    RCC_AHBPeriphClockCmd(P_BZ_GPIO_CLK, ENABLE);

    /* Configure the GPIO_LED pin */
    GPIO_InitStructure.GPIO_Pin = P_BZ_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(P_BZ_GPIO_PORT, &GPIO_InitStructure);
	
		rt_event_init(&bz_event, "bz_event", RT_IPC_FLAG_FIFO);
	
		result = rt_thread_init(&bz_thread,"bz", bz_thread_entry, RT_NULL,
						(rt_uint8_t*)&bz_stack[0], sizeof(bz_stack),20,2);
		
		if(result == RT_EOK)
		{ 
			rt_thread_startup(&bz_thread); 
		}
		return 0;
}

/* Initial components for device */
INIT_DEVICE_EXPORT(rt_hw_bz_init);
