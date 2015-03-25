#include "chandler.h"

static void	F_setProfileLevelKey(rt_uint8_t keyCode)
{
		switch(keyCode)
		{
			case	quick_start_KeyVal:
			bz_short();
			F_ProfileSportInit(setClimbEventVal);
				break;
			case	enter_KeyVal:
			bz_short();
			ui_action.Event = setProfileWorkOutTImeEventVal;
				break;
			case	stop_rest_KeyVal:
			bz_short();
			F_setProfileChooseInit(setClimbEventVal);
				break;
			case	resistance_up_KeyVal:
			if(F_NumberUp_8(&set_profile_data.climbLevel,1,noCycleNumberVal).complyFlg == YesComplyVal) {
				F_ClimbLevelCount(set_profile_data.climbLevel.number,sport_data.progfileArry,ProgfileDataSizeVal);
				bz_short();
			}
				break;
			case	resistance_down_KeyVal:
			if(F_NumberDown_8(&set_profile_data.climbLevel,1,noCycleNumberVal).complyFlg == YesComplyVal) {
				F_ClimbLevelCount(set_profile_data.climbLevel.number,sport_data.progfileArry,ProgfileDataSizeVal);
				bz_short();
			}
				break;
		}
}

static void	F_setProfileWorkOutTImeKey(rt_uint8_t keyCode)
{
		switch(keyCode)
		{
			case	quick_start_KeyVal:
			case	enter_KeyVal:
			bz_short();
			F_ProfileSportInit(setClimbEventVal);
				break;
			case	stop_rest_KeyVal:
			bz_short();
			ui_action.Event = setProfileLevelEventVal;
				break;
			case	resistance_up_KeyVal:
			bz_short();
			F_NumberUp_8(&set_profile_data.climbWorkoutMinTime,1,cycleNumberVal);
				break;
			case	resistance_down_KeyVal:
			bz_short();
			F_NumberDown_8(&set_profile_data.climbWorkoutMinTime,1,cycleNumberVal);
				break;
		}
}

void F_setProfileClimb(void)
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
					switch(ui_action.Event) 
					{
						case	setProfileLevelEventVal:
						F_setProfileLevelKey(keyCode);
							break;
						case	setProfileWorkOutTImeEventVal:
						F_setProfileWorkOutTImeKey(keyCode);
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event) 
					{
						case	setProfileLevelEventVal:
						F_showProfileSetLeve(set_profile_data.climbLevel.number);
						F_ShowProgfileGraph(sport_data.progfileArry,ProgfileDataSizeVal,CommonModeVal,0,0);
							break;
						case	setProfileWorkOutTImeEventVal:
						SetWorkoutTime.timeH = set_profile_data.climbWorkoutMinTime.number;
						SetWorkoutTime.timeL = 0;
						F_showProfileSetWorkoutTime(SetWorkoutTime);
							break;
					}
					F_Display();
				}
				//=====================
			}
}

void F_setProfileClimbInit(void)
{
	ui_action.Status = setClimbVal;
	ui_action.Event = setProfileLevelEventVal;
	F_ClimbLevelCount(set_profile_data.climbLevel.number,sport_data.progfileArry,ProgfileDataSizeVal);
}

