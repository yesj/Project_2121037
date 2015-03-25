#include "chandler.h"

/*
LEVEL 1: 10W (203 cal/hr)
LEVEL 2: 15W (251 cal/hr)
LEVEL 3: 20W (296 cal/hr)
LEVEL 4: 30W (386 cal/hr)
LEVEL 5: 40W (472 cal/hr)
LEVEL 6: 55W (597 cal/hr)
LEVEL 7: 70W (714 cal/hr)
LEVEL 8: 85W (824 cal/hr)
LEVEL 9: 105W (967 cal/hr)
LEVEL 10: 125W (1100 cal/hr)
LEVEL 11: 145W (1225 cal/hr)
LEVEL 12: 165W (1335 cal/hr)
LEVEL 13: 185W (1437 cal/hr)
LEVEL 14: 205W (1528 cal/hr)
LEVEL 15: 225W (1610 cal/hr)
LEVEL 16: 255W (1745 cal/hr)
LEVEL 17: 285W (1865 cal/hr)
LEVEL 18: 315W (1969 cal/hr)
LEVEL 19: 355W (2115 cal/hr)
LEVEL 20: 400W (2268 cal/hr)
*/

const rt_uint16_t	T_WattsTables[21]={
  0,  
  10,15,20,30,40,55,70,85,105,125,
	145,165,185,205,225,255,285,315,355,400
};

void	F_readWatte(rt_uint8_t adr,rt_uint16_t *watt)
{
	*watt = T_WattsTables[adr];
}

