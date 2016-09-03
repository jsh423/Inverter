#include	"SH79F082.H"
#include	"DEFINE.H"
#include	"GLOBAL.H"
#include	"INTRINS.H"


struct _SelfDevice SelfDevice;
struct _SinValue SinWaveValue;
static Word    idata    Tequal;
static Word    xdata  Tab_ADCres[10];
Word	code	Tab_Sin[200] = 	{ 0	,
								13 ,
								26 ,
								39 ,															   			
								52 ,
								65 ,
								78 ,
								91	,
								104	 ,
								117	,
								130	,
								143	 ,
								156	,
								168	,
								181	,
								194	 ,
								206	 ,
								219	 ,
								232	  ,
								244	 ,
								256	 ,
								269	,
								281	,
								293	,
								306	,
								318	 ,
								330	,
								342	 ,
								353	 ,
								365	 ,
								377	 ,
								388	 ,
								400	  ,
								411	 ,
								423	,
								434	 ,
								445	 ,
								456	 ,
								467	 ,
								477	 ,
								488	,
								498	 ,
								509	 ,
								519	  ,
								529	  ,
								539	  ,
								549	  ,
								559	  ,
								568	  ,
								578	  ,
								587	  ,
								596	  ,
								605	  ,
								614	  ,
								623	  ,
								631	  ,
								640	  ,
								648	   ,
								656	  ,
								664	  ,
								671	   ,
								679	   ,
								686	  ,
								694	   ,
								701		,
								708	   ,
								714		,
								721	   ,
								727	   ,
								734	   ,
								740	   ,
								745	  ,
								751	  ,
								756	  ,
								762	  ,
								767	  ,
								772	  ,
								776	  ,
								781	  ,
								785	  ,
								789	  ,
								793	  ,
								797	  ,
								801	  ,
								804	  ,
								807	  ,
								810	   ,
								813	   ,
								815	   ,
								818	  ,
								820	  ,
								822	  ,
								823	 ,
								825	 ,
								826	 ,
								827	 ,
								828	 ,
								829	 ,
								830	  ,
								//830	   ,
								830	   ,
								830	  ,
								830	  ,
								829	  ,
								828	  ,
								827	  ,
								826	  ,
								825	  ,
								823	  ,
								822	  ,
								820	  ,
								818	  ,
								815	  ,
								813	   ,
								810	   ,
								807	   ,
								804	   ,
								801	  ,
								797	   ,
								793	  ,
								789	   ,
								785	   ,
								781	  ,
								776	  ,
								772	  ,
								767	 ,
								762	  ,
								756	   ,
								751	  ,
								745	   ,
								740	   ,
								734	   ,
								727		,
								721		,
								714		,
								708	   ,
								701	   ,
								694	   ,
								686		,
								679	   ,
								671	   ,
								664	   ,
								656	  ,
								648	  ,
								640	   ,
								631	   ,
								623	   ,
								614	  ,
								605	   ,
								596	   ,
								587	   ,
								578	   ,
								568	   ,
								559	   ,
								549	   ,
								539	  ,
								529		,
								519	 ,
								509	 ,
								498	 ,
								488	  ,
								477	  ,
								467	  ,
								456	  ,
								445	 ,
								434	  ,
								423	  ,
								411	  ,
								400	  ,
								388	  ,
								377	   ,
								365	  ,
								353	  ,
								342	 ,
								330	 ,
								318	 ,
								306	 ,
								293	 ,
								281	 ,
								269	 ,
								256	 ,
								244	 ,
								232	 ,
								219	,
								206	,
								194	 ,
								181	 ,
								168	  ,
								156	  ,
								143	 ,
								130	  ,
								117	  ,
								104	  ,
								91	,
								78	,
								65	,
								52	,
								39	 ,
								26	,
								13	,
								0,

								
											   

									 };	 //89
/****************************************************************************
			void	SinWaveStart(void)
π¶ƒ‹Àµ√˜:	’˝œ“≤® ‰≥ˆ≥ı ºªØ
∆‰À˚Àµ√˜:	1.∂‘PWMºƒ¥Ê∆˜Ω¯––øÿ÷∆£¨“™œ»Ω¯––Ω‚À¯°£“™»√PWMºƒ¥Ê∆˜–ﬁ∏ƒµƒƒ⁄»›”––ß£¨
			–Ë“™Ω¯––PWMÀ¯∂®°£

			2.Õ®π˝π´ Ω Period = Fsys/Fsin/N/2£¨”…”⁄Fsys=8.192MHZ£¨Fsin=50HZ£¨
			N=400£¨À˘“‘PeriodŒ™204°£

			3.ø™∆ÙPWM∫Û£¨ª·≥ˆœ÷“ª∏ˆº‚∑Â√´¥Ã°£Ω‚æˆ∑Ω∑®£∫Ω´PWMCºƒ¥Ê∆˜µƒPWMSŒª÷√“ª£¨
			÷Æ∫Û¬Ì…œ«Â¡„°£

			4.ø™∆ÙPWM÷–∂œ∫Û£¨ª·¬Ì…œ÷–∂œ“Á≥ˆ°£Ω‚æˆ∑Ω∑®£∫ø™∆ÙPWM÷–∂œ∫Û£¨—”≥Ÿº∏∏ˆ
			œµÕ≥ ±÷”∫ÛΩ´PWM÷–∂œ«Î«Û±Í÷æ«Â¡„°£

 ‰»Î£∫		Œﬁ
 ‰≥ˆ£∫		Œﬁ
*****************************************************************************/
static Word SinstartNum1=0;
static Word SinshortNum=0;
	
void   SPWM(void) interrupt 12 using 1
{
	//DELAY1_ON=1;
	PWMLO = 0x55;
	PWMINT&=0XBF;
	PWMLO = 0x00;//πÿ±’÷–∂œ
	if((FLTCON&0X10))
	{ 
		SinshortNum++;
		if((SinshortNum>2)&&(SinWaveValue.gBSinShortNum0<1000))
		{
			//F++;
			SinWaveValue.gBSinShortNum0++;
			SinshortNum=0;
			//H=0;
			if((SelfDevice.Out_Voltage>80)||(SinWaveValue.gBSinShortNum0<10))
			{
				PWMLO = 0x55;
				FLTCON&=0XEF;
				PWMLO = 0x00;
			}
		} 
	}	
	     
		if(SinWaveValue.SinStartNum<62 )
		{
			if(SinstartNum1++>250)
			{
				SinstartNum1=0;
				SinWaveValue.gBSinAmplitude++;
				SinWaveValue.SinStartNum++;
			}
		} 
		else	
		{
			SinWaveValue.SinStartNum=62;
		}
	if(SelfDevice.Short_Err==1) SinWaveValue.gBSinAmplitude=0;		//∑¿÷π≥Ã–Úπÿ∂œ≥ˆœ÷“Ï≥£
	if(SinWaveValue.gBSinPWMIndex==400){SinWaveValue.gBSinPWMIndex=0;}//;sin_up=!sin_up;}

	if(SinWaveValue.gBSinPWMIndex<200)
	{
		PWMLO = 0x55;
		SinWaveValue.gBSinPWMDuty1=415+Tab_Sin[SinWaveValue.gBSinPWMIndex]*(SinWaveValue.gBSinAmplitude)/167 ;
		PWM1DL =(unsigned char)(SinWaveValue.gBSinPWMDuty1&0x00ff) ;
		PWM1DH =(unsigned char) (SinWaveValue.gBSinPWMDuty1 >>8);
		PWMLO = 0x00;
	}//ªªœÚ
	else 
	{  	
		PWMLO = 0x55;
		SinWaveValue.gBSinPWMDuty1= 406-Tab_Sin[SinWaveValue.gBSinPWMIndex-200]*(SinWaveValue.gBSinAmplitude)/167 ;
		PWM1DL =(unsigned char)(SinWaveValue.gBSinPWMDuty1&0x00ff) ;
		PWM1DH =(unsigned char) (SinWaveValue.gBSinPWMDuty1 >>8);
		PWMLO = 0x00;
	}//ªÚ

	
	SinWaveValue.gBSinPWMIndex++;

}
void  SinWaveInit(void)
{
		 CURSAMP=0xC2;
		PWMLO = 0x55;						//Ω‚À¯
		PWMPL= 0x48;					//…Ë÷√PWM÷‹∆⁄Period = 818*(1/16.6us) = 50us		Period = 208*(4/16.6us) = 50us
		PWMPH=0X03;
		PWMDT0L= 4;					//…Ë÷√À¿«¯ ±º‰Œ™1.2us = 10*(1/8.192us)
		PWMDT0H= 0;
		PWMDT1L= 4;
		PWMDT1H= 0;
		PWMINT |= 0X80;
		FLTCON = 0xC0;									//π ’œºÏ≤‚π¶ƒ‹ø™∆Ù
		PWMEN =0X12;
		//PWMINT = 0X00;                                 //Ω˚÷πÌPWM÷‹∆⁄÷–∂œ
		PWMINT = 0X00;
		PWMEN |=0X80; 
		PWMCON=0x00;                                   //PWM ±÷”—°‘Ò1/1œµÕ≥ ±÷”£¨∑÷∆µ£¨∏ﬂµÁ∆Ω«˝∂Ø
		PWMLO = 0x00;									//PWMÀ¯∂
		IEN1&=~0X20;
		IPH1|=0X20;
		//IPL1|=0X20;	 			   //PWM”≈œ»º∂÷√Œ™◊Ó∏ﬂº∂£¨µ˜ ‘

}
		
void	SinWaveStart(void)
{

	
		SinWaveValue.gBSinAmplitude=1;			//…Ë÷√’Ò∑˘Œ™MAX
		SinWaveValue.gBSinPWMDuty1=0;
		SinWaveValue.gBSinPWMDuty2=0;
		SinWaveValue.gBSinPWMIndex=0;		//…Ë÷√µ»∑÷º∆ ˝œµ ˝x = 0   
		SinWaveValue.SinStartNum=0;
		PWMLO = 0x55;						//Ω‚À¯
		PWMPL= 0x48;					//…Ë÷√PWM÷‹∆⁄Period = 818*(1/16.6us) = 50us		Period = 208*(4/16.6us) = 50us
		PWMPH=0X03;
		//PWM2DL= 0;					//…Ë÷√PWM’ºø’±»Duty = 0
		//PWM2DH=0;
		//FLTCON&=0XEF;   				  //π ’œ±Í÷æŒª«Â¡„
		PWM1DL=0;
		PWM1DH=0;
	    PWMDT0L= 4;					//…Ë÷√À¿«¯ ±º‰Œ™1.2us = 10*(1/8.192us)
		PWMDT0H= 0;
		PWMDT1L= 4;
		PWMDT1H= 0;
		PWMINT|=0X80;                                 //‘ –ÌPWM÷‹∆⁄÷–∂œ
	//	PWMEN = 0X86;                                  // πƒ‹PWM ‰≥ˆ£¨±ﬂ—ÿ∂‘∆Î°£
		
		PWMCON=0x00;                                   //PWM ±÷”—°‘Ò1/4œµÕ≥ ±÷”£¨∑÷∆µ£¨∏ﬂµÁ∆Ω«˝∂Ø
		PWMEN =0X92;						//
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		PWMINT=0X80; 						//∏’∆Ù∂ØPWM ±£¨ª·¡¢º¥≤˙…˙pwm÷–∂œ±Íº«°£À˘“‘—”≥Ÿº∏∏ˆœµÕ≥÷‹∆⁄∫Û£¨‘Ÿ«Â≥˛PWMIFº¥ø…°£
		FLTCON = 0xC0;							
		PWMLO = 0x00;		//PWMÀ¯∂®
		IEN1|=0X20;
		IPH1|=0X20;
		//CURSAMP=0xC2;	 
		
}


void OutPutVoltage(void)
	{	
		int i = 0;	//,c = 0 ;
		Word c=0;
		ADCON=0X80;
		//Tequal=0;
		for(i=0;i<5;i++)
		{
			ADCON |=0x01 ;
			while((ADCON & 0x01) ==1);
			Tab_ADCres[i]=ADDH;
			c+=Tab_ADCres[i];
		}
		SelfDevice.Out_Voltage=c/5;
	}  	 
void Inputvoltage(void)
	{
		int i;
		Word c=0;
		ADCON=0X84;
		Tequal=0;
		for(i=0;i<5;i++)
		{
			ADCON |=0x01 ;
			while((ADCON & 0x01) ==1)	;
			Tab_ADCres[i]=ADDH*4+ADDL;
			c+=Tab_ADCres[i];
		}
		SelfDevice.InputVoltage=c/5;
	}
void Current(void)
	{	
		int i = 0;
		Word c = 0 ;
		ADCON=0X82;
		//Tequal=0;
		for(i=0;i<10;i++)
		{
			ADCON |=0x01 ;
			while((ADCON & 0x01) ==1);
			Tab_ADCres[i]=ADDH;
			c+=Tab_ADCres[i];
		}
		SelfDevice.Out_Current=c/10;
	}  	 


	
void PFC_Dection(void)
{
	int i = 0;					//,c = 0 ;
	ADCON=0X86;
	Tequal=0;
	for(i=0;i<5;i++)
	{
		ADCON |=0x01 ;
		while((ADCON & 0x01) ==1);
		Tab_ADCres[i]=ADDH;
		Tequal+=Tab_ADCres[i];
	}
	SelfDevice.PFC_Voltage=Tequal/5;
}
void Temperature(void)
{
	int i = 0;//,c = 0 ;
	ADCON=0X88;
	Tequal=0;
	for(i=0;i<5;i++)
	{
		ADCON |=0x01 ;
		while((ADCON & 0x01) ==1);
		Tab_ADCres[i]=ADDH*4+ADDL;
		Tequal+=Tab_ADCres[i];
	}
	SelfDevice.Temperature=Tequal/5;
}			  			  

void math_cy(int i)

{
	Word a,b,j;
	if(Tab_ADCres[0]>Tab_ADCres[1])
	{ 
		a= Tab_ADCres[0];
		b=Tab_ADCres[1];
	}
	else
	{ 
		b=Tab_ADCres[0];
		a=Tab_ADCres[1];	
	}
	for(j=2;j<i;j++)
	{ 
	if(Tab_ADCres[j]>a)	a=Tab_ADCres[j];
	if(Tab_ADCres[j]<b) b=Tab_ADCres[j];
	}
	Tequal-=a;
	Tequal-=b;
	SelfDevice.Out_Current=Tequal/(i-2);

}



/*void Delay(M)
{
int i,j;
for (i=0;i<255;i++)
{
	for (j=0;j<M;j++)
	{

	}
}
}*/
	 	 
     
	
	

/* void  PROTEL(void)
{
		  PWMLO = 0x55;
    	   PWMEN&=0X7f;
		   FLTCON&=0XEF;
		   PWMLO = 0x00;
			 P0_0=0;
			 TR1=1;
		    P1_0=0;
		   gbSinOutputEn=0;	  //µÁ‘¥’˝≥£π§◊˜±Í÷æŒª
		   //BUZCON=0X01;
		 //gbSinOutputErr=0;
		 gBSinAmplitude=0;
		 //gbSinOutputIP=0;
		 gbSinOutputOP=0;
		// gbSinOutputSB=0;
		 //gbSinOutputSH=1;
		  N=0;
		 // J=0;
		 // I=0;
	  		Nfb=0;
}		 
  */
    

