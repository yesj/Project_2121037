#include "chandler.h"

static 	rt_uint8_t	R_Segments,R_SegmentsTime;
static 	rt_bool_t		FlickerFlg;

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
	F_showDistance(distance_data.distance_count,sport_data.UnitFlg);
	F_showHearRateGraph(F_readHandHeartRate(),F_readwHeartRate());
}

static void F_ShowCalorieView(void)
{
	F_show8Time(TimeData);
	F_showResistance(sport_data.resistance.number);
	F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
	F_showMatrixCal(calor_count.calorie,calor_count.calorieHr);
}

static void	F_NoramalLevelCount(rt_uint8_t Level,rt_uint8_t Segments)
{
		rt_uint8_t adr;
		F_Menual_LevelCount(Level,sport_data.progfileArry,ProgfileDataSizeVal);
		for(adr = Segments ; adr < ProgfileDataSizeVal ; adr++) {
			sport_data.progfileArryBuf[adr] = sport_data.progfileArry[adr];
		}
}

static void	F_NormalSegmenTimeCount(void)
{
		R_SegmentsTime++;
		if(R_SegmentsTime >= 60) {
			R_SegmentsTime = 0;
			R_Segments++;
			if(R_Segments >=60) {
				R_Segments = 0;
			}
			F_NoramalLevelCount(sport_data.resistance.number,R_Segments);
		}
}

static void F_NoramalSportNormalKey(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
		switch(Key)
		{
			case	resistance_up_KeyVal:
			if(F_NumberUp_8(&sport_data.resistance,1,noCycleNumberVal).complyFlg == YesComplyVal) {
				if(LongKeyStartFlg == 0){
					bz_short();
				}
				F_NoramalLevelCount(sport_data.resistance.number,R_Segments);
			}
			break;
			case	resistance_down_KeyVal:
			if(F_NumberDown_8(&sport_data.resistance,1,noCycleNumberVal).complyFlg == YesComplyVal) {
				if(LongKeyStartFlg == 0){
					bz_short();
				}
				F_NoramalLevelCount(sport_data.resistance.number,R_Segments);
			}
			break;
			case	view_KeyVal:
				bz_short();
				ui_action.Event++;
				if(ui_action.Event > CalorieVewVal)  {
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

static void F_NoramalSportStopKey(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
	switch(Key) {
		case	stop_rest_KeyVal:
			bz_short();
			F_setNoramalInit();
		break;
		case	quick_start_KeyVal:
			bz_short();
			ui_action.TemporarySportStopEvent = TemporarySportStopNormalEventVal;
		break;
	}
}

void F_SportNoramal(void)
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
					F_ReadKeyCode(&keyCode,&LongKeyStartFlg,&ui_action.SleepTimer);
					F_LongRestKey(keyCode);
					F_SeatPositionControlAllKey(&keyCode,LongKeyStartFlg);
					if(ui_action.TemporarySportStopEvent == TemporarySportStopNormalEventVal) {
						F_NoramalSportNormalKey(keyCode,LongKeyStartFlg);
					} else {
						F_NoramalSportStopKey(keyCode,LongKeyStartFlg);
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					if(ui_action.TemporarySeatPositionEvent == TemporarySeatPositionNormalEventVal) {
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
						if(ui_action.TemporarySportStopEvent == TemporarySportStopNormalEventVal) {
							ui_action.SleepTimer = 0;
							F_timer_process_up(&TimeData);
							F_NormalSegmenTimeCount();
							calor_count.level = sport_data.resistance.number;
							F_readWatte(calor_count.level,&calor_count.watt);					
							F_calorie_process(&calor_count);
							distance_data.rpm = F_readRpm();
							F_VmsDetection(distance_data.rpm,sport_data.resistance.number);
							distance_data.WheelSize = 300;
							F_distance_process(&distance_data);
						}
				}
			}
}

void	F_SportNoramalInit(void)
{
	ui_action.Status = sportManualVal;
	ui_action.Event	= StandardViewVal;
	ui_action.TemporarySportStopEvent = TemporarySportStopNormalEventVal;
	memset(&TimeData,0,sizeof(TimeData));
	memset(&calor_count,0,sizeof(calor_count));
	distance_data.distance_count = 0;
	sport_data.resistance.number = 1;
	F_setVmsDetectionVal(30);
	//fristSportFlg = 1;
	R_SegmentsTime = 0;
	R_Segments = 0;
	F_NoramalLevelCount(sport_data.resistance.number,R_Segments);
}

