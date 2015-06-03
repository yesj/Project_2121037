#include "chandler.h"

void	F_Eng1ControlIncKey(rt_uint8_t keyCode,rt_bool_t LongKeyStartFlg)
{
		switch(keyCode)
		{
			case	seat_position_up_KeyVal:
				if(F_NumberUp_8(&sport_data.IncNumAdBuf,3,noCycleNumberVal).complyFlg == YesComplyVal) {
				rt_inc_micro_control(sport_data.IncNumAdBuf.number);
					if(LongKeyStartFlg==0)
						bz_short();
				}
				break;
			case	seat_position_down_KeyVal:
				if(F_NumberDown_8(&sport_data.IncNumAdBuf,3,noCycleNumberVal).complyFlg == YesComplyVal) {
				rt_inc_micro_control(sport_data.IncNumAdBuf.number);
					if(LongKeyStartFlg==0)
						bz_short();
				}
				break;
			case	stop_rest_KeyVal:
				rt_incline_stop();
				bz_short();
				break;
		}
}

void	F_Eng1EnterKey(rt_uint8_t keyCode)
{
		switch(keyCode)
		{
			case	enter_KeyVal:
			bz_short();
			ui_action.Event = IncAdr2EventVal;
			rt_IncCorrectionAdr_1();
				break;
		}
}

void	F_Eng1EndKey(rt_uint8_t keyCode)
{
		switch(keyCode)
		{
			case	enter_KeyVal:
			bz_short();
			rt_IncCorrectionAdr_2();
			F_IncCorrectionEnd();
				break;
		}
}

void	F_RestKey(rt_uint8_t keyCode)
{
		switch(keyCode)
		{
			case	stop_rest_KeyVal:
			//bz_short();
			//IWDG_Config(0);	
			//while(1)
			F_EngineeringModeInit(SeatLiftInstallEventVal);
				break;
		}
}

void F_EngMode1(void)
{
		rt_uint8_t	keyCode = 0;
		rt_bool_t	LongKeyStartFlg = 0;
		rt_uint32_t e;
		//static rt_uint8_t	TimeTemp = 0;
	
			if (rt_event_recv(&sport_timer_event, 0xFFFF,
					RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
					RT_WAITING_FOREVER, &e) == RT_EOK)
			{
				if((e & time_20ms_val) == time_20ms_val)
				{
					F_ReadKeyCode(&keyCode,&LongKeyStartFlg);
					if(keyCode != 0 ) 
					{
						//rt_kprintf(" EngMode1:%d \r\n",keyCode);
					}
					
					switch(ui_action.Event)
					{
						case	IncAdr1EventVal:
							F_Eng1ControlIncKey(keyCode,LongKeyStartFlg);
							F_Eng1EnterKey(keyCode);
							break;
						case	IncAdr2EventVal:
							F_Eng1ControlIncKey(keyCode,LongKeyStartFlg);
							F_Eng1EndKey(keyCode);
							break;
						case	IncAdrOkEventVal:
							F_RestKey(keyCode);
							break;
						case	IncAdrErrEventVal:
							F_RestKey(keyCode);
							break;
					}

				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event)
					{
						case	IncAdr1EventVal:
							F_showIncAd(rt_inc_read_ad());
							F_showTargetIncAd(sport_data.IncNumAdBuf.number);
							F_showEngIncAdr1();
							break;
						case	IncAdr2EventVal:
							F_showIncAd(rt_inc_read_ad());
							F_showTargetIncAd(sport_data.IncNumAdBuf.number);
							F_showEngIncAdr2();
							break;
						case	IncAdrOkEventVal:
							F_showIncAd(rt_inc_read_ad());
							F_showEngIncOk();
							break;
						case	IncAdrErrEventVal:
							F_showIncAd(rt_inc_read_ad());
							F_showEngIncErr();
							break;
					}
					F_Display();
				}
			}
}

void F_EngMode1_Init(void)
{
	ui_action.Status = eng1Val;
	ui_action.Event = IncAdr1EventVal;
	sport_data.IncNumAdBuf.number = rt_inc_read_ad();
	sport_data.IncNumAdBuf.maxNumber = 250;
	sport_data.IncNumAdBuf.minNumber = 5;
}

void F_EngMode1_AutoOk(void)
{
	ui_action.Event = IncAdrOkEventVal;
}

void F_EngMode1_AutoErr(void)
{
	ui_action.Event = IncAdrErrEventVal;
	
}
