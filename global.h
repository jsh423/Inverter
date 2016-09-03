/***************************************************************************************
	Model		: global.h
	Description	: Head file of defining global variable.
	Author		: CLR
	Create Time	: 2008-05-12
	Version ID      : 0.1
****************************************************************************************/
#ifndef		_GLOBAL_H
#define		_GLOBAL_H

#include  "SH79F082.h"
/*-----------------------------------------------------------------------------------*
 *							isr.c													 *
 *-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
;								Init Module
;write data to the indicate Page of Flash ROM
;-------------------------------------------------------------------------------------*/



//extern	Word	code	Tab_Sin[200];


extern struct _SelfDevice SelfDevice;
extern struct _SinValue SinWaveValue;

extern	void	InitSys(void);
extern	void	SinWaveStart(void);
extern  void     SinWaveInit(void);
extern	void	SPWM(void);
extern	void	ADC_INT1(void);
extern  void    ADC_INT();
extern	void	PROTEL(void);
extern  void  	normal(void);
extern  void     PFC_Dection(void);
extern  void    Current(void);
extern  void    Inputvoltage(void);
extern  void    Temperature(void);
extern  void    OutPutVoltage(void);
//extern  void    Delay(M);
extern  void    math_cy(int i);





#endif
