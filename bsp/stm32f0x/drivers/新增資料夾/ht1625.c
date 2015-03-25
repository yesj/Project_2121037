
#include "stm32f0xx.h"
#include "ht1625.h"

// HT1625
#define P_HT1625CS_PIN                  GPIO_Pin_5                              
#define P_HT1625CS_GPIO_PORT            GPIOB
#define P_HT1625CS_GPIO_CLK             RCC_AHBPeriph_GPIOB

#define P_HT1625WR_PIN                  GPIO_Pin_6                             
#define P_HT1625WR_GPIO_PORT            GPIOB
#define P_HT1625WR_GPIO_CLK             RCC_AHBPeriph_GPIOB

#define P_HT1625DA_PIN                  GPIO_Pin_7                              
#define P_HT1625DA_GPIO_PORT            GPIOB
#define P_HT1625DA_GPIO_CLK             RCC_AHBPeriph_GPIOB

//==========================
#define D_NORMAL	0xe3
#define D_SysEN		0x01
#define D_SysDis	0x00
#define D_TIMEREN	0x06
#define D_IRQEN		0x88
#define D_IRQDIS	0x80
#define D_BIAS		0x29	//0x29
#define D_TONE2K	0x60
#define D_TONEON	0x09
#define D_TONEOFF	0x08
#define D_LCD_ON	0x03
#define D_LCD_OFF	0x02
#define D_IRQ1		0xa0	


//================================================
static void F_1625CS_1(rt_uint8_t data)
{																
  if(data)
    GPIO_SetBits(P_HT1625CS_GPIO_PORT, P_HT1625CS_PIN);
    else
      GPIO_ResetBits(P_HT1625CS_GPIO_PORT, P_HT1625CS_PIN);
}

static void F_1625WR(rt_uint8_t data)
{																
  if(data)
		GPIO_SetBits(P_HT1625WR_GPIO_PORT, P_HT1625WR_PIN);
    else
			GPIO_ResetBits(P_HT1625WR_GPIO_PORT, P_HT1625WR_PIN); 
}

static void F_1625DATA(rt_uint8_t data)
{																
  if(data)
		GPIO_SetBits(P_HT1625DA_GPIO_PORT, P_HT1625DA_PIN);
    else
			GPIO_ResetBits(P_HT1625DA_GPIO_PORT, P_HT1625DA_PIN);  
}
//==============================================================================
// 
//==============================================================================
static void	C_delay(volatile rt_uint8_t count)
{
	//rt_thread_delay(count);
    while(count>1)
    {
      count--;
    }
    count=0;
}
//==============================================================================
// ht1625 選擇
//==============================================================================
static void F_1625ID(rt_uint8_t  a,rt_uint8_t  b,rt_uint8_t  c)
{	
    F_1625DATA(a);
    F_1625WR(0);
    C_delay(2);
    F_1625WR(1);
    C_delay(2);
    F_1625DATA(b);
    F_1625WR(0);
    C_delay(2);
    F_1625WR(1);
    C_delay(2);
    F_1625DATA(c);
    F_1625WR(0);
    C_delay(2);
    F_1625WR(1);
}
//==============================================================================
// ht1625 指令訊號 function
//==============================================================================
static void F_1625Com(rt_uint8_t ch)
{
  unsigned char i,j;
  for(i=0;i<9;i++)
  {
    j=ch&0x80;
    if(j==0)
    {
      F_1625DATA(0);
      F_1625WR(0);
      C_delay(2);		
      F_1625WR(1);
    }	
    else
    { 	
      F_1625DATA(1);
      F_1625WR(0);	
      C_delay(2);
      F_1625WR(1);
    }	
    ch=ch << 1;
  }
}
//================================================
static void F_1625Start(void)
{
    F_1625CS_1(0);
    C_delay(2);
    F_1625ID(1,0,0);
}
//===========
static void F_HT1620Initial(void)
{
    F_1625Start();
    F_1625Com(D_SysEN);
    F_1625Com(D_LCD_ON);
    F_1625Com(D_BIAS);
    F_1625Com(D_NORMAL);
    F_1625CS_1(1);
}
//==============================================
static void F_HT1620Write(rt_uint8_t data)
{
    rt_uint8_t i,j;
    
    for(i=0;i<8;i++)
    {
      j=data&0x80;
      if(j==0)
      {
        F_1625DATA(0);
        F_1625WR(0);
        C_delay(2);
        F_1625WR(1);
      }	
      else
      { 	
        F_1625DATA(1);
        F_1625WR(0);	
        C_delay(2);		
        F_1625WR(1);
      }
      data=data << 1;
    }	
}
//=================================================================	
static void F_HT1620Address(rt_uint8_t adr)
{
  rt_uint8_t k,m;
  
  for(m=0;m<7;m++)
  {
    k=adr&0x40;
    if(k==0)
    {
      F_1625DATA(0);
      F_1625WR(0);
      C_delay(2);		
      F_1625WR(1);
    }	
    else
    {
      F_1625DATA(1);
      F_1625WR(0);	
      C_delay(2);		
      F_1625WR(1);
    }
    adr=adr << 1;
  }	
}

//================================
void F_WriteHT1625(rt_uint8_t *buf,rt_uint8_t bufLength)
{
    rt_uint8_t i;
    F_HT1620Initial();	
    F_1625CS_1(0);
    F_1625ID(1,0,1);	
    F_HT1620Address(0);
    for (i=0;i<bufLength;i++)
    {
      F_HT1620Write(*(buf+i));
    }
    F_1625CS_1(1);
    F_1625WR(1);
    F_1625DATA(1);
}

//================================================
int F_InitialHT1625_GPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
    
  // Output 1625
  // Enable the P_HT1625CS_PIN
  RCC_AHBPeriphClockCmd(P_HT1625CS_GPIO_CLK, ENABLE);
  // Configure the P_HT1625CS_PIN  pin 
  GPIO_InitStructure.GPIO_Pin = P_HT1625CS_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_HT1625CS_GPIO_PORT, &GPIO_InitStructure);
  
  // Enable the P_HT1625WR_PIN
  RCC_AHBPeriphClockCmd(P_HT1625WR_GPIO_CLK, ENABLE);
  // Configure the P_HT1625WR_PIN  pin 
  GPIO_InitStructure.GPIO_Pin = P_HT1625WR_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_HT1625WR_GPIO_PORT, &GPIO_InitStructure);
  
  // Enable the P_HT1625DA_PIN
  RCC_AHBPeriphClockCmd(P_HT1625DA_GPIO_CLK, ENABLE);
  // Configure the P_HT1625WR_PIN  pin
  GPIO_InitStructure.GPIO_Pin = P_HT1625DA_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_HT1625DA_GPIO_PORT, &GPIO_InitStructure);
	
	return 0;
}

INIT_DEVICE_EXPORT(F_InitialHT1625_GPIO);
