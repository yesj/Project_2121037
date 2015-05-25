#include "chandler.h"

static	rt_uint32_t	FocusFormulaSegmentsTime;
static	rt_uint16_t	FocusFormulaTime;
static	rt_uint8_t	FocusFormulaStatus;


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

void	F_FocusFormulaTime(void)
{
		FocusFormulaTime++;
		FocusFormulaStatus = ((FocusFormulaTime*1000) / FocusFormulaSegmentsTime);
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
					F_SeatPositionControlAllKey(keyCode,LongKeyStartFlg);
					switch(keyCode)
					{
						case	stop_rest_KeyVal:
						bz_short();
						F_setProfilesFocusInit(ui_action.FocusEventSave);
						break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					if(ui_action.TemporaryEventFlg == 0) {
						F_show8Time(TimeData);
						F_showResistance(sport_data.resistance.number);
						F_show8HearRate(F_readHandHeartRate(),F_readwHeartRate());
						F_showAction();
					} else {
						F_showSeatPositionMove();
					}
					F_Display();
				}
				//=====================
				if((e & time_1s_val) == time_1s_val)
				{
					F_SwitchingSeatPositionDisplayTimer();
					F_timer_process_down(&TimeData);
					if(TimeData.timeH != 0 || TimeData.timeL != 0) {
						F_FocusFormulaTime();
						distance_data.rpm = F_readRpm();
						F_VmsDetection(distance_data.rpm,sport_data.resistance.number);
					} else {
						F_setProfilesFocusInit(ui_action.FocusEventSave);
					}
				}
			}
}

void F_FocusSportInit(void)
{
		ui_action.Status = FocusSportVal;
	//ui_action.Event = ;
		TimeData.timeH = set_focus_data.FocusWorkoutMinTime.number;
		TimeData.timeL = 0;
		F_FocusFormulaSegmentsTime(set_focus_data.FocusWorkoutMinTime.number);
		sport_data.resistance.number = 1;
		F_setVmsDetectionVal(30);
		FocusFormulaStatus = 0;
		FocusFormulaTime = 0;
		
}
