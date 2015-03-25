//==================================================================
// 揚升馬達相關程式
//==================================================================
#include "chandler.h"
#include <stm32f0xx.h>

 //M2- 2121034
 /*
 #define P_M2_DOWN_PIN                  GPIO_Pin_15              
 #define P_M2_DOWN_GPIO_PORT            GPIOB
 #define P_M2_DOWN_GPIO_CLK             RCC_AHBPeriph_GPIOB
 */
 #define P_M2_DOWN_PIN                  GPIO_Pin_7             
 #define P_M2_DOWN_GPIO_PORT            GPIOA
 #define P_M2_DOWN_GPIO_CLK             RCC_AHBPeriph_GPIOA
 
/*
 //M2+ 2121034
 #define P_M2_UP_PIN                    GPIO_Pin_14                         
 #define P_M2_UP_GPIO_PORT              GPIOB
 #define P_M2_UP_GPIO_CLK               RCC_AHBPeriph_GPIOB
*/
 #define P_M2_UP_PIN                    GPIO_Pin_0                         
 #define P_M2_UP_GPIO_PORT              GPIOB
 #define P_M2_UP_GPIO_CLK               RCC_AHBPeriph_GPIOB
 
 //VR2
 #define P_VR2_PIN                      GPIO_Pin_1                              
 #define P_VR2_GPIO_PORT                GPIOB
 #define P_VR2_GPIO_CLK                 RCC_AHBPeriph_GPIOB
 #define P_VR2_Channel                  ADC_Channel_9


static struct rt_thread			rt_incline_thread;
static rt_uint8_t incline_stack[384];
static rt_inc_init_data_t 	inc_data;


static rt_uint8_t			R_IncNumAd,R_IncNumAdBuf,R_IncNumDetect;
static rt_uint16_t		R_RelayWaitTime;
static rt_uint16_t		R_IncAutoTemp1,R_IncAutoTemp2;
static rt_uint16_t		R_IncAutoAd;
static rt_uint16_t		R_IncErrAd;
static rt_uint16_t		R_IncErrTime;
static rt_uint8_t			R_IncAutoTime,R_IncAutoCnt;

static rt_bool_t IncStopFlg;
static rt_bool_t IncSetFlag;
static rt_bool_t RelayUpDownFlg;
static rt_bool_t IncAutoFlg;
static rt_bool_t IncErrFlg;
static rt_bool_t IncMicroControlFlg;
static rt_bool_t IncControlFlg;
static rt_bool_t IncControlUpDownFlg;
//===================================================
static void F_IncIoUpControl(rt_uint8_t	Data)
{  
    if(Data)
      P_M2_UP_GPIO_PORT -> BSRR = P_M2_UP_PIN;  
      else
        P_M2_UP_GPIO_PORT -> BRR = P_M2_UP_PIN;  
}
//===================================================
static void F_IncIoDownControl(rt_uint8_t	Data)
{
    if(Data)
      P_M2_DOWN_GPIO_PORT -> BSRR = P_M2_DOWN_PIN;   
      else
        P_M2_DOWN_GPIO_PORT->BRR = P_M2_DOWN_PIN; 
}

//======================================================
static void  F_IncAd(rt_uint8_t	Data)
{
  R_IncNumAd = rt_inc_read_ad();
  //=================
  if(Data<=254)
    R_IncAutoTemp1=Data+1;
  else
    R_IncAutoTemp1=Data;
  if(Data>=1)	
    R_IncAutoTemp2=Data-1;
  else
    R_IncAutoTemp2=Data;
}
//=========================================
static void	F_IncErr(void)
{
		IncErrFlg=1;
		inc_data.err_treadmill_handler(InclineErrNumVal);
}
//=========================================
static void  F_IncErrDetection(void)
{	//100mS
  unsigned  char  i;
  if(R_IncErrTime<120)          //  限制R_IncErrTime 溢位
    R_IncErrTime++;
  
  if(R_IncErrTime==1)
  {
    R_IncErrAd=R_IncNumAd;			
  }		
  if(R_IncErrTime==40)       //  4秒後 ad 值沒有任何的動作 error
  {
    R_IncErrTime=0;
    //==================
    if(R_IncNumAd>R_IncErrAd)
      i=R_IncNumAd-R_IncErrAd;
    else
      i=R_IncErrAd-R_IncNumAd;
    //==================
    if(i<5) 
		{			//  AD 值 允許有 正負 5 的誤差
      F_IncErr();
		}
  }
}
//=========================================
static void  F_RelayMoveDown(void)
{
  F_IncIoUpControl(0);          //關閉上升繼電器
  if(RelayUpDownFlg)
  {
    F_IncIoDownControl(1);      //開啟下降繼電器
    F_IncErrDetection();
  }
  else
  {
    R_IncErrTime=0;
    R_RelayWaitTime++;
    if(R_RelayWaitTime >= 10)   //需要等1秒鐘,才能轉成上升模式
    {
      R_RelayWaitTime=0;
      RelayUpDownFlg=1;         //揚升下降
    }
  }
}
//=========================================
static void  F_RelayMoveUp(void)
{ 
  F_IncIoDownControl(0);        //關閉下降繼電器
  if(RelayUpDownFlg)            //上一次為下降時
  {
    R_IncErrTime=0;
    R_RelayWaitTime++;
    if(R_RelayWaitTime >= 10)   //需要等1秒鐘,才能轉成上升模式
    {
      R_RelayWaitTime=0;
      RelayUpDownFlg=0;         //揚升上升
    }
  }
  else
  {
    F_IncIoUpControl(1);        //開啟上升繼電器
    F_IncErrDetection();
  }
}

//=========================================
void  F_RelayMoveStop(void)
{
  F_IncIoUpControl(0);
  F_IncIoDownControl(0);
  IncSetFlag=0;
	IncMicroControlFlg = 0;
  R_RelayWaitTime=0;
  R_IncErrTime=0;
  IncAutoFlg=0;
  R_IncAutoTime=0;
  R_IncAutoCnt=0;
}
//====================================================
//揚升控制
//====================================================
void  F_IncControl(void)
{
  unsigned  char  IncNumTemp,IncParagraph;
  if(IncStopFlg==0)
  {
		if(IncMicroControlFlg == 0)
		{
			if(R_IncNumDetect != inc_data.incNum)
			{  
				R_IncNumDetect = inc_data.incNum;
				IncSetFlag=1;
			}
		} else {
			IncSetFlag=1;
		}
		
    if(IncSetFlag==1)
    {
			if(IncMicroControlFlg == 0)
			{
        //=======================
        IncParagraph = inc_data.incline_eeprom_data.incMaxNum;    //  最大揚升段數
        IncNumTemp = inc_data.incNum;      //  目前揚升段數
        if(inc_data.incline_eeprom_data.incUpDownFlg == 0)       //  反揚升
        IncNumTemp=IncParagraph-IncNumTemp;
        R_IncNumAdBuf = (inc_data.incline_eeprom_data.incMaxAd)-(((inc_data.incline_eeprom_data.incMaxAd - inc_data.incline_eeprom_data.incMinAd)/IncParagraph)*IncNumTemp);
        //=======================
			}
      F_IncAd(R_IncNumAdBuf);     //  需要的AD位置  R_IncNumAdBuf
      if(R_IncNumAd < R_IncAutoTemp2)
      {
        if(inc_data.incline_eeprom_data.incUpDownFlg)
          F_RelayMoveDown();
        else
          F_RelayMoveUp();
      }
      else  if(R_IncNumAd > R_IncAutoTemp1)
      {
        if(inc_data.incline_eeprom_data.incUpDownFlg)
          F_RelayMoveUp();
        else
          F_RelayMoveDown();
      }
      else
        F_RelayMoveStop();
    }
    else
      F_RelayMoveStop();
  }
  else
  {
    F_RelayMoveStop();
    R_IncNumDetect=0xff;
  }
}
//==========================================================================
void	F_IncCorrectionEnd(void)
{
		rt_uint8_t	Temp;
        if(inc_data.incline_eeprom_data.incMaxAd > inc_data.incline_eeprom_data.incMinAd)
        {   //  正向	
          inc_data.incline_eeprom_data.incUpDownFlg = 1;
          Temp = inc_data.incline_eeprom_data.incMaxAd - inc_data.incline_eeprom_data.incMinAd;
        }
        else
        {
          inc_data.incline_eeprom_data.incUpDownFlg = 0;   //  反向
          Temp = inc_data.incline_eeprom_data.incMinAd - inc_data.incline_eeprom_data.incMaxAd;
        }
        if(Temp < 100)
        {         //  揚升校正錯誤
					inc_data.err_treadmill_handler(InclineAutoErrNumVal);
        }
        else
        {       //  揚升校正 OK
          if(inc_data.incline_eeprom_data.incUpDownFlg == 1)
          {
            inc_data.incline_eeprom_data.incMaxAd = inc_data.incline_eeprom_data.incMaxAd - 2;
          }
          else
          {
            Temp = inc_data.incline_eeprom_data.incMaxAd;			//Max 與 Min 對調
            inc_data.incline_eeprom_data.incMaxAd = inc_data.incline_eeprom_data.incMinAd;
            inc_data.incline_eeprom_data.incMinAd = Temp;
            inc_data.incline_eeprom_data.incMinAd = inc_data.incline_eeprom_data.incMinAd + 2;
          }
					inc_data.err_treadmill_handler(InclineAutoOkNumVal);
        }
}

void	rt_IncCorrectionAdr_1(void)
{
		inc_data.incline_eeprom_data.incMinAd = rt_inc_read_ad();
}

void	rt_IncCorrectionAdr_2(void)
{
		inc_data.incline_eeprom_data.incMaxAd = rt_inc_read_ad();
}

//==========================================================
//自動校正
//==========================================================
void  F_IncAuto(void)
{
  R_IncAutoTime++;
  F_IncAd(R_IncAutoAd);
  //=====================
  if(R_IncAutoTemp1<=253)
    R_IncAutoTemp1=R_IncAutoTemp1+2;
  else
    R_IncAutoTemp1=R_IncAutoTemp1;
  if(R_IncAutoTemp2>=2)	
    R_IncAutoTemp2=R_IncAutoTemp2-2;
  else
    R_IncAutoTemp2=R_IncAutoTemp2;
  //=====================
  switch(R_IncAutoCnt)          //  揚升校準處理
  {	
  case  0:
    F_IncIoUpControl(1);        //  開啟上升繼電器
    F_IncIoDownControl(0);      //  關閉下降繼電器
    R_IncAutoTime=0;
    R_IncAutoCnt=1;
    break;
    //===================================
  case  1:
    if((R_IncNumAd>=R_IncAutoTemp2)&&(R_IncNumAd<=R_IncAutoTemp1))
    {
      if(R_IncAutoTime>60)      //  穩定超過6秒
      {
        R_IncAutoTime=0;	
        F_IncIoUpControl(0);    //  關閉上升繼電器
				rt_IncCorrectionAdr_1();
        R_IncAutoCnt=2;
      }
    }
    else
    {
      R_IncAutoAd=R_IncNumAd;
      R_IncAutoTime=0;
    }
    break;
    //===================================
  case  2:
    if(R_IncAutoTime>=30)       //需要等3秒鐘,才能轉成下降模式
    {
      R_IncAutoTime=0;
      F_IncIoDownControl(1);    //開啟下降繼電器
      R_IncAutoCnt=3;
    }
    break;
    //===================================
  case  3:
    if((R_IncNumAd>=R_IncAutoTemp2)&&(R_IncNumAd<=R_IncAutoTemp1))
    {
      if(R_IncAutoTime>60)      //穩定超過6秒 
      {
        R_IncAutoTime=0;
				rt_IncCorrectionAdr_2();
        F_RelayMoveStop();
        IncStopFlg=1;           //揚升關閉
				F_IncCorrectionEnd();
      }
    }
    else
    {
      R_IncAutoAd=R_IncNumAd;
      R_IncAutoTime=0;
    }
    break;
  }
}

//==============================================================================
//    
//==============================================================================
static void incline_thread_entry(void* parameter)
{
		while(1)
		{
			rt_thread_delay(100);
			if(IncControlFlg == 0) {
				if(IncErrFlg==0)
				{
					if(IncAutoFlg)
						F_IncAuto();        //揚升自動校正
					else
						F_IncControl();			//揚升控制
				}
					else
					{	
						F_RelayMoveStop();
					}
			} else {
				if(IncControlUpDownFlg) {
					F_IncAd(inc_data.incline_eeprom_data.incMaxAd);     //  需要的AD位置 
					if(R_IncNumAd < R_IncAutoTemp2) {
						F_RelayMoveUp();
					} else {
						F_RelayMoveStop();	
					}
				} else {
					F_IncAd(inc_data.incline_eeprom_data.incMinAd);     //  需要的AD位置 
					if(R_IncNumAd > R_IncAutoTemp1) {
						F_RelayMoveDown();
					} else{
						F_RelayMoveStop();
					}
				}
			}
		}
}

void	rt_incline_control(rt_uint8_t incNum)
{
		inc_data.incNum = incNum;
		IncStopFlg = 0;
}

void	rt_incline_auto(void)
{
		IncAutoFlg = 1;
}

void	rt_incline_stop(void)
{
		IncStopFlg = 1;
}

void	rt_inc_micro_control(rt_uint8_t IncNumAdBuf)
{
	IncMicroControlFlg = 1;
	R_IncNumAdBuf = IncNumAdBuf;
	IncStopFlg = 0;
	IncErrFlg=0;
}

rt_uint8_t	rt_inc_read_ad(void)
{
  rt_uint16_t	AdTemp=0,IncAdTemp=0;
  rt_uint8_t  i;	
  for(i=0;i<5;i++)
  {
    AdTemp = ADC_GetConversionValue(ADC1);  	//  開始進行ADC轉換
    IncAdTemp=AdTemp+IncAdTemp;	    
  }
  IncAdTemp=IncAdTemp/5;
	
	return	(rt_uint8_t)255-IncAdTemp;
}
	
void	rt_read_incline_eeprom_data(rt_incline_eeprom_data_t *data)
{
	(*data) = inc_data.incline_eeprom_data;
}
//==============================================================================
//    
//==============================================================================
void	rt_seat_position_up(void)
{
	IncControlFlg = 1;
	IncControlUpDownFlg = 1;
	R_RelayWaitTime = 10;
}

void	rt_seat_position_down(void)
{
	IncControlFlg = 1;
	IncControlUpDownFlg = 0;
	R_RelayWaitTime = 10;
}

void	rt_seat_position_stop(void)
{
	IncControlFlg = 0;
	F_RelayMoveStop();
}
//==============================================================================
//      ADC 初始化
//==============================================================================
void F_InitialADC(void)
{
  ADC_InitTypeDef          ADC_InitStructure;
  GPIO_InitTypeDef         GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	// 聲明定時器初始化結構體
  TIM_OCInitTypeDef        TIM_OCInitStructure; 
  
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(P_VR2_GPIO_CLK, ENABLE);
  
  /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  /* TIM3 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  
  /* Configure ADC Channel0 as analog input */
  GPIO_InitStructure.GPIO_Pin = P_VR2_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(P_VR2_GPIO_PORT, &GPIO_InitStructure);
  
  /* TIM3 Configuration *******************************************************/
  TIM_DeInit(TIM3);
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_OCStructInit(&TIM_OCInitStructure);
  
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 0xFF;
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  
  /* TIM3 TRGO selection */
  TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);
  
  /* ADC2 Configuration *******************************************************/
  /* ADCs DeInit */  
  ADC_DeInit(ADC1);
  
  /* Configure the ADC1 in continous mode withe a resolutuion equal to 8 bits*/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;    
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 
  
  /* Convert the ADC1 Channel 0 with 239.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, P_VR2_Channel , ADC_SampleTime_28_5Cycles);   
  
  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable the auto delay feature */    
  ADC_WaitModeCmd(ADC1, ENABLE); 
  
  /* Enable the Auto power off mode */
  ADC_AutoPowerOffCmd(ADC1, ENABLE); 
  
  /* Enable ADCperipheral[PerIdx] */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADCEN falg */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  
  /* TIM2 enable counter */
  TIM_Cmd(TIM3, ENABLE);
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
}
//==============================================================================
//  GPIO 設定
//==============================================================================
void  rt_hw_incline_control_init(rt_inc_init_data_t	inc_data_init)
{
		rt_err_t result;
		GPIO_InitTypeDef GPIO_InitStructure;
	 
		/* Enable the M2- */
		RCC_AHBPeriphClockCmd(P_M2_DOWN_GPIO_CLK, ENABLE);
		
		/* Configure the M2- pin */
		GPIO_InitStructure.GPIO_Pin = P_M2_DOWN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(P_M2_DOWN_GPIO_PORT, &GPIO_InitStructure);
		
		/* Enable the M2+ */
		RCC_AHBPeriphClockCmd(P_M2_UP_GPIO_CLK, ENABLE);
		
		/* Configure the M2+ pin */
		GPIO_InitStructure.GPIO_Pin = P_M2_UP_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(P_M2_UP_GPIO_PORT, &GPIO_InitStructure);
		
		F_InitialADC();
	
		inc_data = inc_data_init;
		
		result = rt_thread_init(&rt_incline_thread,"incline", incline_thread_entry, RT_NULL,
						(rt_uint8_t*)&incline_stack[0], sizeof(incline_stack),3,2);
		
		if(result == RT_EOK) 
		{ 
			rt_thread_startup(&rt_incline_thread); 
		}
}

#include <finsh.h>

int inc_err(void)
{
		//rt_kprintf("setSpeed = %d\n", speed_data.setSpeed);

		F_IncErr();
		return 0;
}

FINSH_FUNCTION_EXPORT_ALIAS(inc_err, __cmd_inc_err, inc err test);

int inc_auto(void)
{
		rt_incline_auto();
		return 0;
}

FINSH_FUNCTION_EXPORT_ALIAS(inc_auto, __cmd_inc_auto, inc_auto);

int incline_adr(int argc , char** argv)
{
	if(inc_data.incline_eeprom_data.incMaxNum >= atoi(argv[1]))
	{
		rt_incline_control(atoi(argv[1]));
		rt_kprintf("incNum = %d\n", inc_data.incNum);
	} 
		else 
		{
			rt_kprintf("inc adr must <= %d\n", inc_data.incline_eeprom_data.incMaxNum);
		}
		return 0;
}

MSH_CMD_EXPORT(incline_adr, do incline adr);

int inc_read_data(void)
{
		rt_kprintf("incMaxAd = %d\n", inc_data.incline_eeprom_data.incMaxAd);
	
		rt_kprintf("incMinAd = %d\n", inc_data.incline_eeprom_data.incMinAd);
	
		rt_kprintf("incUpDownFlg = %d\n", inc_data.incline_eeprom_data.incUpDownFlg);
	
		rt_kprintf("incAd = %d\n", rt_inc_read_ad());
	
		return 0;
}

FINSH_FUNCTION_EXPORT_ALIAS(inc_read_data, __cmd_inc_read_data, inc all data);
