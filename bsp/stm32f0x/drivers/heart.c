#include "heart.h"
#include <stm32f0xx.h>


//PULSE2
#define P_PULSE2_PIN                    GPIO_Pin_14
#define P_PULSE2_GPIO_PORT              GPIOC
#define P_PULSE2_GPIO_CLK               RCC_AHBPeriph_GPIOC
//PULSE1
#define P_PULSE1_PIN                    GPIO_Pin_15
#define P_PULSE1_GPIO_PORT              GPIOA
#define P_PULSE1_GPIO_CLK               RCC_AHBPeriph_GPIOA

//Pluse
static rt_uint16_t	R_Plusecount;
static rt_uint8_t		R_PluseTemp,R_Pluse,R_PluOld;
static rt_uint8_t		R_pluseIndex;
static rt_uint8_t		R_pubf[4];
static rt_uint8_t		R_HeartPluseWidth;
//WPluse
static rt_uint16_t	R_W_Plusecount;
static rt_uint8_t		R_W_PluseTemp,R_W_Pluse,R_W_PluOld;
static rt_uint8_t		R_W_pluseIndex;
static rt_uint8_t		R_W_pubf[4];
static rt_uint8_t		R_Heart_W_PluseWidth;
static rt_uint8_t		R_W_DelayTime;

static rt_bool_t HeartPluseFlg;
//static rt_bool_t W_Pu1intFlg;
//static rt_bool_t HandHeartDetectionFlg;
//static rt_bool_t Pu1intFlg;
static rt_bool_t Heart_W_PluseFlg;
//static rt_bool_t wHeartDetectionFlg;

static rt_timer_t heart_timer;
//========================================================================
//SPD IN
#define P_SPD_IN_PIN                    GPIO_Pin_10                           
#define P_SPD_IN_GPIO_PORT              GPIOB
#define P_SPD_IN_GPIO_CLK               RCC_AHBPeriph_GPIOB

static rt_uint16_t	R_SpeedCntBuf;
static rt_uint16_t	R_SpeedCnt;
//static rt_uint16_t	R_SpeedDetectTime;
//static rt_uint16_t	R_SpeedPwmCnt;
//static rt_uint16_t	R_SpeedPwmCntSave;
//static rt_uint16_t	R_SpeedAutoCnt;
//static rt_uint8_t		R_LowSpeedCntDelay;
//static rt_uint8_t		R_SpeedErrTime;
static rt_uint16_t	R_Rpm;
static rt_uint8_t		realSpeed;

static rt_bool_t SpeedStatusFlg;
static rt_bool_t FriestSpeedFlg;


static void	F_SpeedDetection(void)
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
  }
}

rt_uint16_t	F_readRpm(void)
{
	float Temp;
			if(R_SpeedCnt==0)
			{
				R_Rpm=0;
			}
			else
			{
				R_Rpm=(60000/R_SpeedCnt);
			}
			/*
				if(speed_data.changeUnit == RT_TRUE)
					i=0.0002971;
					else
						i=0.0004785;
			*/		
				Temp=(float)(0.0004785 * R_Rpm * 254);   // 單位  60*RpmTemp*R_WheelSize*3.14*2.54)/1000000
				realSpeed=(rt_uint8_t)Temp;
			return	R_Rpm;
}
//==========================================
//手握心線訊號計算
//==========================================
void	F_PluseFunction1(void)
{
  rt_uint16_t		i; 
  rt_uint8_t		k,l,m;

    if(R_Pluse==0)
    {
      R_pluseIndex=0;
      if(R_PluseTemp>99)
      {
        R_Pluse=99;
        R_pubf[0]=R_Pluse;
        R_pubf[1]=R_Pluse;
        R_pubf[2]=R_Pluse;
        R_pubf[3]=R_Pluse;	
      }
      else if(R_PluseTemp<70)
      {
        R_Pluse=70;			
        R_pubf[0]=R_Pluse;
        R_pubf[1]=R_Pluse;
        R_pubf[2]=R_Pluse;
        R_pubf[3]=R_Pluse;
      }
      else
      {
        R_Pluse=R_PluseTemp;			
        R_pubf[0]=R_Pluse;
        R_pubf[1]=R_Pluse;
        R_pubf[2]=R_Pluse;
        R_pubf[3]=R_Pluse;
      }		
    }
    else
    {
      k=0;
      m=0;
      //===============				
      if(R_PluseTemp>R_Pluse)
      {
        k=R_PluseTemp-R_Pluse;
      }
      else
      {
        m=R_Pluse-R_PluseTemp;
      }
      //===============						
      //				l=R_PluseTemp;
      if(k>8)
      {
        l=R_Pluse+8;
      }
      else	if(m>8)
      {
        l=R_Pluse-8;
      }
      else
        l=R_PluseTemp;
      R_PluseTemp=l;
      R_pubf[R_pluseIndex]=R_PluseTemp;
      
      R_pluseIndex++;
      if(R_pluseIndex>3)
        R_pluseIndex=0;
      if(R_pluseIndex==0)
      {
        i=R_pubf[0];
        i=i+R_pubf[1];
        i=i+R_pubf[2];
        i=i+R_pubf[3];			
        i=i>>2;			//i/4			
        R_Pluse=i;	
      }
    }
}
//===========================================================================		
//手握心線訊號偵測
//===========================================================================	
void	F_Pluse1sub(void)		
{
  rt_uint8_t	i;
  R_Plusecount++;
  if(GPIO_ReadInputDataBit(P_PULSE1_GPIO_PORT,P_PULSE1_PIN))	//pluse_P=1
  {
    //=================		
    if(HeartPluseFlg==0)	//low-->Hi
    {
      R_HeartPluseWidth++;
      if(R_HeartPluseWidth>10)	//Hi寬度需大於10mS才承認心跳訊號
      {	
        R_HeartPluseWidth=0;
        HeartPluseFlg=1;
        if((R_Plusecount<1500)&&(R_Plusecount>272))	//	(60000/40)<R_Plusecount<(60000/220)
        {											//	40<R_Pluse1<220
          R_PluseTemp=60000/R_Plusecount;
          R_Plusecount=0;
          //HandHeartDetectionFlg=1;
          //==============================
          if(R_Pluse==0)
          {
            if(R_PluOld==0)
            {
              R_PluOld=R_PluseTemp;
            }
            else
            {
              if(R_PluseTemp>R_PluOld)
                i=R_PluseTemp-R_PluOld;
              else
                i=R_PluOld-R_PluseTemp;
              //===================
              if(i<10) 
							{
                F_PluseFunction1();
							}
              //===================
              R_PluOld=R_PluseTemp;
            }		
          }
          else
          {
						F_PluseFunction1();
          }
          //==============================
        }
        else
        {
          R_Plusecount=0;
        }
      }							
    }
    //=================	
  }
  else
  {
    HeartPluseFlg=0;
    R_HeartPluseWidth=0;	
  }
  //==================	
  if(R_Plusecount>3000)
  {
    R_Plusecount=0;
    R_Pluse=0;
    R_PluseTemp=0;
    R_PluOld=0;
    //HandHeartDetectionFlg=0;
    R_pubf[0]=0;
    R_pubf[1]=0;
    R_pubf[2]=0;
    R_pubf[3]=0;
  }
}

//=======================================
//無線心跳訊號計算
//=======================================	
void	F_PluseFunction2(void)
{
  rt_uint16_t i; 
  rt_uint8_t k,l,m;

    if(R_W_Pluse==0)	
    {
      R_W_pluseIndex=0;
      if(R_W_PluseTemp>99)
      {
        R_W_Pluse=99;
        R_W_pubf[0]=R_W_Pluse;
        R_W_pubf[1]=R_W_Pluse;
        R_W_pubf[2]=R_W_Pluse;
        R_W_pubf[3]=R_W_Pluse;	
      }
      else if(R_W_PluseTemp<70)
      {
        R_W_Pluse=70;			
        R_W_pubf[0]=R_W_Pluse;
        R_W_pubf[1]=R_W_Pluse;
        R_W_pubf[2]=R_W_Pluse;
        R_W_pubf[3]=R_W_Pluse;
      }
      else
      {
        R_W_Pluse=R_W_PluseTemp;			
        R_W_pubf[0]=R_W_Pluse;
        R_W_pubf[1]=R_W_Pluse;
        R_W_pubf[2]=R_W_Pluse;
        R_W_pubf[3]=R_W_Pluse;
      }		
    }
    else
    {
      k=0;
      m=0;
      //===============
      if(R_W_PluseTemp>R_W_Pluse)
      {
        k=R_W_PluseTemp-R_W_Pluse;
      }
      else
      {
        m=R_W_Pluse-R_W_PluseTemp;
      }
      //=================
      if(k>8)
      {
        l=R_W_Pluse+8;
      }
      else	if(m>8)
      {
        l=R_W_Pluse-8;
      }
      else
        l=R_W_PluseTemp;
      R_W_PluseTemp=l;
      R_W_pubf[R_W_pluseIndex]=R_W_PluseTemp;
      R_W_pluseIndex++;
      if(R_W_pluseIndex>3)
        R_W_pluseIndex=0;
      if(R_W_pluseIndex==0)
      {
        i=R_W_pubf[0];
        i=i+R_W_pubf[1];
        i=i+R_W_pubf[2];
        i=i+R_W_pubf[3];			
        i=i>>2;			//i/4			
        R_W_Pluse=i;	
      }
    }
}
//========================================================
//無線心跳訊號偵側
//========================================================
void	F_Pluse2sub(void)	
{
  rt_uint8_t i;
	
  R_W_Plusecount++;
  if(GPIO_ReadInputDataBit(P_PULSE2_GPIO_PORT,P_PULSE2_PIN))	//Wpluse_P=1	PG1_P
  {	
    //===========================================================		
    if(Heart_W_PluseFlg==0)	//low-->Hi
    {
      R_Heart_W_PluseWidth++;
      if(R_Heart_W_PluseWidth>10)	//Hi寬度需大於10mS才承認心跳訊號
      {	
        R_Heart_W_PluseWidth=0;
        Heart_W_PluseFlg=1;
        if((R_W_Plusecount<1500)&&(R_W_Plusecount>272))	//	(60000/40)<R_Plusecount<(60000/220)
        {											//	40<R_Pluse1<220
          R_W_PluseTemp=60000/R_W_Plusecount;
          R_W_Plusecount=0;
          //wHeartDetectionFlg=1;
          //==============================		
          if(R_W_Pluse==0)
          {
            if(R_W_PluOld==0)
            {
              R_W_PluOld=R_W_PluseTemp;
            }
            else
            {
              if(R_W_PluseTemp>R_W_PluOld)
                i=R_W_PluseTemp-R_W_PluOld;
              else
                i=R_W_PluOld-R_W_PluseTemp;
              //===================
              if(i<4)
              {
                R_W_DelayTime++;
                if(R_W_DelayTime>3)
                {
                  R_W_DelayTime=0;
									F_PluseFunction2();
                }
              }
              //===================
              R_W_PluOld=R_W_PluseTemp;
            }
          }
          else
          {
						F_PluseFunction2();
          }
          //==============================		
        }
        else
        {
          R_W_Plusecount=0;
        }
      }					
    }
    //==========================================================
  }
  else
  {
    Heart_W_PluseFlg=0;
    R_Heart_W_PluseWidth=0;	
  }
  //==================
  if(R_W_Plusecount>3000)
  {
    R_W_Plusecount=0;
    R_W_DelayTime=0;
    R_W_Pluse=0;
    //wHeartDetectionFlg=0;
    R_W_PluseTemp=0;			
    R_W_PluOld=0;
    R_W_pubf[0]=0;
    R_W_pubf[1]=0;
    R_W_pubf[2]=0;
    R_W_pubf[3]=0;
  }
}

static void timeout_callbak(void* parameter)
{
		F_Pluse1sub();	
		F_Pluse2sub();
		F_SpeedDetection();
}

rt_uint8_t	F_readHandHeartRate(void)
{

	return R_Pluse;
}

rt_uint8_t	F_readwHeartRate(void)
{

	return R_W_Pluse;
}

//==============================================================================
//This routine will setup the PULSE Port
//==============================================================================
void rt_hw_heart_rate_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

		
		// Input PULSE2   on PA11  
		// Enable the PULSE2 
		RCC_AHBPeriphClockCmd(P_PULSE2_GPIO_CLK, ENABLE);
		// Configure the PULSE2  pin 
		GPIO_InitStructure.GPIO_Pin = P_PULSE2_PIN ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(P_PULSE2_GPIO_PORT, &GPIO_InitStructure);
  
		// Input PULSE1   on PA12       
		// Enable the PULSE1 
		RCC_AHBPeriphClockCmd(P_PULSE1_GPIO_CLK, ENABLE);
		// Configure the PULSE1  pin 
		GPIO_InitStructure.GPIO_Pin = P_PULSE1_PIN ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(P_PULSE1_GPIO_PORT, &GPIO_InitStructure);
	
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
	
	
		heart_timer = rt_timer_create("heartSpeed",
																	timeout_callbak,
																	RT_NULL,
																	1,
																	RT_TIMER_FLAG_PERIODIC);
																	
		if(heart_timer != RT_NULL) rt_timer_start(heart_timer);
}

#include <finsh.h>

int read_heart(void)
{
		rt_kprintf("5K_heart=%d\n", R_Pluse);
		rt_kprintf("heart=%d\n", R_W_Pluse);
		return 0;
}

FINSH_FUNCTION_EXPORT_ALIAS(read_heart, __cmd_read_heart, read heart rate);
