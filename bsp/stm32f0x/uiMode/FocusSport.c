#include "chandler.h"

static	rt_uint32_t	FocusFormulaSegmentsTime;
static	rt_uint16_t	FocusFormulaTime;
static	rt_uint8_t	FocusFormulaStatus;
static	rt_uint8_t	FocusRealLevel;

static 	rt_uint8_t	R_Segments,R_SegmentsTime;
static 	rt_bool_t		FlickerFlg;

static 	rt_bool_t		ShowMaxLevelFlg;
static	rt_uint8_t	ShowMaxLevelTime;

static void	F_MaxLevelTimer(void)
{
	ShowMaxLevelTime++;
	if(ShowMaxLevelTime >= 3) {
		ShowMaxLevelTime = 3;
		ShowMaxLevelFlg = 0;
	}
}

static void	F_FocusLevelCount(rt_uint8_t Level,rt_uint8_t Segments)
{
		rt_uint8_t adr;
		
		F_Menual_LevelCount(Level,sport_data.progfileArry,ProgfileDataSizeVal);
		for(adr = Segments ; adr < ProgfileDataSizeVal ; adr++) {
			sport_data.progfileArryBuf[adr] = sport_data.progfileArry[adr];
		}
}

static void	F_FocusFormulaSegmentsTime(rt_uint8_t	FocusFormulaTimeMin)
{
	if(FocusFormulaTimeMin <= 10) {
		FocusFormulaSegmentsTime = (FocusFormulaTimeMin * 60000) / 8;
	} else if(FocusFormulaTimeMin <= 20) {
		FocusFormulaSegmentsTime = (FocusFormulaTimeMin * 60000) / 16;
	} else if(FocusFormulaTimeMin <= 30) {
		FocusFormulaSegmentsTime = (FocusFormulaTimeMin * 60000) / 24;
	} else {
		FocusFormulaSegmentsTime = (FocusFormulaTimeMin * 60000) / 32;
	}	
}

static void	F_FocusFormulaTime(void)
{
		FocusFormulaTime++;
		FocusFormulaStatus = ((FocusFormulaTime*1000) / FocusFormulaSegmentsTime);
}

static void	F_TotalBodyFouseCount(rt_uint8_t MaxLevel,rt_uint8_t	FocusSegment,rt_uint8_t *Level)
{
		switch(FocusSegment) {
			case	0:
			case	2:
			case	3:
			case	6:
			case	7:
			*Level = MaxLevel * 0.5;
				break;
			case	1:
			case	5:
			*Level = MaxLevel;
				break;
			case	4:
			*Level = MaxLevel * 0.75;
				break;
		}
		if(*Level == 0) {
			*Level = 1;
		}
}

static void	F_ArmsFouseCount(rt_uint8_t MaxLevel,rt_uint8_t	FocusSegment,rt_uint8_t *Level)
{
		switch(FocusSegment) {
			case	0:
			case	3:
			*Level = MaxLevel * 0.5;
				break;
			case	1:
			case	2:
			*Level = MaxLevel;
				break;
			case	4:
			case	6:
			*Level = MaxLevel * 0.25;
				break;
			case	5:
			case	7:
			*Level = MaxLevel * 0.75;
				break;
		}
		if(*Level == 0) {
			*Level = 1;
		}
}

static void	F_LegsFouseCount(rt_uint8_t MaxLevel,rt_uint8_t	FocusSegment,rt_uint8_t *Level)
{
		switch(FocusSegment) {
			case	0:
			*Level = MaxLevel * 0.5;
				break;
			case	1:
			case	2:
			*Level = MaxLevel * 0.75;
				break;
			case	3:
			case	4:
			*Level = MaxLevel;
				break;
			case	5:
			case	6:
			*Level = MaxLevel * 0.4;
				break;
			case	7:
			*Level = MaxLevel * 0.25;
				break;
		}
		if(*Level == 0) {
			*Level = 1;
		}
}

static void	F_CountFocusLevel(void)
{
		switch(ui_action.FocusEventSave) {
			case	FocusTotalBodyEventVal:
			F_TotalBodyFouseCount(sport_data.resistance.number,FocusFormulaStatus,&FocusRealLevel);
				break;
			case	FocusArmsEventVal:
			F_ArmsFouseCount(sport_data.resistance.number,FocusFormulaStatus,&FocusRealLevel);
				break;
			case	FocusLegsEventVal:
			F_LegsFouseCount(sport_data.resistance.number,FocusFormulaStatus,&FocusRealLevel);
				break;
		}
}

static void	F_showAction(void)
{
		switch(ui_action.FocusEventSave) {
			case	FocusTotalBodyEventVal:
			F_ShowTotalBodyFocus(FocusFormulaStatus);
				break;
			case	FocusArmsEventVal:
			F_ShowArmsFocus(FocusFormulaStatus);
				break;
			case	FocusLegsEventVal:
			F_ShowLegsFocus(FocusFormulaStatus);
				break;
		}
}

void F_FocusSportTimerInit(void)
{
		ui_action.TemporarySportStopEvent = TemporarySportStopNormalEventVal;
		TimeData.timeH = sport_data.sportSetTimer.number;
		TimeData.timeL = 0;
		R_SegmentsTime = TimeData.timeH;
		F_FocusFormulaSegmentsTime(TimeData.timeH);
		//==========
		F_CountFocusLevel();
		//==========
		FocusFormulaStatus = 0;
		FocusFormulaTime = 0;
		F_ProfileTimeSegments(&R_Segments,TimeData,R_SegmentsTime,59);
		F_FocusLevelCount(FocusRealLevel,R_Segments);
		FlickerFlg = 0;
		ShowMaxLevelFlg = 0;
}

static void	F_ShowStandardView(void)
{
		F_showMatrixProfileWrokOutTime(TimeData);
		F_ShowProgfileGraph(sport_data.progfileArryBuf,ProgfileDataSizeVal,FlickerModeVal,R_Segments,FlickerFlg);
		F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
		F_showCal(calor_count.calorie);
}

static void F_ShowBasicView(void)
{
		F_showMatrixTime(TimeData);
		F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
		F_showCal(calor_count.calorie);
}

static void F_ShowHeartRateView(void)
{
	F_show8Time(TimeData);
	F_showDistance(distance_data.distance_count,sport_data.UnitFlg);
	F_showHearRateGraph(F_readHandHeartRate(),F_readwHeartRate());
}

static void F_ShowCalorieView(void)
{
	F_show8Time(TimeData);
	F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
	F_showMatrixCal(calor_count.calorie,calor_count.calorieHr);
}

static void	F_ShowFocusView(void)
{
	F_show8Time(TimeData);
	F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
	F_showAction();
}

static void F_FocusSportNormalKey(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
		switch(Key)
		{
			case	resistance_up_KeyVal:
				if(F_NumberUp_8(&sport_data.resistance,1,noCycleNumberVal).complyFlg == YesComplyVal) {
					if(LongKeyStartFlg == 0){
						bz_short();
					}
					ShowMaxLevelTime = 0;
					ShowMaxLevelFlg = 1;
					F_CountFocusLevel();
					F_FocusLevelCount(FocusRealLevel,R_Segments);
				}
				break;
			case	resistance_down_KeyVal:
				if(F_NumberDown_8(&sport_data.resistance,1,noCycleNumberVal).complyFlg == YesComplyVal) {
					if(LongKeyStartFlg == 0) {
						bz_short();
					}
					ShowMaxLevelTime = 0;
					ShowMaxLevelFlg = 1;
					F_CountFocusLevel();
					F_FocusLevelCount(FocusRealLevel,R_Segments);
				}
				break;
			case	view_KeyVal:
				bz_short();
				ui_action.Event++;
				if(ui_action.Event > FocusVewVal)  {
					ui_action.Event = StandardViewVal;
				}
				break;
			case	stop_rest_KeyVal:
				bz_short();
				F_vms_control(0);
				ui_action.TemporarySportStopEvent = TemporarySportStopEventVal;
				break;	
		}
}

static void F_FocusSportStopKey(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
	switch(Key) {
		case	programs_KeyVal:
			bz_short();
			ui_action.TemporarySportStopEvent = TemporarySportStopSetTimeEventVal;
			sport_data.sportSetTimer.number = TimeData.timeH;
			break;
		case	stop_rest_KeyVal:
			bz_short();
			F_setProfilesFocusInit(ui_action.FocusEventSave);
		break;
		case	quick_start_KeyVal:
			bz_short();
			ui_action.TemporarySportStopEvent = TemporarySportStopNormalEventVal;
		break;
	}
}

static void F_FocusSportStopSetKey(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
	switch(Key) {
		case	quick_start_KeyVal:
		case	enter_KeyVal:
			bz_short();
			F_FocusSportTimerInit();
		break;
		case	stop_rest_KeyVal:
			bz_short();
			ui_action.TemporarySportStopEvent = TemporarySportStopEventVal;
		break;
		case	resistance_up_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberUp_8(&sport_data.sportSetTimer,1,cycleNumberVal);
		break;
		case	resistance_down_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberDown_8(&sport_data.sportSetTimer,1,cycleNumberVal);
		break;
	}
}

static void F_FocusView(void)
{
		if(ShowMaxLevelFlg)
		F_showMaxResistance(sport_data.resistance.number);
			else
			F_showResistance(FocusRealLevel);
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
			case	FocusVewVal:
				F_ShowFocusView();
				break;
		}
}

void F_FocusSport(void)
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
					F_SeatPositionControlAllKey(&keyCode,LongKeyStartFlg);
						switch(ui_action.TemporarySportStopEvent) {
							case	TemporarySportStopNormalEventVal:
								F_FocusSportNormalKey(keyCode,LongKeyStartFlg);
								break;
							case	TemporarySportStopEventVal:
								F_FocusSportStopKey(keyCode,LongKeyStartFlg);
								break;
							case	TemporarySportStopSetTimeEventVal:
								F_FocusSportStopSetKey(keyCode,LongKeyStartFlg);
								break;
						}	
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					if(ui_action.TemporarySeatPositionEvent == TemporarySeatPositionNormalEventVal) {
						switch(ui_action.TemporarySportStopEvent) {
							case	TemporarySportStopNormalEventVal:
							case	TemporarySportStopEventVal:
								F_FocusView();
								break;
							case	TemporarySportStopSetTimeEventVal:
								sport_data.SetWorkoutTime.timeH = sport_data.sportSetTimer.number;
								sport_data.SetWorkoutTime.timeL = 0;
								F_showProfileSetWorkoutTime(sport_data.SetWorkoutTime);
								break;
						}
					} else {
						F_showSeatPositionStatus(ui_action.TemporarySeatPositionEvent);
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
					F_MaxLevelTimer();
					if(ui_action.TemporarySportStopEvent == TemporarySportStopNormalEventVal) {
						distance_data.rpm = F_readRpm();
						if(distance_data.rpm != 0) {
							F_timer_process_down(&TimeData);
							if(TimeData.timeH != 0 || TimeData.timeL != 0) {
								F_FocusFormulaTime();
								F_ProfileTimeSegments(&R_Segments,TimeData,R_SegmentsTime,59);
								calor_count.level = FocusRealLevel;
								F_readWatte(calor_count.level,&calor_count.watt);					
								F_calorie_process(&calor_count);
								
								F_VmsDetection(distance_data.rpm,FocusRealLevel);
								distance_data.WheelSize = 300;
								F_distance_process(&distance_data);
							} else {
								F_vms_control(0);
								F_setProfilesFocusInit(ui_action.FocusEventSave);
							}
						} else {
							F_vms_control(0);
						}
					}
				}
			}
}

void F_FocusSportInit(void)
{
		ui_action.Status = FocusSportVal;
		ui_action.Event = StandardViewVal;
		ui_action.TemporarySportStopEvent = TemporarySportStopNormalEventVal;
		TimeData.timeH = set_focus_data.FocusWorkoutMinTime.number;
		TimeData.timeL = 0;
		memset(&calor_count,0,sizeof(calor_count));
		distance_data.distance_count = 0;
		F_FocusFormulaSegmentsTime(set_focus_data.FocusWorkoutMinTime.number);
		//==========
		sport_data.resistance.number = 1;
		F_CountFocusLevel();
		//==========
		F_setVmsDetectionVal(30);
		FocusFormulaStatus = 0;
		FocusFormulaTime = 0;
		R_SegmentsTime = TimeData.timeH;
		F_ProfileTimeSegments(&R_Segments,TimeData,R_SegmentsTime,59);
		F_FocusLevelCount(FocusRealLevel,R_Segments);
		FlickerFlg = 0;
		ShowMaxLevelFlg = 0;
}
