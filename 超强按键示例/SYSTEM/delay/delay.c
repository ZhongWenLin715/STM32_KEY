#include "delay.h"
#include "key.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2018/8/29
//�汾��V1.0
//Made by warship									  
//////////////////////////////////////////////////////////////////////////////////   

//ʹ��SysTick�ļ���ģʽ���ӳٽ��й����ʺ�STM32F10xϵ�У�
//����delay_us,delay_ms, ��Ӱ��SysTick�ж�ϵͳ
//��ʱ������SysTick�м�����24λ������,һ�ο���ʱ��47�����,�ߴ�1��Сʱ

//���ļ��л�������SysTick���жϷ������SysTick_Handler()

//2018/5/10

//////////////////////////////////////////////////////////////////////////////////  
static u8  fac_us=9;							//us��ʱ������			   
//static u32 fac_ms=0;	//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��



//��ʱ��ʼ��: ��������ڴ�ֱ�ӵ��øú�������,�ɴ˼�ʵ����ȫϵͳ��ʱ������
//������ʵ����ֻ��ѡ����SysTick��ʱ��Դ, ���趨SysTickΪ1�����ж�һ��
//ϵͳRCC����ʱ�ӵĳ�ʼ��SystemInit�������������(����鲢ȷ�Ϲ�����ѡ�õ������ļ�����ض���)
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//�ж�ʱ��time  =  ( SysTick->LOAD + 1 ) / f                        f = AHB��AHB/8            ��9000-1+1��/9M=1ms
void delay_init(void)
{
  SysTick->LOAD=9000-1;    //װ��ֵ�趨Ϊ9*1000-1=8999  ��ÿms�ж�һ�� 
	SysTick->CTRL|=3;        //����SYSTICK�������ж�	
}

//΢����ʱ����:
//��������������ȡSYSTICK�ĵ�ǰֵ,ֱ����������ʱʱ�䵽��, ��Ӱ��SYSTICK���Զ���װ,Ҳ��Ӱ�����ж�
//��ʹ����ʱ�����з����ж�,ֻҪ�жϷ����ʱ������1ms, ������Ӱ�챾��������ʱ����
//nus:0~2^32/fac_us=4294967296/9=477,218,588 �ߴ�4.7��΢��                                                                             
void delay_us(u32 nus)
{                
	static u32 ticks;
	static u32 told,tnow,tcnt=0;
	static u32 reload;
	static u32 OldLongTicks;
	told=SysTick->VAL;     //ȡ�ս���ʱ�ļ�����ֵ
	OldLongTicks=GetTicks();  //ȡ�ս���ʱ��ϵͳ��઼���ֵ��������
	reload=SysTick->LOAD;   //ȡϵͳ��વ���װ��ֵ����ÿ��વ�ticks����                     
	ticks=nus*fac_us;       //���㱾������Ҫ��ʱ��ticks��(ÿusռfac_us��ticks)                           

	while(1)
	{
		tnow=SysTick->VAL;        //ȡ��ǰ����ֵ
		tcnt=(GetTicks()-OldLongTicks)*reload-tnow+told;
		if(tcnt>=ticks)break;   //�ۼƽ���������/������Ҫ�ӳٵĽ�����,����ʱʱ�䵽��, ���˳�������.
	}        
}


//������ʱ����:
//����������ʱ����������1000��ֱ�ӵ���΢����ʱ����
//nms:0---2^32/1000/fac_us=47�����  
void delay_ms(u32 nms)
{                                     
  delay_us((u32)(nms*1000));                                        //ֱ�ӵ���delay_us����������ʱ  
}


//�������ʱ�ӳ���: ʵ��ֵԼ5500Ϊ1������,5.5Ϊһ��΢��
void SoftDelay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}


//�������ʱ�ӳ���: ʵ��ֵԼ5500Ϊ1������,5.5Ϊһ��΢��
void SoftDelay_ms(u16 nms)
{
	u32 nCount=(u32)(5500*nms);
  for(; nCount != 0; nCount--);
}


//�������ʱ�ӳ���: ʵ��ֵԼ5500Ϊ1������,5.5Ϊһ��΢��
void SoftDelay_us(u16 nus)
{
	u32 nCount=(u32)(5*nus+nus/2);
  for(; nCount != 0; nCount--);
}


/*******************************************************************************
* Function Name  : SysTickHandler
* Description    : ϵͳÿ1�������һ���жϣ�����˷������
ע��: ����������ʱ��������ͻ
*******************************************************************************/
//nTicksΪһ��32λ�ľ�̬ȫ�ֱ���,�����ۼ�SysTick�ܴ���
static u32 nTicks = 0;  //��̬ȫ�ֱ���ֻ�ڱ��ļ�������
u32 GetTicks()
{
	return nTicks;
}

extern u8 Flag300ms;
/* SysTick�жϷ����� */
void SysTick_Handler(void)
{
	nTicks++;
	if(!(nTicks%300)) Flag300ms=1;

	if (( nTicks % TICKS_INTERVAL) == 0 )
	 {
		Key_Scan_Stick(); //ÿ5msɨ��һ��
		if ( nTicks % (TICKS_INTERVAL*12) == 0 ) 
			 GetAndSaveKey();//ÿ60ms����һ�μ�ֵ
	 }
}





