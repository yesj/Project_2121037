#include "chandler.h"

static void	F_setTargetKey(rt_uint8_t keyCode,rt_bool_t LongKeyStartFlg)
{
		switch(keyCode)
		{
			case	enter_KeyVal:
			bz_short();
			ui_action.Event = showManualWorkoutEventVal;
				break;
			case	stop_rest_KeyVal:
			bz_short();
			F_setProfilesManualInit(showManualTargetEventVal);
				break;
			case	resistance_up_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberUp_8(&set_manual_data.TargetTarget,1,cycleNumberVal);
				break;
			case	resistance_down_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberDown_8(&set_manual_data.TargetTarget,1,cycleNumberVal);
				break;
		}
}

static void	F_setFatBurnWorkOutTImeKey(rt_uint8_t keyCode,rt_bool_t LongKeyStartFlg)
{
		switch(keyCode)
		{
			case	enter_KeyVal:
			bz_short();
			F_ProfilesManualSportInit(set_manual_data.TargetWorkoutMinTime.number,set_manual_data.TargetTarget.number,showManualTargetEventVal);
				break;
			case	stop_rest_KeyVal:
			bz_short();
			ui_action.Event = showManualSetTargetEventVal;
				break;
			case	resistance_up_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberUp_8(&set_manual_data.TargetWorkoutMinTime,1,cycleNumberVal);
				break;
			case	resistance_down_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberDown_8(&set_manual_data.TargetWorkoutMinTime,1,cycleNumberVal);
				break;
		}
}

static	void	F_SportKey(rt_uint8_t keyCode)
{
		switch(keyCode)
		{
			case	quick_start_KeyVal:
			bz_short();
			F_ProfilesManualSportInit(set_manual_data.TargetWorkoutMinTime.number,set_manual_data.TargetTarget.number,showManualTargetEventVal);
				break;
		}
}

void F_setManualTarget(void)
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
					F_SportKey(keyCode);
					switch(ui_action.Event) {
						case	showManualSetTargetEventVal:
						F_setTargetKey(keyCode,LongKeyStartFlg);
							break;
						case	showManualWorkoutEventVal:
						F_setFatBurnWorkOutTImeKey(keyCode,LongKeyStartFlg);
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event) {
						case	showManualSetTargetEventVal:
						F_showSetTargetNum(set_manual_data.TargetTarget.number,0);
							break;
						case	showManualWorkoutEventVal:
						SetWorkoutTime.timeH = set_manual_data.TargetWorkoutMinTime.number;
						SetWorkoutTime.timeL = 0;
						F_showProfileSetWorkoutTime(SetWorkoutTime);
							break;
					}
					F_Display();
				}
				//=====================
			}
}

void F_setManualTargetInit(void)
{
		ui_action.Status = setManualTargetVal;
		ui_action.Event = showManualSetTargetEventVal;
}
