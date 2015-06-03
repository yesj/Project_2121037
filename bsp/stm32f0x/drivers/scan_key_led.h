
#ifndef __SCAN_KEY_LED_H__
#define __SCAN_KEY_LED_H__

#include <rthw.h>

//按鍵參數設定
#define user_KeyVal									16
#define focus_KeyVal								15
#define view_KeyVal									14
#define programs_KeyVal							13
#define seat_position_down_KeyVal		4
#define enter_KeyVal								3
#define stop_rest_KeyVal						2
#define resistance_down_KeyVal			1
#define seat_position_up_KeyVal			10
#define quick_start_KeyVal					9
#define resistance_up_KeyVal				7
#define eng1_KeyVal									31

#define fast_seat_position_up_KeyVal		29
#define fast_seat_position_down_KeyVal		24

#define seat_position_home_1_KeyVal		30
#define seat_position_home_2_KeyVal		23

#define seat_position_stop_KeyVal			100

#define seat_position_home_1_long_KeyVal			101
#define seat_position_home_2_long_KeyVal			102

#define short_enter_KeyVal			103
#define long_enter_KeyVal				104

#define engineering_KeyVal			105		//	seat_position_down_KeyVal + enter_KeyVal
#define long_stop_rest_KeyVal		106

#define view_programs_KeyVal		107	
#define long_view_KeyVal				108

//typedef void (*app_button_handler_t)(rt_uint8_t button_action);

extern void	F_ReadKeyCode(rt_uint8_t *KeyCode,rt_bool_t *LongKeyStart);

//extern void rt_button_evt_init(app_button_handler_t button_handler);

extern void rt_hw_key_led_scan_init(void);

//extern void  F_InitialKB_GPIO(void);

//extern void F_LedKeyScanReadRealSignal(uint8 LedSegData);

//extern void F_ReadKeyCode(uint8 *KeyCode);

#endif
