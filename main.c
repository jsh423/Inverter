#include	"SH79F082.H"
#include	"DEFINE.H"
#include	"GLOBAL.H"
#include    "timer.h"

#define Delay_State 0
#define Err_Dection_State 1
#define PFC_ON_State 2
#define Work_ON_State 3
#define Work_State 4
#define Turn_off_state 5
#define Waite_State0 6
#define Waite_State1 7

#define Turn_on_timer 300
#define Delay_timer 1000
#define Waite_timer 500
#define Start_timer 1000

#define Err_Detection_state 0
#define In_Ovp_delay_state 1
#define In_Uvp_Delay_State 2
#define PFC_OVP_Delay_state 3
#define OTP_delay_state 4
#define OCP_Delay_State 5
#define OUT_OVP_Delay_state 6
#define OUT_UVP_Delay_state 7
#define Short_Delay_state 8
#define Out_Normal_state 9
#define PFC_UVP_State 10



//#define IN_OVP_CONST 170
#define IN_OVP_CONST (182*4) 	//  输入400V最低393V最高409		3.64V
#define IN_UVP_CONST (82*4)   		//输入200V保护最低189 最高197	1.64V
#define PFC_LINE_CONST 170		//	   			3.4V
#define OUT_OCP_CONST 66		//输出863W保护	1.4V	60
#define OUT_OVP_CONST 200		//输出250Vac 保护 4V
#define OUT_UVP_CONST 120		//输出180VAC保护  2.4V
#define OTP_CONST 64			//95摄氏度保护	  0.30V										f
#define PFC_OVP_CONST 	190		//410		 3.6V
#define OUTPUT_NORMAL_CONST 130 //2.6V
#define SHORT_NUM 3			//短路保护恢复的次数短路次数不积累
#define RCD_OVER_NUM 5		//RCD过载次数积累



static int Tem_Flag=0;
static int Power_Process=0;
static int err_state=0;
static int Rest_Start=0;
static int Short_Num1=0;
static int Ocp_Num0=0;
static int Waite1=0;
Word UartTimer=0;


void	main(void)
{
    Word Timer=0;
	Word Adc_Timer =0;
	Word err_timer0=0;
	Word err_timer1=0;
	Word err_timer2=0;
	Word err_timer3=0;
	Word err_timer4=0;
	
	InitSys();			//端口初始化
	
	TimerInit();	     //定时器初始化程序
	
	ADC_INT();			//ADC初始化

	//SinWaveInit();		//SPWM初始化
	//SelfDevice.Tem_err=1;
	EA=1;
	CURSAMP=0xC2;
	RESET_TIME_MS(Timer);
	while(1)
		{

		 	RSTSTAT = 0x00;
			UpdateTime();
		  if(TIME_MS(Adc_Timer) >= 50)  //50ms采样一次
			{ 
					RESET_TIME_MS(Adc_Timer);
					Inputvoltage();		//输入电压采样
					PFC_Dection();
					//ADC_INT1();		//输出电压采样
					Current();		//输出电流采样
					//math_cy(10);  
					Temperature();	//温度采样
	        }
			OutPutVoltage();		//输出电压采样
			//Inputvoltage();
		   switch(Power_Process)
		   	{
		   		case Delay_State:
					if(TIME_MS(Timer) >= Delay_timer)
						{
							DELAY0_ON=1;				  //开启继电器
							Power_Process=Err_Dection_State;
							RESET_TIME_MS(Timer);							
						}
					break;
				case Err_Dection_State:   //错误检测
					if(TIME_MS(Timer) >= Start_timer)//
						{
							if(SelfDevice.InputVoltage>(IN_UVP_CONST+5*4)) 	SelfDevice.Input_Uvp=0;//欠压检测
							else 	SelfDevice.Input_Uvp=1;
							if(SelfDevice.InputVoltage<(IN_OVP_CONST-2*4))	SelfDevice.Input_Ovp=0;//过压检测
							else 	SelfDevice.Input_Ovp=1;
							if((SelfDevice.Tem_err==1)&&(SelfDevice.Temperature>=(OTP_CONST+5)))	 	SelfDevice.Tem_err=0;
							else if((SelfDevice.Tem_err==0)&&(SelfDevice.Temperature>=OTP_CONST)) 		SelfDevice.Tem_err=0;
							else	SelfDevice.Tem_err=1;
							if(SelfDevice.PFC_Voltage<PFC_OVP_CONST)		SelfDevice.PFC_OVP=0;
							else	SelfDevice.PFC_OVP=1;  
							if((SelfDevice.Input_Ovp==0)&&(SelfDevice.Input_Uvp==0)&&(SelfDevice.PFC_OVP==0)//如果输入电压正常，PFC不过压
								&&(SelfDevice.Tem_err==0)&&(Rest_Start==0))									
								{
									PFC_ON=1;
									SelfDevice.Short_Err=0;
									Power_Process=PFC_ON_State;
									RESET_TIME_MS(Timer);	
								}
						}
					break;
				case PFC_ON_State:
					if(TIME_MS(Timer) >= Start_timer)//
						{	
							if(SelfDevice.PFC_Voltage>PFC_LINE_CONST)  //PFC电压是否正常 此处可改高些
								{
									DELAY1_ON=1;
									RESET_TIME_MS(Timer);
		 							SinWaveStart();
									Power_Process=Work_ON_State;
								}
						}
					break;
				case Work_ON_State:
					if(TIME_MS(Timer) >= 200)//
						{
							 DELAY1_ON=1;
							RESET_TIME_MS(Timer);
							Power_Process=Work_State;
							err_state=Err_Detection_state;
						}
					break;
				case Work_State:
					if(1)
					{
					switch (err_state)
						{
							case Err_Detection_state:
								if((SelfDevice.InputVoltage>(IN_OVP_CONST))&&(SelfDevice.Input_Ovp==0))//输入过压
									{
										//Power_Process=Turn_off_state;
										SelfDevice.Input_Ovp=1;	
										RESET_TIME_MS(err_timer4);
										//Waite1=0;
										//break;
									}
								if((SelfDevice.Input_Ovp==1)&&(SelfDevice.InputVoltage>IN_OVP_CONST)&&(TIME_MS(err_timer4) >= 1000))
									{
										//RESET_TIME_MS(err_timer2);
										SelfDevice.Input_Ovp=0;
										Power_Process=Turn_off_state;
									}
								if(SelfDevice.InputVoltage<(IN_UVP_CONST))		//输入欠压
									{
										//err_state=In_Uvp_Delay_State;
										//RESET_TIME_MS(err_timer0);
										Power_Process=Turn_off_state;
										//	SelfDevice.Input_Ovp=1;	
										Waite1=0;
										break;
									}		
								if(SelfDevice.PFC_Voltage>(PFC_OVP_CONST))		//PFC过压保护
									{
										err_state=PFC_OVP_Delay_state;
										RESET_TIME_MS(err_timer0);
									}	  
								if(SelfDevice.PFC_Voltage<(PFC_LINE_CONST-5))		//PFC欠压保护
									{
										err_state=PFC_UVP_State;
										RESET_TIME_MS(err_timer0);
									} 
								if((SelfDevice.Out_Current>(OUT_OCP_CONST))&&(SelfDevice.Out_Ocp==0))//&&(SelfDevice.InputVoltage<IN_OVP_CONST-3))		//过流保护
									{
										//err_state=OCP_Delay_State;
										RESET_TIME_MS(err_timer2);
										SelfDevice.Out_Ocp=1;
									}	
								if((SelfDevice.Out_Ocp==1)&&(TIME_MS(err_timer2) >= 10000))
									{	
										SelfDevice.Out_Ocp=0;	  
									if((SelfDevice.Out_Current>(OUT_OCP_CONST)))//&&(SelfDevice.InputVoltage<IN_OVP_CONST-3))
										{
											if(Ocp_Num0++>SHORT_NUM) Rest_Start=1;
											Power_Process=Turn_off_state;
											//SelfDevice.Out_Ocp=1;
											Waite1=1;
											break;
										}
									 
									}	 
							/*	if(SelfDevice.Out_Voltage<(OUT_UVP_CONST))		//输楚欠压保护
									{
										err_state=OUT_UVP_Delay_state;
										RESET_TIME_MS(err_timer0);
										//Power_Process=Turn_off_state;
										SelfDevice.Tem_err=1;	
										//Waite1=0;
									} 	 	 */
								if(SelfDevice.Out_Voltage>(OUT_OVP_CONST))		//输出过压保护
									{
										err_state=OUT_OVP_Delay_state;
										RESET_TIME_MS(err_timer0);
										//Power_Process=Turn_off_state;
											//SelfDevice.Tem_err=1;	
											//Waite1=0;
									}	   
								if((SelfDevice.Temperature<(OTP_CONST))&&(Tem_Flag==0))//过温保护
									{
										//err_state=OTP_delay_state;
										RESET_TIME_MS(err_timer3);
										//Power_Process=Turn_off_state;
											Tem_Flag=1;	
											//Waite1=0;
											//break;
									}
								if((Tem_Flag==1)&&(TIME_MS(err_timer3)>2000))
									{
										if(SelfDevice.Temperature<(OTP_CONST))
											{
												Power_Process=Turn_off_state;
												Waite1=0;
												SelfDevice.Tem_err=1;
											}
										Tem_Flag=0;
									}
								if(SinWaveValue.gBSinShortNum0>900)		//短路保护
									{
										Power_Process=Turn_off_state;
										SinWaveValue.gBSinShortNum1++;
										SinWaveValue.gBSinShortNum0=0;
									}
								if(SinWaveValue.gBSinShortNum1>RCD_OVER_NUM)//RCD过载次数积累
									{
										Rest_Start=1;
									}
									
								if(((SelfDevice.Out_Voltage>OUTPUT_NORMAL_CONST)&&(SelfDevice.Out_Current<OUT_OCP_CONST))&&(SelfDevice.Work_ok==0))
									{
										//err_state=Out_Normal_state;
										RESET_TIME_MS(err_timer1);
										SelfDevice.Work_ok=1;
										
									}  
								if((SelfDevice.Work_ok==1)&&(TIME_MS(err_timer1) >= 2000))
									{
											if((SelfDevice.Out_Voltage>OUTPUT_NORMAL_CONST)&&(SelfDevice.Out_Current<OUT_OCP_CONST))
												{
												Short_Num1=0;
												Ocp_Num0=0;
												}
											SelfDevice.Work_ok=0;
									} 	   
							//	else SelfDevice.StatusBits&=~Power_line;
								break;
							/*case In_Ovp_delay_state:				//输入过压
								if(TIME_MS(err_timer0) >= 20)
									{
									if(SelfDevice.InputVoltage>(IN_OVP_CONST))
										{
											Power_Process=Turn_off_state;
											SelfDevice.Input_Ovp=1;	
											Waite1=0;
										}
									 err_state=Err_Detection_state;
									}
								break;
							case In_Uvp_Delay_State:		//输入欠压
								if(TIME_MS(err_timer0) >= 20)
									{
									if(SelfDevice.InputVoltage<(IN_UVP_CONST))
										{
											Power_Process=Turn_off_state;
											SelfDevice.Input_Uvp=1;
											Waite1=0;
										}
									 err_state=Err_Detection_state;
									}
								break; */
							case PFC_OVP_Delay_state:			//PFC过压
								if(TIME_MS(err_timer0) >= 100)
									{
									if(SelfDevice.PFC_Voltage>(PFC_OVP_CONST))
										{
										//	Rest_Start=1;
											Power_Process=Turn_off_state;
											SelfDevice.PFC_OVP=1;
											PFC_ON=0;
											Waite1=1;
										}
									else err_state=Err_Detection_state;
									}
								break;
							case PFC_UVP_State:			//PFC欠压
								if(TIME_MS(err_timer0) >= 200)
									{
									if(SelfDevice.PFC_Voltage<(PFC_LINE_CONST-5))
										{
											Rest_Start=1;
											Power_Process=Turn_off_state;
											//SelfDevice.PFC_OVP=1;
											//PFC_ON=0;
											Waite1=0;
										}
									else err_state=Err_Detection_state;
									}
								break;
							/*case OTP_delay_state:				//过温保护
								if(TIME_MS(err_timer0) >= 20)
									{
									if(SelfDevice.Temperature<(OTP_CONST))
										{
											Power_Process=Turn_off_state;
											SelfDevice.Tem_err=1;	
											Waite1=0;
										}
									 err_state=Err_Detection_state;
									}
								break;
							case OCP_Delay_State:					//过流保护
								if(TIME_MS(err_timer0) >= 100)
									{
									if(SelfDevice.Out_Current>(OUT_OCP_CONST))
										{
											if(Ocp_Num0++>SHORT_NUM) Rest_Start=1;
											Power_Process=Turn_off_state;
											SelfDevice.Out_Ocp=1;
											Waite1=1;
										}
									 err_state=Err_Detection_state;
									}
								break;*/
							case OUT_OVP_Delay_state:				//输出过压保护
								if(TIME_MS(err_timer0) >= 200)
									{
									if(SelfDevice.Out_Voltage>(OUT_OVP_CONST))
										{
											Rest_Start=1;
											Power_Process=Turn_off_state;
											SelfDevice.Out_Ovp=1;
											Waite1=1;
											
										}
									 err_state=Err_Detection_state;
									}
								break;
							case OUT_UVP_Delay_state:				//输出欠压保护
								if(TIME_MS(err_timer0) >= 10)
									{
									if(SelfDevice.Out_Voltage<(OUT_UVP_CONST))
										{											
											if(Short_Num1++>SHORT_NUM) Rest_Start=1;
											Power_Process=Turn_off_state;
											SelfDevice.Out_Uvp=1;
											Waite1=1;
										}
									 err_state=Err_Detection_state;
									}
								break;
						/*	case Out_Normal_state:
								if(TIME_MS(err_timer0) >= 2000)
									{
									if((SelfDevice.Out_Voltage>OUTPUT_NORMAL_CONST)&&(SelfDevice.Out_Current<OUT_OCP_CONST))
										{											
											Short_Num1=0;
											Ocp_Num0=0;
											//Power_Process=Turn_off_state;
											//SelfDevice.Out_Uvp=1;
											//Waite1=1;
										}
									 err_state=Err_Detection_state;
									}
								break;*/
								default:
								err_state=Err_Detection_state;
						}
						}
						break;
					case Turn_off_state:
						
							PWMLO = 0x55;
							PWMEN&=0X7f;
							FLTCON&=0XEF;
							PWMLO = 0x00;
							SelfDevice.Short_Err=1;
							//SelfDevice.Work_ok=1;
							SinWaveValue.gBSinAmplitude=0;			//设置振幅为MAX
							SinWaveValue.gBSinPWMDuty1=0;
							SinWaveValue.gBSinPWMDuty2=0;
							SinWaveValue.gBSinPWMIndex=0;
							SinWaveValue.gBSinShortNum0=0;
							SinWaveValue.SinStartNum=0;
							DELAY1_ON=0;
							RESET_TIME_MS(Timer);
							if(Waite1==1)	Power_Process=Waite_State1;
							else Power_Process=Waite_State0;
						break;
					case Waite_State0:
						if(TIME_MS(Timer) >= 3000)
							{
								Power_Process=Err_Dection_State;
								RESET_TIME_MS(Timer);
							}
						break;
					case Waite_State1:
						if(TIME_MS(Timer) >= 8000)
							{
								Power_Process=Err_Dection_State;
								RESET_TIME_MS(Timer);
							}
						break;	
					default:
						Power_Process=Turn_off_state;
						break;
		   	}
		}
}




									


/* void  normal(void)
 {
	K=0;
    gbSinOutputEn=1;	  //电源正常工作标志位
	TR1=0;

	PWMLO=0X55;
	PWMEN|=0X80;
	gBSinAmplitude=0;
	//gbSinOutputSH=0;
	 //gbSinOutputIP=0;
	 gbSinOutputOP=0;
		gWSinPWMIndex=0;
	  PWMLO = 0x00;
	  N=0;
	  Nfb=0;
	  I=0;
	  F=0;
	 // J=0;
	//P2_6=1;
	//TL1		=	0x07;	//定时200uS
	//TH1		=	0xF3;
	//TR1=1;
	gbSinOutputErr=0;
	}	 
	*/