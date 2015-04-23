#include "chandler.h"

static void	F_setManualChooseMode(void)
{
		switch(ui_action.Event) {
		case	showManualFatBurnEventVal:
			F_setManualFatBurnInit();	
			break;
		case	showManualCardicEventVal:
			F_setManualCardioInit();
			break;
		case	showManualTargetEventVal:
			F_setManualTargetInit();
			break;
		}
}

static	void	F_ManualSportMode(void)
{
	rt_uint8_t	WorkOutTimeMin;
	rt_uint8_t	Target;
		switch(ui_action.Event) {
		case	showManualFatBurnEventVal:
		WorkOutTimeMin = set_manual_data.FatBurnWorkoutMinTime.number;
		Target = set_manual_data.FatBurnTarget;
			break;
		case	showManualCardicEventVal:
		WorkOutTimeMin = set_manual_data.CardioWorkoutMinTime.number;
		Target = set_manual_data.CardioTarget;
			break;
		case	showManualTargetEventVal:
		WorkOutTimeMin = set_manual_data.TargetWorkoutMinTime.number;
		Target = set_manual_data.TargetTarget.number;
			break;
		}
		
		F_ProfilesManualSportInit(WorkOutTimeMin,Target,ui_action.Event);
}

void F_setProfilesManual(void)
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
							F_ManualSportMode();
						break;
						case	stop_rest_KeyVal:
							bz_short();
							F_setProfileInit(setManualEventVal);
						break;
						case	enter_KeyVal:
							bz_short();
							F_setManualChooseMode();
						break;
						case	resistance_up_KeyVal:
							bz_short();
							if(ui_action.Event > showManualFatBurnEventVal)
								ui_action.Event--;
								else
									ui_action.Event = showManualTargetEventVal;
							break;
						case	resistance_down_KeyVal:
							bz_short();
							ui_action.Event++;
							if(ui_action.Event>showManualTargetEventVal)
								ui_action.Event = showManualFatBurnEventVal;
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event) {
						case	showManualFatBurnEventVal:
							F_showFatburn();
							break;
						case	showManualCardicEventVal:
							F_showCardio();
							break;
						case	showManualTargetEventVal:
							F_showTarget();
							break;
					}
					F_Display();
				}
				//=====================
			}
}

void F_setProfilesManualInit(rt_uint8_t Event)
{
		ui_action.Status = setProfilesManualVal;
		ui_action.Event = Event;
}
