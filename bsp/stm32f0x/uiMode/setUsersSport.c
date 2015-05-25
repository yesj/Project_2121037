#include "chandler.h"
#include "24lcxx_user.h"

static 	rt_uint8_t	R_Segments,R_SegmentsTime;
static 	rt_bool_t		FlickerFlg;
static 	rt_uint8_t	UserProfile;

static void	F_MaxLevelCount(rt_uint8_t MaxLevel,rt_uint8_t Segments)
{
	rt_uint8_t adr;
		switch(UserProfile) 
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

static void F_ShowBasicView(void)
{
		F_showMatrixProfileWrokOutTime(TimeData);
		F_ShowProgfileGraph(sport_data.progfileArryBuf,ProgfileDataSizeVal,FlickerModeVal,R_Segments,FlickerFlg);
		F_showResistance(sport_data.progfileArryBuf[R_Segments]);
		switch(ui_action.Event) {
			case	CalHrViewVal:
			F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
			F_showCal(calor_count.calorie);
				break;
			case	RpmDisViewVal:
			F_showDistance(distance_data.distance_count);
			F_Show8Rpm(F_readRpm());
				break;
		}
}

static void F_UserSportNormalKey(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
	switch(Key) {
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
		case	view_KeyVal:
			bz_short();
			ui_action.Event++;
			if(ui_action.Event > RpmDisViewVal) 
			{
				ui_action.Event = CalHrViewVal;
			}
		break;
		case	stop_rest_KeyVal:
			bz_short();
			ui_action.TemporarySportStopEventFlg = 1;
		break;
	}
}

static void F_UserSportStopKey(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
	switch(Key) {
		case	stop_rest_KeyVal:
			bz_short();
			F_SaveSportData();
			F_setUsersInit(ui_action.UsersEventSave);
		break;
		case	quick_start_KeyVal:
			bz_short();
			ui_action.TemporarySportStopEventFlg = 0;
		break;
	}
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
					F_LongRestKey(keyCode);
					F_SeatPositionControlAllKey(keyCode,LongKeyStartFlg);
					if(ui_action.TemporarySportStopEventFlg == 0) {
						F_UserSportNormalKey(keyCode,LongKeyStartFlg);
					} else {
						F_UserSportStopKey(keyCode,LongKeyStartFlg);
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					if(ui_action.TemporaryEventFlg == 0) {
						F_ShowBasicView();
					} else {
						F_showSeatPositionMove();
					}
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
					F_SwitchingSeatPositionDisplayTimer();
						if(ui_action.TemporarySportStopEventFlg == 0) {
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
								F_UserSportTimeSecCount();
							} else {
								F_SaveSportData();
								F_setUsersInit(ui_action.UsersEventSave);
							}
						}
				}
			}
}

void F_setUsersSportInit(void)
{
	ui_action.Status = setUsersSportVal;
	ui_action.Event = CalHrViewVal;
	ui_action.TemporarySportStopEventFlg = 0;
	memset(&TimeData,0,sizeof(TimeData));
	memset(&calor_count,0,sizeof(calor_count));
	F_setVmsDetectionVal(30);
	F_eeprom_user_time(ReadDataVal,ui_action.UsersEventSave,&set_user_data.SportTimeSec);
	F_eeprom_user_cal(ReadDataVal,ui_action.UsersEventSave,&set_user_data.SportCal);
	F_eeprom_user_km(ReadDataVal,ui_action.UsersEventSave,&set_user_data.SportKm);
	//----------
	F_eeprom_profile(ReadDataVal,ui_action.UsersEventSave,&UserProfile);
	F_eeprom_level(ReadDataVal,ui_action.UsersEventSave,&sport_data.resistance.number);
	F_eeprom_worktime(ReadDataVal,ui_action.UsersEventSave,&TimeData.timeH);
	TimeData.timeL = 0;
	R_SegmentsTime = TimeData.timeH;
	F_ProfileTimeSegments(&R_Segments,TimeData,R_SegmentsTime,59);
	F_MaxLevelCount(sport_data.resistance.number,R_Segments);
	FlickerFlg = 0;
}
