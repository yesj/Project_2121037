/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <board.h>
#include <rtthread.h>
#ifdef  RT_USING_COMPONENTS_INIT
#include <components.h>
#endif  /* RT_USING_COMPONENTS_INIT */
//#include <rtdevice.h>

#include "led.h"
#include "cpuusage.h"

//#include "speed_control.h"
#include "i2c_device.h"
#include "Incline.h"
#include "heart.h"
#include "24lcxx_user.h"
#include "pwm_vms.h"


static struct rt_thread control_thread;
static rt_uint8_t control_stack[512];

static	rt_incline_eeprom_data_t	incline_eeprom_data;

rt_ui_action_t	ui_action;

rt_time_data_t TimeData;

rt_sport_data_t	sport_data;

rt_calor_data_t calor_count;

rt_distance_data_t	distance_data;

rt_set_profile_data_t set_profile_data;

rt_user_data_t	set_user_data;

rt_set_manual_data_t	set_manual_data;
//==============================================================================
void IWDG_Config(unsigned char timeout)
{
  /* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
  dispersion) */
  /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  
  /* IWDG counter clock: LSI/32 */
  //IWDG_SetPrescaler(IWDG_Prescaler_32);
  /* IWDG counter clock: LSI/256 */
  IWDG_SetPrescaler(IWDG_Prescaler_256);
  
  /* Set counter reload value to obtain 250ms IWDG TimeOut.
  Counter Reload Value = 250ms/IWDG counter clock period
  = 250ms / (LSI/32)
  = 0.25s / (LsiFreq/32)
  = LsiFreq/(32 * 4)
  = LsiFreq/128
  */
  // IWDG_SetReload(LsiFreq/128);
  
  IWDG_SetReload(timeout);
  
  /* Reload IWDG counter */
  IWDG_ReloadCounter();
  
  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();
}
//====================================================
static void err_message_evt(rt_uint8_t message)
{
	rt_kprintf("Err : %d \n>" ,message);
	//rt_speed_control_start(0);
	switch(message)
	{
		case	InclineAutoOkNumVal:
		rt_read_incline_eeprom_data(&incline_eeprom_data);
		F_eeprom_incline_data(1,&incline_eeprom_data);	//	write
		if(ui_action.Status == eng1Val)
		{
			F_EngMode1_AutoOk();
		}
			break;
		case	InclineAutoErrNumVal:
		if(ui_action.Status == eng1Val)
		{
			F_EngMode1_AutoErr();
		}
			break;
	}
}

static void	incline_control_init(rt_incline_eeprom_data_t eeprom_data)
{
	rt_inc_init_data_t incline_data;
	eeprom_data.incMaxNum = InclineMaxAdrVal;
	incline_data.incNum = 0;
	incline_data.incline_eeprom_data = eeprom_data;
	incline_data.err_treadmill_handler = err_message_evt;
	rt_hw_incline_control_init(incline_data);
}

static	void	F_InitSportParameters(void)
{
	sport_data.resistance.maxNumber = 20;
	sport_data.resistance.minNumber	= 1;
	
	sport_data.seatPosition.maxNumber = InclineMaxAdrVal;
	sport_data.seatPosition.minNumber = 0;
	sport_data.seatPosition.number = 0;
}

static	void	F_InitSetProfileData(void)
{
	set_profile_data.roolingHillLevel.number = 7;
	set_profile_data.roolingHillLevel.maxNumber = 20;
	set_profile_data.roolingHillLevel.minNumber = 1;
	
	set_profile_data.roolingHillWorkoutMinTime.number = workOutTimeMinuteNumVal;
	set_profile_data.roolingHillWorkoutMinTime.maxNumber = workOutTimeMinuteNumMaxVal;
	set_profile_data.roolingHillWorkoutMinTime.minNumber = workOutTimeMinuteNumMinVal;
	
	set_profile_data.peakLevel.number = 7;
	set_profile_data.peakLevel.maxNumber = 20;
	set_profile_data.peakLevel.minNumber = 1;
	
	set_profile_data.peakWorkoutMinTime.number = workOutTimeMinuteNumVal;
	set_profile_data.peakWorkoutMinTime.maxNumber = workOutTimeMinuteNumMaxVal;
	set_profile_data.peakWorkoutMinTime.minNumber = workOutTimeMinuteNumMinVal;
	
	set_profile_data.plateauLevel.number = 7;
	set_profile_data.plateauLevel.maxNumber = 20;
	set_profile_data.plateauLevel.minNumber = 1;
	
	set_profile_data.plateauWorkoutMinTime.number = workOutTimeMinuteNumVal;
	set_profile_data.plateauWorkoutMinTime.maxNumber = workOutTimeMinuteNumMaxVal;
	set_profile_data.plateauWorkoutMinTime.minNumber = workOutTimeMinuteNumMinVal;
	
	set_profile_data.climbLevel.number = 7;
	set_profile_data.climbLevel.maxNumber = 20;
	set_profile_data.climbLevel.minNumber = 1;
	
	set_profile_data.climbWorkoutMinTime.number = workOutTimeMinuteNumVal;
	set_profile_data.climbWorkoutMinTime.maxNumber = workOutTimeMinuteNumMaxVal;
	set_profile_data.climbWorkoutMinTime.minNumber = workOutTimeMinuteNumMinVal;
	
	set_profile_data.interval_1_Level.number = 7;
	set_profile_data.interval_1_Level.maxNumber = 20;
	set_profile_data.interval_1_Level.minNumber = 1;
	
	set_profile_data.interval_1_WorkoutMinTime.number = workOutTimeMinuteNumVal;
	set_profile_data.interval_1_WorkoutMinTime.maxNumber = workOutTimeMinuteNumMaxVal;
	set_profile_data.interval_1_WorkoutMinTime.minNumber = workOutTimeMinuteNumMinVal;
	
	set_profile_data.interval_2_Level.number = 7;
	set_profile_data.interval_2_Level.maxNumber = 20;
	set_profile_data.interval_2_Level.minNumber = 1;
	
	set_profile_data.interval_2_WorkoutMinTime.number = workOutTimeMinuteNumVal;
	set_profile_data.interval_2_WorkoutMinTime.maxNumber = workOutTimeMinuteNumMaxVal;
	set_profile_data.interval_2_WorkoutMinTime.minNumber = workOutTimeMinuteNumMinVal;
}

static	void	F_InitManualData(void)
{
		set_manual_data.FatBurnAge.maxNumber = ageNumMaxVal;
		set_manual_data.FatBurnAge.minNumber = ageNumMinVal;
		set_manual_data.FatBurnAge.number = ageNumVal;
	
		set_manual_data.CardioAge.maxNumber = ageNumMaxVal;
		set_manual_data.CardioAge.minNumber = ageNumMinVal;
		set_manual_data.CardioAge.number = ageNumVal;

		set_manual_data.TargetTarget.maxNumber = 220;
		set_manual_data.TargetTarget.minNumber = 40;
		set_manual_data.TargetTarget.number = 120;
	
		set_manual_data.FatBurnWorkoutMinTime.number = workOutTimeMinuteNumVal;
		set_manual_data.FatBurnWorkoutMinTime.maxNumber = workOutTimeMinuteNumMaxVal;
		set_manual_data.FatBurnWorkoutMinTime.minNumber = workOutTimeMinuteNumMinVal;
	
		set_manual_data.CardioWorkoutMinTime.number = workOutTimeMinuteNumVal;
		set_manual_data.CardioWorkoutMinTime.maxNumber = workOutTimeMinuteNumMaxVal;
		set_manual_data.CardioWorkoutMinTime.minNumber = workOutTimeMinuteNumMinVal;

		set_manual_data.TargetWorkoutMinTime.number = workOutTimeMinuteNumVal;
		set_manual_data.TargetWorkoutMinTime.maxNumber = workOutTimeMinuteNumMaxVal;
		set_manual_data.TargetWorkoutMinTime.minNumber = workOutTimeMinuteNumMinVal;
}
static	void	F_InitSetProfileEvent(void)
{
	
	ui_action.ProfileEventSave = setRollingHillEventVal;
	
}

static void rt_control_thread_entry(void* parameter)
{
    volatile rt_uint32_t count=0;
    rt_uint8_t major, minor;
		rt_uint8_t	buf;
	//char buf[20];
	//static rt_uint8_t uart_rx_data_buf[segLengthVal];
	
	rt_hw_key_led_scan_init();
	F_startSportTimerInit();

	//speed_control_init();
	ui_action.Status = sysPowerStartVal;
	while(1)
	{
		switch(ui_action.Status) 
		{
			case	sysPowerStartVal:
			rt_thread_delay(500);		//	等待電源穩定
															//	顯示
			if(F_eeprom_test() == RT_EOK) {
				rt_kprintf("eeprom_OK");
				if(F_eeprom_whether_init() == RT_EOK) {
					// eeprom 資料讀取
					F_eeprom_incline_data(ReadDataVal,&incline_eeprom_data);	//	read
					F_eeprom_home1_data(ReadDataVal,&sport_data.saveSeatPositionHome_1);
					F_eeprom_home2_data(ReadDataVal,&sport_data.saveSeatPositionHome_2);
				} else {
					// eeprom 資料初始化
					//incline_eeprom_data.incMaxNum = 15;
					incline_eeprom_data.incMaxAd = 0xE1;
					incline_eeprom_data.incMinAd = 0x1E;
					incline_eeprom_data.incUpDownFlg = 0;
					F_eeprom_incline_data(WriteDataVal,&incline_eeprom_data);	//	write
					sport_data.saveSeatPositionHome_1 = incline_eeprom_data.incMaxAd;
					F_eeprom_home1_data(WriteDataVal,&sport_data.saveSeatPositionHome_1);
					sport_data.saveSeatPositionHome_2 = incline_eeprom_data.incMinAd;
					F_eeprom_home2_data(WriteDataVal,&sport_data.saveSeatPositionHome_2);
					buf = 0;
					F_eeprom_user_DetectionData(InitDataVal,EepromNothingVal,&buf);		
					F_eeprom_write_init();
				}
				incline_control_init(incline_eeprom_data);
				rt_hw_pwm_vms_init();
				rt_hw_led_on();	
				rt_hw_heart_rate_init();
				F_InitSportParameters();
				F_InitSetProfileData();
				F_InitSetProfileEvent();
				F_InitManualData();
				ui_action.Status = sysUiStartVal;
			} else {
				rt_kprintf("eeprom_ERR");
				ui_action.Status = eepromErrVal;
			}
				break;
			//==================
			case	sysUiStartVal:
			F_SysUiStart();
				break;
			//==================
			case	setNoramalVal:
			F_setNoramal();
				break;
			//==================
			case	sportManualVal:
			F_SportNoramal();
				break;
			//==================
			case	setProfilesVal:
			F_setProfiles();
				break;
			//==================
			case	setProfileChooseVal:
			F_setProfileChoose();
				break;
			//==================
			case	setRollingHillVal:
			F_setProfileRollingHill();
				break;
			//==================
			case	setPeakVal:
			F_setProfilePeak();
				break;
			//==================
			case	setPlateauVal:
			F_setProfilePlateau();
				break;
			//==================
			case	setClimbVal:
			F_setProfileClimb();
				break;
			//==================
			case	setInterval_1_Val:
			F_setProfileInterval_1();
				break;
			//==================
			case	setInterval_2_Val:
			F_setProfileInterval_2();
				break;
			//==================
			case	profileSportVal:
			F_ProfileSport();
				break;
			//==================
			case	setUsersVal:
			F_setUsers();
				break;
			//==================
			case	setUsersNoDataVal:
			F_setUsersNoData();
				break;
			//==================
			case	setUsersDataVal:
			F_setUsersData();
				break;
			//==================
			case	setUsersResetDataVal:
			F_setUsersResetData();
				break;
			//==================
			case	setUsersSportVal:
			F_setUsersSport();
				break;
			//==================
			case	setProfilesManualVal:
			F_setProfilesManual();
				break;
			//==================
			case	setManualFatBurnVal:
			F_setManualFatBurn();
				break;
			//==================
			case	setManualCardioVal:
			F_setManualCardio();
				break;
			//==================
			case	setManualTargetVal:
			F_setManualTarget();
				break;
			//==================
			case	setManualSportVal:
			F_ProfilesManualSport();
				break;
			//==================
			case	eng1Val:
			F_EngMode1();
				break;
			case	eepromErrVal:
			
				break;
		}
		//memset(uart_rx_data_buf,0xFF,sizeof(uart_rx_data_buf));
		//F_WriteHT1625(uart_rx_data_buf,segLengthVal);
		cpu_usage_get(&major, &minor);
		//rt_sprintf(buf,"%d.%d%%",major,minor);
		//rt_kprintf(" CPU usage is: %s \r\n", buf);
		
		//rt_kprintf("test");
		/*
		for(i=0;i<10;i++) 
		{
			rt_thread_delay(RT_TICK_PER_SECOND);
			rt_kprintf(" test2 thread count:%d \r\n",i);
		}
		*/
	}
		
}

/* test thread entry */
/*
static void test_thread_entry(void* parameter)
{
	//rt_uint32_t i;
	while(1)
	{
        rt_hw_led_on();
        rt_thread_delay(1000);

        //rt_hw_led_off();
        //rt_thread_delay(RT_TICK_PER_SECOND);
	}
}
*/

static void rt_init_thread_entry(void* parameter)
{
	//rt_thread_t led_thread;
/* Initialization RT-Thread Components */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_init();
#endif

/* Set finsh device */
#ifdef  RT_USING_FINSH
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif  /* RT_USING_FINSH */

	/*
    led_thread = rt_thread_create("test",
    		test_thread_entry, RT_NULL,
    		256, 20, 20);
    if(led_thread != RT_NULL)
    	rt_thread_startup(led_thread);
	*/
	
}

int rt_application_init()
{
		rt_thread_t init_thread;
		rt_err_t result;
	
#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   512, 8, 20);
#else
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   512, 80, 20);
#endif
	
    if(init_thread != RT_NULL)
    	rt_thread_startup(init_thread);

		result = rt_thread_init(&control_thread,"control", rt_control_thread_entry, RT_NULL,
						(rt_uint8_t*)&control_stack[0], sizeof(control_stack),20,2);
		
		if(result == RT_EOK)
		{ 
			rt_thread_startup(&control_thread); 
		}

    return 0;
}


/*@}*/
