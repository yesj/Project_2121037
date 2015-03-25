#include "chandler.h"

rt_comply_t	F_NumberUp_8(uint8_Number_t *Number_t,rt_uint8_t upNumber,rt_uint8_t mode) 
{
		rt_comply_t		comply;
      if((Number_t ->number) >= (Number_t->maxNumber)) {
        switch(mode) {
          case cycleNumberVal:
            Number_t ->number = Number_t ->minNumber;
						comply.complyFlg = YesComplyVal;
            break;
          case noCycleNumberVal:
            comply.complyFlg = NoComplyVal;
            break; 
        }
      } else {
        if((0xFF-Number_t ->number) >= upNumber) {
          Number_t ->number = (Number_t ->number + upNumber);
        } else {
          Number_t ->number = 0xFF;
        }
				comply.complyFlg = YesComplyVal;
      }
			return	comply;
}

void F_NumberUp_16(uint16_Number_t *Number_t,rt_uint16_t upNumber,rt_uint8_t mode)
{
      if((Number_t ->number) >= (Number_t->maxNumber)) {
        switch(mode) {
          case cycleNumberVal:
            Number_t ->number = Number_t ->minNumber;
            break;
          case noCycleNumberVal:
            
            break; 
        }
      } else {
        if((0xFFFF-Number_t ->number) >= upNumber) {
          Number_t ->number = (Number_t ->number + upNumber);
        } else {
          Number_t ->number = 0xFFFF;
        }
      }
}
//========================================================================
rt_comply_t	F_NumberDown_8(uint8_Number_t *Number_t,rt_uint8_t upNumber,rt_uint8_t mode) 
{
			rt_comply_t		comply;
      if((Number_t ->number) <= (Number_t->minNumber)) {
        switch(mode) {
          case cycleNumberVal:
            Number_t ->number = Number_t ->maxNumber;
						comply.complyFlg = YesComplyVal;
            break;
          case noCycleNumberVal:
            comply.complyFlg = NoComplyVal;
            break; 
        }
      } else {
        if((Number_t ->number) >= upNumber) {
          Number_t ->number = ((Number_t ->number) - upNumber);
        } else {
          Number_t ->number = Number_t->minNumber;
        }
				comply.complyFlg = YesComplyVal;
      }
			return	comply;
}

void F_NumberDown_16(uint16_Number_t *Number_t,rt_uint16_t upNumber,rt_uint8_t mode) 
{
      if((Number_t ->number) < (Number_t->minNumber)) {
        switch(mode) {
          case cycleNumberVal:
            Number_t ->number = Number_t ->maxNumber;
            break;
          case noCycleNumberVal:
            
            break; 
        }
      } else {
        if((Number_t ->number) >= upNumber) {
          Number_t ->number = (Number_t ->number - upNumber);
        } else {
          Number_t ->number = 0;
        }
      }
}
//========================================================================
void	F_timer_process_up(rt_time_data_t *time_data)
{
	time_data->timeL++;
	if(time_data->timeL > 59) 
	{
		time_data->timeL = 0;
		time_data->timeH++;
		if(time_data->timeH > 99)
		{
			time_data->timeH = 0;
		}
	}
}

rt_bool_t	F_timer_process_down(rt_time_data_t *time_data)
{
	if(time_data->timeL == 0)
	{
		time_data->timeH--;
		time_data->timeL = 59;
	} else {
		time_data->timeL--;
		if((time_data->timeL == 0) && (time_data->timeH == 0))
		{
			return 1;
		}
	}
	return	0;
}

//[2-(LEVEL - 1)*0.05]*watts*time*6/1000/4.1854 + time/36
//	time = 1 秒 
// 	放到大小數點第 5 位
void	F_calorie_process(rt_calor_data_t *calorie_data)
{
		rt_uint32_t calorieTemp;
	
		calorieTemp = ((2-((calorie_data ->level)-1)*0.05) * ((calorie_data->watt) * 6) * (100000 / 1000) / 4.1854) + (100000 / 36);
	

		calorie_data-> calorie = (calorie_data-> calorie) + calorieTemp;
	
		if((calorie_data-> calorie) >= 999999999) {
			calorie_data-> calorie = 999999999;
		}
}

// 距離單位 公分
//	time 
//
void	F_distance_process(rt_distance_data_t *distance_data_t)
{
		distance_data_t->distance_count = (((distance_data_t->rpm) * (distance_data_t->WheelSize) *0.01 * 3.14 * 2.54) / 60) + distance_data_t->distance_count;
	
		if(distance_data_t->distance_count >= 99999) {
			distance_data_t->distance_count = 99999;
		}
}
// Progfile RollingHill
void	F_RollingHillLevelCount(rt_uint8_t MaxLevel,rt_uint8_t *LevelData,rt_uint8_t DataSize)
{
	rt_uint8_t	MinLevel;
	rt_uint8_t	SegmentAdr,TempAdr;
	if(MaxLevel < 11) {
		MinLevel = 1;
	} else {
		MinLevel = MaxLevel - 10;
	}
	SegmentAdr = 0;
	for(TempAdr = 0 ; TempAdr <DataSize ; TempAdr++) {
		SegmentAdr++;
		if(SegmentAdr <= 5) {
			*(LevelData+TempAdr) = (((MaxLevel - MinLevel) * SegmentAdr) / 4) + (MinLevel - ((MaxLevel - MinLevel) / 4));
		} else if(SegmentAdr <= 10) {
			*(LevelData+TempAdr) = *(LevelData+(4-(TempAdr % 5)));
		} else {
			*(LevelData+TempAdr) = *(LevelData+(9-(TempAdr % 10)));
		}
	}
}
// Progfile Peak
void	F_PeakLevelCount(rt_uint8_t MaxLevel,rt_uint8_t *LevelData,rt_uint8_t DataSize)
{
	rt_uint8_t	MinLevel,LevelTemp2,LevelTemp3;
	rt_uint16_t LevelTemp1;
	rt_uint8_t	SegmentAdr,TempAdr;
	if(MaxLevel < 11) {
		MinLevel = 1;
	} else {
		MinLevel = MaxLevel - 10;
	}
	SegmentAdr = 0;
	for(TempAdr = 0 ; TempAdr <DataSize ; TempAdr++) {
		SegmentAdr++;
		if(SegmentAdr <= 30) {
			LevelTemp1 = (((MaxLevel - MinLevel) * SegmentAdr) * 10 / 30);
			LevelTemp2 = LevelTemp1 / 10;
			LevelTemp3 = LevelTemp1 % 10;
			if(LevelTemp3 >= 5) {
				LevelTemp2++;
			}
			*(LevelData+TempAdr) = LevelTemp2 + MinLevel;
		} else {
			*(LevelData+TempAdr) = *(LevelData+(29-(TempAdr % 30)));
		}
	}
}
// Progfile Plateau
void	F_PlateauLevelCount(rt_uint8_t MaxLevel,rt_uint8_t *LevelData,rt_uint8_t DataSize)
{
	rt_uint8_t	MinLevel,LevelTemp2,LevelTemp3;
	rt_uint16_t LevelTemp1;
	rt_uint8_t	SegmentAdr,TempAdr;
	
	if(MaxLevel < 11) {
		MinLevel = 1;
	} else {
		MinLevel = MaxLevel - 10;
	}
	SegmentAdr = 0;
	for(TempAdr = 0 ; TempAdr <DataSize ; TempAdr++) {
		SegmentAdr++;
		if(SegmentAdr <= 20) {
			LevelTemp1 = (((MaxLevel - MinLevel) * SegmentAdr) * 10 / 20);
			LevelTemp2 = LevelTemp1 / 10;	// 四捨五入
			LevelTemp3 = LevelTemp1 % 10;
			if(LevelTemp3 >= 5) {
				LevelTemp2++;
			}
			*(LevelData+TempAdr) = LevelTemp2 + MinLevel;
		} else if(SegmentAdr <= 40) {
			*(LevelData+TempAdr) = MaxLevel;
		} else {
			*(LevelData+TempAdr) = MaxLevel - *(LevelData+ (TempAdr % 20)) + MinLevel;
		}
	}
}
// Progfile Climb
void	F_ClimbLevelCount(rt_uint8_t MaxLevel,rt_uint8_t *LevelData,rt_uint8_t DataSize)
{
	rt_uint8_t	MinLevel,LevelTemp2,LevelTemp3;
	rt_uint16_t LevelTemp1;
	rt_uint8_t	SegmentAdr,TempAdr;
	
	MinLevel = 1;

	SegmentAdr = 0;
	for(TempAdr = 0 ; TempAdr <DataSize ; TempAdr++) {
		SegmentAdr++;
		if(SegmentAdr <= 60) {
			LevelTemp1 = (((MaxLevel - MinLevel) * SegmentAdr) * 10 / 60);
			LevelTemp2 = LevelTemp1 / 10;	// 四捨五入
			LevelTemp3 = LevelTemp1 % 10;
			if(LevelTemp3 >= 5) {
				LevelTemp2++;
			}
			*(LevelData+TempAdr) = LevelTemp2 + MinLevel;
		}
	}
}
// Progfile Interval 1
void	F_Interval_1_LevelCount(rt_uint8_t MaxLevel,rt_uint8_t *LevelData,rt_uint8_t DataSize)
{
	rt_uint8_t	MinLevel,LevelTemp2,LevelTemp3;
	rt_uint16_t LevelTemp1;
	rt_uint8_t	SegmentAdr,TempAdr;
	
	MinLevel = 1;

	SegmentAdr = 0;
	for(TempAdr = 0 ; TempAdr <DataSize ; TempAdr++) {
		SegmentAdr++;
		if(SegmentAdr <= 2) {
			*(LevelData+TempAdr) = MinLevel;
		} else if(SegmentAdr <= 6) {
			LevelTemp1 = ((MaxLevel - MinLevel) * 10 / 4);
			LevelTemp2 = LevelTemp1 / 10;	// 四捨五入
			LevelTemp3 = LevelTemp1 % 10;
			if(LevelTemp3 >= 5) {
				LevelTemp2++;
			}
			*(LevelData+TempAdr) = LevelTemp2 + *(LevelData+TempAdr - 1);
		}	else if(SegmentAdr <= 18) {
			*(LevelData+TempAdr) = *(LevelData+(TempAdr % 6));
		}	else if(SegmentAdr <= 20) {
			*(LevelData+TempAdr) = MinLevel;
		}	else {
			*(LevelData+TempAdr) = *(LevelData+(TempAdr % 20));
		}
	}
}
// Progfile Interval 2
void	F_Interval_2_LevelCount(rt_uint8_t MaxLevel,rt_uint8_t *LevelData,rt_uint8_t DataSize)
{
	rt_uint8_t	MinLevel,LevelTemp2,LevelTemp3;
	rt_uint16_t LevelTemp1;
	rt_uint8_t	SegmentAdr,TempAdr;
	
	MinLevel = 1;

	SegmentAdr = 0;
	for(TempAdr = 0 ; TempAdr <DataSize ; TempAdr++) {
		SegmentAdr++;
		if(SegmentAdr <= 2) {
			*(LevelData+TempAdr) = MinLevel;
		} else if(SegmentAdr <= 6) {
			LevelTemp1 = ((MaxLevel - MinLevel) * 10 / 4);
			LevelTemp2 = LevelTemp1 / 10;	// 四捨五入
			LevelTemp3 = LevelTemp1 % 10;
			if(LevelTemp3 >= 5) {
				LevelTemp2++;
			}
			*(LevelData+TempAdr) = LevelTemp2 + *(LevelData+TempAdr - 1);
		}	else if(SegmentAdr <= 18) {
			*(LevelData+TempAdr) = *(LevelData+(TempAdr % 6));
		}	else if(SegmentAdr <= 20) {
			*(LevelData+TempAdr) = MinLevel;
		}	else {
			*(LevelData+TempAdr) = *(LevelData+(TempAdr % 20));
		}
	}
}


