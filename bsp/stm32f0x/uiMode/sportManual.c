#include "chandler.h"

static 	rt_uint8_t VmsDetectionTime;
//static 	rt_bool_t fristSportFlg;

void	F_VmsDetection(rt_uint8_t rpm)
{
		if(rpm) {
			VmsDetectionTime = 0;
			F_vms_control(sport_data.resistance.number);
		} else {
			VmsDetectionTime++;
			if(VmsDetectionTime>=30) {
				VmsDetectionTime = 30;
				F_vms_control(0);
			} else {
				F_vms_control(sport_data.resistance.number);
			}
		}
	/*
	if(fristSportFlg) {
		//第一次進入運動模式
		VmsDetectionTime++;
		if(VmsDetectionTime>=10) {
			VmsDetectionTime = 0;
			fristSportFlg = 0;
		}
	} else {
		if(rpm) {
			VmsDetectionTime = 0;
			F_vms_control(sport_data.resistance.number);
		} else {
			VmsDetectionTime++;
			if(VmsDetectionTime>=30) {
				VmsDetectionTime = 30;
				F_vms_control(0);
			} else {
				F_vms_control(sport_data.resistance.number);
			}
		}
	}
	*/
}

void F_ShowBasicView(void)
{
		F_showMatrixTime(TimeData);
		F_showResistance(sport_data.resistance.number);
		F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
		F_showCal(calor_count.calorie);
}


void F_ShowHeartRateView(void)
{
	F_show8Time(TimeData);
	F_showResistance(sport_data.resistance.number);
	F_showDistance(distance_data.distance_count);
	F_showHearRateGraph(F_readHandHeartRate(),F_readwHeartRate());
}

void F_ShowCalorieView(void)
{
	F_show8Time(TimeData);
	F_showResistance(sport_data.resistance.number);
	F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
	F_showMatrixCal(calor_count.calorie);
	//F_showMatrixCalHr(calor_count.calorie);
}

void F_SportManual(void)
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
							bz_short();
						}
						break;
						case	resistance_down_KeyVal:
						if(F_NumberDown_8(&sport_data.resistance,1,noCycleNumberVal).complyFlg == YesComplyVal) {
							bz_short();
						}
						break;
						case	view_KeyVal:
							bz_short();
							ui_action.Event++;
							if(ui_action.Event > CalorieVewVal) 
							{
								ui_action.Event = BasicViewVal;
							}
						break;
						case	stop_rest_KeyVal:
							bz_short();
							F_setNoramalInit();
						break;	
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event)
					{
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
					F_Display();
				}
				//=====================
				if((e & time_1s_val) == time_1s_val)
				{
					F_timer_process_up(&TimeData);
					calor_count.level = sport_data.resistance.number;
					F_readWatte(calor_count.level,&calor_count.watt);					
					F_calorie_process(&calor_count);
					//rt_kprintf("RPM:%d \r\n",F_readRpm());
					distance_data.rpm = F_readRpm();
					F_VmsDetection(distance_data.rpm);
					distance_data.WheelSize = 300;
					F_distance_process(&distance_data);
				}
			}
}

void	F_SportManualInit(void)
{
	ui_action.Status = sportManualVal;
	ui_action.Event	= BasicViewVal;
	memset(&TimeData,0,sizeof(TimeData));
	memset(&calor_count,0,sizeof(calor_count));
	sport_data.resistance.number = 1;
	VmsDetectionTime = 30;
	//fristSportFlg = 1;
}

