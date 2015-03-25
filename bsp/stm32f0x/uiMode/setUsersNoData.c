#include "chandler.h"

static	rt_uint8_t	TimeCount;
		
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
      if(NameData == 'Z') {
        NameData = ' ';
      } else {
          if(NameData == ' ') {
            NameData = '0';
					} else {
							NameData++;
							if(NameData == ':') {
								NameData = 'A';
							}
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
      if(NameData == 'A') {
          NameData = '9';
      } else {
          if(NameData==' ') {
            NameData = 'Z';
					} else {
						NameData--;
						if(NameData == '/') {
							NameData = ' ';
						}
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
		ui_action.Event++;
		if(ui_action.Event == setWeightEventVal) {
			
		}
			break;
		case	stop_rest_KeyVal:
		bz_short();
		if(ui_action.Event > setUsersName_1_EventVal) {
			ui_action.Event--;
		} else {
			F_setUsersInit();
		}	
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
		if(LongKeyStartFlg == 0)
			bz_short();
		F_NumberUp_8(&set_user_data.age,1,cycleNumberVal);
			break;
		case	resistance_down_KeyVal:
		if(LongKeyStartFlg == 0)
			bz_short();
		F_NumberDown_8(&set_user_data.age,1,cycleNumberVal);
			break;
	}
}

static void F_SetUsersWeightUpDown(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
	switch(Key) {
		case	resistance_up_KeyVal:
		if(LongKeyStartFlg == 0)
			bz_short();
		F_NumberUp_8(&set_user_data.Weight,1,cycleNumberVal);
			break;
		case	resistance_down_KeyVal:
		if(LongKeyStartFlg == 0)
			bz_short();
		F_NumberDown_8(&set_user_data.Weight,1,cycleNumberVal);
			break;
	}
}

void F_setUsersNoData(void)
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
					switch(ui_action.Event) {
						case setUsersNoDataEventVal:

							break;
						case setUsersName_1_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,0);
							break;
						case setUsersName_2_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,1);
							break;
						case setUsersName_3_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,2);
							break;
						case setUsersName_4_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,3);
							break;
						case setUsersName_5_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,4);
							break;
						case setUsersName_6_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,5);
							break;
						case setUsersName_7_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,6);
							break;
						case setUsersName_8_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,7);
							break;
						case setUsersName_9_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,8);
							break;
						case setUsersName_10_EventVal:
						F_SetUsersEnterStopKey(keyCode);
						F_SetUsersNameUpDownKey(keyCode,LongKeyStartFlg,9);
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
		rt_uint8_t i;
		ui_action.Status = setUsersNoDataVal;
		ui_action.Event = setUsersNoDataEventVal;
		TimeCount = 0;
		for(i=0;i<10;i++) {
			set_user_data.UserNaume[i] = ' ';
		}
		set_user_data.age.maxNumber = 99;
		set_user_data.age.minNumber = 10;
		set_user_data.age.number = 40;
		
		set_user_data.Weight.maxNumber = 250;
		set_user_data.Weight.minNumber = 100;
		set_user_data.Weight.number = 150;
		set_user_data.Gender = 1;
}

