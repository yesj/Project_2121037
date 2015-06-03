#include "chandler.h"

static void	F_setTargetKey(rt_uint8_t keyCode,rt_bool_t LongKeyStartFlg)
{
		switch(keyCode)
		{
			case	enter_KeyVal:
			bz_short();
			ui_action.Event = showHeartRateWorkoutEventVal;
				break;
			case	stop_rest_KeyVal:
			bz_short();
			F_setProfilesHeartRateInit(showHeartRateTargetEventVal);
				break;
			case	resistance_up_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberUp_8(&profile_heartrate_data.TargetTarget,1,cycleNumberVal);
				break;
			case	resistance_down_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberDown_8(&profile_heartrate_data.TargetTarget,1,cycleNumberVal);
				break;
		}
}

static void	F_setFatBurnWorkOutTImeKey(rt_uint8_t keyCode,rt_bool_t LongKeyStartFlg)
{
		switch(keyCode)
		{
			case	enter_KeyVal:
			bz_short();
			F_ProfilesHeartRateSportInit(profile_heartrate_data.TargetWorkoutMinTime.number,profile_heartrate_data.TargetTarget.number,showHeartRateTargetEventVal);
				break;
			case	stop_rest_KeyVal:
			bz_short();
			ui_action.Event = showHeartRateSetTargetEventVal;
				break;
			case	resistance_up_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberUp_8(&profile_heartrate_data.TargetWorkoutMinTime,1,cycleNumberVal);
				break;
			case	resistance_down_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberDown_8(&profile_heartrate_data.TargetWorkoutMinTime,1,cycleNumberVal);
				break;
		}
}

static	void	F_SportKey(rt_uint8_t keyCode)
{
		switch(keyCode)
		{
			case	quick_start_KeyVal:
			bz_short();
			F_ProfilesHeartRateSportInit(profile_heartrate_data.TargetWorkoutMinTime.number,profile_heartrate_data.TargetTarget.number,showHeartRateTargetEventVal);
				break;
		}
}

void F_setHeartRateTarget(void)
{
		rt_uint8_t	keyCode = 0;
		rt_bool_t	LongKeyStartFlg = 0;
		rt_uint32_t e;
		rt_time_data_t SetWorkoutTime;
	
			if (rt_event_recv(&sport_timer_event, 0xFFFF,
					RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
					RT_WAITING_FOREVER, &e) == RT_EOK)
			{
				if((e & time_20ms_val) == time_20ms_val)
				{
					F_ReadKeyCode(&keyCode,&LongKeyStartFlg);
					F_LongRestKey(keyCode);
					F_SeatPositionControlAllKey(&keyCode,LongKeyStartFlg);
					F_SportKey(keyCode);
						switch(ui_action.Event) {
							case	showHeartRateSetTargetEventVal:
							F_setTargetKey(keyCode,LongKeyStartFlg);
								break;
							case	showHeartRateWorkoutEventVal:
							F_setFatBurnWorkOutTImeKey(keyCode,LongKeyStartFlg);
								break;
						}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					if(ui_action.TemporarySeatPositionEvent == TemporarySeatPositionNormalEventVal) {
						switch(ui_action.Event) {
							case	showHeartRateSetTargetEventVal:
							F_showSetTargetNum(profile_heartrate_data.TargetTarget.number,0);
								break;
							case	showHeartRateWorkoutEventVal:
							SetWorkoutTime.timeH = profile_heartrate_data.TargetWorkoutMinTime.number;
							SetWorkoutTime.timeL = 0;
							F_showProfileSetWorkoutTime(SetWorkoutTime);
								break;
						}
					} else {
						F_showSeatPositionStatus(ui_action.TemporarySeatPositionEvent);
					}
					F_Display();
				}
				//=====================
				if((e & time_1s_val) == time_1s_val)
				{
					F_SwitchingSeatPositionDisplayTimer();
				}
			}
}

void F_setHeartRateTargetInit(void)
{
		ui_action.Status = setHeartRateTargetVal;
		ui_action.Event = showHeartRateSetTargetEventVal;
}
