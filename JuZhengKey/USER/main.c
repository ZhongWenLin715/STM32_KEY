///////////////////////////////////////////////////////////////////////////////
//����ƽ̨  STM32F103ZET6  ս��V3
//PF0-3�����ó��������  ��Ϊ4x4���̵���
//PF4-7�����ó���������  ��Ϊ4x4���̵���
//�������������LED������������   
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

