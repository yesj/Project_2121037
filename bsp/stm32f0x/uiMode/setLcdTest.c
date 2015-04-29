#include "chandler.h"

#define Eng3TestDisplayTime	10
static rt_uint16_t	R_EngFlashCnt;

void F_setLcdTest(void)
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
					switch(keyCode) {
						case engineering_KeyVal:
						bz_short();
						F_EngineeringModeInit(DisplayTestEventVal);
							break;		
					}
				}
				//=====================
				if((e & time_100ms_val) == time_100ms_val)
				{
					F_SetDisplayRam(0);
					R_EngFlashCnt++;
					if(R_EngFlashCnt<Eng3TestDisplayTime*1) {
						F_Show_8_DotDisplay(0);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*2) {
						F_Show_8_DotDisplay(1);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*3) {
						F_Show_8_DotDisplay(2);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*4) {
						F_Show_8_DotDisplay(3);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*5) {
						F_Show_8_DotDisplay(4);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*6) {
						F_Show_8_DotDisplay(5);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*7) {
						F_Show_8_DotDisplay(6);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*8) {
						F_Show_8_DotDisplay(7);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*9) {
						F_Show_8_DotDisplay(8);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*11) {
						F_Show_8_DotDisplay(9);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*12) {
						F_ShowMatrixDotDisplayTest(0x00000001);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*13) {
						F_ShowMatrixDotDisplayTest(0x00000002);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*14) {
						F_ShowMatrixDotDisplayTest(0x00000004);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*15) {
						F_ShowMatrixDotDisplayTest(0x00000008);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*16) {
						F_ShowMatrixDotDisplayTest(0x00000010);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*17) {
						F_ShowMatrixDotDisplayTest(0x00000020);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*18){
						F_ShowMatrixDotDisplayTest(0x00000040);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*19) {
						F_ShowMatrixDotDisplayTest(0x00000080);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*20) {
						F_ShowMatrixDotDisplayTest(0x00000100);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*21) {
						F_ShowMatrixDotDisplayTest(0x00000200);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*22) {
						F_ShowMatrixDotDisplayTest(0x00000400);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*23) {
						F_ShowMatrixDotDisplayTest(0x00000800);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*24) {
						F_ShowMatrixDotDisplayTest(0x00001000);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*25) {
						F_ShowMatrixDotDisplayTest(0x00002000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*26) {
						F_ShowMatrixDotDisplayTest(0x00004000);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*27) {
						F_ShowMatrixDotDisplayTest(0x00008000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*28) {
						F_ShowMatrixDotDisplayTest(0x00010000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*29) {
						F_ShowMatrixDotDisplayTest(0x00020000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*30) {
						F_ShowMatrixDotDisplayTest(0x00040000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*31) {
						F_ShowMatrixDotDisplayTest(0x00080000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*32) {
						F_ShowMatrixDotDisplayTest(0x00100000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*33) {
						F_ShowMatrixDotDisplayTest(0x00200000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*34) {
						F_ShowMatrixDotDisplayTest(0x00400000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*35) {
						F_ShowMatrixDotDisplayTest(0x00800000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*36) {
						F_ShowMatrixDotDisplayTest(0x01000000);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*37) {
						F_ShowMatrixDotDisplayTest(0x02000000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*38) {
						F_ShowMatrixDotDisplayTest(0x04000000);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*39) {
						F_ShowMatrixDotDisplayTest(0x08000000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*40) {
						F_ShowMatrixDotDisplayTest(0x10000000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*41) {
						F_ShowMatrixDotDisplayTest(0x20000000);
					}	else	if(R_EngFlashCnt<Eng3TestDisplayTime*42) {
						F_ShowMatrixDotDisplayTest(0x40000000);
					} else	if(R_EngFlashCnt<Eng3TestDisplayTime*43) {
						F_ShowMatrixDotDisplayTest(0x80000000);
					} else {
						F_SetDisplayRam(1);
					}
					F_Display();
				}
			}
}

void F_setLcdTestInit(void)
{
	ui_action.Status = setLcdTestVal;
	//ui_action.Event = ;
	R_EngFlashCnt = 0;
}
