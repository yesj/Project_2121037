#include "chandler.h"
#include "24lcxx_user.h"

static rt_uint8_t SeatPositionUnlockEvent = 0;

static void	F_ClearSwitchingSeatPositionDisplay(void)
{
	ui_action.TemporarySeatPositionEvent = TemporarySeatPositionNormalEventVal;
	//ui_action.TemporaryEventTimer = 3;
}

static void	F_SwitchingSeatPositionMoveDisplay(void)
{
	ui_action.TemporarySeatPositionEvent = TemporarySeatPositionMoveEventVal;
	ui_action.TemporaryEventTimer = 0;
}

static void	F_SwitchingSeatPositionUnlockDisplay(void)
{
	ui_action.TemporarySeatPositionEvent = TemporarySeatPositionUnlockEventVal;
	ui_action.TemporaryEventTimer = 0;
}

static void	F_SwitchingSeatPositionUnlockNoDisplay(void)
{
	ui_action.TemporarySeatPositionEvent = TemporarySeatPositionUnlockNoEventVal;
	ui_action.TemporaryEventTimer = 0;
}

void	F_SwitchingSeatPositionDisplayTimer(void)
{
		ui_action.TemporaryEventTimer++;
		if(ui_action.TemporaryEventTimer > 3) {
			ui_action.TemporaryEventTimer=3;
			ui_action.TemporarySeatPositionEvent = TemporarySeatPositionNormalEventVal;
			if(SeatPositionUnlockEvent == 2) {
				SeatPositionUnlockEvent = 1;
			}
		}
}

void	F_SeatPositionControlAllKey(rt_uint8_t *Key,rt_bool_t LongKeyStartFlg)
{
	rt_bool_t	TempFlg = 0;

	switch(SeatPositionUnlockEvent) {
		case	0:
			switch(*Key)
			{
				case	long_view_KeyVal:
					bz_short();
					SeatPositionUnlockEvent = 1;
					TempFlg = 1;
					F_SwitchingSeatPositionUnlockDisplay();
					break;
				case	seat_position_stop_KeyVal:
					bz_short();
					TempFlg = 1;
					rt_seat_position_stop();
				break;
				case	seat_position_up_KeyVal:
				case	fast_seat_position_up_KeyVal:
					TempFlg = 1;
					rt_seat_position_up();
					F_SwitchingSeatPositionMoveDisplay();
					if(LongKeyStartFlg==0)
						bz_short();
				break;
				case	seat_position_down_KeyVal:
				case	fast_seat_position_down_KeyVal:
					TempFlg = 1;
					rt_seat_position_down();
					F_SwitchingSeatPositionMoveDisplay();
					if(LongKeyStartFlg==0)
						bz_short();
				break;
				case	seat_position_home_1_KeyVal:	// 最高點
					bz_short();			
				rt_inc_micro_control(sport_data.saveSeatPositionHome_1);
				TempFlg = 1;
				F_SwitchingSeatPositionMoveDisplay();
				break;	
				case	seat_position_home_2_KeyVal:	// 最低點
					bz_short();
				rt_inc_micro_control(sport_data.saveSeatPositionHome_2);
				TempFlg = 1;
				F_SwitchingSeatPositionMoveDisplay();
				break;	
				case	seat_position_home_1_long_KeyVal:
				bz_short3bz();
				sport_data.saveSeatPositionHome_1 = rt_inc_read_ad();
				F_eeprom_home1_data(1,&sport_data.saveSeatPositionHome_1);
				break;	
				case	seat_position_home_2_long_KeyVal:
				bz_short3bz();
				sport_data.saveSeatPositionHome_2 = rt_inc_read_ad();
				F_eeprom_home2_data(1,&sport_data.saveSeatPositionHome_2);
				break;	
			}
			break;
		//====================================
		case	1:
			switch(*Key)
			{
				case	long_view_KeyVal:
					bz_short();
					TempFlg = 1;
					SeatPositionUnlockEvent = 2;
					F_SwitchingSeatPositionUnlockNoDisplay();		
					break;
				case	seat_position_stop_KeyVal:
				case	seat_position_up_KeyVal:
				case	fast_seat_position_up_KeyVal:
				case	seat_position_down_KeyVal:
				case	fast_seat_position_down_KeyVal:
				case	seat_position_home_1_KeyVal:
				case	seat_position_home_2_KeyVal:
				case	seat_position_home_1_long_KeyVal:
				case	seat_position_home_2_long_KeyVal:
				TempFlg = 1;
				F_SwitchingSeatPositionUnlockDisplay();
					break;
			}
			break;
		//====================================
		case	2:
			switch(*Key)
			{
				case	seat_position_stop_KeyVal:
					TempFlg = 1;		
					break;
				case	seat_position_up_KeyVal:
				case	seat_position_down_KeyVal:
					ui_action.TemporaryEventTimer = 0;
					TempFlg = 1;
					if(LongKeyStartFlg==0) {
						bz_short();
						if(ui_action.TemporarySeatPositionEvent == TemporarySeatPositionUnlockYesEventVal)
							ui_action.TemporarySeatPositionEvent = TemporarySeatPositionUnlockNoEventVal;
							else
								ui_action.TemporarySeatPositionEvent = TemporarySeatPositionUnlockYesEventVal;
					}
					break;
				case	enter_KeyVal:
					bz_short();
					*Key = 0;
					if(ui_action.TemporarySeatPositionEvent == TemporarySeatPositionUnlockYesEventVal) {
						SeatPositionUnlockEvent = 0;
					}
					break;
			}
			break;
	}

	if(TempFlg == 0)	{
		if(*Key) {
			if(ui_action.TemporarySeatPositionEvent) {
				F_ClearSwitchingSeatPositionDisplay();
			}
		}
	}	
}

void	F_SetUserKey(rt_uint8_t keyCode) 
{
		switch(keyCode)
		{
			case	user_KeyVal:
			bz_short();
			F_setUsersInit(setUser_1_EventVal);
				break;
		}	
}

void	F_SetProgramsKey(rt_uint8_t keyCode) 
{
		switch(keyCode)
		{
			case	programs_KeyVal:
			bz_short();
			F_setProfileInit(setProfileEventVal);
				break;
		}	
}

void	F_LongRestKey(rt_uint8_t keyCode) 
{
		switch(keyCode)
		{
			case	long_stop_rest_KeyVal:
			IWDG_Config(0);	
			while(1)
				break;
		}
}

static 	rt_uint8_t	VmsDetectionTime;

void	F_VmsDetection(rt_uint8_t rpm,rt_uint8_t resistance)
{
		if(rpm) {
			VmsDetectionTime = 0;
			F_vms_control(resistance);
		} else {
			VmsDetectionTime++;
			if(VmsDetectionTime>=30) {
				VmsDetectionTime = 30;
				F_vms_control(0);
			} else {
				F_vms_control(resistance);
			}
		}
}

void	F_setVmsDetectionVal(rt_uint8_t val)
{
	VmsDetectionTime = val;
	
}
