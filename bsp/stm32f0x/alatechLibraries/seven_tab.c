#include "chandler.h"

#define	r_Seg00		0
#define	r_Seg01		1
#define	r_Seg63		63
#define	r_Seg62		62


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

const rt_uint8_t SevenLcdRam[]={         
r_Seg00,r_Seg01,r_Seg63,r_Seg62,
r_Seg00,r_Seg01,r_Seg63,r_Seg62,
r_Seg00,r_Seg01,r_Seg63,r_Seg62
};

const rt_uint32_t SevenLcdBit_00[]={         
D_COM06,D_COM07,D_COM10,D_COM12,
D_COM11,D_COM08,D_COM09
};

const rt_uint32_t SevenLcdBit_01[]={         
D_COM17,D_COM16,D_COM01,D_COM03,
D_COM02,D_COM15,D_COM14
};

const rt_uint32_t SevenLcdBit_02[]={         
D_COM26,D_COM25,D_COM22,D_COM20,
D_COM21,D_COM24,D_COM23
};

//=================================================================
//
//=================================================================
#define   d_a1	0x08
#define   d_b1	0x04
#define   d_c1	0x02
#define   d_d1	0x01
#define   d_e1	0x20
#define   d_f1	0x10
#define   d_g1	0x40

const rt_uint8_t	NunberCode_0[]={
    d_a1+d_b1+d_c1+d_d1+d_e1+d_f1,        //  0
    d_b1+d_c1,                            //  1
    d_a1+d_b1+d_d1+d_e1+d_g1,             //  2
    d_a1+d_b1+d_c1+d_d1+d_g1,             //  3
    d_b1+d_c1+d_f1+d_g1,                  //  4
    d_a1+d_c1+d_d1+d_f1+d_g1,             //  5
    d_a1+d_c1+d_d1+d_e1+d_f1+d_g1,        //  6
    d_a1+d_b1+d_c1,                       //  7
    d_a1+d_b1+d_c1+d_d1+d_e1+d_f1+d_g1,   //  8
    d_a1+d_b1+d_c1+d_d1+d_f1+d_g1,        //  9
    d_a1+d_b1+d_c1+d_e1+d_f1+d_g1,        //  a
    d_c1+d_d1+d_e1+d_f1+d_g1,             //  b
    d_a1+d_d1+d_e1+d_f1,                  //  c
    d_b1+d_c1+d_d1+d_e1+d_g1,             //  d
    d_a1+d_e1+d_d1+d_f1+d_g1,             //  e
    d_a1+d_e1+d_f1+d_g1,                  //  f
};
//===============================
void  F_Show_8_LcdDot(rt_uint8_t	lcdRamAdr,rt_uint8_t dataDot,rt_uint32_t *displayAdr)
{		
	rt_uint8_t	i,k,lcdRamAdrTemp;
	rt_uint32_t	lcdBitAdrTemp;
	rt_uint32_t	dataTemp;
	
	lcdRamAdrTemp = SevenLcdRam[lcdRamAdr];

	dataTemp = *(displayAdr + lcdRamAdrTemp);
	
		for(i=0;i<7;i++)
		{
			switch(lcdRamAdr)
			{
				case 0:
				case 1:
				case 2:
				case 3:
					lcdBitAdrTemp = SevenLcdBit_00[i];
					break;
				case 4:
				case 5:
				case 6:
				case 7:
					lcdBitAdrTemp = SevenLcdBit_01[i];
					break;
				case 8:
				case 9:
				case 10:
				case 11:
					lcdBitAdrTemp = SevenLcdBit_02[i];
					break;
			}
      k = dataDot & 0x01;
      if(k) 
			{
        dataTemp = dataTemp | lcdBitAdrTemp;
      }
      dataDot = dataDot >> 1;
		}
	
	*(displayAdr+lcdRamAdrTemp) = dataTemp;
}
void	F_Show_8_FontLcd(rt_uint8_t	adr,rt_uint8_t	dataNum,rt_uint32_t *displayAdr)
{
	dataNum = dataNum & 0x0F;
	F_Show_8_LcdDot(adr,NunberCode_0[dataNum],displayAdr);
}

void  F_Show_8_Lcd(rt_uint8_t	adr3,rt_uint8_t	adr2,rt_uint8_t	adr1,rt_bool_t ShowHiByeFlg,rt_uint16_t data,rt_uint32_t *displayAdr)
{
    rt_uint8_t a,b,c;
		if(data>999) {
			data = 999;
		}
    a=data/100;
    b=(data%100)/10;
    c=data%10;
      if(adr3!=blankVal)
      {
        if(data>99)
          F_Show_8_FontLcd(adr3,a,displayAdr);
      }
	//=============
        if(ShowHiByeFlg==ShowHiByeVal)
          F_Show_8_FontLcd(adr2,b,displayAdr);
          else
          {  
            if(data>9)
              F_Show_8_FontLcd(adr2,b,displayAdr);
          }
	//=============			
    F_Show_8_FontLcd(adr1,c,displayAdr);
}




