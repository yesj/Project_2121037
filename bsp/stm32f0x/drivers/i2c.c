/*
 * File      : usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 
 */
 
/*
設置文件
*/
#include "i2c_device.h"
#include <stm32f0xx.h>
//#include "rtdef.h"

#define delay_time_val		10
/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef SDAOutput_InitStructure;
GPIO_InitTypeDef SDAInput_InitStructure;
GPIO_InitTypeDef SCLOutput_InitStructure;
GPIO_InitTypeDef SCLInput_InitStructure;

/* Private define ------------------------------------------------------------*/
//EEPROM SCL
#define P_SCL_PIN                       GPIO_Pin_8                              
#define P_SCL_GPIO_PORT                 GPIOB
#define P_SCL_GPIO_CLK                  RCC_AHBPeriph_GPIOB
//EEPROM SDA
#define P_SDA_PIN                       GPIO_Pin_9                            
#define P_SDA_GPIO_PORT                 GPIOB
#define P_SDA_GPIO_CLK                  RCC_AHBPeriph_GPIOB


/* Private macro -------------------------------------------------------------*/
#define M_SCL_SetHigh                   P_SCL_GPIO_PORT->BSRR = P_SCL_PIN 
#define M_SCL_SetLow                    P_SCL_GPIO_PORT->BRR = P_SCL_PIN 
#define M_SDA_SetHigh                   P_SDA_GPIO_PORT->BSRR = P_SDA_PIN
#define M_SDA_SetLow                    P_SDA_GPIO_PORT->BRR = P_SDA_PIN 
#define M_SDA_Read                      GPIO_ReadInputDataBit(P_SDA_GPIO_PORT,P_SDA_PIN)
/* Private variables ---------------------------------------------------------*/

void F_SDA_SetOutput(void)
{
  GPIO_Init(P_SDA_GPIO_PORT, &SDAOutput_InitStructure);
}

void F_SDA_SetInput(void)
{
  GPIO_Init(P_SDA_GPIO_PORT, &SDAInput_InitStructure);
}

void F_SCL_SetOutput(void)
{
  GPIO_Init(P_SCL_GPIO_PORT, &SCLOutput_InitStructure);
}

void F_SCL_SetInput(void)
{
  GPIO_Init(P_SCL_GPIO_PORT, &SCLInput_InitStructure);
}
//==============================================================================
//This routine will setup the I2C Port
//==============================================================================
void  F_InitialEEPROM_GPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  // Output EEPROM    
  // Enable the EEPROM SCL
  RCC_AHBPeriphClockCmd(P_SCL_GPIO_CLK, ENABLE);

  SCLInput_InitStructure.GPIO_Pin = P_SDA_PIN ;
  SCLInput_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  SCLInput_InitStructure.GPIO_OType = GPIO_OType_PP;
  SCLInput_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  SCLInput_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  F_SCL_SetInput();
  SCLOutput_InitStructure.GPIO_Pin = P_SCL_PIN ;
  SCLOutput_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  SCLOutput_InitStructure.GPIO_OType = GPIO_OType_PP;
  SCLOutput_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  SCLOutput_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	F_SCL_SetOutput();

	/*
  GPIO_InitStructure.GPIO_Pin = P_SCL_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_SDA_GPIO_PORT, &GPIO_InitStructure);
	*/
  //set high
  P_SCL_GPIO_PORT->BSRR = P_SCL_PIN;  

  // Enable EEPROM SDA
  RCC_AHBPeriphClockCmd(P_SDA_GPIO_CLK, ENABLE);
  // Configure the EEPROM SDA  pin 
  GPIO_InitStructure.GPIO_Pin = P_SDA_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(P_SDA_GPIO_PORT, &GPIO_InitStructure);
  //set high
  P_SDA_GPIO_PORT->BSRR = P_SDA_PIN;
  
  // Configure the EEPROM SDA  pin
  SDAOutput_InitStructure.GPIO_Pin = P_SDA_PIN ;
  SDAOutput_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  SDAOutput_InitStructure.GPIO_OType = GPIO_OType_PP;
  SDAOutput_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  SDAOutput_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  // Configure the EEPROM SDA  pin 
  SDAInput_InitStructure.GPIO_Pin = P_SDA_PIN ;
  SDAInput_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  SDAInput_InitStructure.GPIO_OType = GPIO_OType_PP;
  SDAInput_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  SDAInput_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
}

static void F_EEDelay(rt_uint32_t us)
{
    rt_uint32_t delta;
    /* 獲得延時經過 tick 數 */
    us = us * (SysTick->LOAD/(1000000/RT_TICK_PER_SECOND));
    /* 獲得當前的時間 */
    delta = SysTick->VAL;
    /* 循環獲得當前的時間，直到達到指定的時間後退出循環 */
    while (delta - SysTick->VAL< us);
}
//==============================================================================
//This routine returns a 0 if the I2C device sends an acknowledge
//==============================================================================
void F_I2C_Ackn(void)
{
  //unsigned char Ackn = 0,PortData;      // Temp RAM for Ackn flag
  
  F_SDA_SetInput();                     // Set SDA to input
  F_EEDelay(delay_time_val);
  M_SCL_SetHigh;                        // Clock the ACK bit
  F_EEDelay(delay_time_val); 
  //PortData = M_SDA_Read;  
	while(M_SDA_Read);
  //if(PortData)
  //  Ackn = 1;                           // Check the ACK bit on SDA	
  M_SCL_SetLow;                         // Clear the clock
}	
//==============================================================================
//This routine will send the I2C Start Bit
//==============================================================================
void F_I2C_Start (void)
{  
  F_SDA_SetOutput();                    // Set SDA to output
  F_EEDelay(delay_time_val);
  M_SCL_SetHigh;                        // Set SCL High
  F_EEDelay(delay_time_val);
  M_SDA_SetHigh;                        // Set SDA High
  F_EEDelay(delay_time_val);                         // Delay for EEPROM Write
  M_SDA_SetLow;                         // Clear SDA
  F_EEDelay(delay_time_val);                         // Delay for EEPROM Write
}
//==============================================================================
//This routine will send the I2C Stop Bit
//==============================================================================
void F_I2C_Stop (void)
{
  F_SDA_SetOutput();                    // Set SDA to output
  F_EEDelay(delay_time_val);
  M_SDA_SetLow;                         // Clear SDA
  F_EEDelay(delay_time_val);
  M_SCL_SetLow;                         // Clear SCL
  F_EEDelay(delay_time_val);
  M_SCL_SetHigh;                        // Set SCL High
  F_EEDelay(delay_time_val);
  M_SDA_SetHigh;                        // Set SDA High
  F_EEDelay(delay_time_val);
}
//==============================================================================
//This routine will send the I2C clock pulse
//==============================================================================
void F_I2C_Clock (void)
{
	F_EEDelay(delay_time_val);
  M_SCL_SetHigh;
  F_EEDelay(delay_time_val);
  M_SCL_SetLow;
  F_EEDelay(delay_time_val);
}
//==============================================================================
//This routine will write a byte to the I2C device
//==============================================================================
void F_Write_I2C_Byte(unsigned char byte)
{
  unsigned char i;
  
  F_SDA_SetOutput();                    // Set SDA to output
  M_SCL_SetLow;                         // Clear I2C SCL PIN
  F_EEDelay(delay_time_val);     
  
  for (i = 0; i < 8; i++)               // Loop for our 8 bits
  {  				
    // Set or Clear SDA pin
    if((byte & 0x80) == 0x80)
      M_SDA_SetHigh;                    // Set I2C SDA PIN
    else 
      M_SDA_SetLow;                     // Clear I2C SDA PIN
    
    M_SCL_SetHigh;                      // Set SCL High, Clock data
    F_EEDelay(delay_time_val); 
    byte = byte << 1;                   // Shift data in buffer right one
    M_SCL_SetLow;                       // Clear SCL
    F_EEDelay(delay_time_val);   
  }
	F_I2C_Ackn();
}
//==============================================================================
//This routine will read a byte from the I2C device
//==============================================================================
rt_uint8_t F_Read_I2C_Byte(void)
{	
  unsigned char i,buff = 0,PortData;
  F_SDA_SetInput();  
  
  for(i = 0; i < 8; i++)
  {
    buff = buff << 1;           // Set SDA to input
    M_SCL_SetHigh;              // Set SCL High,Clock bit out
    F_EEDelay(delay_time_val);
    PortData = M_SDA_Read;      // Read data on P_SDA_Pin pin
    if(PortData) 
      buff = buff | 0x01;	
    M_SCL_SetLow;               // Clear SCL
    F_EEDelay(delay_time_val);
  }
	F_I2C_Clock();
  return buff;                  // Return our I2C byte
}

//==============================================================================
//This routine will write the I2C device code,set the device chip select bits, 
//and set or clear the I2C R/W bit	
//==============================================================================
void F_Write_I2C_Control(unsigned char D_Code,unsigned char H_ADD,unsigned char RW)
{
  // Send the I2C device Control code
  M_SCL_SetLow;                                 // Clear SCL clock
  F_EEDelay(delay_time_val);
  
  if((D_Code & 0x08) == 0x08) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  if((D_Code & 0x04) == 0x04) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  if((D_Code & 0x02) == 0x02) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  if((D_Code & 0x01) == 0x01) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  // Send the I2C Control byte chip selects bits 
  
  if((H_ADD & 0x04) == 0x04) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  if((H_ADD & 0x02) == 0x02) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  if((H_ADD & 0x01) == 0x01) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
  
  // Set or Clear the read / write bit for I2C control 
  if(RW) 
    M_SDA_SetHigh;                              // Set I2C SDA PIN
  else 
    M_SDA_SetLow;                               // Clear I2C SDA PIN
  F_I2C_Clock();                                // Clock I2C bit
	F_I2C_Ackn();
}

void EE_WriteData(rt_uint8_t* pBuffer, rt_off_t WriteAddr, rt_size_t NumByteToWrite)
{
		rt_uint8_t i;
		static rt_uint8_t temp;
		F_I2C_Start();
		F_Write_I2C_Control(0x0A,0,0);
		F_Write_I2C_Byte(WriteAddr);
		for(i=0; i<NumByteToWrite ; i++) 
		{
			temp = *(pBuffer + i);
			F_Write_I2C_Byte(temp);
		}
		F_I2C_Stop();
}

void EE_ReadData(rt_uint8_t* pBuffer, rt_off_t ReadAddr, rt_size_t NumByteToRead)
{  
		rt_uint8_t i;
		static rt_uint8_t temp;
		F_I2C_Start();
		F_Write_I2C_Control(0x0A,0,0);
		F_Write_I2C_Byte(ReadAddr);
		F_I2C_Start();
		F_Write_I2C_Control(0x0A,0,1);
		
		for(i=0; i<NumByteToRead ; i++) 
		{
			temp = F_Read_I2C_Byte();
			*(pBuffer + i) = temp;
				/*
			if(i < (NumByteToRead-1))
			{
				F_EEDelay(delay_time_val); 
				M_SCL_SetHigh;
				F_SDA_SetOutput();
				F_EEDelay(delay_time_val); 
				M_SDA_SetHigh; 
				F_EEDelay(delay_time_val); 
				M_SCL_SetLow;
				F_EEDelay(delay_time_val); 
				M_SDA_SetLow;
				// ack
				F_SDA_SetOutput();
				M_SDA_SetLow;
				F_EEDelay(delay_time_val); 
				M_SDA_SetHigh; 
				F_EEDelay(delay_time_val); 
				M_SCL_SetHigh;
				F_EEDelay(delay_time_val); 
				M_SCL_SetLow;
				F_EEDelay(delay_time_val); 
				M_SDA_SetLow;
				//------
				F_EEDelay(delay_time_val); 
				M_SCL_SetHigh;
				F_EEDelay(delay_time_val); 
				M_SDA_SetHigh;
				
			}
			*/
		}
		F_I2C_Stop();
}
