///////////////////////////////////////////////////////////////////////////////
//开发平台  STM32F103ZET6  战舰V3
//PF0-3口配置成推挽输出  作为4x4键盘的行
//PF4-7口配置成上拉输入  作为4x4键盘的列
//这个程序用两个LED灯来反馈现象   
////////////////////////////////////////////////////////////////////////////////
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "beep.h"
#include "usart.h" 



int main(void)
{
	delay_init();	    	 
 	LED_Init();			     
	KEY_Init();
    uart_init(115200);    
	LED0=0;
        
	while(1)
	{  
        uint8_t mottor;
       mottor=GET_NUM();
       printf("%d",mottor);
	}	 
}

