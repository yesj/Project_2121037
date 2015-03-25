/*
 * File      : gpio_e.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 
 */

#include "gpio_interrupt.h"
#include <stm32f0xx.h>
#include <rthw.h>

#define SPEED_PIN                   GPIO_Pin_6
#define SPEED_GPIO_PORT             GPIOA
#define SPEED_GPIO_CLK              RCC_AHBPeriph_GPIOA
#define SPEED_EXTI_LINE             EXTI_Line6
#define SPEED_EXTI_PORT_SOURCE      EXTI_PortSourceGPIOA
#define SPEED_EXTI_PIN_SOURCE       EXTI_PinSource6
#define SPEED_EXTI_IRQn             EXTI4_15_IRQn

/*
#define P_FAN_PIN                   GPIO_Pin_7
#define P_FAN_GPIO_PORT             GPIOF
#define P_FAN_GPIO_CLK              RCC_AHBPeriph_GPIOF
*/

/* 定時器的控制塊 */
static rt_timer_t timer_test;
static rt_tick_t timeout_value=1;

void EXTI2_3_IRQHandler(void)
{

	
	
}

void EXTI4_15_IRQHandler(void)
{
    if((EXTI_GetITStatus(SPEED_EXTI_LINE) != RESET)) {
      EXTI_ClearITPendingBit(SPEED_EXTI_LINE);

    }
}


/* 超時時回調的處理函數 */
static void timeout_callbak(void* parameter)
{
	/*
			if(GPIO_ReadOutputDataBit(P_FAN_GPIO_PORT,P_FAN_PIN))
				GPIO_WriteBit(P_FAN_GPIO_PORT,P_FAN_PIN,Bit_RESET);
			else
				GPIO_WriteBit(P_FAN_GPIO_PORT,P_FAN_PIN,Bit_SET);
	*/
    //rt_kprintf("timer time out !\n");
}

/*


*/

/* Initial led gpio pin  */
int	rt_hw_gpio_interrupt_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		/* Enable the BUTTON Clock */
		RCC_AHBPeriphClockCmd(SPEED_GPIO_CLK, ENABLE);
		//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

		/* Configure Button pin as input */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Pin = SPEED_PIN;
		GPIO_Init(SPEED_GPIO_PORT , &GPIO_InitStructure);


    /* Connect Button EXTI Line to Button GPIO Pin */
    SYSCFG_EXTILineConfig(SPEED_EXTI_PORT_SOURCE, SPEED_EXTI_PIN_SOURCE);

    /* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line = SPEED_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    

		//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;						// Chandler
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	// Chandler
		
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = SPEED_EXTI_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
		//==============================
		/*
    RCC_AHBPeriphClockCmd(P_FAN_GPIO_CLK, ENABLE);
    // Configure the FAN pin
    GPIO_InitStructure.GPIO_Pin = P_FAN_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(P_FAN_GPIO_PORT, &GPIO_InitStructure);
	*/
		//==============================
		timer_test = rt_timer_create("timer1",
																	timeout_callbak,
																	RT_NULL,
																	timeout_value,
																	RT_TIMER_FLAG_PERIODIC);
																	
		if(timer_test != RT_NULL) rt_timer_start(timer_test);
		
		return 0;
}

/* Initial components for device */
//INIT_DEVICE_EXPORT(rt_hw_gpio_interrupt_init);
