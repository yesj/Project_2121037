#include "chandler.h"

static void	F_ChooseMode(void)
{
	rt_bool_t	BzOnFlg = 0;
		switch(ui_action.Event) {
			case	UnitEventVal:
				BzOnFlg = 1;
				F_setUintInit();
				break;
			case	VersionEventVal:
				
				break;
			case	BeeperTestEventVal:
				BzOnFlg = 1;
				F_setBzTestInit();
				break;
			case	DisplayTestEventVal:
				BzOnFlg = 1;
				F_setLcdTestInit();
				break;
			case	KeypadTestEventVal:
				BzOnFlg = 1;
				F_setKeyTestInit();
				break;
			case	SeatLiftInstallEventVal:
				BzOnFlg = 1;
				F_EngMode1_Init();
				break;
		}
		if(BzOnFlg) {
			bz_short();
		}
}

void F_EngineeringMode(void)
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
					F_ReadKeyCode(&keyCode,&LongKeyStartFlg,&ui_action.SleepTimer);
					switch(keyCode)
					{
						case	stop_rest_KeyVal:
							IWDG_Config(0);	
							while(1)
							break;
						case	enter_KeyVal:
							F_ChooseMode();
							break;
						case	resistance_up_KeyVal:
						if(LongKeyStartFlg == 0)	{
							bz_short();
							ui_action.Event++;
							if(ui_action.Event>SeatLiftInstallEventVal)
								ui_action.Event = UnitEventVal;
						}
							break;
						case	resistance_down_KeyVal:
						if(LongKeyStartFlg == 0)	{
							bz_short();
							if(ui_action.Event > UnitEventVal)
								ui_action.Event--;
								else
									ui_action.Event = SeatLiftInstallEventVal;
						}
							break;
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					switch(ui_action.Event) {
						case	UnitEventVal:
							F_ShowUnit();
							break;
						case	VersionEventVal:
							F_ShowSoftwareVersion();
							break;
						case	BeeperTestEventVal:
							F_ShowBeeperTest();
							break;
						case	DisplayTestEventVal:
							F_ShowDisplayTest();
							break;
						case	KeypadTestEventVal:
							F_ShowKeypedTest();
							break;
						case	SeatLiftInstallEventVal:
							F_ShowSeatLiftInstall();
							break;
					}
					F_Display();
				}
			}
}

void F_EngineeringModeInit(rt_uint8_t Event)
{
	ui_action.Status = engineeringModeVal;
	ui_action.Event = Event;
}
