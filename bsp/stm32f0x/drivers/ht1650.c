
#include "stm32f0xx.h"
#include "ht1650.h"

#define P_HT165XCS_PIN                  GPIO_Pin_12                              
#define P_HT165XCS_GPIO_PORT            GPIOA
#define P_HT165XCS_GPIO_CLK             RCC_AHBPeriph_GPIOA

#define P_HT165XWR_PIN                  GPIO_Pin_11                             
#define P_HT165XWR_GPIO_PORT            GPIOA
#define P_HT165XWR_GPIO_CLK             RCC_AHBPeriph_GPIOA

#define P_HT165XDB0_PIN                	GPIO_Pin_12                              
#define P_HT165XDB0_GPIO_PORT         	GPIOB
#define P_HT165XDB0_GPIO_CLK						RCC_AHBPeriph_GPIOB

#define P_HT165XDB1_PIN                	GPIO_Pin_13                              
#define P_HT165XDB1_GPIO_PORT         	GPIOB
#define P_HT165XDB1_GPIO_CLK						RCC_AHBPeriph_GPIOB

#define P_HT165XDB2_PIN                	GPIO_Pin_14                              
#define P_HT165XDB2_GPIO_PORT         	GPIOB
#define P_HT165XDB2_GPIO_CLK						RCC_AHBPeriph_GPIOB

#define P_HT165XDB3_PIN                	GPIO_Pin_15                              
#define P_HT165XDB3_GPIO_PORT         	GPIOB
#define P_HT165XDB3_GPIO_CLK						RCC_AHBPeriph_GPIOB

/* LCDBuffer size */



/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/
/* 165x cmd ?? */
#define C_16_WRITE					0x05		
#define C_16_CMD						0x04		
/* 165x cmd */
#define C_16_SYSDIS					0x00					//; Turn off LCD bias generator
#define C_16_SYSEN					0x01					//; Turn on LCD oscillator
#define C_16_LCDOFF					0x02					//; Turn off LCD
#define C_16_LCDON					0x03					//; Turn on LCD
#define C_16_F170						0x1C					//; Turn on LCD

/* ???? */
#define LCD_Delay_Val				0
/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
rt_uint32_t LCDBuffer[C_LCDRamSize];

static void F_EEDelay(volatile rt_uint32_t us)
{
	
    while(us>1)
    {
      us--;
    }
    us=0;	

    //rt_uint32_t delta;
    /* 獲得延時經過 tick 數 */
    //us = us * (SysTick->LOAD/(1000000/RT_TICK_PER_SECOND));
    /* 獲得當前的時間 */
    //delta = SysTick->VAL;
    /* 循環獲得當前的時間，直到達到指定的時間後退出循環 */
   // while (delta - SysTick->VAL< us);
}
/*============================================================================
* Function	: F_165XCS
* Description	: CS pin ?? 
* Input 		: uInt8 => data is hight or low
* Return Value : void
=============================================================================*/
void	F_165XCS(rt_uint8_t data)
{	
  if(data)
    P_HT165XCS_GPIO_PORT->BSRR = P_HT165XCS_PIN;
  else
    P_HT165XCS_GPIO_PORT->BRR = P_HT165XCS_PIN;
}
/*============================================================================
* Function	: F_165XWR
* Description	: WR ??
* Input 		: uInt8 => data is hight or low
* Return Value : void
=============================================================================*/
void	F_165XWR(rt_uint8_t data)
{	
  if(data)
    P_HT165XWR_GPIO_PORT->BSRR = P_HT165XWR_PIN;
  else
    P_HT165XWR_GPIO_PORT->BRR = P_HT165XWR_PIN;
}
/*============================================================================
* Function	: F_165XDB0
* Description	: DATA ??
* Input 		: uInt8 =>data is hight or low
* Return Value : void
=============================================================================*/
void	F_165XDB0(rt_uint8_t data)
{	
  if(data)
    P_HT165XDB0_GPIO_PORT->BSRR = P_HT165XDB0_PIN;
  else
    P_HT165XDB0_GPIO_PORT->BRR = P_HT165XDB0_PIN;
}
/*============================================================================
* Function	: F_165XDB1
* Description	: DATA ??
* Input 		: uInt8 =>data is hight or low
* Return Value : void
=============================================================================*/
void	F_165XDB1(rt_uint8_t data)
{	
  if(data)
    P_HT165XDB1_GPIO_PORT->BSRR = P_HT165XDB1_PIN;
  else
    P_HT165XDB1_GPIO_PORT->BRR = P_HT165XDB1_PIN;
}
/*============================================================================
* Function	: F_165XDB2
* Description	: DATA ??
* Input 		: uInt8 =>data is hight or low
* Return Value : void
=============================================================================*/
void	F_165XDB2(rt_uint8_t data)
{	
  if(data)
    P_HT165XDB2_GPIO_PORT->BSRR = P_HT165XDB2_PIN;
  else
    P_HT165XDB2_GPIO_PORT->BRR = P_HT165XDB2_PIN;
}
/*============================================================================
* Function	: F_165XDB3
* Description	: DATA ??
* Input 		: uInt8 =>data is hight or low
* Return Value : void
=============================================================================*/
void	F_165XDB3(rt_uint8_t data)
{	
  if(data)
    P_HT165XDB3_GPIO_PORT->BSRR = P_HT165XDB3_PIN;
  else
    P_HT165XDB3_GPIO_PORT->BRR = P_HT165XDB3_PIN;
}

/*============================================================================
* Function	: F_165XDATA
* Description	: DATA ??
* Input 		: uInt8 =>data is hight or low
* Return Value : void
=============================================================================*/
void	F_165XDATA(rt_uint8_t data)
{
  rt_uint8_t a,b,c,d;
  a = ((data >> 3) & 0x01);
  b = ((data >> 2) & 0x01);
  c = ((data >> 1) & 0x01);
  d = (data  & 0x01);
	  
  F_165XDB3(a);
  F_165XDB2(b);
  F_165XDB1(c);
  F_165XDB0(d);
}
/*============================================================================
* Function	: F_165XID
* Description	: ??ID 
* Input  		: uInt8 =>ID is ID
* Return Value : void
=============================================================================*/
void F_165XID(rt_uint8_t ID)
{	
  F_165XDATA(ID);
  F_165XWR(0);
  F_EEDelay(LCD_Delay_Val);
  F_165XWR(1);
}
/*============================================================================
* Function	: F_162XCom
* Description	: command ??
* Input  		: uInt8 =>ch is ??
* Return Value : void
=============================================================================*/
void F_165XCom(rt_uint8_t ch)
{
  rt_uint8_t i,j;
  
  i = ((ch & 0xF0) >> 4);
  j = (ch & 0x0F);
  
  F_165XDATA(i);
  F_165XWR(0);
  F_EEDelay(LCD_Delay_Val);		
  F_165XWR(1);
  
  F_165XDATA(j);
  F_165XWR(0);	
  F_EEDelay(LCD_Delay_Val);
  F_165XWR(1);
  
  F_165XDATA(0);
  F_165XWR(0);	
  F_EEDelay(LCD_Delay_Val);
  F_165XWR(1);
  
}
/*============================================================================
* Function	: F_HT165XInitial
* Description	: ???
* Input 		: void
* Return Value : void
=============================================================================*/
void F_HT165XInitial(void)
{
  F_165XCS(0);
  F_165XID(C_16_CMD);
  //F_165XCom(C_16_F170);
  F_165XCom(C_16_SYSEN );
  F_165XCom(C_16_LCDON );
  F_165XCS(1);
}
/*============================================================================
* Function	: F_LCDSleep
* Description	: LcdDriverSleep
* Input 		: void
* Return Value : void
=============================================================================*/
void F_LCDSleep(void)
{
  F_165XCS(0);
  F_165XID(C_16_CMD);
  F_165XCom(C_16_SYSDIS );
  F_165XCom(C_16_LCDOFF );
  F_165XCS(1);
}
/*============================================================================
* Function	: F_HT162XAddress
* Description	: ????
* Input Para	: uInt16 => adr is ????
* Return Value : void
=============================================================================*/
void F_HT165XAddress(rt_uint16_t adr)
{
  rt_uint8_t k,m,n;
  
  k = ((adr >> 5) & 0x08);
  m = ((adr >> 4) & 0x0F);
  n = (adr & 0x0F);
  
  F_165XID((C_16_WRITE | k));
  
  F_165XDATA(m);
  F_165XWR(0);
  F_EEDelay(LCD_Delay_Val);
  F_165XWR(1);
  
  F_165XDATA(n);
  F_165XWR(0);
  F_EEDelay(LCD_Delay_Val);
  F_165XWR(1);
}
/*============================================================================
* Function	: F_HT165XWrite
* Description	: ???
* Input 		: uInt32 => data is ????
* Return Value : void
=============================================================================*/
void F_HT165XWrite(rt_uint32_t data)
{
  rt_uint8_t i,j;
  
  for(j = 0 ;j < 8; j++)
  { 
    i = (rt_uint8_t)(data & 0x0F);
    
    F_165XDATA(i);
    F_165XWR(0);
    F_EEDelay(LCD_Delay_Val);
    F_165XWR(1);

    data = data >> 4;
  }
}
/*============================================================================
* Function	: F_SetDisplayRam
* Description	: ?? LCD RAM ? 0 or 1
* Input 		: uInt8 => SetClear is ????  0:0x00 1=0xFF
* Return Value : void
=============================================================================*/
void F_SetDisplayRam(rt_uint8_t SetClear)
{
  rt_uint8_t i;
  if(SetClear)
  {
    for(i = 0;i < C_LCDRamSize;i++)
	 LCDBuffer[i] = 0xffffffff;
  }
  else
  {
    for(i = 0;i < C_LCDRamSize;i++)
	 LCDBuffer[i] = 0;
  }
}
/*============================================================================
* Function	: F_Display
* Description	: ?RAM???Driver
* Input 		: void
* Return Value : void
=============================================================================*/
void F_Display(void)
{
  rt_uint8_t i;
  
  F_HT165XInitial();
  F_165XCS(0);
  F_HT165XAddress(0);
  for(i = 0;i < C_LCDRamSize;i++)
  {
    F_HT165XWrite(LCDBuffer[i]);
  }
  F_165XCS(1);
  F_165XWR(1);
  F_165XDATA(0x0F);	
}
/*============================================================================
* Function	: F_InitialLCD_GPIO
* Description	: This routine will setup the LCD Pin
* Input 		: void
* Return Value : void
=============================================================================*/
int F_InitialHT165x_GPIO(void)
{

  GPIO_InitTypeDef GPIO_InitStructure;
  
  // Output 165X 
  // Enable the P_HT165XCS_PIN 

  RCC_AHBPeriphClockCmd(P_HT165XCS_GPIO_CLK, ENABLE);
  
  // Configure the P_HT162XCS_PIN  pin
  GPIO_InitStructure.GPIO_Pin = P_HT165XCS_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_HT165XCS_GPIO_PORT, &GPIO_InitStructure);
  
  // Enable the P_HT162XWR_PIN

  RCC_AHBPeriphClockCmd(P_HT165XWR_GPIO_CLK, ENABLE);

  
  // Configure the P_HT162XWR_PIN  pin
  GPIO_InitStructure.GPIO_Pin = P_HT165XWR_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_HT165XWR_GPIO_PORT, &GPIO_InitStructure);
  
  // Enable the P_HT165XDBX_PIN

  RCC_AHBPeriphClockCmd(P_HT165XDB0_GPIO_CLK, ENABLE);
  RCC_AHBPeriphClockCmd(P_HT165XDB1_GPIO_CLK, ENABLE);
  RCC_AHBPeriphClockCmd(P_HT165XDB2_GPIO_CLK, ENABLE);
  RCC_AHBPeriphClockCmd(P_HT165XDB3_GPIO_CLK, ENABLE);

  
  // Configure the P_HT165XDBX_PIN  pin 
  GPIO_InitStructure.GPIO_Pin = P_HT165XDB0_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_HT165XDB0_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = P_HT165XDB1_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_HT165XDB1_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = P_HT165XDB2_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_HT165XDB2_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = P_HT165XDB3_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_HT165XDB3_GPIO_PORT, &GPIO_InitStructure);
	
	return 0;
}

INIT_DEVICE_EXPORT(F_InitialHT165x_GPIO);
