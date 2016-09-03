#ifndef	_DEFINE_H
#define	_DEFINE_H

typedef	bit				Bit;
typedef	bit				Bool;
typedef	unsigned char	Byte;
typedef	unsigned int	Word;
typedef	unsigned long	Dword;

//Mode1 16 bit counter.T=1/8.192M t=1000us N=t/T=8192  
#define	CLOCK_1MS		(2^16-8192)

#define DELAY0_ON P3_5
#define PFC_ON	P3_4
#define DELAY1_ON P0_0

 #define LongToBin(n) \
(                    \
((n >> 21) & 0x80) | \
((n >> 18) & 0x40) | \
((n >> 15) & 0x20) | \
((n >> 12) & 0x10) | \
((n >>  9) & 0x08) | \
((n >>  6) & 0x04) | \
((n >>  3) & 0x02) | \
((n      ) & 0x01)   \
)
#define Bin(n) LongToBin(0x##n##l)	//write binary charactor set,exsample : Bin(11111111) = 0xff


//#pragma pack(1)
//定义系统参数结构

struct _SinValue					
{
	Word	gBSinAmplitude;		//正弦波幅度控制
	Word	gBSinPWMDuty1;		//正弦波占空比
	Word 	gBSinPWMDuty2;		//正弦波占空比
	Word 	gBSinPWMIndex;		//正弦波序号
	Word	gBSinShortNum0;
	Word    gBSinShortNum1;
	Word    SinStartNum;
};
	
struct _SelfDevice
{
	unsigned Work_ok:1;		//工作正常标志位
	unsigned PFC_OVP: 1;	//工作异常标志位
	unsigned Input_Uvp:1;	//输入欠压标志位
	unsigned Input_Ovp:1;	//输入过压标志位
	unsigned Tem_err:1;		//温度故障标志位
	unsigned Short_Err:1;	//短路标志位
	unsigned Out_Ocp:1;		//输出过载标志位
	unsigned Out_Ovp:1;		//输出过压标志位
	unsigned Out_Uvp:1;		//输出欠压标志位
	Word InputVoltage;  //输入电压
	Word PFC_Voltage;   //PFC输出电压
	Word Out_Voltage;  	//逆变输出电压
	Word Out_Current; 	//逆变输出电流
	Word Temperature;   //温度值
	struct _SinValue SinWaveValue;	//设定正弦波参数
} ;

//#pragma pack()



#endif