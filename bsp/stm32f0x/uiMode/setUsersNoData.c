#include "chandler.h"
#include "24lcxx_user.h"

#define NoDataSetInitVal			0
#define DataSetInitVal				1

static	rt_uint8_t	TimeCount;
static 	rt_bool_t		UserSetOrNoDataFlg;

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

static void	F_ResetUserSportData(void)
{
		set_user_data.SportTimeSec = 0;
		F_eeprom_user_time(WriteDataVal,ui_action.UsersEventSave,&set_user_data.SportTimeSec);
		set_user_data.SportCal = 0;
		F_eeprom_user_cal(WriteDataVal,ui_action.UsersEventSave,&set_user_data.SportCal);
		set_user_data.SportKm = 0;
		F_eeprom_user_mile(WriteDataVal,ui_action.UsersEventSave,&set_user_data.SportKm);
}

static void F_TimeCount(void)	
{
		TimeCount++;
		if(TimeCount >= 10) {
			TimeCount = 0;
			ui_action.Event = setUsersName_1_EventVal;
		}
}

static void F_UserNameChangeDetection(void)
{
	rt_uint8_t	NumAdr = 0;
	rt_bool_t	SetFlg = 0;
	switch(ui_action.Event) {
		case setUsersName_1_EventVal:
		SetFlg = 1;
		NumAdr = 0;
			break;
		case setUsersName_2_EventVal:
		SetFlg = 1;
		NumAdr = 1;
			break;
		case setUsersName_3_EventVal:
		SetFlg = 1;
		NumAdr = 2;
			break;
		case setUsersName_4_EventVal:
		SetFlg = 1;
		NumAdr = 3;
			break;
		case setUsersName_5_EventVal:
		SetFlg = 1;
		NumAdr = 4;
			break;
		case setUsersName_6_EventVal:
		SetFlg = 1;
		NumAdr = 5;
			break;
		case setUsersName_7_EventVal:
		SetFlg = 1;
		NumAdr = 6;
			break;
		case setUsersName_8_EventVal:
		SetFlg = 1;
		NumAdr = 7;
			break;
		case setUsersName_9_EventVal:
		SetFlg = 1;
		NumAdr = 8;
			break;
	}
		if(SetFlg) {
			if(set_user_data.UserNaume[NumAdr] == ' ') {
				set_user_data.UserNaume[NumAdr] = 'A';
			}
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
		rt_uint8_t	buf;
	switch(Key) {
		case	enter_KeyVal:
		bz_short();
		if(ui_action.Event < setUserRollingHillEventVal) {
			ui_action.Event++;
			F_UserNameChangeDetection();
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
				if(UserSetOrNoDataFlg == NoDataSetInitVal) {
					F_ResetUserSportData();	//要先清除資料
					F_setUsersSportInit();
				} else {
					F_setUsersDataInit(showUserSeetingsEventVal);
				}
			}
		}
			break;
		case	stop_rest_KeyVal:
		bz_short();
		if(ui_action.Event < setUserRollingHillEventVal) {
			if(ui_action.Event > setUsersName_1_EventVal) {
				bz_short();
				ui_action.Event--;
			} else {
				if(UserSetOrNoDataFlg == NoDataSetInitVal) {
					buf = 0;
					F_eeprom_user_DetectionData(WriteDataVal,ui_action.UsersEventSave,&buf);		// 不儲存資料 離開 
					F_setUsersInit(ui_action.UsersEventSave);
				} else {
					F_setUsersDataInit(showUserSeetingsEventVal);
				}
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
		F_NumberUp_16(&set_user_data.Weight,1,cycleNumberVal);
			break;
		case	resistance_down_KeyVal:
		if(LongKeyStartFlg == 0){
			bz_short();
		}
		F_NumberDown_16(&set_user_data.Weight,1,cycleNumberVal);
			break;
	}
}

static void	F_SetUserProfileChooseUpDown(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
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

static void	F_SetUserLevelChooseUpDown(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
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

static void	F_SetUserWorkoutTimeChooseUpDown(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
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

static void	F_SetUserEnterSaveProfile(rt_uint8_t Key)
{
	switch(Key) {
		case	enter_KeyVal:
			F_eeprom_profile(WriteDataVal,ui_action.UsersEventSave,&ui_action.Event);
			break;
	}
}

static void	F_SetUserEnterSaveSeatPosition(rt_uint8_t Key)
{
	switch(Key) {
		case	enter_KeyVal:
		set_user_data.SetSeatPositionAd = rt_inc_read_ad();
		F_eeprom_user_seat_position(WriteDataVal,ui_action.UsersEventSave,&set_user_data.SetSeatPositionAd);
			break;
	}
}

static void	F_SetUserEnterSaveGender(rt_uint8_t Key)
{
	switch(Key) {
		case	enter_KeyVal:
		F_eeprom_user_gender(WriteDataVal,ui_action.UsersEventSave,&set_user_data.Gender);	
			break;
	}
}

static void	F_SetUserEnterSaveAge(rt_uint8_t Key)
{
	switch(Key) {
		case	enter_KeyVal:
		F_eeprom_user_age(WriteDataVal,ui_action.UsersEventSave,&set_user_data.age.number);
			break;
	}
}

static void	F_SetUserEnterSaveWeight(rt_uint8_t Key)
{
	switch(Key) {
		case	enter_KeyVal:
			F_eeprom_user_wigeht(WriteDataVal,ui_action.UsersEventSave,&set_user_data.Weight.number);
			break;
	}
}

static void	F_SetUserEnterSaveLeve(rt_uint8_t Key)
{
	switch(Key) {
		case	enter_KeyVal:
			F_eeprom_level(WriteDataVal,ui_action.UsersEventSave,&set_user_data.userLevel.number);
			break;
	}
}

static void	F_SetUserEnterSaveWorktime(rt_uint8_t Key)
{
	switch(Key) {
		case	enter_KeyVal:
			F_eeprom_worktime(WriteDataVal,ui_action.UsersEventSave,&set_user_data.userWorkoutTime.number);
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
					F_LongRestKey(keyCode);
					F_SeatPositionControlAllKey(&keyCode,LongKeyStartFlg);
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
						case setSeatPositionEventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUserEnterSaveSeatPosition(keyCode);
							break;
						case setGenderEventVal:
						F_SetUsersGenderUpDown(keyCode,LongKeyStartFlg);	
						F_SetUsersEnterStopKey(keyCode);
						F_SetUserEnterSaveGender(keyCode);
							break;
						case setAgeEventVal:
						F_SetUsersAgeUpDown(keyCode,LongKeyStartFlg);
						F_SetUsersEnterStopKey(keyCode);
						F_SetUserEnterSaveAge(keyCode);
							break;
						case setWeightEventVal:
						F_SetUsersWeightUpDown(keyCode,LongKeyStartFlg);
						F_SetUsersEnterStopKey(keyCode);
						F_SetUserEnterSaveWeight(keyCode);
							break;
						case setUserRollingHillEventVal:
						case setUserPeakEventVal:
						case setUserPlateauEventVal:
						case setUserClimbEventVal:
						case setUserInterval_1_EventVal:
						case setUserInterval_2_EventVal:
						F_SetUserEnterSaveProfile(keyCode);
						F_SetUsersEnterStopKey(keyCode);
						F_SetUserProfileChooseUpDown(keyCode,LongKeyStartFlg);
							break;
						case setUserProfileLevelEventVal:
						F_SetUserEnterSaveLeve(keyCode);
						F_SetUsersEnterStopKey(keyCode);
						F_SetUserLevelChooseUpDown(keyCode,LongKeyStartFlg);
							break;
						case setUserProfileWorkOutTImeEventVal:
						F_SetUserEnterSaveWorktime(keyCode);
						F_SetUsersEnterStopKey(keyCode);
						F_SetUserWorkoutTimeChooseUpDown(keyCode,LongKeyStartFlg);
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					if(ui_action.TemporarySeatPositionEvent == TemporarySeatPositionNormalEventVal) {
						switch(ui_action.Event) {
							case setUsersNoDataEventVal:
								F_showNoData();
								F_TimeCount();
								break;
							case setUsersName_1_EventVal:
								F_showSetUserName(0,set_user_data.UserNaume,UserNaumSizeVal);
								break;
							case setUsersName_2_EventVal:
								F_showSetUserName(1,set_user_data.UserNaume,UserNaumSizeVal);
								break;
							case setUsersName_3_EventVal:
								F_showSetUserName(2,set_user_data.UserNaume,UserNaumSizeVal);
								break;
							case setUsersName_4_EventVal:
								F_showSetUserName(3,set_user_data.UserNaume,UserNaumSizeVal);
								break;
							case setUsersName_5_EventVal:
								F_showSetUserName(4,set_user_data.UserNaume,UserNaumSizeVal);
								break;
							case setUsersName_6_EventVal:
								F_showSetUserName(5,set_user_data.UserNaume,UserNaumSizeVal);
								break;
							case setUsersName_7_EventVal:
								F_showSetUserName(6,set_user_data.UserNaume,UserNaumSizeVal);
								break;
							case setUsersName_8_EventVal:
								F_showSetUserName(7,set_user_data.UserNaume,UserNaumSizeVal);
								break;
							case setUsersName_9_EventVal:
								F_showSetUserName(8,set_user_data.UserNaume,UserNaumSizeVal);
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
								F_RollingHillLevelCount(15,sport_data.progfileArry,ProgfileDataSizeVal);
								F_ShowProgfileGraph(sport_data.progfileArry,ProgfileDataSizeVal,CommonModeVal,0,0);
								break;
							case setUserPeakEventVal:
								F_showPeakGraph();
								F_PeakLevelCount(15,sport_data.progfileArry,ProgfileDataSizeVal);
								F_ShowProgfileGraph(sport_data.progfileArry,ProgfileDataSizeVal,CommonModeVal,0,0);
								break;
							case setUserPlateauEventVal:
								F_showPlateauGraph();
								F_PlateauLevelCount(15,sport_data.progfileArry,ProgfileDataSizeVal);
								F_ShowProgfileGraph(sport_data.progfileArry,ProgfileDataSizeVal,CommonModeVal,0,0);
								break;
							case setUserClimbEventVal:
								F_showClimbGraph();
								F_ClimbLevelCount(15,sport_data.progfileArry,ProgfileDataSizeVal);
								F_ShowProgfileGraph(sport_data.progfileArry,ProgfileDataSizeVal,CommonModeVal,0,0);
								break;
							case setUserInterval_1_EventVal:
								F_showInterval_1_Graph();
								F_Interval_1_LevelCount(15,sport_data.progfileArry,ProgfileDataSizeVal);
								F_ShowProgfileGraph(sport_data.progfileArry,ProgfileDataSizeVal,CommonModeVal,0,0);
								break;
							case setUserInterval_2_EventVal:
								F_showInterval_2_Graph();
								F_Interval_2_LevelCount(15,sport_data.progfileArry,ProgfileDataSizeVal);
								F_ShowProgfileGraph(sport_data.progfileArry,ProgfileDataSizeVal,CommonModeVal,0,0);
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

void F_setUsersNoDataInit(void)
{
		rt_uint8_t	i;

		ui_action.Status = setUsersNoDataVal;
		ui_action.Event = setUsersNoDataEventVal;
		UserSetOrNoDataFlg = NoDataSetInitVal;
		TimeCount = 0;
	
		for(i=0;i < UserNaumSizeVal ;i++) {
			set_user_data.UserNaume[i] = ' ';
		}
		set_user_data.UserNaume[0] = 'A';

		set_user_data.Gender = 1;
		
		set_user_data.age.maxNumber = ageNumMaxVal;
		set_user_data.age.minNumber = ageNumMinVal;
		set_user_data.age.number = ageNumVal;
		
		set_user_data.Weight.maxNumber = WeightNumMaxVal;
		set_user_data.Weight.minNumber = WeightNumMinVal;
		set_user_data.Weight.number = WeightNumVal;
		
		set_user_data.UserProfileChoose = setUserRollingHillEventVal;	
		
		set_user_data.userLevel.number = LevelNumVal;
		set_user_data.userLevel.maxNumber = LevelNumMaxVal;
		set_user_data.userLevel.minNumber = LevelNumMinVal;
		
		set_user_data.userWorkoutTime.number = workOutTimeMinuteNumVal;
		set_user_data.userWorkoutTime.maxNumber = workOutTimeMinuteNumMaxVal;
		set_user_data.userWorkoutTime.minNumber = workOutTimeMinuteNumMinVal;
}

void F_setUsersDataSetInit(void)
{
		ui_action.Status = setUsersNoDataVal;
		ui_action.Event = setUsersName_1_EventVal;
		UserSetOrNoDataFlg = DataSetInitVal;
		F_eeprom_user_name(ReadDataVal,ui_action.UsersEventSave,set_user_data.UserNaume,0);
		F_eeprom_user_seat_position(ReadDataVal,ui_action.UsersEventSave,&set_user_data.SetSeatPositionAd);
		F_eeprom_user_gender(ReadDataVal,ui_action.UsersEventSave,&set_user_data.Gender);
		F_eeprom_user_age(ReadDataVal,ui_action.UsersEventSave,&set_user_data.age.number);
		F_eeprom_user_wigeht(ReadDataVal,ui_action.UsersEventSave,&set_user_data.Weight.number);
		F_eeprom_profile(ReadDataVal,ui_action.UsersEventSave,&set_user_data.UserProfileChoose);
		F_eeprom_level(ReadDataVal,ui_action.UsersEventSave,&set_user_data.userLevel.number);
		F_eeprom_worktime(ReadDataVal,ui_action.UsersEventSave,&set_user_data.userWorkoutTime.number);
}
