/*
 * File      : scan_key_led.c
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
 
#include "scan_key_led.h"
#include <stm32f0xx.h>

//static rt_uint8_t key_stack[256];
//static struct rt_thread key_thread;

//KBSense
#define P_KBSense_PIN1                  GPIO_Pin_1
#define P_KBSense_PIN2                  GPIO_Pin_2
#define P_KBSense_PIN3                  GPIO_Pin_3
#define P_KBSense_PIN4                  GPIO_Pin_4
#define P_KBSense_PIN5                  GPIO_Pin_5 
#define P_KBSense_PIN6                  GPIO_Pin_6
#define P_KBSense_GPIO_PORT             GPIOA
#define P_KBSense_GPIO_CLK              RCC_AHBPeriph_GPIOA
//KBScan 
#define P_KBScan_PIN1                   GPIO_Pin_3
#define P_KBScan_PIN2                   GPIO_Pin_4
#define P_KBScan_PIN3                   GPIO_Pin_5
#define P_KBScan_PIN4                   GPIO_Pin_6
#define P_KBScan_PIN5                   GPIO_Pin_7
#define P_KBScan_GPIO_PORT              GPIOB
#define P_KBScan_GPIO_CLK               RCC_AHBPeriph_GPIOB


#define ScanLine1Out(x)		if(x)   GPIO_SetBits(P_KBScan_GPIO_PORT, P_KBScan_PIN1); else  GPIO_ResetBits(P_KBScan_GPIO_PORT, P_KBScan_PIN1);
#define ScanLine2Out(x)		if(x)   GPIO_SetBits(P_KBScan_GPIO_PORT, P_KBScan_PIN2); else  GPIO_ResetBits(P_KBScan_GPIO_PORT, P_KBScan_PIN2);
#define ScanLine3Out(x)		if(x)   GPIO_SetBits(P_KBScan_GPIO_PORT, P_KBScan_PIN3); else  GPIO_ResetBits(P_KBScan_GPIO_PORT, P_KBScan_PIN3);
#define ScanLine4Out(x)		if(x)   GPIO_SetBits(P_KBScan_GPIO_PORT, P_KBScan_PIN4); else  GPIO_ResetBits(P_KBScan_GPIO_PORT, P_KBScan_PIN4);
#define ScanLine5Out(x)		if(x)   GPIO_SetBits(P_KBScan_GPIO_PORT, P_KBScan_PIN5); else  GPIO_ResetBits(P_KBScan_GPIO_PORT, P_KBScan_PIN5);


#define RT_KEY_NUM_1			1
#define RT_KEY_NUM_2			2
#define RT_KEY_NUM_3			3
#define RT_KEY_NUM_4			4
#define RT_KEY_NUM_5			5
#define RT_KEY_NUM_6			6
#define RT_KEY_NUM_7			7
#define RT_KEY_NUM_8			8
#define RT_KEY_NUM_9			9
#define RT_KEY_NUM_10			10
#define RT_KEY_NUM_11			11
#define RT_KEY_NUM_12			12
#define RT_KEY_NUM_13			13
#define RT_KEY_NUM_14			14
#define RT_KEY_NUM_15			15
#define RT_KEY_NUM_16			16
#define RT_KEY_NUM_17			17
#define RT_KEY_NUM_18			18
#define RT_KEY_NUM_19			19
#define RT_KEY_NUM_20			20
#define RT_KEY_NUM_21			21
#define RT_KEY_NUM_22			22
#define RT_KEY_NUM_23			23
#define RT_KEY_NUM_24			24
#define RT_KEY_NUM_25			25

#define RT_KEY_NUM_26			26
#define RT_KEY_NUM_27			27
#define RT_KEY_NUM_28			28
#define RT_KEY_NUM_29			29
#define RT_KEY_NUM_30			30
#define RT_KEY_NUM_31			31
#define RT_KEY_NUM_32			32

#define RT_KEY_NUM_100		100
#define RT_KEY_NUM_101		101
#define RT_KEY_NUM_102		102

#define RT_KEY_NUM_103		103
#define RT_KEY_NUM_104		104
#define RT_KEY_NUM_105		105
#define RT_KEY_NUM_106		106
#define RT_KEY_NUM_107		107
#define RT_KEY_NUM_108		108

/* 定時器的控制塊 */
//static rt_timer_t	key_led_scan_timer;
//static rt_tick_t	timeout_value=2;

//static app_button_handler_t    m_evt_schedule_func;

static rt_uint8_t R_ScanKey[5];
static rt_uint8_t R_LongFastKeyCnt,KeyCnt;
static rt_uint8_t KeyRam,R_NoKeyCnt,KeyRamBak;
static rt_uint8_t KeyCodeSave;
//__IO static rt_uint8_t *KeyCode;
//__IO static rt_uint8_t ledSegData,ledSegDataBuf;
//=====================================================
//	
//=====================================================	
rt_uint8_t F_ReadScanKey(void)
{
  rt_uint16_t ReadkeyData=0;
  ReadkeyData = ~GPIO_ReadInputData(P_KBSense_GPIO_PORT);
	ReadkeyData &= 0x00FF;
	ReadkeyData &= ~(GPIO_Pin_0 + GPIO_Pin_7);
  return (rt_uint8_t)ReadkeyData;       
}
//==========================================================
//
//==========================================================
static void  F_LongFast(void)
{
  if(R_LongFastKeyCnt<200)
    R_LongFastKeyCnt++;
    switch(R_LongFastKeyCnt)
    {
      case 0:
                  
        break;
      //========= 
      case 1:
      KeyCnt=10;	            
        break;
      //=========  
      case 2:
      KeyCnt=10;	     
        break;
      //=========  
      case 3:
      KeyCnt=10;	          
        break;
      //=========  
      case 4:
      KeyCnt=10;	      
        break;
      //========= 
      case 5:
      KeyCnt=10;	         
        break;
      //========= 
      case 6:
      KeyCnt=10;	   
        break;
      //========= 
      case 7:
      KeyCnt=10;	    
        break;
      //========= 
      case 8:
      KeyCnt=10;	 
        break;
      //=========       
      case 9:
      KeyCnt=10;	     
        break;
      //========= 
      case 10:
      KeyCnt=15;	            
        break;
      //=========  
      case 11:
      KeyCnt=15;	     
        break;
      //=========  
      case 12:
      KeyCnt=15;	          
        break;
      //=========  
      case 13:
      KeyCnt=15;	      
        break;
      //========= 
      case 14:
      KeyCnt=15;	         
        break;
      //========= 
      case 15:
      KeyCnt=15;	   
        break;
      //========= 
      case 16:
      KeyCnt=15;	    
        break;
      //========= 
      case 17:
      KeyCnt=15;	 
        break;
      //=========       
      case 18:
      KeyCnt=15;	     
        break;
      //=========  		
      default :
      KeyCnt=19;
        break;
      }
}

static void F_EEDelay(rt_uint32_t us)
{
    rt_uint32_t delta;
    /* 獲得延時經過 tick 數 */
    us = us * (SysTick->LOAD/(1000000/RT_TICK_PER_SECOND));
    /* 獲得當前的時間 */
    delta = SysTick->VAL;
    /* 循環獲得當前的時間，直到達到指定的時間後退出循環 */
    while (delta - SysTick->VAL< us);
}

//===================================================
void	F_ReadKeyCode(rt_uint8_t *KeyCode,rt_bool_t *LongKeyStart,rt_uint16_t *SleepTimer)
{
		rt_uint8_t  i;
	
    KeyRam=0;
		ScanLine1Out(0);
		ScanLine2Out(1);
		ScanLine3Out(1);
		ScanLine4Out(1);
		ScanLine5Out(1);
		F_EEDelay(50);
		R_ScanKey[0] = F_ReadScanKey();
	
		ScanLine1Out(1);
		ScanLine2Out(0);
		ScanLine3Out(1);
		ScanLine4Out(1);
		ScanLine5Out(1);
		F_EEDelay(50);
		R_ScanKey[1] = F_ReadScanKey();
	
		ScanLine1Out(1);
		ScanLine2Out(1);
		ScanLine3Out(0);
		ScanLine4Out(1);
		ScanLine5Out(1);
		F_EEDelay(50);
		R_ScanKey[2] = F_ReadScanKey();
	
		ScanLine1Out(1);
		ScanLine2Out(1);
		ScanLine3Out(1);
		ScanLine4Out(0);
		ScanLine5Out(1);
		F_EEDelay(50);
		R_ScanKey[3] = F_ReadScanKey();
		
		ScanLine1Out(1);
		ScanLine2Out(1);
		ScanLine3Out(1);
		ScanLine4Out(1);
		ScanLine5Out(0);
		F_EEDelay(50);
		R_ScanKey[4] = F_ReadScanKey();

    switch(R_ScanKey[0])
    {
      case 0x00:									break;	
      case 0x02:	KeyRam=RT_KEY_NUM_1;       break;
      case 0x04:	KeyRam=RT_KEY_NUM_2;       break;
      case 0x08:	KeyRam=RT_KEY_NUM_3;       break;
      case 0x10:  KeyRam=RT_KEY_NUM_4;       break;
      case 0x20:  KeyRam=RT_KEY_NUM_5;       break;
      case 0x40:  KeyRam=RT_KEY_NUM_6;       break;
      default :   KeyRam=0;       break;
    }
    switch(R_ScanKey[1])
    {
      case 0x00:									break;
      case 0x02:	KeyRam=RT_KEY_NUM_7;      break;
      case 0x04:	KeyRam=RT_KEY_NUM_8;      break;	
      case 0x08:	KeyRam=RT_KEY_NUM_9;      break;
      case 0x10:	KeyRam=RT_KEY_NUM_10;      break;
      case 0x20:	KeyRam=RT_KEY_NUM_11;      break;
      case 0x40:	KeyRam=RT_KEY_NUM_12;      break;
      default :		KeyRam=0;       break;
    }
    switch(R_ScanKey[2])
    {
    case  0x00:										break;
    case  0x02:		KeyRam=RT_KEY_NUM_13;      break;
    case  0x04:		KeyRam=RT_KEY_NUM_14;      break;
    case  0x08:		KeyRam=RT_KEY_NUM_15;      break;
    case  0x10:		KeyRam=RT_KEY_NUM_16;      break;	
    case  0x20:		KeyRam=RT_KEY_NUM_17;      break;
    case	0x40:		KeyRam=RT_KEY_NUM_18;      break;  
		case  0x18:		KeyRam=RT_KEY_NUM_31;      break;			// 複合鍵
    default :			KeyRam=0;       break;
    }
    switch(R_ScanKey[3])
    {
    case  0x00:										break;
    case  0x02:		KeyRam=RT_KEY_NUM_19;      break;
    case  0x04:		KeyRam=RT_KEY_NUM_20;      break;
    case  0x08:		KeyRam=RT_KEY_NUM_21;      break;
    case  0x10:		KeyRam=RT_KEY_NUM_22;      break;	
    case  0x20:		KeyRam=RT_KEY_NUM_23;      break;
    case	0x40:		KeyRam=RT_KEY_NUM_24;      break;  
    default :			KeyRam=0;       break;
    }
    switch(R_ScanKey[4])
    {
    case  0x00:										break;
    case  0x02:		KeyRam=RT_KEY_NUM_25;      break;
    case  0x04:		KeyRam=RT_KEY_NUM_26;      break;
    case  0x08:		KeyRam=RT_KEY_NUM_27;      break;
    case  0x10:		KeyRam=RT_KEY_NUM_28;      break;	
    case  0x20:		KeyRam=RT_KEY_NUM_29;      break;
    case	0x40:		KeyRam=RT_KEY_NUM_30;      break;  
    default :			KeyRam=0;       break;
    }

		if(R_ScanKey[2] == 0x0C) {
			KeyRam=RT_KEY_NUM_105;
		}
		
		if(R_ScanKey[2] == 0x06) {
			KeyRam=RT_KEY_NUM_107;
		}
		
			for(i=0;i<5;i++)
				R_ScanKey[i]=0;
		
    //==============================
    // 下方為KEY檢查
      if(KeyRam!=0)
      {
        if(KeyRam==KeyRamBak)
        {
          R_NoKeyCnt=0;
          KeyCnt++;
          if(KeyCnt==1)	//Wait Debums
          {
            R_LongFastKeyCnt=0;
						*SleepTimer = 0;
						KeyCodeSave = KeyRam;
            switch(KeyRam)		//short key
            {
              case	RT_KEY_NUM_1:				*KeyCode=RT_KEY_NUM_1;				break;
              case	RT_KEY_NUM_2:				*KeyCode=RT_KEY_NUM_2;				break;
              case	RT_KEY_NUM_3:				*KeyCode=RT_KEY_NUM_3;				break;
              case	RT_KEY_NUM_4:				*KeyCode=RT_KEY_NUM_4;				break;
              case	RT_KEY_NUM_5:				*KeyCode=RT_KEY_NUM_5;				break;
              case	RT_KEY_NUM_6:				*KeyCode=RT_KEY_NUM_6;				break;
              case	RT_KEY_NUM_7:				*KeyCode=RT_KEY_NUM_7;				break;
              case	RT_KEY_NUM_8:				*KeyCode=RT_KEY_NUM_8;				break;
              case	RT_KEY_NUM_9:				*KeyCode=RT_KEY_NUM_9;				break;
              case	RT_KEY_NUM_10:			*KeyCode=RT_KEY_NUM_10;      break;
              case	RT_KEY_NUM_11:      *KeyCode=RT_KEY_NUM_11;      break;
              case	RT_KEY_NUM_12:      *KeyCode=RT_KEY_NUM_12;      break;
              case	RT_KEY_NUM_13:      *KeyCode=RT_KEY_NUM_13;      break;
              case	RT_KEY_NUM_14:      *KeyCode=RT_KEY_NUM_14;      break;
              case	RT_KEY_NUM_15:      *KeyCode=RT_KEY_NUM_15;      break;
              case	RT_KEY_NUM_16:      *KeyCode=RT_KEY_NUM_16;      break;
              case	RT_KEY_NUM_17:      *KeyCode=RT_KEY_NUM_17;      break;
              case	RT_KEY_NUM_18:      *KeyCode=RT_KEY_NUM_18;      break;
              case	RT_KEY_NUM_19:      *KeyCode=RT_KEY_NUM_19;      break;
              case	RT_KEY_NUM_20:      *KeyCode=RT_KEY_NUM_20;      break;
              case	RT_KEY_NUM_21:      *KeyCode=RT_KEY_NUM_21;      break;
              case	RT_KEY_NUM_22:      *KeyCode=RT_KEY_NUM_22;      break;
              case	RT_KEY_NUM_24:      *KeyCode=RT_KEY_NUM_24;      break;
              case	RT_KEY_NUM_25:      *KeyCode=RT_KEY_NUM_25;      break;
              case	RT_KEY_NUM_26:      *KeyCode=RT_KEY_NUM_26;      break;
              case	RT_KEY_NUM_27:      *KeyCode=RT_KEY_NUM_27;      break;
              case	RT_KEY_NUM_28:      *KeyCode=RT_KEY_NUM_28;      break;
              case	RT_KEY_NUM_29:      *KeyCode=RT_KEY_NUM_29;      break;
              case	RT_KEY_NUM_31:      *KeyCode=RT_KEY_NUM_31;      break;
							case	RT_KEY_NUM_105:			*KeyCode=RT_KEY_NUM_105;			break;
							case	RT_KEY_NUM_107:			*KeyCode=RT_KEY_NUM_107;			break;
            }
          }
          //=====================
          if(KeyCnt==20)    //20mS*20=0.4s
          {	
						*LongKeyStart = 1;
            switch(KeyRam)  //long key
            {
              case	RT_KEY_NUM_4:
                *KeyCode=RT_KEY_NUM_4;
                F_LongFast();
                break;
              case	RT_KEY_NUM_10:
                *KeyCode=RT_KEY_NUM_10;
                F_LongFast();
                break;
              case	RT_KEY_NUM_29:
                *KeyCode=RT_KEY_NUM_29;
                F_LongFast();
                break;
              case	RT_KEY_NUM_24:
                *KeyCode=RT_KEY_NUM_24;
                F_LongFast();
                break;
              case	RT_KEY_NUM_1:
                *KeyCode=RT_KEY_NUM_1;
                F_LongFast();
                break;
              case	RT_KEY_NUM_7:
                *KeyCode=RT_KEY_NUM_7;
                F_LongFast();
                break;
            }
          }
          //=====================
          if(KeyCnt==100)    //20mS*100=2s
          {	
            switch(KeyRam)  //long key
            {
              case	RT_KEY_NUM_30:
                *KeyCode = RT_KEY_NUM_101;
                break;
              case	RT_KEY_NUM_23:
                *KeyCode = RT_KEY_NUM_102;
                break;
              case	RT_KEY_NUM_3:
                *KeyCode = RT_KEY_NUM_104;
                break;
              case	RT_KEY_NUM_2:
                *KeyCode = RT_KEY_NUM_106;
                break;
              case	RT_KEY_NUM_14:
								*KeyCode = RT_KEY_NUM_108;
								break;
            }	
						KeyCodeSave = *KeyCode;
					}
          //=====================
          if(KeyCnt>253)
          {
            KeyCnt=253;             //限制數字超過255
          }
					//m_evt_schedule_func(KeyCode);
					//KeyCode=0;
        }
        else
          KeyRamBak=KeyRam;         //備份key
      }		
      else      //no key
      {
        R_NoKeyCnt++;
        if(R_NoKeyCnt>1)
        {
          R_NoKeyCnt=0;
          R_LongFastKeyCnt=0;
          KeyCnt=0;
          KeyRamBak=0;
					switch(KeyCodeSave) {
						case RT_KEY_NUM_4:
						case RT_KEY_NUM_10:
						case RT_KEY_NUM_29:
						case RT_KEY_NUM_24:
						*KeyCode = RT_KEY_NUM_100;
							break;
						case	RT_KEY_NUM_23:
							*KeyCode=RT_KEY_NUM_23;
							break;
						case	RT_KEY_NUM_30:
							*KeyCode=RT_KEY_NUM_30;
							break;
						case	RT_KEY_NUM_3:
							*KeyCode=RT_KEY_NUM_103;
							break;
					}
					KeyCodeSave = 0;
        }
      }
}

/*
static void timeout_callbak(void* parameter)
{
		F_ReadKeyCode();
	
}


void	rt_button_evt_init(app_button_handler_t button_handler)
{
    m_evt_schedule_func = button_handler;
}


static void key_thread_entry(void* parameter)
{
	rt_uint32_t e;
	
	while(1)
	{
		rt_thread_delay(20);
		
		
	}
}
*/

void	rt_hw_key_led_scan_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		//rt_err_t result;
	
		// Input KBSense  on PA3~A7     
		// Enable the KBSense
		RCC_AHBPeriphClockCmd(P_KBSense_GPIO_CLK, ENABLE);
		// Configure the KBSense pin 
		GPIO_InitStructure.GPIO_Pin = P_KBSense_PIN1 +P_KBSense_PIN2 + P_KBSense_PIN3 +P_KBSense_PIN4 + P_KBSense_PIN5 + P_KBSense_PIN6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(P_KBSense_GPIO_PORT, &GPIO_InitStructure);
		
		// Output KBScan
		// Enable the KBScan 
		RCC_AHBPeriphClockCmd(P_KBScan_GPIO_CLK, ENABLE);
		// Configure the KBScan pin 
		GPIO_InitStructure.GPIO_Pin =  P_KBScan_PIN1 + P_KBScan_PIN2 + P_KBScan_PIN3 + P_KBScan_PIN4 + P_KBScan_PIN5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(P_KBScan_GPIO_PORT, &GPIO_InitStructure);

	/*
		key_led_scan_timer = rt_timer_create("key",
																	timeout_callbak,
																	RT_NULL,
																	20,		// timeout_value
																	RT_TIMER_FLAG_PERIODIC);
																		
		if(key_led_scan_timer != RT_NULL) rt_timer_start(key_led_scan_timer);
		
		
		result = rt_thread_init(&key_thread,"key", key_thread_entry, RT_NULL,
						(rt_uint8_t*)&key_stack[0], sizeof(key_stack),20,2);
		
		if(result == RT_EOK)
		{ 
			rt_thread_startup(&bz_thread); 
		}		
		*/
		
}

/* Initial components for device */
//INIT_DEVICE_EXPORT(rt_hw_key_led_scan_init);
