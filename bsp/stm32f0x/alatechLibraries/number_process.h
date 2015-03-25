#include <rthw.h>

typedef struct
{
  rt_uint8_t number;
  rt_uint8_t maxNumber;
  rt_uint8_t minNumber;
} uint8_Number_t;

typedef struct
{
  rt_uint16_t number;
  rt_uint16_t maxNumber;
  rt_uint16_t minNumber;
} uint16_Number_t;

typedef struct
{
  rt_uint32_t number;
  rt_uint32_t maxNumber;
  rt_uint32_t minNumber;
} uint32_Number_t;

struct rt_comply
{
	rt_bool_t complyFlg;
};
typedef struct rt_comply rt_comply_t;


