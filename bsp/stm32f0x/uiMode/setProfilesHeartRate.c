#include "chandler.h"

static void	F_setHeartRateChooseMode(void)
{
		switch(ui_action.Event) {
		case	showHeartRateFatBurnEventVal:
			F_setHeartRateFatBurnInit();	
			break;
		case	showHeartRateCardicEventVal:
			F_setHeartRateCardioInit();
			break;
		case	showHeartRateTargetEventVal:
			F_setHeartRateTargetInit();
			break;
		}
}

static	void	F_HeartRateSportMode(void)
{
	rt_uint8_t	WorkOutTimeMin;
	rt_uint8_t	Target;
		switch(ui_action.Event) {
		case	showHeartRateFatBurnEventVal:
		WorkOutTimeMin = profile_heartrate_data.FatBurnWorkoutMinTime.number;
		Target = profile_heartrate_data.FatBurnTarget;
			break;
		case	showHeartRateCardicEventVal:
		WorkOutTimeMin = profile_heartrate_data.CardioWorkoutMinTime.number;
		Target = profile_heartrate_data.CardioTarget;
			break;
		case	showHeartRateTargetEventVal:
		WorkOutTimeMin = profile_heartrate_data.TargetWorkoutMinTime.number;
		Target = profile_heartrate_data.TargetTarget.number;
			break;
		}
		
		F_ProfilesHeartRateSportInit(WorkOutTimeMin,Target,ui_action.Event);
}

void F_setProfilesHeartRate(void)
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
					F_SetUserKey(keyCode);
					switch(keyCode)
					{
						case	quick_start_KeyVal:
							bz_short();
							F_HeartRateSportMode();
						break;
						case	stop_rest_KeyVal:
							bz_short();
							F_setProfileInit(setHeartRateEventVal);
						break;
						case	enter_KeyVal:
							bz_short();
							F_setHeartRateChooseMode();
						break;
						case	resistance_up_KeyVal:
							bz_short();
							if(ui_action.Event > showHeartRateFatBurnEventVal)
								ui_action.Event--;
								else
									ui_action.Event = showHeartRateTargetEventVal;
							break;
						case	resistance_down_KeyVal:
							bz_short();
							ui_action.Event++;
							if(ui_action.Event>showHeartRateTargetEventVal)
								ui_action.Event = showHeartRateFatBurnEventVal;
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event) {
						case	showHeartRateFatBurnEventVal:
							F_showFatburn();
							break;
						case	showHeartRateCardicEventVal:
							F_showCardio();
							break;
						case	showHeartRateTargetEventVal:
							F_showTarget();
							break;
					}
					F_Display();
				}
				//=====================
			}
}

void F_setProfilesHeartRateInit(rt_uint8_t Event)
{
		ui_action.Status = setProfilesHeartRateVal;
		ui_action.Event = Event;
}
