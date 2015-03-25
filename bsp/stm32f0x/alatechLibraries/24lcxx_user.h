#ifndef __24LCXX_USER_H__
#define __24LCXX_USER_H__

#include "chandler.h"

extern rt_uint8_t	F_eeprom_test(void);

extern rt_uint8_t	F_eeprom_whether_init(void);

extern void	F_eeprom_write_init(void);

extern void F_eeprom_incline_data(rt_uint8_t status,rt_incline_eeprom_data_t *data);

extern void	F_eeprom_home1_data(rt_uint8_t status,rt_uint8_t *data);

extern void	F_eeprom_home2_data(rt_uint8_t status,rt_uint8_t *data);

extern void	F_eeprom_user_DetectionData(rt_uint8_t status,rt_uint8_t Num,rt_uint8_t *data);

#endif
