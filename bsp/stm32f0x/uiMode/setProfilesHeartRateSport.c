#include "chandler.h"

static rt_uint8_t	SportTargetTime;
static rt_uint8_t	TargetTemp;
static 	rt_uint8_t	R_Segments,R_SegmentsTime;
static 	rt_bool_t		FlickerFlg;

static void	F_HeartRateLevelCount(rt_uint8_t Level,rt_uint8_t Segments)
{
		rt_uint8_t adr;
		
		F_Menual_LevelCount(Level,sport_data.progfileArry,ProgfileDataSizeVal);
		for(adr = Segments ; adr < ProgfileDataSizeVal ; adr++) {
			sport_data.progfileArryBuf[adr] = sport_data.progfileArry[adr];
		}
}

static void	F_ShowStandardView(void)
{
		F_showMatrixProfileWrokOutTime(TimeData);
		F_ShowProgfileGraph(sport_data.progfileArryBuf,ProgfileDataSizeVal,FlickerModeVal,R_Segments,FlickerFlg);
		F_showResistance(sport_data.resistance.number);
		F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
		F_showCal(calor_count.calorie);
}

static void F_ShowBasicView(void)
{
		F_showMatrixTime(TimeData);
		F_showResistance(sport_data.resistance.number);
		F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
		F_showCal(calor_count.calorie);
}

static void F_ShowHeartRateView(void)
{
		F_show8Time(TimeData);
		F_showResistance(sport_data.resistance.number);
		F_showDistance(distance_data.distance_count);
		F_showHearRateGraph(F_readHandHeartRate(),F_readwHeartRate());
}

static void F_ShowCalorieView(void)
{
		F_show8Time(TimeData);
		F_showResistance(sport_data.resistance.number);
		F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
		F_showMatrixCal(calor_count.calorie);
		//F_showMatrixCalHr(calor_count.calorie);
}


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
			F_HeartRateLevelCount(sport_data.resistance.number,R_Segments);
		}
	} else {
		SportTargetTime = 0;
	}
}

static void F_HeartRateSportNormalKey(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
		switch(Key)
		{
			case	resistance_up_KeyVal:
			if(F_NumberUp_8(&sport_data.resistance,1,noCycleNumberVal).complyFlg == YesComplyVal) {
				if(LongKeyStartFlg == 0){
					bz_short();
				}
				F_HeartRateLevelCount(sport_data.resistance.number,R_Segments);
			}
			break;
			case	resistance_down_KeyVal:
			if(F_NumberDown_8(&sport_data.resistance,1,noCycleNumberVal).complyFlg == YesComplyVal) {
				if(LongKeyStartFlg == 0){
					bz_short();
				}
				F_HeartRateLevelCount(sport_data.resistance.number,R_Segments);
			}
			break;
			case	view_KeyVal:
				bz_short();
				ui_action.Event++;
				if(ui_action.Event > CalorieVewVal) 
				{
					ui_action.Event = StandardViewVal;
				}
			break;
			case	stop_rest_KeyVal:
			bz_short();
			ui_action.TemporarySportStopEventFlg = 1;
			break;	
		}
}

static void F_HeartRateSportStopKey(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
	switch(Key) {
		case	stop_rest_KeyVal:
			bz_short();
			F_setProfilesHeartRateInit(ui_action.HeartRateEventSave);
		break;
		case	quick_start_KeyVal:
			bz_short();
			ui_action.TemporarySportStopEventFlg = 0;
		break;
	}
}

void F_ProfilesHeartRateSport(void)
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
						F_HeartRateSportNormalKey(keyCode,LongKeyStartFlg);
					} else {
						F_HeartRateSportStopKey(keyCode,LongKeyStartFlg);
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					if(ui_action.TemporaryEventFlg == 0) {
						switch(ui_action.Event)
						{
							case	StandardViewVal:
								F_ShowStandardView();
								break;
							case	BasicViewVal:
								F_ShowBasicView();
								break;
							case	HeartRateViewVal:
								F_ShowHeartRateView();
								break;
							case	CalorieVewVal:
								F_ShowCalorieView();
								break;
						}
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
						} else {
							F_setProfilesHeartRateInit(ui_action.HeartRateEventSave);
						}
					}
				}
			}
}

void F_ProfilesHeartRateSportInit(rt_uint8_t WorkOutTimeMin,rt_uint8_t Target,rt_uint8_t HeartRateEvent)
{
		ui_action.Status = setHeartRateSportVal;
		ui_action.Event = StandardViewVal;
		ui_action.HeartRateEventSave = HeartRateEvent;
		TargetTemp = Target;
		memset(&calor_count,0,sizeof(calor_count));
		ui_action.TemporarySportStopEventFlg = 0;
		sport_data.resistance.number = 1;
		TimeData.timeH = WorkOutTimeMin;
		TimeData.timeL = 0;
		R_SegmentsTime = TimeData.timeH;
		F_ProfileTimeSegments(&R_Segments,TimeData,R_SegmentsTime,59);
		F_HeartRateLevelCount(sport_data.resistance.number,R_Segments);
		FlickerFlg = 0;
		SportTargetTime = 0;
}
