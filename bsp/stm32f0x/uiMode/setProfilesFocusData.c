#include "chandler.h"

static void	F_setFocusLevelKey(rt_uint8_t keyCode,rt_bool_t LongKeyStartFlg)
{
		switch(keyCode)
		{
			case	quick_start_KeyVal:
			bz_short();
			F_FocusSportInit();
				break;
			case	enter_KeyVal:
			bz_short();
			ui_action.Event = FocusWorkoutTimeEventVal;
				break;
			case	stop_rest_KeyVal:
			bz_short();
			F_setProfilesFocusInit(ui_action.FocusEventSave);
				break;
			case	resistance_up_KeyVal:
			if(F_NumberUp_8(&set_focus_data.FocusLevel,1,noCycleNumberVal).complyFlg == YesComplyVal) {
				if(LongKeyStartFlg == 0){
					bz_short();
				}
			}
				break;
			case	resistance_down_KeyVal:
			if(F_NumberDown_8(&set_focus_data.FocusLevel,1,noCycleNumberVal).complyFlg == YesComplyVal) {
				if(LongKeyStartFlg == 0){
					bz_short();
				}
			}
				break;
		}
}

static void	F_setFocusWorkOutTImeKey(rt_uint8_t keyCode,rt_bool_t LongKeyStartFlg)
{
		switch(keyCode)
		{
			case	quick_start_KeyVal:
			case	enter_KeyVal:
			bz_short();
			F_FocusSportInit();
				break;
			case	stop_rest_KeyVal:
			bz_short();
			ui_action.Event = FocusMaximumLevelEventVal;
				break;
			case	resistance_up_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberUp_8(&set_focus_data.FocusWorkoutMinTime,1,cycleNumberVal);
				break;
			case	resistance_down_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberDown_8(&set_focus_data.FocusWorkoutMinTime,1,cycleNumberVal);
				break;
		}
}

void F_setProfilesFocusData(void)
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
					F_LongRestKey(keyCode);
					F_SeatPositionControlAllKey(&keyCode,LongKeyStartFlg);
					switch(ui_action.Event) 
					{
						case	FocusMaximumLevelEventVal:
						F_setFocusLevelKey(keyCode,LongKeyStartFlg);
							break;
						case	FocusWorkoutTimeEventVal:
						F_setFocusWorkOutTImeKey(keyCode,LongKeyStartFlg);
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					if(ui_action.TemporarySeatPositionEvent == TemporarySeatPositionNormalEventVal) {
						switch(ui_action.Event) {
							case	FocusMaximumLevelEventVal:
								F_ShowMaximumResistanceLevel(set_focus_data.FocusLevel.number);
								break;
							case	FocusWorkoutTimeEventVal:
							SetWorkoutTime.timeH = set_focus_data.FocusWorkoutMinTime.number;
							SetWorkoutTime.timeL = 0;
							F_showProfileSetWorkoutTime(SetWorkoutTime);	
								break;
						}
					} else {
						F_showSeatPositionStatus(ui_action.TemporarySeatPositionEvent);
					}
					F_Display();
				}
				//=====================
				if((e & time_1s_val) == time_1s_val)
				{
					F_SwitchingSeatPositionDisplayTimer();
				}
			}
}

void F_setProfilesFocusDataInit(void)
{
	ui_action.Status = setProfilesFocusDataVal;
	ui_action.Event = FocusMaximumLevelEventVal;
}
