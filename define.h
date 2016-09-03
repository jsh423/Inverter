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
//����ϵͳ�����ṹ

struct _SinValue					
{
	Word	gBSinAmplitude;		//���Ҳ����ȿ���
	Word	gBSinPWMDuty1;		//���Ҳ�ռ�ձ�
	Word 	gBSinPWMDuty2;		//���Ҳ�ռ�ձ�
	Word 	gBSinPWMIndex;		//���Ҳ����
	Word	gBSinShortNum0;
	Word    gBSinShortNum1;
	Word    SinStartNum;
};
	
struct _SelfDevice
{
	unsigned Work_ok:1;		//����������־λ
	unsigned PFC_OVP: 1;	//�����쳣��־λ
	unsigned Input_Uvp:1;	//����Ƿѹ��־λ
	unsigned Input_Ovp:1;	//�����ѹ��־λ
	unsigned Tem_err:1;		//�¶ȹ��ϱ�־λ
	unsigned Short_Err:1;	//��·��־λ
	unsigned Out_Ocp:1;		//������ر�־λ
	unsigned Out_Ovp:1;		//�����ѹ��־λ
	unsigned Out_Uvp:1;		//���Ƿѹ��־λ
	Word InputVoltage;  //�����ѹ
	Word PFC_Voltage;   //PFC�����ѹ
	Word Out_Voltage;  	//��������ѹ
	Word Out_Current; 	//����������
	Word Temperature;   //�¶�ֵ
	struct _SinValue SinWaveValue;	//�趨���Ҳ�����
} ;

//#pragma pack()



#endif