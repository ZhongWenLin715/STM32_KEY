#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"  
	 
void delay_init(void);
void delay_ms(u32 nms);
void delay_us(u32 nus);

//�������ʱ�ӳ���: ʵ��ֵԼ5500Ϊ1������,5.5Ϊһ��΢�� 
void SoftDelay(vu32 nCount);
void SoftDelay_ms(u16 nms);
void SoftDelay_us(u16 nus);

u32 GetTicks(void); 		//��ȡSysTick�����ۼƴ���

#endif





























