//==================================================================
//
//==================================================================
#include "pwm_vms.h"
//#include "chandler.h"
#include <rthw.h>
#include <stm32f0xx.h>

static struct rt_thread			rt_vms_thread;
static rt_uint8_t		vms_stack[256];

static rt_uint8_t		R_RLevel;
//static rt_uint8_t		R_RLevelBackup;

const rt_uint16_t	T_Leveltables[21]={
  0,  
  22,   80,    124,    165,    206,    251,   290,   337,   381,   431,
  481 , 531,   583,   632,   694,    760,   830,  895,   967,   1032 
};

void	F_vms_control(rt_uint8_t level)
{
	R_RLevel = level;
}

static void vms_thread_entry(void* parameter)
{
		while(1)
		{
			rt_thread_delay(100);
			if(R_RLevel !=0 ) 
			{
				TIM_CtrlPWMOutputs(TIM1, ENABLE);
				TIM1->CCR1 = T_Leveltables[R_RLevel];
			} else {
				TIM_CtrlPWMOutputs(TIM1, DISABLE);
				TIM1->CCR1 = 0 ;
			}
		}
}

void  rt_hw_pwm_vms_init(void)
{
	rt_err_t result;
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  /* GPIOA Clocks enable */
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* GPIOA Configuration: Channel 1 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);
  
  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
  
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Period = 1200;										// 要分幾階在這裡設定  0.05ms(20khz) =>1200階    TimerCLK = 1200 * 20000 =24M 
  TIM_TimeBaseStructure.TIM_Prescaler = 2;										// (48M(SysCLK) / 24M) -1  = 除頻值 = 1
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  
  /* Channel 1, 2, 3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);
  
  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);
  
  /* TIM1 Main Output Enable */
  //TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
		result = rt_thread_init(&rt_vms_thread,"vms", vms_thread_entry, RT_NULL,
						(rt_uint8_t*)&vms_stack[0], sizeof(vms_stack),3,2);
		
		if(result == RT_EOK) 
		{ 
			rt_thread_startup(&rt_vms_thread); 
		}
}

#include <finsh.h>

int vms_level(int argc , char** argv)
{
	if(atoi(argv[1]) <= 21)
	{
		F_vms_control(atoi(argv[1]));
	} else {
		rt_kprintf("level must <= %d\n", 21);
	}
		return 0;
}

MSH_CMD_EXPORT(vms_level, do vms level);
