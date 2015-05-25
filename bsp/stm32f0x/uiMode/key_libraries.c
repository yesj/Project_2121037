#include "chandler.h"
#include "24lcxx_user.h"

void	F_ClearSwitchingSeatPositionDisplay(void)
{
	ui_action.TemporaryEventFlg = 0;
	//ui_action.TemporaryEventTimer = 3;
}

void	F_SwitchingSeatPositionDisplay(void)
{
	ui_action.TemporaryEventFlg = 1;
	ui_action.TemporaryEventTimer = 0;
}

void	F_SwitchingSeatPositionDisplayTimer(void)
{
		ui_action.TemporaryEventTimer++;
		if(ui_action.TemporaryEventTimer > 3) {
			ui_action.TemporaryEventTimer=3;
			ui_action.TemporaryEventFlg = 0;
		}
}

void	F_SeatPositionControlAllKey(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
	rt_bool_t	TempFlg = 0;
		switch(Key)
		{
			case	seat_position_stop_KeyVal:
				TempFlg = 1;
				rt_seat_position_stop();
				bz_short();
			break;
			case	seat_position_up_KeyVal:
			case	fast_seat_position_up_KeyVal:
				TempFlg = 1;
				rt_seat_position_up();
				F_SwitchingSeatPositionDisplay();
				if(LongKeyStartFlg==0)
					bz_short();
			break;
			case	seat_position_down_KeyVal:
			case	fast_seat_position_down_KeyVal:
				TempFlg = 1;
				rt_seat_position_down();
				F_SwitchingSeatPositionDisplay();
				if(LongKeyStartFlg==0)
					bz_short();
			break;
			case	seat_position_home_1_KeyVal:	// 最高點
				bz_short();			
			rt_inc_micro_control(sport_data.saveSeatPositionHome_1);
			TempFlg = 1;
			F_SwitchingSeatPositionDisplay();
			break;	
			case	seat_position_home_2_KeyVal:	// 最低點
				bz_short();
			rt_inc_micro_control(sport_data.saveSeatPositionHome_2);
			TempFlg = 1;
			F_SwitchingSeatPositionDisplay();
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
	if(TempFlg == 0)	{
		if(Key) {
			if(ui_action.TemporaryEventFlg) {
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
