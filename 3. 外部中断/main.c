#include <Ai8051U.h>

// 默认频率为：11.0592MHz
#define MAIN_Fosc 11059200UL

unsigned char count = 0;

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
	
	IE0 = 0;                   // 外部中断0标志位
	EX0 = 1;                   // 外部中断0使能
	IT0 = 1;                   // 外部中断0下降沿触发
	EA = 1;                    // 总中断允许

	
	while(1)
	{
		delay_ms(1);
		P0 = ~count;
	}
}


void INT0_int(void) interrupt 0
{
	delay_ms(15);
	if(P32 == 0)
		count++;
}
