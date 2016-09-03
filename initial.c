
//#include	".\head\CPU32.h"
#include	"define.h"
#include	"global.h"

void	InitSys(void)
{
	//P0SS	=	Bin(00000000);		//关闭P0、P1共享
	//P1SS	=	Bin(00000000);
 	CLKCON=0X00; 

	P0CR	=	Bin(00000001);		//
	P0PCR	=	Bin(10000001);
	P0		=	Bin(00000000);

	P1CR	=	Bin(00000001);		//
	P1PCR	=	Bin(11000001);
	P1		=	Bin(00000000);
			  
	P2CR	=	Bin(01110110);		//P2.1 p2.2输出PWM，P2.4 p2.5输出NPWM
	P2PCR	=	Bin(11111111);
	P2		=	Bin(00000000);
 
 	P3CR 	= 	Bin(00110100);		//P3.4～P3.7
	P3PCR	= 	Bin(11111101);
	P3	 	= 	Bin(00000000);





//	//Priority
//									//			 Bit7	Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0 
	IPH0	=0X00;// Bin(00001000);		//IEN0		 N/A 	EADC  ET2   ES    ET1   EX1   ET0   EX0 
	IPL0	= 0X00;//Bin(00001000);		//			 00		00	  00	00	  00	00	  00	00
	IPH1	=0X00;// Bin(00100000);		//IEN1	  	 EFCOF  EI2C  EPWM  ESCM  EHSEC ES1   EX2   ESPI 
	IPL1	=0X00;// Bin(00100000);		//			 00		00	  11	00	  00	00	  00	00
//
//	//	 		 Bit7	Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0 
////	IEN0		 EA 	EADC  ET2   ES0   ET1   EX1   ET0   EX0 
//	//IEN1	  	 EFCOF  EI2C  EPWM  ESCM  EHSEC ES1   EX2   ESPI 
	IEN0	=Bin(00001000);		//enable timer0,pwm interrupt
	IEN1	=Bin(00200000);		

	
}
