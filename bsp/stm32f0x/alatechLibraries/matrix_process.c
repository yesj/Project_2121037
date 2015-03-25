#include "chandler.h"

const	rt_uint8_t	MatrixAsciiCode[59][6] = 
{
{0x00,0x00,0x00,0x00,0x00,0x00},		//  空格 0x20
{0x00,0x00,0x00,0x00,0x00,0x00},		//  !
{0x00,0x00,0x00,0x00,0x00,0x00},		//  " 
{0x00,0x00,0x00,0x00,0x00,0x00},		//  #
{0x00,0x00,0x00,0x00,0x00,0x00},		//  $
{0x26,0x16,0x08,0x34,0x32,0x00},		//	%
{0x00,0x00,0x00,0x00,0x00,0x00},		//	&
{0x00,0x00,0x00,0x00,0x00,0x00},		//  '
{0x00,0x00,0x00,0x00,0x00,0x00},		//  (
{0x00,0x00,0x00,0x00,0x00,0x00},		//  )
{0x00,0x00,0x00,0x00,0x00,0x00},		//  *
{0x00,0x00,0x00,0x00,0x00,0x00},		//  +
{0x00,0x00,0x00,0x00,0x00,0x00},		//  ,  
{0x08,0x08,0x08,0x08,0x08,0x00},		//  -
{0x60,0x60,0x00,0x00,0x00,0x00},		//  .   
{0x20,0x10,0x08,0x04,0x02,0x00},		//  /
{0x3E,0x51,0x49,0x45,0x3E,0x00},		//	0
{0x00,0x42,0x7F,0x40,0x00,0x00},		//	1
{0x42,0x61,0x51,0x49,0x46,0x00},		//	2
{0x22,0x41,0x49,0x49,0x36,0x00},		//	3
{0x18,0x14,0x12,0x7F,0x10,0x00},		//	4
{0x27,0x45,0x45,0x45,0x39,0x00},		//	5
{0x3E,0x49,0x49,0x49,0x32,0x00},		//	6
{0x03,0x01,0x71,0x09,0x07,0x00},		//	7
{0x36,0x49,0x49,0x49,0x36,0x00},		//	8
{0x26,0x49,0x49,0x49,0x3E,0x00},		//	9
{0x00,0x00,0x00,0x00,0x00,0x00},		//	:
{0x00,0x00,0x00,0x00,0x00,0x00},		//	;
{0x00,0x00,0x00,0x00,0x00,0x00},		//  <
{0x00,0x00,0x00,0x00,0x00,0x00},		//	=
{0x00,0x00,0x00,0x00,0x00,0x00},		//  >
{0x00,0x00,0x00,0x00,0x00,0x00},		//	?
{0x00,0x00,0x00,0x00,0x00,0x00},		//	@
{0x7E,0x09,0x09,0x09,0x7E,0x00},		//	A
{0x7F,0x49,0x49,0x49,0x36,0x00},		//	B
{0x3E,0x41,0x41,0x41,0x22,0x00},		//	C
{0x7F,0x41,0x41,0x22,0x1C,0x00},		//	D
{0x7F,0x49,0x49,0x49,0x41,0x00},		//	E
{0x7F,0x09,0x09,0x09,0x01,0x00},		//	F
{0x3E,0x41,0x49,0x49,0x7A,0x00},		//	G
{0x7F,0x08,0x08,0x08,0x7F,0x00},		//	H
{0x41,0x41,0x7F,0x41,0x41,0x00},		//	I
{0x20,0x40,0x41,0x3F,0x01,0x00},		//	J
{0x7F,0x08,0x14,0x22,0x41,0x00},		//	K
{0x7F,0x40,0x40,0x40,0x40,0x00},		//	L
{0x7F,0x02,0x0C,0x02,0x7F,0x00},		//	M
{0x7F,0x04,0x08,0x10,0x7F,0x00},		//	N
{0x3E,0x41,0x41,0x41,0x3E,0x00},		//	O
{0x7F,0x09,0x09,0x09,0x06,0x00},		//	P
{0x3E,0x41,0x51,0x21,0x5E,0x00},		//	Q
{0x7F,0x09,0x19,0x29,0x46,0x00},		//	R
{0x26,0x49,0x49,0x49,0x32,0x00},		//	S
{0x01,0x01,0x7F,0x01,0x01,0x00},		//	T
{0x3F,0x40,0x40,0x40,0x3F,0x00},		//	U
{0x1F,0x20,0x40,0x20,0x1F,0x00},		//	V
{0x7F,0x20,0x1C,0x20,0x7F,0x00},		//	W
{0x63,0x14,0x08,0x14,0x63,0x00},		//	X
{0x03,0x04,0x78,0x04,0x03,0x00},		//	Y
{0x61,0x51,0x49,0x45,0x43,0x00},		//	Z
};

/*
//
const unsigned char MatrixAsciiCode[60][6]={
  {0x00,0x00,0x00,0x00,0x00,0X00},			//  空格 0x20
  {0x00,0x00,0x00,0x00,0x00,0X00},      // !
  {0x00,0x00,0x00,0x00,0x00,0X00},      // "
  {0x00,0x00,0x00,0x00,0x00,0X00},      // #
  {0x00,0x00,0x00,0x00,0x00,0X00},      // $
  {0x44,0x24,0x10,0x48,0x44,0X00},              // %
  {0x00,0x00,0x00,0x00,0x00,0X00},      // &
  {0x00,0x00,0x00,0x00,0x00,0X00},      // '
  {0x00,0x00,0x00,0x00,0x00,0X00},      // (
  {0x00,0x00,0x00,0x00,0x00,0X00},      // )
  {0x00,0x00,0x00,0x00,0x00,0X00},      // *
  {0x08,0x08,0x3E,0x08,0x08,0X00},              // +
  {0x00,0x00,0x00,0x00,0x00,0X00},      // ,
  {0x08,0x08,0x08,0x08,0x08,0X00},              // -
  {0x40,0x00,0x00,0x00,0x00,0X00},              // .
  {0x00,0x00,0x00,0x00,0x00,0X00},      // /
  {0x7F,0x41,0x41,0x41,0x7F,0X00},              // 0
  {0x44,0x42,0x7F,0x40,0x40,0X00},              // 1        
  {0x79,0x49,0x49,0x49,0x4F,0X00},              // 2
  {0x41,0x49,0x49,0x49,0x7F,0X00},              // 3
  {0x0F,0x08,0x08,0x08,0x7F,0X00},              // 4
  {0x4F,0x49,0x49,0x49,0x79,0X00},              // 5
  {0x7F,0x49,0x49,0x49,0x79,0X00},              // 6
  {0x01,0x01,0x01,0x01,0x7F,0X00},              // 7
  {0x7F,0x49,0x49,0x49,0x7F,0X00},              // 8
  {0x4F,0x49,0x49,0x49,0x7F,0X00},              // 9
  {0x14,0x00,0x00,0x00,0x00,0X00},              // :
  {0x00,0x00,0x00,0x00,0x00,0X00},      // ;
  {0x00,0x00,0x00,0x00,0x00,0X00},      // <
  {0x00,0x00,0x00,0x00,0x00,0X00},      // =
  {0x00,0x00,0x00,0x00,0x00,0X00},      // >
  {0x00,0x00,0x00,0x00,0x00,0X00},      // ?
  {0x00,0x00,0x00,0x00,0x00,0X00},      // @
  {0x7E,0x11,0x11,0x11,0x7E,0X00},              // A
  {0x7F,0x49,0x49,0x49,0x36,0X00},              // B
  {0x3E,0x41,0x41,0x41,0x22,0X00},              // C
  {0x7F,0x41,0x41,0x41,0x3E,0X00},              // D
  {0x7F,0x49,0x49,0x49,0x41,0X00},              // E
  {0x7F,0x09,0x09,0x09,0x01,0X00},              // F
  {0x3E,0x41,0x41,0x51,0x32,0X00},              // G
  {0x7F,0x08,0x08,0x08,0x7F,0X00},              // H
  {0x41,0x41,0x7F,0x41,0x41,0X00},              // I
  {0x23,0x41,0x41,0x41,0x3F,0X00},              // J
  {0x7F,0x08,0x14,0x22,0x41,0X00},              // K
  {0x7F,0x40,0x40,0x40,0x40,0X00},              // L
  {0x7F,0x02,0x0C,0x02,0x7F,0X00},              // M
  {0x7F,0x04,0x08,0x10,0x7F,0X00},              // N
  {0x3E,0x41,0x41,0x41,0x3E,0X00},              // O
  {0x7F,0x11,0x11,0x11,0x0E,0X00},              // P
  {0x3E,0x41,0x51,0x21,0x5E,0X00},              // Q
  {0x7F,0x09,0x19,0x29,0x46,0X00},              // R
  {0x26,0x49,0x49,0x49,0x32,0X00},              // S
  {0x01,0x01,0x7F,0x01,0x01,0X00},              // T
  {0x3F,0x40,0x40,0x40,0x3F,0X00},              // U
  {0x7F,0x20,0x10,0x08,0x07,0X00},              // V
  {0x7F,0x20,0x18,0x20,0x7F,0X00},              // W
  {0x63,0x14,0x08,0x14,0x63,0X00},              // X
  {0x07,0x08,0x70,0x08,0x07,0X00},              // Y
  {0x63,0x51,0x49,0x45,0x63,0X00},              // Z
};
*/
#define D_COM01		0x00000001
#define D_COM02		0x00000002
#define D_COM03		0x00000004
#define D_COM04		0x00000008
#define D_COM05		0x00000010
#define D_COM06		0x00000020
#define D_COM07		0x00000040
#define D_COM08		0x00000080
#define D_COM09		0x00000100
#define D_COM10		0x00000200
#define D_COM11		0x00000400
#define D_COM12		0x00000800
#define D_COM13		0x00001000
#define D_COM14		0x00002000
#define D_COM15		0x00004000
#define D_COM16		0x00008000
#define D_COM17		0x00010000
#define D_COM18		0x00020000
#define D_COM19		0x00040000
#define D_COM20		0x00080000
#define D_COM21		0x00100000
#define D_COM22		0x00200000
#define D_COM23		0x00400000
#define D_COM24		0x00800000
#define D_COM25		0x01000000
#define D_COM26		0x02000000
#define D_COM27		0x04000000
#define D_COM28		0x08000000
#define D_COM29		0x10000000
#define D_COM30		0x20000000
#define D_COM31		0x40000000
#define D_COM32		0x80000000

#define	r_Seg00		0
#define	r_Seg01		1
#define	r_Seg02		2
#define	r_Seg03		3
#define	r_Seg04		4
#define	r_Seg05		5
#define	r_Seg06		6
#define	r_Seg07		7
#define	r_Seg08		8
#define	r_Seg09		9
#define	r_Seg10		10
#define	r_Seg11		11
#define	r_Seg12		12
#define	r_Seg13		13
#define	r_Seg14		14
#define	r_Seg15		15
#define	r_Seg16		16
#define	r_Seg17		17
#define	r_Seg18		18
#define	r_Seg19		19
#define	r_Seg20		20
#define	r_Seg21		21
#define	r_Seg22		22
#define	r_Seg23		23
#define	r_Seg24		24

#define	r_Seg25		25
#define	r_Seg26		26
#define	r_Seg27		27
#define	r_Seg28		28
#define	r_Seg29		29
#define	r_Seg30		30
#define	r_Seg31		31
#define	r_Seg32		32
#define	r_Seg33		33
#define	r_Seg34		34
#define	r_Seg35		35
#define	r_Seg36		36
#define	r_Seg37		37
#define	r_Seg38		38
#define	r_Seg39		39
#define	r_Seg40		40
#define	r_Seg41		41
#define	r_Seg42		42
#define	r_Seg43		43
#define	r_Seg44		44
#define	r_Seg45		45
#define	r_Seg46		46
#define	r_Seg47		47
#define	r_Seg48		48
#define	r_Seg49		49
#define	r_Seg50		50
#define	r_Seg51		51
#define	r_Seg52		52
#define	r_Seg53		53
#define	r_Seg54		54
#define	r_Seg55		55
#define	r_Seg56		56
#define	r_Seg57		57
#define	r_Seg58		58
#define	r_Seg59		59
#define	r_Seg60		60
#define	r_Seg61		61
#define	r_Seg62		62
#define	r_Seg63		63
/*
const rt_uint32_t LcdBit[]={
D_COM01,D_COM02,D_COM03,D_COM04,D_COM05,D_COM06,D_COM07,D_COM08,
D_COM09,D_COM10,D_COM11,D_COM12,D_COM13,D_COM14,D_COM15,D_COM16,
D_COM17,D_COM18,D_COM19,D_COM20,D_COM21,D_COM22,D_COM23,D_COM24,
D_COM25,D_COM26,D_COM27,D_COM28,D_COM29,D_COM30,D_COM31,D_COM32
};
*/
const rt_uint32_t LcdBit[]={
D_COM32,D_COM31,D_COM30,D_COM29,D_COM28,D_COM27,D_COM26,D_COM25,
D_COM24,D_COM23,D_COM22,D_COM21,D_COM20,D_COM19,D_COM18,D_COM17,
D_COM16,D_COM15,D_COM14,D_COM01,D_COM02,D_COM03,D_COM04,D_COM05,
D_COM06,D_COM07,D_COM08,D_COM09,D_COM10,D_COM11,D_COM12,D_COM13
};

const rt_uint8_t LcdRam[]={         
r_Seg61,r_Seg02,r_Seg60,r_Seg03,r_Seg59,r_Seg04,r_Seg58,r_Seg05,
r_Seg57,r_Seg06,r_Seg56,r_Seg07,r_Seg55,r_Seg08,r_Seg54,r_Seg09,
r_Seg53,r_Seg10,r_Seg52,r_Seg11,r_Seg51,r_Seg12,r_Seg50,r_Seg13,
r_Seg49,r_Seg14,r_Seg48,r_Seg15,r_Seg47,r_Seg16,r_Seg46,r_Seg17,
r_Seg45,r_Seg18,r_Seg44,r_Seg19,r_Seg43,r_Seg20,r_Seg42,r_Seg21,
r_Seg41,r_Seg22,r_Seg40,r_Seg23,r_Seg39,r_Seg24,r_Seg38,r_Seg25,
r_Seg37,r_Seg26,r_Seg36,r_Seg27,r_Seg35,r_Seg28,r_Seg34,r_Seg29,
r_Seg33,r_Seg30,r_Seg32,r_Seg31
};

//==============================================================================
// ASCII 
//==============================================================================
rt_uint8_t	F_ASCII(rt_uint8_t	data)
{
  rt_uint8_t	k;
  switch(data)
  {
    case	0:	k=0x30;		break;
    case	1:	k=0x31;		break;
    case	2:	k=0x32;		break;
    case	3:	k=0x33;		break;
    case	4:	k=0x34;		break;
    case	5:	k=0x35;		break;
    case	6:	k=0x36;		break;
    case	7:	k=0x37;		break;
    case	8:	k=0x38;		break;
    case	9:	k=0x39;		break;
    case	10:	k=0x41;		break;
    case	11:	k=0x42;		break;
    case	12:	k=0x43;		break;
    case	13:	k=0x44;		break;
    case	14:	k=0x45;		break;
    case	15:	k=0x46;		break;
  default :	        k=0x00;		break;
  }	
  return k;
}
//==============================================================================
rt_uint8_t  F_ASCII_Change_Byte(rt_uint8_t		data)
{
  rt_uint8_t		k;
  switch(data)
  {
    case	0x30:	k=0;		break;
    case	0x31:	k=1;		break;
    case	0x32:	k=2;		break;
    case	0x33:	k=3;		break;
    case	0x34:	k=4;		break;
    case	0x35:	k=5;		break;
    case	0x36:	k=6;		break;
    case	0x37:	k=7;		break;
    case	0x38:	k=8;		break;
    case	0x39:	k=9;		break;
  default :		k=255;	break;
  }	
  return k;
}

//==============================================================
void  F_ShowMatrixLcd(rt_uint8_t	lcdRamAdr,rt_uint32_t data,rt_uint8_t dataLongSize,rt_uint32_t *displayAdr)
{		
		rt_uint8_t	lcdBitAdr,lcdRamAdrTemp;
		rt_uint32_t	dataTemp,k,lcdBitAdrTemp;
	
		lcdRamAdrTemp = LcdRam[lcdRamAdr];
	
		dataTemp = *(displayAdr + lcdRamAdrTemp);
	
    for(lcdBitAdr = 0;lcdBitAdr <dataLongSize ;lcdBitAdr++)
    {
      lcdBitAdrTemp = LcdBit[lcdBitAdr];
      k = data & 0x00000001;
      if(k) 
			{
        dataTemp = dataTemp | lcdBitAdrTemp;
      }
      data = data >> 1;
    }
		*(displayAdr+lcdRamAdrTemp) = dataTemp;
}
//===============================================================
// 矩陣點黑
void F_ShowMatrixLcdChossDot(rt_coordinate_t	adr,rt_uint8_t x_long,rt_uint8_t y_long,rt_uint32_t *displayAdr)
{
		rt_uint8_t	lcdBitAdr,lcdRamAdrTemp;
		rt_uint32_t	dataTemp,lcdBitAdrTemp;
		rt_uint8_t	i;
		for(i = 0;i < x_long;i++) {
			
			lcdRamAdrTemp = LcdRam[adr.x];
			adr.x++;
			dataTemp = *(displayAdr + lcdRamAdrTemp);
		
			for(lcdBitAdr = adr.y;lcdBitAdr < (adr.y+y_long) ;lcdBitAdr++)
			{
				lcdBitAdrTemp = LcdBit[lcdBitAdr];
				dataTemp = dataTemp | lcdBitAdrTemp;
			}
			*(displayAdr+lcdRamAdrTemp) = dataTemp;
		}
}

void F_ShowMatrixLcdChossReverse(rt_coordinate_t	adr,rt_uint8_t x_long,rt_uint8_t y_long,rt_uint32_t data,rt_uint32_t *displayAdr)
{
		rt_uint8_t	lcdBitAdr,lcdRamAdrTemp;
		rt_uint32_t	dataTemp,lcdBitAdrTemp,k,dataBuf;
		rt_uint8_t	i;
		for(i = 0;i < x_long;i++) {
			
			lcdRamAdrTemp = LcdRam[adr.x];
			adr.x++;
			dataTemp = *(displayAdr + lcdRamAdrTemp);
			dataBuf = data;
			for(lcdBitAdr = adr.y;lcdBitAdr < (adr.y+y_long) ;lcdBitAdr++)
			{
				lcdBitAdrTemp = LcdBit[lcdBitAdr];
				k = dataBuf & 0x00000001;
				if(k) 
				{
					dataTemp = dataTemp | lcdBitAdrTemp;
				} else {
					dataTemp = dataTemp & ~lcdBitAdrTemp;
				}
				dataBuf = dataBuf >> 1;
			}
			*(displayAdr+lcdRamAdrTemp) = dataTemp;
		}
}
//==============================================================
//
//==============================================================
static void	F_ShowMatrixFontChange(rt_coordinate_t adr,rt_uint32_t data,rt_uint32_t *displayAdr)
{
		rt_uint8_t	lcdBitAdr,lcdRamAdrTemp;
		rt_uint32_t	dataTemp,k,lcdBitAdrTemp;

		lcdRamAdrTemp = LcdRam[adr.x];
		
		//if(lcdRamAdrTemp>r_Seg63) {
		//	lcdRamAdrTemp=r_Seg63;		//保護 displayAdr 位址 溢位
		//}
	
		dataTemp = *(displayAdr + lcdRamAdrTemp);
    for(lcdBitAdr = adr.y;lcdBitAdr < (adr.y+7) ;lcdBitAdr++)
    {
				lcdBitAdrTemp = LcdBit[lcdBitAdr];
				k = data & 0x40;
				if(k) 
				{
					dataTemp = dataTemp | lcdBitAdrTemp;
				} else {
					//dataTemp = dataTemp & ~lcdBitAdrTemp;
				}
				data = data << 1;
    }	
		*(displayAdr+lcdRamAdrTemp) = dataTemp;		
}

void  F_ShowMatrixFontLcd(rt_coordinate_t adr,rt_uint8_t asciiNum,rt_uint32_t *displayAdr)
{		
	rt_uint8_t	i,Temp;
	
	asciiNum = asciiNum - ' ';
	Temp = adr.x;
	for(i=0 ; i<6 ; i++) {
		adr.x = Temp + i;
		F_ShowMatrixFontChange(adr,MatrixAsciiCode[asciiNum][i],displayAdr);
	}
}

//=======================================================================================
// 以下功能與上面的功能類似
// 矩陣字型驅動(反向)
static void	F_ShowMatrixFontChangeReverse(rt_coordinate_t adr,rt_uint32_t data,rt_uint32_t *displayAdr)
{
		rt_uint8_t	lcdBitAdr,lcdRamAdrTemp;
		rt_uint32_t	dataTemp,k,lcdBitAdrTemp;

		lcdRamAdrTemp = LcdRam[adr.x];
		
		//if(lcdRamAdrTemp>r_Seg63) {
		//	lcdRamAdrTemp=r_Seg63;		//保護 displayAdr 位址 溢位
		//}
	
		dataTemp = *(displayAdr + lcdRamAdrTemp);
    for(lcdBitAdr = adr.y;lcdBitAdr < (adr.y+7) ;lcdBitAdr++)
    {
				lcdBitAdrTemp = LcdBit[lcdBitAdr];
				k = data & 0x40;
				if(k == 0) 
				{
					dataTemp = dataTemp & ~lcdBitAdrTemp;
				}
				data = data << 1;
    }	
		*(displayAdr+lcdRamAdrTemp) = dataTemp;		
}
// 選擇矩陣字型(反向)
void  F_ShowMatrixFontLcdReverse(rt_coordinate_t adr,rt_uint8_t asciiNum,rt_uint32_t *displayAdr)
{		
	rt_uint8_t	i,Temp;
	
	asciiNum = asciiNum - ' ';
	Temp = adr.x;
	for(i=0 ; i<6 ; i++) {
		adr.x = Temp + i;
		F_ShowMatrixFontChangeReverse(adr,~(MatrixAsciiCode[asciiNum][i]),displayAdr);
	}
}
// 輸入座標及字型(反向)
#define Font_sizeVal		6
void  F_ShowMatrixStringLcdReverse(rt_coordinate_t adr,const rt_uint8_t *asciiString,rt_uint8_t stringSize,rt_uint32_t *displayAdr)
{	
	rt_uint8_t	i;
	rt_uint8_t	Temp,stringSizeTemp;
	rt_coordinate_t coordinateTemp;

	coordinateTemp.x = adr.x-1;
	coordinateTemp.y = adr.y-1;
	
	Temp = adr.x;
	stringSizeTemp = stringSize-1;
	
	F_ShowMatrixLcdChossDot(coordinateTemp,(stringSizeTemp *Font_sizeVal)+1,9,LCDBuffer);
	
	for(i=0 ; i< stringSizeTemp ; i++)
	{
		adr.x = Temp+(Font_sizeVal * i);
		F_ShowMatrixFontLcdReverse(adr , *(asciiString+i) , displayAdr);
	}
}

void  F_ShowMatrixNumProcessReverse(rt_coordinate_t	adr3,rt_coordinate_t	adr2,rt_coordinate_t	adr1,rt_bool_t ShowHiByeFlg,rt_uint16_t data,rt_uint32_t *displayAdr)
{
    rt_uint8_t a,b,c;
		rt_coordinate_t coordinateTemp;
    a=data/100;
    b=(data%100)/10;
    c=data%10;

      if(adr3.x != blankVal)
      {
        if(data>99) {
					coordinateTemp.x = adr3.x-1;
					coordinateTemp.y = adr3.y-1;
					F_ShowMatrixLcdChossDot(coordinateTemp,Font_sizeVal+1,9,LCDBuffer);
          F_ShowMatrixFontLcdReverse(adr3,F_ASCII(a),displayAdr);
				}
      }
	//=============
        if(ShowHiByeFlg==1) {
					coordinateTemp.x = adr2.x-1;
					coordinateTemp.y = adr2.y-1;
					F_ShowMatrixLcdChossDot(coordinateTemp,Font_sizeVal+1,9,LCDBuffer);
          F_ShowMatrixFontLcdReverse(adr2,F_ASCII(b),displayAdr);
				}
          else
          {  
            if(data>9) {
							coordinateTemp.x = adr2.x-1;
							coordinateTemp.y = adr2.y-1;
							F_ShowMatrixLcdChossDot(coordinateTemp,Font_sizeVal+1,9,LCDBuffer);
              F_ShowMatrixFontLcdReverse(adr2,F_ASCII(b),displayAdr);
						}
          }
	//=============			
		coordinateTemp.x = adr1.x-1;
		coordinateTemp.y = adr1.y-1;
		F_ShowMatrixLcdChossDot(coordinateTemp,Font_sizeVal+1,9,LCDBuffer);
		F_ShowMatrixFontLcdReverse(adr1,F_ASCII(c),displayAdr);
}

void  F_ShowMatrixNumProcess(rt_coordinate_t	adr3,rt_coordinate_t	adr2,rt_coordinate_t	adr1,rt_bool_t ShowHiByeFlg,rt_uint16_t data,rt_uint32_t *displayAdr)
{
    rt_uint8_t a,b,c;
	
    a=data/100;
    b=(data%100)/10;
    c=data%10;
      if(adr3.x != blankVal)
      {
        if(data>99)
          F_ShowMatrixFontLcd(adr3,F_ASCII(a),displayAdr);
      }
	//=============
        if(ShowHiByeFlg==1)
          F_ShowMatrixFontLcd(adr2,F_ASCII(b),displayAdr);
          else
          {  
            if(data>9)
              F_ShowMatrixFontLcd(adr2,F_ASCII(b),displayAdr);
          }
	//=============			
		F_ShowMatrixFontLcd(adr1,F_ASCII(c),displayAdr);
}

void  F_ShowMatrixStringLcd(rt_coordinate_t adr,const rt_uint8_t *asciiString,rt_uint8_t stringSize,rt_uint32_t *displayAdr)
{	
	rt_uint8_t	i;
	rt_uint8_t	Temp;
	Temp = adr.x;
	for(i=0 ; i< (stringSize-1) ; i++)
	{
		adr.x = Temp+(Font_sizeVal * i);
		F_ShowMatrixFontLcd(adr , *(asciiString+i) , displayAdr);
	}
}
//==============================================================
//
//==============================================================
const	rt_uint16_t	MatrixBigNumCode[][8] = 
{																																										
{0x03F0,0x0FFC,0x1C0E,0x1002,0x1002,0x1C0E,0x0FFC,0x03F0},		//	0
{0x0000,0x0002,0x0802,0x1FFE,0x1FFE,0x0002,0x0002,0x0000},		// 	1
{0x0C06,0x1C0E,0x101A,0x1032,0x1062,0x18C2,0x0F86,0x0706},		//	2
{0x0004,0x0806,0x1882,0x1082,0x1182,0x1FC6,0x0E7C,0x0038},		//	3
{0x0030,0x00F0,0x03D0,0x0F10,0x1FFE,0x1FFE,0x0010,0x0010},		//	4
{0x0004,0x1F06,0x1F02,0x1102,0x1102,0x1186,0x10FC,0x1078},		//	5
{0x03F8,0x07FC,0x0D86,0x1902,0x1102,0x1186,0x10FC,0x0078},		//	6
{0x1C00,0x1C00,0x1000,0x100E,0x107E,0x13F0,0x1F80,0x1C00},		//  7
{0x0638,0x0F7C,0x18C2,0x1082,0x1082,0x19C6,0x0F7C,0x0638},		//  8
{0x0780,0x0FC2,0x1862,0x1022,0x1026,0x184C,0x0FF8,0x07F0}			//  9
};

static void	F_ShowMatrixBigNumFontChange(rt_coordinate_t adr,rt_uint16_t data,rt_uint32_t *displayAdr)
{
		rt_uint8_t	lcdBitAdr,lcdRamAdrTemp;
		rt_uint32_t	dataTemp,k,lcdBitAdrTemp;

		lcdRamAdrTemp = LcdRam[adr.x];
	
		dataTemp = *(displayAdr + lcdRamAdrTemp);
    for(lcdBitAdr = adr.y;lcdBitAdr < (adr.y+12) ;lcdBitAdr++)
    {
				lcdBitAdrTemp = LcdBit[lcdBitAdr];
				k = data & 0x0002;
				if(k) 
				{
					dataTemp = dataTemp | lcdBitAdrTemp;
				}
				data = data >> 1;
    }	
		*(displayAdr+lcdRamAdrTemp) = dataTemp;		
}

void  F_ShowMatrixBigNumFontLcd(rt_coordinate_t adr,rt_uint8_t asciiNum,rt_uint32_t *displayAdr)
{		
	rt_uint8_t	i;
	rt_uint8_t	Temp;
	Temp = adr.x;
	for(i=0 ; i<8 ; i++) {
		adr.x = Temp + i;
		F_ShowMatrixBigNumFontChange(adr, MatrixBigNumCode[asciiNum][i] , displayAdr);
	}
}

void  F_ShowMatrixBigNumProcess(rt_coordinate_t	adr3,rt_coordinate_t	adr2,rt_coordinate_t	adr1,rt_bool_t ShowHiByeFlg,rt_uint16_t data,rt_uint32_t *displayAdr)
{
    rt_uint8_t a,b,c;
	
    a=data/100;
    b=(data%100)/10;
    c=data%10;
      if(adr3.x != blankVal)
      {
        if(data>99)
          F_ShowMatrixBigNumFontLcd(adr3,a,displayAdr);
      }
	//=============
        if(ShowHiByeFlg==1)
          F_ShowMatrixBigNumFontLcd(adr2,b,displayAdr);
          else
          {  
            if(data>9)
              F_ShowMatrixBigNumFontLcd(adr2,b,displayAdr);
          }
	//=============			
		F_ShowMatrixBigNumFontLcd(adr1,c,displayAdr);
}
//==========================================================
static void	F_ShowMatrixBigNumFontChangeReverse(rt_coordinate_t adr,rt_uint16_t data,rt_uint32_t *displayAdr)
{
		rt_uint8_t	lcdBitAdr,lcdRamAdrTemp;
		rt_uint32_t	dataTemp,k,lcdBitAdrTemp;

		lcdRamAdrTemp = LcdRam[adr.x];
	
		dataTemp = *(displayAdr + lcdRamAdrTemp);
    for(lcdBitAdr = adr.y;lcdBitAdr < (adr.y+12) ;lcdBitAdr++)
    {
				lcdBitAdrTemp = LcdBit[lcdBitAdr];
				k = data & 0x0002;
				if(k == 0) 
				{
					dataTemp = dataTemp & ~lcdBitAdrTemp;
				}
				data = data >> 1;
    }
		*(displayAdr+lcdRamAdrTemp) = dataTemp;		
}

void  F_ShowMatrixBigNumFontLcdReverse(rt_coordinate_t adr,rt_uint8_t asciiNum,rt_uint32_t *displayAdr)
{
	rt_uint8_t	i;
	rt_uint8_t	Temp;
	Temp = adr.x;
	for(i=0 ; i<8 ; i++) {
		adr.x = Temp + i;
		F_ShowMatrixBigNumFontChangeReverse(adr, ~(MatrixBigNumCode[asciiNum][i]) , displayAdr);
	}
}

void  F_ShowMatrixBigNumProcessReverse(rt_coordinate_t	adr3,rt_coordinate_t	adr2,rt_coordinate_t	adr1,rt_bool_t ShowHiByeFlg,rt_uint16_t data,rt_uint32_t *displayAdr)
{
    rt_uint8_t a,b,c;
		rt_coordinate_t coordinateTemp;
    a=data/100;
    b=(data%100)/10;
    c=data%10;
      if(adr3.x != blankVal)
      {
        if(data>99) {
					coordinateTemp.x = adr3.x-1;
					coordinateTemp.y = adr3.y-1;
					F_ShowMatrixLcdChossDot(coordinateTemp,10,14,LCDBuffer);
          F_ShowMatrixBigNumFontLcdReverse(adr3,a,displayAdr);
				}
      }
	//=============
        if(ShowHiByeFlg==1) {
					coordinateTemp.x = adr2.x-1;
					coordinateTemp.y = adr2.y-1;
					F_ShowMatrixLcdChossDot(coordinateTemp,10,14,LCDBuffer);
          F_ShowMatrixBigNumFontLcdReverse(adr2,b,displayAdr);
				}
          else
          {  
            if(data>9) {
							coordinateTemp.x = adr2.x-1;
							coordinateTemp.y = adr2.y-1;
							F_ShowMatrixLcdChossDot(coordinateTemp,10,14,LCDBuffer);
              F_ShowMatrixBigNumFontLcdReverse(adr2,b,displayAdr);
						}
          }
	//=============
		coordinateTemp.x = adr1.x-1;
		coordinateTemp.y = adr1.y-1;
		F_ShowMatrixLcdChossDot(coordinateTemp,10,14,LCDBuffer);
		F_ShowMatrixBigNumFontLcdReverse(adr1,c,displayAdr);
}
