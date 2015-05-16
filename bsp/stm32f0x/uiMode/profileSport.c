#include "chandler.h"

static 	rt_uint8_t	R_Segments,R_SegmentsTime;
static 	rt_bool_t		FlickerFlg;

static void	F_MaxLevelCount(rt_uint8_t MaxLevel,rt_uint8_t Segments)
{
	rt_uint8_t adr;
		switch(ui_action.ProfileEventSave) 
		{
			case	setRollingHillEventVal:
			F_RollingHillLevelCount(MaxLevel,sport_data.progfileArry,ProgfileDataSizeVal);
				break;
			case	setPeakEventVal:
			F_PeakLevelCount(MaxLevel,sport_data.progfileArry,ProgfileDataSizeVal);
				break;
			case	setPlateauEventVal:
			F_PlateauLevelCount(MaxLevel,sport_data.progfileArry,ProgfileDataSizeVal);
				break;
			case	setClimbEventVal:
			F_ClimbLevelCount(MaxLevel,sport_data.progfileArry,ProgfileDataSizeVal);
				break;
			case	setInterval_1_EventVal:
			F_Interval_1_LevelCount(MaxLevel,sport_data.progfileArry,ProgfileDataSizeVal);
				break;
			case	setInterval_2_EventVal:
			F_Interval_2_LevelCount(MaxLevel,sport_data.progfileArry,ProgfileDataSizeVal);
				break;
		}
		for(adr = Segments ; adr < ProgfileDataSizeVal ; adr++) {
			sport_data.progfileArryBuf[adr] = sport_data.progfileArry[adr];
		}
}

static void F_ShowBasicView(void)
{
		F_showMatrixProfileWrokOutTime(TimeData);
		F_ShowProgfileGraph(sport_data.progfileArryBuf,ProgfileDataSizeVal,FlickerModeVal,R_Segments,FlickerFlg);
		F_showResistance(sport_data.resistance.number);
		F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
		F_showCal(calor_count.calorie);
}

void F_ProfileSport(void)
{
		rt_uint8_t	keyCode;
		rt_bool_t	LongKeyStartFlg = 0;
		rt_uint32_t e;
			if (rt_event_recv(&sport_timer_event, 0xFFFF,
					RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
					RT_WAITING_FOREVER, &e) == RT_EOK)
			{
				if((e & time_20ms_val) == time_20ms_val)
				{
					keyCode = 0;
					F_ReadKeyCode(&keyCode,&LongKeyStartFlg);
					F_SeatPositionControlAllKey(keyCode,LongKeyStartFlg);
					switch(keyCode)
					{
						case	resistance_up_KeyVal:
						if(F_NumberUp_8(&sport_data.resistance,1,noCycleNumberVal).complyFlg == YesComplyVal) {
							if(LongKeyStartFlg == 0){
								bz_short();
							}
							F_MaxLevelCount(sport_data.resistance.number,R_Segments);
						}
						break;
						case	resistance_down_KeyVal:
						if(F_NumberDown_8(&sport_data.resistance,1,noCycleNumberVal).complyFlg == YesComplyVal) {
							if(LongKeyStartFlg == 0){
								bz_short();
							}
							F_MaxLevelCount(sport_data.resistance.number,R_Segments);
						}
						break;
						case	stop_rest_KeyVal:
							bz_short();
							F_setProfileInit(setProfileEventVal);
						break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					F_ShowBasicView();
					F_Display();
				}
				//=====================
				if((e & time_500ms_val) == time_500ms_val)
				{
					if(FlickerFlg)
						FlickerFlg = 0;
						else
							FlickerFlg = 1;
				}
				//=====================
				if((e & time_1s_val) == time_1s_val)
				{
					F_timer_process_down(&TimeData);
					if(TimeData.timeH != 0 || TimeData.timeL != 0) {
						F_ProfileTimeSegments(&R_Segments,TimeData,R_SegmentsTime,59);
						calor_count.level = sport_data.resistance.number;
						F_readWatte(calor_count.level,&calor_count.watt);					
						F_calorie_process(&calor_count);
						distance_data.rpm = F_readRpm();
						F_VmsDetection(distance_data.rpm,sport_data.resistance.number);
						distance_data.WheelSize = 300;
						F_distance_process(&distance_data);
					} else {
						F_setProfileInit(setProfileEventVal);
					}
				}
			}
}

void	F_ProfileSportInit(rt_uint8_t Evnet)
{
	ui_action.Status = profileSportVal;
	ui_action.Event	= BasicViewVal;
	ui_action.ProfileEventSave = Evnet;
	memset(&calor_count,0,sizeof(calor_count));
	F_setVmsDetectionVal(30);
		switch(ui_action.ProfileEventSave) 
		{
			case	setRollingHillEventVal:
			TimeData.timeH = set_profile_data.roolingHillWorkoutMinTime.number;
			sport_data.resistance.number = set_profile_data.roolingHillLevel.number;
				break;
			case	setPeakEventVal:
			TimeData.timeH = set_profile_data.peakWorkoutMinTime.number;
			sport_data.resistance.number = set_profile_data.peakLevel.number;
				break;
			case	setPlateauEventVal:
			TimeData.timeH = set_profile_data.plateauWorkoutMinTime.number;
			sport_data.resistance.number = set_profile_data.plateauLevel.number;
				break;
			case	setClimbEventVal:
			TimeData.timeH = set_profile_data.climbWorkoutMinTime.number;
			sport_data.resistance.number = set_profile_data.climbLevel.number;
				break;
			case	setInterval_1_EventVal:
			TimeData.timeH = set_profile_data.interval_1_WorkoutMinTime.number;
			sport_data.resistance.number = set_profile_data.interval_1_Level.number;
				break;
			case	setInterval_2_EventVal:
			TimeData.timeH = set_profile_data.interval_2_WorkoutMinTime.number;
			sport_data.resistance.number = set_profile_data.interval_2_Level.number;
				break;
		}
		
		TimeData.timeL = 0;
		R_SegmentsTime = TimeData.timeH;
		F_ProfileTimeSegments(&R_Segments,TimeData,R_SegmentsTime,59);
		F_MaxLevelCount(sport_data.resistance.number,R_Segments);
		FlickerFlg = 0;
}

