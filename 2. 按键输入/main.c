#include <Ai8051U.h>

// 默认频率为：11.0592MHz
#define MAIN_Fosc 11059200UL

sbit SW1 = P1^0;
sbit SW2 = P1^1;
sbit SW3 = P1^2;
sbit SW4 = P1^3;

void delay_ms(unsigned int ms)
{
	unsigned int i;
	do{
		i = MAIN_Fosc / 10000;
		while(--i);
	}while(--ms);
}

void main()
{
	P0M0 = 0x00; P0M1 = 0x00;  // P0口准双向口模式
	P1M0 = 0x00; P1M1 = 0x00;  // P1口准双向口模式
	
	while(1)
	{
		if(SW1 == 0)             // LED1~LED4依次点亮
		{
			delay_ms(10);
			if(SW1 == 0)
			{
				P0 = 0xfe;
				delay_ms(500);
				P0 = 0xfd;
				delay_ms(500);
				P0 = 0xfb;
				delay_ms(500);
				P0 = 0xf7;
				delay_ms(500);
				P0 = 0xff;
				delay_ms(500);
			}
		}
		
		if(SW2 == 0)             // LED4~LED1依次点亮
		{
			delay_ms(10);
			if(SW2 == 0)
			{
				P0 = 0xf7;
				delay_ms(500);
				P0 = 0xfb;
				delay_ms(500);
				P0 = 0xfd;
				delay_ms(500);
				P0 = 0xfe;
				delay_ms(500);
				P0 = 0xff;
				delay_ms(500);
			}
		}
		
		if(SW3 == 0)             // 奇偶交替闪烁
		{
			delay_ms(10);
			if(SW3 == 0)
			{
				P0 = 0xfa;
				delay_ms(500);
				P0 = 0xf5;
				delay_ms(500);
				P0 = 0xfa;
				delay_ms(500);
				P0 = 0xf5;
				delay_ms(500);
				P0 = 0xff;
			}
		}
		
		if(SW4 == 0)             // LED1~LED4同时闪烁
		{
			delay_ms(10);
			if(SW4 == 0)
			{
				P0 = 0xf0;
				delay_ms(500);
				P0 = 0xff;
				delay_ms(500);
				P0 = 0xf0;
				delay_ms(500);
				P0 = 0xff;
				delay_ms(500);
			}
		}
	}
}
