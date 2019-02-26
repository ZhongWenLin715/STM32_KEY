#include "delay.h"
#include "key.h"
#include "sys.h"
#include "myiic.h"
#include "oled.h"
 

int main(void)
{
    u8 key;
    u8 *str=0;
	delay_init();			     
	KEY_Init();
    IIC_Init();
    OLED_Init();    					     
	while(1)
	{  
		key=keyscan();
        if(key)
        {            
			switch(key)
			{
				case 1:str="0";OLED_CLS();OLED_P8x16Str(0,4,str);break;
                case 2:str="1";OLED_CLS();OLED_P8x16Str(0,4,str);break;
                case 3:str="2";OLED_CLS();OLED_P8x16Str(0,4,str);break;
                case 4:str="3";OLED_CLS();OLED_P8x16Str(0,4,str);break;
                case 5:str="4";OLED_CLS();OLED_P8x16Str(0,4,str);break;	
                case 6:str="5";OLED_CLS();OLED_P8x16Str(0,4,str);break;	
                case 7:str="6";OLED_CLS();OLED_P8x16Str(0,4,str);break;	
                case 8:str="7";OLED_CLS();OLED_P8x16Str(0,4,str);break;
                case 9:str="8";OLED_CLS();OLED_P8x16Str(0,4,str);break;
                case 10:str="9";OLED_CLS();OLED_P8x16Str(0,4,str);break;
                case 11:str="10";OLED_CLS();OLED_P8x16Str(0,4,str);break;
                case 12:str="11";OLED_CLS();OLED_P8x16Str(0,4,str);break;	
                case 13:str="12";OLED_CLS();OLED_P8x16Str(0,4,str);break;
                case 14:str="13";OLED_CLS();OLED_P8x16Str(0,4,str);break;
                case 15:str="14";OLED_CLS();OLED_P8x16Str(0,4,str);break;	
                case 16:str="15";OLED_CLS();OLED_P8x16Str(0,4,str);break;	
                default:break;						 
			}
        }else {delay_ms(10);}
	}	 
}

