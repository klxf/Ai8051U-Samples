#include <Ai8051U.h>

// 默认频率为：11.0592MHz
#define MAIN_Fosc 11059200UL

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
	P0M0 = 0xff; P0M1 = 0x00;  // P0口推挽输出模式
	
	while(1)
	{
		P0 = 0xfe;
		delay_ms(500);
		P0 = 0xfd;
		delay_ms(500);
		P0 = 0xfb;
		delay_ms(500);
		P0 = 0xf7;
		delay_ms(500);
		P0 = 0xfb;
		delay_ms(500);
		P0 = 0xfd;
		delay_ms(500);
	}
}
