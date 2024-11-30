#include <Ai8051U.h>

// 默认频率为：11.0592MHz
#define MAIN_Fosc 11059200UL
// 定时 1000us
#define TIME_us   1000

// 计算定时器初值
#define TIMER0_INIT_VALUE (65536 - (TIME_us * (MAIN_Fosc / 1000000)) / 12)

unsigned int time = 0;

void main() {
	P0M0 = 0xff; P0M1 = 0x00;       // P0口推挽输出模式
	P0 = 0x00;
	
	TMOD |= 0x01;                   // 定时器0为16位定时器
	TH0 = TIMER0_INIT_VALUE / 256;
	TL0 = TIMER0_INIT_VALUE % 256;
	ET0 = 1;                        // 定时器0使能
	EA  = 1;                        // 总中断允许
	TR0 = 1;                        // 启动定时器0

	while(1) {
		// 主循环空闲，等待中断
	}
}

void Timer0(void) interrupt 1 {
	// 重新装载TH0和TL0的值
	TH0 = TIMER0_INIT_VALUE / 256;
	TL0 = TIMER0_INIT_VALUE % 256;

	time++;
	
	if(time >= 1000) {
		P0 = ~P0;  // 每1s翻转P0口状态
		time = 0;
	}
}