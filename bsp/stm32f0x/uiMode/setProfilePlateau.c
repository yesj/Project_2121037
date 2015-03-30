#include "chandler.h"

static void	F_setProfileLevelKey(rt_uint8_t keyCode,rt_bool_t LongKeyStartFlg)
{
		switch(keyCode)
		{
			case	quick_start_KeyVal:
			bz_short();
			F_ProfileSportInit(setPlateauEventVal);
				break;
			case	enter_KeyVal:
			bz_short();
			ui_action.Event = setProfileWorkOutTImeEventVal;
				break;
			case	stop_rest_KeyVal:
			bz_short();
			F_setProfileChooseInit(setPlateauEventVal);
				break;
			case	resistance_up_KeyVal:
			if(F_NumberUp_8(&set_profile_data.plateauLevel,1,noCycleNumberVal).complyFlg == YesComplyVal) {
				F_PlateauLevelCount(set_profile_data.plateauLevel.number,sport_data.progfileArry,ProgfileDataSizeVal);
				if(LongKeyStartFlg == 0){
					bz_short();
				}
			}
				break;
			case	resistance_down_KeyVal:
			if(F_NumberDown_8(&set_profile_data.plateauLevel,1,noCycleNumberVal).complyFlg == YesComplyVal) {
				F_PlateauLevelCount(set_profile_data.plateauLevel.number,sport_data.progfileArry,ProgfileDataSizeVal);
				if(LongKeyStartFlg == 0){
					bz_short();
				}
			}
				break;
		}
}

static void	F_setProfileWorkOutTImeKey(rt_uint8_t keyCode,rt_bool_t LongKeyStartFlg)
{
		switch(keyCode)
		{
			case	quick_start_KeyVal:
			case	enter_KeyVal:
			bz_short();
			F_ProfileSportInit(setPlateauEventVal);
				break;
			case	stop_rest_KeyVal:
			bz_short();
			ui_action.Event = setProfileLevelEventVal;
				break;
			case	resistance_up_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberUp_8(&set_profile_data.plateauWorkoutMinTime,1,cycleNumberVal);
				break;
			case	resistance_down_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberDown_8(&set_profile_data.plateauWorkoutMinTime,1,cycleNumberVal);
				break;
		}
}

void F_setProfilePlateau(void)
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
					F_SetUserKey(keyCode);
					switch(ui_action.Event) 
					{
						case	setProfileLevelEventVal:
						F_setProfileLevelKey(keyCode,LongKeyStartFlg);
							break;
						case	setProfileWorkOutTImeEventVal:
						F_setProfileWorkOutTImeKey(keyCode,LongKeyStartFlg);
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
						F_showProfileSetLeve(set_profile_data.plateauLevel.number);
						F_ShowProgfileGraph(sport_data.progfileArry,ProgfileDataSizeVal,CommonModeVal,0,0);
							break;
						case	setProfileWorkOutTImeEventVal:
						SetWorkoutTime.timeH = set_profile_data.plateauWorkoutMinTime.number;
						SetWorkoutTime.timeL = 0;
						F_showProfileSetWorkoutTime(SetWorkoutTime);
							break;
					}
					F_Display();
				}
				//=====================
			}
}

void F_setProfilePlateauInit(void)
{
	ui_action.Status = setPlateauVal;
	ui_action.Event = setProfileLevelEventVal;
	F_PlateauLevelCount(set_profile_data.plateauLevel.number,sport_data.progfileArry,ProgfileDataSizeVal);
}

