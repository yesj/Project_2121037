#include "chandler.h"
#include "24lcxx_user.h"

static void F_UserSportTimeSecCount(void)
{
	set_user_data.SportTimeSec++;
}

static void F_SaveSportData(void)
{
		set_user_data.SportCal = set_user_data.SportCal + (calor_count.calorie / 100000);				// 卡路里計算 小數點第5位
		set_user_data.SportKm = set_user_data.SportKm + (distance_data.distance_count / 1000);	// 單位公分 轉換 公里
	
		F_eeprom_user_time(WriteDataVal,ui_action.UsersEventSave,&set_user_data.SportTimeSec);
		F_eeprom_user_cal(WriteDataVal,ui_action.UsersEventSave,&set_user_data.SportCal);
		F_eeprom_user_km(WriteDataVal,ui_action.UsersEventSave,&set_user_data.SportKm);
}

void F_setUsersSport(void)
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
					F_ReadKeyCode(&keyCode,&LongKeyStartFlg);
					switch(keyCode)
					{
						case	resistance_up_KeyVal:
						if(F_NumberUp_8(&sport_data.resistance,1,noCycleNumberVal).complyFlg == YesComplyVal) {
							if(LongKeyStartFlg == 0){
								bz_short();
							}
						}
						break;
						case	resistance_down_KeyVal:
						if(F_NumberDown_8(&sport_data.resistance,1,noCycleNumberVal).complyFlg == YesComplyVal) {
							if(LongKeyStartFlg == 0){
								bz_short();
							}
						}
						break;
						case	stop_rest_KeyVal:
						bz_short();
						F_SaveSportData();
						F_setUsersInit(ui_action.UsersEventSave);
						break;	
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					F_showMatrixTime(TimeData);
					F_showResistance(sport_data.resistance.number);
					F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
					F_showCal(calor_count.calorie);
					F_Display();
				}
				//=====================
				if((e & time_1s_val) == time_1s_val)
				{
					F_timer_process_up(&TimeData);
					calor_count.level = sport_data.resistance.number;
					F_readWatte(calor_count.level,&calor_count.watt);					
					F_calorie_process(&calor_count);
					//rt_kprintf("RPM:%d \r\n",F_readRpm());
					distance_data.rpm = F_readRpm();
					F_VmsDetection(distance_data.rpm);
					distance_data.WheelSize = 300;
					F_distance_process(&distance_data);
					F_UserSportTimeSecCount();
				}
			}
}

void F_setUsersSportInit(void)
{
	ui_action.Status = setUsersSportVal;
	//ui_action.Event = showUserResetNoEventVal;
	memset(&TimeData,0,sizeof(TimeData));
	memset(&calor_count,0,sizeof(calor_count));
	sport_data.resistance.number = 1;
	F_setVmsDetectionVal(30);
	F_eeprom_user_time(ReadDataVal,ui_action.UsersEventSave,&set_user_data.SportTimeSec);
	F_eeprom_user_cal(ReadDataVal,ui_action.UsersEventSave,&set_user_data.SportCal);
	F_eeprom_user_km(ReadDataVal,ui_action.UsersEventSave,&set_user_data.SportKm);
}
