#include	"SH79F082.H"
#include	"DEFINE.H"
#include	"GLOBAL.H"


void ADC_INT(void)
{
	ADCH=Bin(00011111);//0X1f;   //��ͨ����ADCͨ��
	ADT= Bin(11100111); //ADC����ʱ��ѡ��1/16��2us,����ʱ��ѡ��16us,�ܹ�����ʱ����t=12*1+8=20us
	
}

