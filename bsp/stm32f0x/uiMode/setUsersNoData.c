#include "chandler.h"
#include "24lcxx_user.h"

static	rt_uint8_t	TimeCount;
		
static void	F_ChooseProfileLeveArry(rt_uint8_t Profile) 
{
	switch(Profile) {
		case setUserRollingHillEventVal:
			F_RollingHillLevelCount(set_user_data.userLevel.number,sport_data.progfileArry,ProgfileDataSizeVal);
			break;		
		case setUserPeakEventVal:
			F_PeakLevelCount(set_user_data.userLevel.number,sport_data.progfileArry,ProgfileDataSizeVal);
			break;	
		case setUserPlateauEventVal:
			F_PlateauLevelCount(set_user_data.userLevel.number,sport_data.progfileArry,ProgfileDataSizeVal);
			break;	
		case setUserClimbEventVal:
			F_ClimbLevelCount(set_user_data.userLevel.number,sport_data.progfileArry,ProgfileDataSizeVal);
			break;	
		case setUserInterval_1_EventVal:
			F_Interval_1_LevelCount(set_user_data.userLevel.number,sport_data.progfileArry,ProgfileDataSizeVal);
			break;	
		case setUserInterval_2_EventVal:
			F_Interval_2_LevelCount(set_user_data.userLevel.number,sport_data.progfileArry,ProgfileDataSizeVal);
			break;	
	}
}	
		
static void F_TimeCount(void)	
{
		TimeCount++;
		if(TimeCount >= 10) {
			TimeCount = 0;
			ui_action.Event = setUsersName_1_EventVal;
		}
}

static void F_SetNameUp(rt_uint8_t *Data,rt_uint8_t DataAdr)	
{
	rt_uint8_t NameData;
	
	NameData = *(Data + DataAdr);
	
    if((NameData >= ' ') && (NameData <= 'Z')) {
			if(NameData ==  ' ') {
				NameData = 'A';
			} else if((NameData >= 'A') && (NameData <= 'Z')) {
				if(NameData == 'Z') {
					NameData = '0';
				} else {
					NameData++;
				}
			} else {
				if(NameData == '9') {
					NameData = ' ';
				} else {
					NameData++;
				}
			}
    } else {
        NameData = ' ';
		}
		*(Data + DataAdr) = NameData;
}
		
static void F_SetNameDown(rt_uint8_t *Data,rt_uint8_t DataAdr)	
{
	rt_uint8_t NameData;
	
	NameData = *(Data + DataAdr);
	
    if((NameData >= ' ') && (NameData <= 'Z')) {
      if(NameData == ' ') {
          NameData = '9';
      } else if((NameData >= '0') && (NameData <= '9')) {
					if(NameData == '0') {
						NameData = 'Z';
					} else {
						NameData--;
					}
			} else {
					if(NameData== 'A' ) {
						NameData = ' ';
					} else {
						NameData--;
					}
			}
    } else {
        NameData = ' ';
		}
		
		*(Data + DataAdr) = NameData;
}

static void F_SetUsersNameUpDownKey(rt_uint8_t Key,rt_bool_t LongKeyStartFlg,rt_uint8_t adr)
{
	switch(Key) {
		case	resistance_up_KeyVal:
		if(LongKeyStartFlg == 0)	
			bz_short();
		F_SetNameUp(set_user_data.UserNaume,adr);
			break;
		case	resistance_down_KeyVal:
		if(LongKeyStartFlg == 0)	
			bz_short();
		F_SetNameDown(set_user_data.UserNaume,adr);
			break;
	}
}

static void F_SetUsersEnterStopKey(rt_uint8_t Key)
{
	switch(Key) {
		case	enter_KeyVal:
		bz_short();
		if(ui_action.Event < setUserRollingHillEventVal) {
			ui_action.Event++;
			if(ui_action.Event > setWeightEventVal) {
				ui_action.Event = set_user_data.UserProfileChoose;
			}
		} else if(ui_action.Event <= setUserInterval_2_EventVal) {
			set_user_data.UserProfileChoose = ui_action.Event;
			F_ChooseProfileLeveArry(set_user_data.UserProfileChoose);
			ui_action.Event = setUserProfileLevelEventVal;
		} else if(ui_action.Event <= setUserProfileWorkOutTImeEventVal) {
			ui_action.Event++;
			if(ui_action.Event > setUserProfileWorkOutTImeEventVal) {
				F_setUsersInit(ui_action.UsersEventSave);
			}
		}
			break;
		case	stop_rest_KeyVal:
		if(ui_action.Event < setUserRollingHillEventVal) {
			if(ui_action.Event > setUsersName_1_EventVal) {
				bz_short();
				ui_action.Event--;
			} else {
				//F_setUsersInit(ui_action.UsersEventSave);
			}
		} else if(ui_action.Event <= setUserInterval_2_EventVal) {
			ui_action.Event = setWeightEventVal;
		} else if(ui_action.Event == setUserProfileLevelEventVal) {		
			ui_action.Event = set_user_data.UserProfileChoose;
		} else if(ui_action.Event == setUserProfileWorkOutTImeEventVal) {
			ui_action.Event = setUserProfileLevelEventVal;
		}
			break;
	}
}	

static void F_SetUsersEnterNameKey(rt_uint8_t Key,rt_uint8_t DataAdr)
{
	switch(Key) {
		case	enter_KeyVal:
		F_eeprom_user_name(WriteSpecificDataAdrVal,ui_action.UsersEventSave,set_user_data.UserNaume,DataAdr);
			break;
	}
}

static void F_SetUsersGenderUpDown(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
	switch(Key) {
		case	resistance_up_KeyVal:
		if(LongKeyStartFlg == 0)	{
			bz_short();
			if(set_user_data.Gender)
				set_user_data.Gender = 0;
				else
					set_user_data.Gender = 1;
		}
			break;
		case	resistance_down_KeyVal:
		if(LongKeyStartFlg == 0)	{
			bz_short();
			if(set_user_data.Gender)
				set_user_data.Gender = 0;
				else
					set_user_data.Gender = 1;
		}
			break;
	}
}

static void F_SetUsersAgeUpDown(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
	switch(Key) {
		case	resistance_up_KeyVal:
		if(LongKeyStartFlg == 0){
			bz_short();
		}
		F_NumberUp_8(&set_user_data.age,1,cycleNumberVal);
			break;
		case	resistance_down_KeyVal:
		if(LongKeyStartFlg == 0){
			bz_short();
		}
		F_NumberDown_8(&set_user_data.age,1,cycleNumberVal);
			break;
	}
}

static void F_SetUsersWeightUpDown(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
	switch(Key) {
		case	resistance_up_KeyVal:
		if(LongKeyStartFlg == 0){
			bz_short();
		}
		F_NumberUp_8(&set_user_data.Weight,1,cycleNumberVal);
			break;
		case	resistance_down_KeyVal:
		if(LongKeyStartFlg == 0){
			bz_short();
		}
		F_NumberDown_8(&set_user_data.Weight,1,cycleNumberVal);
			break;
	}
}

void	F_SetUserProfileChooseUpDown(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
		switch(Key) {
			case	resistance_up_KeyVal:
			if(LongKeyStartFlg == 0)	{
				bz_short();
				ui_action.Event++;
				if(ui_action.Event>setUserInterval_2_EventVal)
					ui_action.Event = setUserRollingHillEventVal;
			}
				break;
			case	resistance_down_KeyVal:
			if(LongKeyStartFlg == 0)	{
				bz_short();
				if(ui_action.Event > setUserRollingHillEventVal)
					ui_action.Event--;
					else
						ui_action.Event = setUserInterval_2_EventVal;
			}
				break;
		}
}

void	F_SetUserLevelChooseUpDown(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
		switch(Key) {
			case	resistance_up_KeyVal:
			if(F_NumberUp_8(&set_user_data.userLevel,1,noCycleNumberVal).complyFlg == YesComplyVal) {
				F_ChooseProfileLeveArry(set_user_data.UserProfileChoose);
				if(LongKeyStartFlg == 0){
					bz_short();
				}
			}
				break;
			case	resistance_down_KeyVal:
			if(F_NumberDown_8(&set_user_data.userLevel,1,noCycleNumberVal).complyFlg == YesComplyVal) {
				F_ChooseProfileLeveArry(set_user_data.UserProfileChoose);
				if(LongKeyStartFlg == 0){
					bz_short();
				}
			}
				break;
		}
}

void	F_SetUserWorkoutTimeChooseUpDown(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
		switch(Key) {
			case	resistance_up_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberUp_8(&set_user_data.userWorkoutTime,1,cycleNumberVal);
				break;
			case	resistance_down_KeyVal:
			if(LongKeyStartFlg == 0){
				bz_short();
			}
			F_NumberDown_8(&set_user_data.userWorkoutTime,1,cycleNumberVal);
				break;
		}
}

void F_setUsersNoData(void)
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
					F_SeatPositionControlAllKey(keyCode,LongKeyStartFlg);
					switch(ui_action.Event) {
						case setUsersNoDataEventVal:

							break;
						case setUsersName_1_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,0);
						F_SetUsersEnterNameKey(keyCode,0);
							break;
						case setUsersName_2_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,1);
						F_SetUsersEnterNameKey(keyCode,1);
							break;
						case setUsersName_3_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,2);
						F_SetUsersEnterNameKey(keyCode,2);
							break;
						case setUsersName_4_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,3);
						F_SetUsersEnterNameKey(keyCode,3);
							break;
						case setUsersName_5_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,4);
						F_SetUsersEnterNameKey(keyCode,4);
							break;
						case setUsersName_6_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,5);
						F_SetUsersEnterNameKey(keyCode,5);
							break;
						case setUsersName_7_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,6);
						F_SetUsersEnterNameKey(keyCode,6);
							break;
						case setUsersName_8_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,7);
						F_SetUsersEnterNameKey(keyCode,7);
							break;
						case setUsersName_9_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,8);
						F_SetUsersEnterNameKey(keyCode,8);
							break;
						case setUsersName_10_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,9);
						F_SetUsersEnterNameKey(keyCode,9);
							break;
						case setSeatPositionEventVal:
						F_SetUsersEnterStopKey(keyCode);
							break;
						case setGenderEventVal:
						F_SetUsersGenderUpDown(keyCode,LongKeyStartFlg);	
						F_SetUsersEnterStopKey(keyCode);
							break;
						case setAgeEventVal:
						F_SetUsersAgeUpDown(keyCode,LongKeyStartFlg);
						F_SetUsersEnterStopKey(keyCode);
							break;
						case setWeightEventVal:
						F_SetUsersWeightUpDown(keyCode,LongKeyStartFlg);
						F_SetUsersEnterStopKey(keyCode);
							break;
						case setUserRollingHillEventVal:
						case setUserPeakEventVal:
						case setUserPlateauEventVal:
						case setUserClimbEventVal:
						case setUserInterval_1_EventVal:
						case setUserInterval_2_EventVal:
						F_SetUsersEnterStopKey(keyCode);	
						F_SetUserProfileChooseUpDown(keyCode,LongKeyStartFlg);
							break;
						case setUserProfileLevelEventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUserLevelChooseUpDown(keyCode,LongKeyStartFlg);
							break;
						case setUserProfileWorkOutTImeEventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUserWorkoutTimeChooseUpDown(keyCode,LongKeyStartFlg);
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event) {
						case setUsersNoDataEventVal:
							F_showNoData();
							F_TimeCount();
							break;
						case setUsersName_1_EventVal:
							F_showSetUserName(0,set_user_data.UserNaume,10);
							break;
						case setUsersName_2_EventVal:
							F_showSetUserName(1,set_user_data.UserNaume,10);
							break;
						case setUsersName_3_EventVal:
							F_showSetUserName(2,set_user_data.UserNaume,10);
							break;
						case setUsersName_4_EventVal:
							F_showSetUserName(3,set_user_data.UserNaume,10);
							break;
						case setUsersName_5_EventVal:
							F_showSetUserName(4,set_user_data.UserNaume,10);
							break;
						case setUsersName_6_EventVal:
							F_showSetUserName(5,set_user_data.UserNaume,10);
							break;
						case setUsersName_7_EventVal:
							F_showSetUserName(6,set_user_data.UserNaume,10);
							break;
						case setUsersName_8_EventVal:
							F_showSetUserName(7,set_user_data.UserNaume,10);
							break;
						case setUsersName_9_EventVal:
							F_showSetUserName(8,set_user_data.UserNaume,10);
							break;
						case setUsersName_10_EventVal:
							F_showSetUserName(9,set_user_data.UserNaume,10);
							break;
						case setSeatPositionEventVal:
							F_showSetSeatPosition();
							break;
						case setGenderEventVal:
							F_showGender(set_user_data.Gender);
							break;
						case setAgeEventVal:
							F_showSetAge(set_user_data.age.number);
							break;
						case setWeightEventVal:
							F_showSetWeight(set_user_data.Weight.number);
							break;
						case setUserRollingHillEventVal:
							F_showRollingHillGraph();
							break;
						case setUserPeakEventVal:
							F_showPeakGraph();
							break;
						case setUserPlateauEventVal:
							F_showPlateauGraph();
							break;
						case setUserClimbEventVal:
							F_showClimbGraph();
							break;
						case setUserInterval_1_EventVal:
							F_showInterval_1_Graph();
							break;
						case setUserInterval_2_EventVal:
							F_showInterval_2_Graph();
							break;
						case setUserProfileLevelEventVal:
							F_showProfileSetLeve(set_user_data.userLevel.number);
							F_ShowProgfileGraph(sport_data.progfileArry,ProgfileDataSizeVal,CommonModeVal,0,0);
							break;
						case setUserProfileWorkOutTImeEventVal:
						SetWorkoutTime.timeH = set_user_data.userWorkoutTime.number;
						SetWorkoutTime.timeL = 0;
						F_showProfileSetWorkoutTime(SetWorkoutTime);
							break;
					}
					F_Display();
				}
				//=====================
				if((e & time_1s_val) == time_1s_val)
				{
					
					
				}
			}
}

void F_setUsersNoDataInit(void)
{
		rt_uint8_t	i;
		rt_uint8_t	AdTemp;
	
		ui_action.Status = setUsersNoDataVal;
		ui_action.Event = setUsersNoDataEventVal;
		TimeCount = 0;
		for(i=0;i<10;i++) {
			set_user_data.UserNaume[i] = ' ';
		}
		
		F_eeprom_user_name(WriteDataVal,ui_action.UsersEventSave,set_user_data.UserNaume,0);
		AdTemp = rt_inc_read_ad();
		F_eeprom_user_seat_position(WriteDataVal,ui_action.UsersEventSave,&AdTemp);
		
		set_user_data.age.maxNumber = 99;
		set_user_data.age.minNumber = 10;
		set_user_data.age.number = 40;
		F_eeprom_user_age(WriteDataVal,ui_action.UsersEventSave,&set_user_data.age.number);
		
		set_user_data.Weight.maxNumber = 250;
		set_user_data.Weight.minNumber = 100;
		set_user_data.Weight.number = 150;
		F_eeprom_user_wigeht(WriteDataVal,ui_action.UsersEventSave,&set_user_data.Weight.number);
		set_user_data.Gender = 1;
		F_eeprom_user_gender(WriteDataVal,ui_action.UsersEventSave,&set_user_data.Gender);
				
		set_user_data.userLevel.number = 7;
		set_user_data.userLevel.maxNumber = 20;
		set_user_data.userLevel.minNumber = 1;
		
		set_user_data.userWorkoutTime.number = workOutTimeMinuteNumVal;
		set_user_data.userWorkoutTime.maxNumber = workOutTimeMinuteNumMaxVal;
		set_user_data.userWorkoutTime.minNumber = workOutTimeMinuteNumMinVal;
		
		set_user_data.UserProfileChoose = setUserRollingHillEventVal;
}



