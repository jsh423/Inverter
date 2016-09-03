#include	"SH79F082.H"
#include	"DEFINE.H"
#include	"GLOBAL.H"


void ADC_INT(void)
{
	ADCH=Bin(00011111);//0X1f;   //开通所有ADC通道
	ADT= Bin(11100111); //ADC采样时钟选择1/16，2us,采样时间选择16us,总共采样时间邋t=12*1+8=20us
	
}

