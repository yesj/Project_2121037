#include "chandler.h"
#include "24lcxx_user.h"

void	F_AllKey(rt_uint8_t Key,rt_bool_t LongKeyStartFlg)
{
					switch(Key)
					{
						case	seat_position_stop_KeyVal:
							rt_seat_position_stop();
							bz_short();
						break;
						case	seat_position_up_KeyVal:
						case	fast_seat_position_up_KeyVal:
							rt_seat_position_up();
							if(LongKeyStartFlg==0)
								bz_short();
						break;
						case	seat_position_down_KeyVal:
						case	fast_seat_position_down_KeyVal:
							rt_seat_position_down();
							if(LongKeyStartFlg==0)
								bz_short();
						break;
						case	seat_position_home_1_KeyVal:	// 最高點
							bz_short();			
						rt_inc_micro_control(sport_data.saveSeatPositionHome_1);
						break;	
						case	seat_position_home_2_KeyVal:	// 最低點
							bz_short();
						rt_inc_micro_control(sport_data.saveSeatPositionHome_2);
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
}
