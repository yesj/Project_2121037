#include "chandler.h"

static rt_uint8_t	SportTargetTime;
static rt_uint8_t	TargetTemp;

void	F_SportTargetTimeDetection(void)
{
	rt_uint8_t HeartRateTemp,HandHeartRate,wHeartRate;

	wHeartRate = F_readwHeartRate();
	HandHeartRate = F_readHandHeartRate();
	if(wHeartRate) {
		HeartRateTemp = wHeartRate;
	} else {
		HeartRateTemp = HandHeartRate;
	}
	
	if(HeartRateTemp) {
		if(SportTargetTime >= 15) {
			if(HeartRateTemp >= TargetTemp) {
				F_NumberDown_8(&sport_data.resistance,1,noCycleNumberVal);
			} else {
				F_NumberUp_8(&sport_data.resistance,1,noCycleNumberVal);
			}
		}
	} else {
		SportTargetTime = 0;
	}
}

void F_ProfilesManualSport(void)
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
					F_SeatPositionControlAllKey(keyCode,LongKeyStartFlg);
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
						F_setProfilesManualInit(ui_action.ManualEventSave);
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
					F_timer_process_down(&TimeData);
					if(TimeData.timeH != 0 || TimeData.timeL != 0) {
					calor_count.level = sport_data.resistance.number;
					F_readWatte(calor_count.level,&calor_count.watt);					
					F_calorie_process(&calor_count);
					distance_data.rpm = F_readRpm();
					F_VmsDetection(distance_data.rpm);
					distance_data.WheelSize = 300;
					F_distance_process(&distance_data);
					} else {
						F_setProfilesManualInit(ui_action.ManualEventSave);
					}
				}
			}
}

void F_ProfilesManualSportInit(rt_uint8_t WorkOutTimeMin,rt_uint8_t Target,rt_uint8_t ManualEvent)
{
		ui_action.Status = setManualSportVal;
		//ui_action.Event = Event;
		TimeData.timeH = WorkOutTimeMin;
		TimeData.timeL = 0;
		memset(&calor_count,0,sizeof(calor_count));
		sport_data.resistance.number = 1;
		ui_action.ManualEventSave = ManualEvent;
		TargetTemp = Target;
		SportTargetTime = 0;
}
