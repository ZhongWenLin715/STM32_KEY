///////////////////////////////////////////////////////////////////////////////
//开发平台  STM32F103ZET6  战舰V3
//PF0-3口配置成推挽输出  作为4x4键盘的行
//PF4-7口配置成上拉输入  作为4x4键盘的列
//这个程序用两个LED灯来反馈现象   
////////////////////////////////////////////////////////////////////////////////

#include "stm32f10x.h"
#include "key.h"
#include "led.h"
#include "sys.h" 
#include "delay.h"

u16 keyz=0;

void KEY_Init(void) 
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);//使能PORTA,PORTF时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//KEY0-KEY3  矩阵键盘的行
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //设置成推挽输出  GPIO_Mode_Out_OD
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//KEY4-KEY7  矩阵键盘的列
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      //设置成上拉输入  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOF, &GPIO_InitStructure);	
	GPIO_SetBits(GPIOF,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); 
}



u8 keyscan(void)
{ 
	uint8_t LIE,HANG,k,i=0;
	
	GPIO_Write(GPIOF, 0xF0);                            //D0-D3拉低，D4-D7拉高
	if((GPIO_ReadInputData(GPIOF)&0xF0)!=0xF0)          //有按键按下
	{
	  delay_ms(40);                                     //消抖
	   if((GPIO_ReadInputData(GPIOF)&0xF0)!=0xF0)       //再次判断是否按下
	   {
		   LIE=GPIO_ReadInputData(GPIOF);                 //读取按键按下后得到的代码
           HANG=LIE;                                      //将代码复制给行
		   LIE=~LIE;                                      //将键码取反，例如：按下某个键得到0111 0000，取反后得到1000 1111;
		   LIE=LIE&0XF0;                                  //得到列1000 1111&1111 0000得到1000 0000，得到列数
		   for(i=0;i<4&&((HANG&0xF0)!=0xF0);i++)          //逐次将行拉高，判断列数中原来变低的位是否变高
		   {                                              //读到之前检测到为低的列变高则退出
		       GPIO_Write(GPIOF, (HANG&0xF0)|(0x01<<i));  //进行行扫描，逐次将行口线拉高，列保持为按下时的状态
		       HANG=GPIO_ReadInputData(GPIOF);            //读取IO口，用以判断是否扫描到行坐标			   
		   }
		   HANG&=0x0F;                                    //将行值取出
		   k=LIE|HANG;                                    //行列相加则得到键码
		   GPIO_Write(GPIOF, 0xF0);                       //D0-D3拉低，D4-D7拉高，此处用来将行列状态初始化为未按下时的状态
	     while((GPIO_ReadInputData(GPIOF)&0xF0)!=0xF0)  //判释放
		   {
		        delay_ms(40);                             //后沿消抖，时间需长一点，小按键消抖时间可以短一点，大按键抖动严重消抖需长一点
		   }
		   return k;                                      //返回键码 
	   }
	}	
	return (0);                                         //无键按下,返回0
}


 u8 keychuli(void)
{ 
	uint8_t key_1=0;
	uint8_t i=1;
	while(i)
	{
		keyz=keyscan();
		if(keyz!=0)
		{ 
			switch(keyz)
			{
				case 0x11: PBout(5)=1;key_1=1;i--;break; 
				case 0x21: PEout(5)=0;key_1=2;i--;break; 
				case 0x41: PBout(5)=0;key_1=3;i--;break; 
				//case 0x81: PEout(5)=1;key_1=A;i--;break; 
				case 0x12: PBout(5)=1;key_1=4;i--;break; 
				case 0x22: PEout(5)=0;key_1=5;i--;break; 
				case 0x42: PBout(5)=0;key_1=6;i--;break; 
				//case 0x82: PEout(5)=1;key_1=B;i--;break;
				case 0x14: PBout(5)=1;key_1=7;i--;break;
				case 0x24: PEout(5)=0;key_1=8;i--;break;
                case 0x44: PBout(5)=0;key_1=9;i--;break;	
		        //case 0x84: PEout(5)=1;key_1=C;i--;break;				
				case 0x18: PBout(5)=1;key_1=10;i--;break;
				case 0x28: PEout(5)=0;key_1=0;i--;break;
                case 0x48: PBout(5)=0;key_1=11;i--;break;	
		        //case 0x88: PEout(5)=1;key_1=D;i--;break;		
				default:break;
			}
		}
	}
	return key_1;
	
}
u16 GET_NUM(void)
{
	u8  key_num=0;
	u16 num=0;
	while(1)
	{
		key_num=keychuli();	
		if(key_num)
		{		
			if(key_num>0&&key_num<10&&num<99)//‘1-9’键(限制输入3位数)
				num =num*10+key_num;		
			if(key_num==10)num =num/10;//‘Del’键			
			if(key_num==0&&num<99)num =num*10;//‘0’键
			if(key_num==11)return num;  //‘Enter’键
		}
	}	
}


