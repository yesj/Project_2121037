#include "chandler.h"

static 	rt_uint8_t	R_Segments,R_SegmentsTime;
static 	rt_bool_t		FlickerFlg;

static void	F_LevelCount(rt_uint8_t Level,rt_uint8_t Segments)
{
		rt_uint8_t adr;
		
		F_Menual_LevelCount(Level,sport_data.progfileArry,ProgfileDataSizeVal);
		for(adr = Segments ; adr < ProgfileDataSizeVal ; adr++) {
			sport_data.progfileArryBuf[adr] = sport_data.progfileArry[adr];
		}
}

void F_manualSport(void)
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
							F_LevelCount(sport_data.resistance.number,R_Segments);
						}
						break;
						case	resistance_down_KeyVal:
						if(F_NumberDown_8(&sport_data.resistance,1,noCycleNumberVal).complyFlg == YesComplyVal) {
							if(LongKeyStartFlg == 0){
								bz_short();
							}
							F_LevelCount(sport_data.resistance.number,R_Segments);
						}
						break;
						case	stop_rest_KeyVal:
							bz_short();
							F_manualSportInit();
						break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					F_showMatrixProfileWrokOutTime(TimeData);
					F_ShowProgfileGraph(sport_data.progfileArryBuf,ProgfileDataSizeVal,FlickerModeVal,R_Segments,FlickerFlg);
					F_showResistance(sport_data.resistance.number);
					F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
					F_showCal(calor_count.calorie);
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
						F_setProfileManualInit();
					}
				}
			}
}

void F_manualSportInit(void)
{
	ui_action.Status = manualSportVal;
	//ui_action.Event = ;
	memset(&calor_count,0,sizeof(calor_count));
	F_setVmsDetectionVal(30);
	TimeData.timeH = set_profile_data.menualWorkoutTime.number;
	TimeData.timeL = 0;
	R_SegmentsTime = TimeData.timeH;
	F_ProfileTimeSegments(&R_Segments,TimeData,R_SegmentsTime,59);
	sport_data.resistance.number = set_profile_data.menualLevel.number;
	F_LevelCount(sport_data.resistance.number,R_Segments);
	FlickerFlg = 0;
}

