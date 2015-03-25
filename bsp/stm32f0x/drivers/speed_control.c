#include "speed_control.h"
#include <stm32f0xx.h>

//SPD IN
#define P_SPD_IN_PIN                    GPIO_Pin_4                            
#define P_SPD_IN_GPIO_PORT              GPIOA
#define P_SPD_IN_GPIO_CLK               RCC_AHBPeriph_GPIOA

 //Speed Up
#define P_Speed_UP_PIN                 GPIO_Pin_12                        
#define P_Speed_UP_GPIO_PORT           GPIOB
#define P_Speed_UP_GPIO_CLK            RCC_AHBPeriph_GPIOB
#define M_Speed_UP_SetHigh             P_Speed_UP_GPIO_PORT -> BSRR = P_Speed_UP_PIN   
#define M_Speed_UP_SetLow              P_Speed_UP_GPIO_PORT -> BRR = P_Speed_UP_PIN 


 //Speed Down
#define P_Speed_DOWN_PIN                GPIO_Pin_13        
#define P_Speed_DOWN_GPIO_PORT          GPIOB
#define P_Speed_DOWN_GPIO_CLK           RCC_AHBPeriph_GPIOB
#define M_Speed_DOWN_SetHigh            P_Speed_DOWN_GPIO_PORT -> BSRR = P_Speed_DOWN_PIN   
#define M_Speed_DOWN_SetLow             P_Speed_DOWN_GPIO_PORT -> BRR = P_Speed_DOWN_PIN


  //Sw Ctrl
#define P_Sw_Ctrl_PIN                   GPIO_Pin_6        
#define P_Sw_Ctrl_GPIO_PORT             GPIOF
#define P_Sw_Ctrl_GPIO_CLK              RCC_AHBPeriph_GPIOF
#define M_Sw_Ctrl_SetHigh            P_Sw_Ctrl_GPIO_PORT -> BSRR = P_Sw_Ctrl_PIN   
#define M_Sw_Ctrl_SetLow             P_Sw_Ctrl_GPIO_PORT -> BRR = P_Sw_Ctrl_PIN

static struct rt_thread speed_control_thread;

static rt_uint8_t speed_control[256];
static rt_timer_t timer_test;
static rt_tick_t timeout_value = 1;

static rt_uint16_t	R_SpeedCntBuf;
static rt_uint16_t	R_SpeedCnt;
static rt_uint16_t	R_SpeedDetectTime;
static rt_uint16_t	R_SpeedPwmCnt;
static rt_uint16_t	R_SpeedPwmCntSave;
static rt_uint16_t	R_SpeedAutoCnt;
static rt_uint8_t		R_LowSpeedCntDelay;
static rt_uint8_t		R_SpeedErrTime;
static rt_uint16_t	R_Rpm;
static rt_uint8_t		realSpeed;


static rt_bool_t MotoUpDownFlg;
static rt_bool_t SpeedStatusFlg;
static rt_bool_t FriestSpeedFlg;
static rt_bool_t SpeedMoveFlg;
static rt_bool_t SpeedAutoFlg;

static rt_speed_init_data_t speed_data;

//=====================================
static void F_SpeedSwCotrol(rt_bool_t Data)
{
    if(Data)	
      M_Sw_Ctrl_SetHigh;
    else
      M_Sw_Ctrl_SetLow;
}

static void	F_PwmCntSend(void)
{
  //	轉速偵測
  R_SpeedCntBuf++;
  if((GPIO_ReadInputDataBit(P_SPD_IN_GPIO_PORT, P_SPD_IN_PIN))==0x00)
  {
    if(SpeedStatusFlg==0)	//low-->Hi
    {
      SpeedStatusFlg=1;
      if((R_SpeedCntBuf<3000)&&(R_SpeedCntBuf>20))
      {
        if(FriestSpeedFlg)
        {
          if(R_SpeedCntBuf<2000)
            SpeedMoveFlg=1;
          else
            SpeedMoveFlg=0;
          R_SpeedCnt=R_SpeedCntBuf;
          R_SpeedCntBuf=0;
        }
        else
        {
          FriestSpeedFlg=1;
          R_SpeedCntBuf=0;
        }
      }
      else
      {
        R_SpeedCntBuf=0;
        FriestSpeedFlg=0;
      }
    }
  }
  else
    SpeedStatusFlg=0;
  //==============	
  if(R_SpeedCntBuf>3000)
  {
    R_SpeedCntBuf=0;			
    R_SpeedCnt=0;
    FriestSpeedFlg=0;	
    SpeedMoveFlg=0;
  }

  R_SpeedDetectTime++;
  if(R_SpeedDetectTime>30)
  {	// 每 31ms 執行一次
    R_SpeedDetectTime=0;
    //===== 送出 Speed Count ========
    if(R_SpeedPwmCnt==0)				// Speed 傳送階數
    {
      M_Speed_UP_SetLow;
      M_Speed_DOWN_SetLow;
    }
    else
    {
      if(MotoUpDownFlg==0)
      {	// 0:馬達加速 / 1:馬達減速
        if( !GPIO_ReadInputDataBit( P_Speed_UP_GPIO_PORT , P_Speed_UP_PIN ))
          M_Speed_UP_SetHigh;
        else
        {
          M_Speed_UP_SetLow;
          R_SpeedPwmCnt--;       // 送出 speed count
          if(R_SpeedPwmCntSave<475)
            R_SpeedPwmCntSave++;	
        }
      }
      else
      {
        if( !GPIO_ReadInputDataBit( P_Speed_DOWN_GPIO_PORT , P_Speed_DOWN_PIN ))
          M_Speed_DOWN_SetHigh;
        else
        {
          M_Speed_DOWN_SetLow;
          R_SpeedPwmCnt--;       // 送出 speed count
          if(R_SpeedPwmCntSave!=0)
            R_SpeedPwmCntSave--;
        }
      }
    }
  }
}

//=====================================
static void	F_SpeedAuto(rt_uint8_t	Speed)
{
  unsigned	char	i;
  switch(R_SpeedAutoCnt)
  {
    case	0:	//	低速校正
      if((Speed >= speed_data.speedMin) &&(Speed <= speed_data.speedMin+2))
      {	//	低速校正結束
        R_LowSpeedCntDelay++;
        if(R_LowSpeedCntDelay>2)
        {
          R_LowSpeedCntDelay=0;
          speed_data.pwmLowSpeed = R_SpeedPwmCntSave;
          //EE_Write(EE_PwmLowSpeed,R_PwmLowSpeed);
          R_SpeedAutoCnt=1;
        }
      }
      else	if(speed_data.speedMin >Speed)
      {
        R_LowSpeedCntDelay=0;					
        MotoUpDownFlg=0;			//	馬達加速 
        R_SpeedPwmCnt=1;
      }
      else
      {
        R_LowSpeedCntDelay=0;		
        MotoUpDownFlg=1;		//	馬達減速
        R_SpeedPwmCnt=1;
      }
      break;
      //============================
      case	1:	//	高速確認 
        if(speed_data.speedMax <= Speed)		//校正完成
        {	
          SpeedAutoFlg=0;		//速度校正完成
          R_SpeedPwmCnt=0;
          F_SpeedSwCotrol(0);
        }
        else
        {
          if(speed_data.speedMax > Speed)
          {
            MotoUpDownFlg=0;			//	馬達加速
            i = speed_data.speedMax-Speed;
          }
          else
          {
            MotoUpDownFlg=1;		//	馬達減速
            i = Speed-speed_data.speedMax;
          }
          if(i>99)            // > ±5.0Km
            R_SpeedPwmCnt = 25;
          else if(i>49)     // > ±4.0Km 
            R_SpeedPwmCnt = 20;
          else if(i>39)     // > ±3.0Km
            R_SpeedPwmCnt = 13;
          else if(i>19)     // > ±2.0Km
            R_SpeedPwmCnt = 10;
          else if(i>9)       // > ±1.0Km
            R_SpeedPwmCnt = 8;
          else if(i>2)       // > ±0.5Km
            R_SpeedPwmCnt = 3;
          else if(i>0)       // > ±0.1Km
            R_SpeedPwmCnt = 1;  				// 1 階
        }
        break;
  }
}
//=====================================
void	rt_speed_control_start(rt_uint8_t set_speed)
{
  F_SpeedSwCotrol(1);
	
	if(speed_data.setSpeed ==0 ) {
		MotoUpDownFlg = 0;			//	馬達加速
		R_SpeedPwmCnt = speed_data.pwmLowSpeed;
	}
	
	speed_data.setSpeed = set_speed;
}
//=====================================
void	rt_speed_control_auto_init(void)
{
  SpeedAutoFlg=1;
  MotoUpDownFlg=0;
  R_SpeedAutoCnt=0;
  R_SpeedPwmCnt=13;
  F_SpeedSwCotrol(1);
}
//=====================================
static void	F_SpeedControl(rt_uint8_t	Speed)
{
  rt_uint8_t	i;
  if(speed_data.setSpeed)
  {
    F_SpeedSwCotrol(1);
    if(speed_data.setSpeed > Speed)
    {
      MotoUpDownFlg=0;			//	馬達加速
      i = speed_data.setSpeed-Speed;
    }
    else
    {
      MotoUpDownFlg=1;		//	馬達減速
      i = Speed-speed_data.setSpeed;
    }
    if(i>99)            // > ±5.0Km
      R_SpeedPwmCnt = 20;
    else if(i>49)     // > ±4.0Km 
      R_SpeedPwmCnt = 17;
    else if(i>39)     // > ±3.0Km
      R_SpeedPwmCnt = 13;
    else if(i>19)     // > ±2.0Km
      R_SpeedPwmCnt = 9; 
    else if(i>9)       // > ±1.0Km
      R_SpeedPwmCnt = 8;
    else if(i>2)       // > ±0.5Km
      R_SpeedPwmCnt = 3;
    else if(i>0)       // > ±0.1Km
      R_SpeedPwmCnt = 1;
    //====================
    //速度信號偵側
    if(SpeedMoveFlg==0)
    {
      R_SpeedErrTime++;
      if(R_SpeedErrTime>4)		// 8秒後無信號錯誤
      {
        R_SpeedErrTime=0;	
				rt_speed_control_start(0);
				speed_data.err_treadmill_handler(SpeedErrNumVal);
      }
    }
    else
      R_SpeedErrTime=0;
    //====================	
  }
  else
  {
    R_SpeedErrTime=0;
    if(R_SpeedPwmCntSave>50)
    {
      MotoUpDownFlg=1;		//	馬達減速
      R_SpeedPwmCnt = 50;
    }
    else
      F_SpeedSwCotrol(0);	
  }
}

static void static_thread_entry(void* parameter)
{
	float Temp,i;
		while(1)
		{
			rt_thread_delay(2000);

			if(R_SpeedCnt==0)
			{
				R_Rpm=0;
			}
			else
			{
				R_Rpm=(60000/R_SpeedCnt);
			}
			
				if(speed_data.changeUnit == RT_TRUE)
					i=0.0002971;
					else
						i=0.0004785;
					
				Temp=(float)(i * R_Rpm * speed_data.wheelSize);   // 單位  60*RpmTemp*R_WheelSize*3.14*2.54)/1000000
				realSpeed=(rt_uint8_t)Temp;
		
					
				if(SpeedAutoFlg)
					F_SpeedAuto(realSpeed);
					else
						F_SpeedControl(realSpeed);
		}
}

/* 超時時回調的處理函數 */
static void timeout_callbak(void* parameter)
{
		F_PwmCntSend();
}

void	rt_hw_speed_control_init(rt_speed_init_data_t speed_data_init)
{
		rt_err_t result;
	
		GPIO_InitTypeDef GPIO_InitStructure;
		
		// Enable the Speed Up
		RCC_AHBPeriphClockCmd(P_Speed_UP_GPIO_CLK, ENABLE);
		
		// Configure the Speed Up pin
		GPIO_InitStructure.GPIO_Pin = P_Speed_UP_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(P_Speed_UP_GPIO_PORT, &GPIO_InitStructure);
		
		// Enable the Speed Down
		RCC_AHBPeriphClockCmd(P_Speed_DOWN_GPIO_CLK, ENABLE);
		
		// Configure the Speed Down pin
		GPIO_InitStructure.GPIO_Pin = P_Speed_DOWN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(P_Speed_DOWN_GPIO_PORT, &GPIO_InitStructure);
		
		// Enable the Sw Ctrl
		RCC_AHBPeriphClockCmd(P_Sw_Ctrl_GPIO_CLK, ENABLE);
		
		// Configure the Sw Ctrl pin
		GPIO_InitStructure.GPIO_Pin = P_Sw_Ctrl_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(P_Sw_Ctrl_GPIO_PORT, &GPIO_InitStructure);
		
		
		// Input SPD IN  on PA9  
		// Enable the SPD IN 
		RCC_AHBPeriphClockCmd(P_SPD_IN_GPIO_CLK, ENABLE);
		// Configure the SPD IN pin 
		GPIO_InitStructure.GPIO_Pin = P_SPD_IN_PIN ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(P_SPD_IN_GPIO_PORT, &GPIO_InitStructure);
	
	
		speed_data = speed_data_init;
	
		result = rt_thread_init(&speed_control_thread,"speed", static_thread_entry, RT_NULL,
						(rt_uint8_t*)&speed_control[0], sizeof(speed_control),2,2);
		
		if(result == RT_EOK) 
		{ 
			rt_thread_startup(&speed_control_thread); 
		}
		
		timer_test = rt_timer_create("speed_control_timer",
																	timeout_callbak,
																	RT_NULL,
																	timeout_value,
																	RT_TIMER_FLAG_PERIODIC);
																	
		if(timer_test != RT_NULL) rt_timer_start(timer_test);
} 

#include <finsh.h>

int read_seed_cnt(void)
{
		rt_kprintf("setSpeed = %d\n", speed_data.setSpeed);
		rt_kprintf("changeUnit : %d \n" ,speed_data.changeUnit);
		rt_kprintf("wheelSize : %d \n" ,speed_data.wheelSize);
		rt_kprintf("pwmLowSpeed : %d \n" ,speed_data.pwmLowSpeed);
		rt_kprintf("speedMax : %d \n" ,speed_data.speedMax);
		rt_kprintf("speedMax : %d \n" ,speed_data.speedMin);
		return 0;
}

FINSH_FUNCTION_EXPORT_ALIAS(read_seed_cnt, __cmd_read_seed_cnt, read seed cnt number);
/*
int sum(int argc , char** argv)
{
		int i;
		int total=0;
		for (i=1; i<argc; i++)
		{
		total += atoi(argv[i]);
		}
		rt_kprintf("total = %d\n", total);
		return 0;
}

MSH_CMD_EXPORT(sum, do sum in finsh);
*/

int speed_start(int argc , char** argv)
{
		//speed_data.setSpeed = atoi(argv[1]);
		rt_speed_control_start(atoi(argv[1]));
		rt_kprintf("setSpeed = %d\n", speed_data.setSpeed);
		return 0;
}

MSH_CMD_EXPORT(speed_start, do speed start);
