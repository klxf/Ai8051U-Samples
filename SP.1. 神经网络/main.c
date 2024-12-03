#include <Ai8051U.h>
#include <delay.h>
#include <oled.h>
#include <bmp.h>
#include <nn.h>

unsigned char input[][64] = {{0}};
float output[][10] = {{0}};
unsigned char result = 0;
unsigned char cursor = 0;

sbit W = P1^0;  // 上移光标
sbit S = P1^1;  // 下移光标
sbit A = P1^2;  // 左移光标
sbit D = P1^3;  // 右移光标

sbit R = P4^7;  // 绘制

void main()
{
	unsigned char i;
	unsigned char x1, x2, y1, y2;
	P4M0 = 0x00; P4M1 = 0x00;
	P2M0 = 0xff; P2M1 = 0x00;
	P1M0 = 0x00; P1M1 = 0x00;
	
	P17 = 0;
	
	IE0 = 0;  // 外部中断0标志位
	EX0 = 1;  // 外部中断0使能
	IT0 = 1;  // 外部中断0下降沿触发
	EA  = 1;  // 总中断允许
	
	OLED_Init();
	OLED_Clear();
	
	OLED_ColorTurn(0);
  OLED_DisplayTurn(0);
	
	OLED_ShowPicture(0, 0, 128, 64, BMP1, 1);
	OLED_Refresh();
	delay_ms(1000);
	
	while(1)
	{
		OLED_Clear();
		OLED_DrawRectangle(4, 4, 61, 61, 0);
		for(i = 0; i < 64; i++)
		{
			if(input[0][i])
			{
				x1 = i % 8 * 7 + 5;
				y1 = i / 8 * 7 + 5;
				x2 = x1 + 6;
				y2 = y1 + 6;
				OLED_DrawRectangle(x1, y1, x2, y2, 1);
			}
		}
		OLED_Refresh();
		
		x1 = cursor % 8 * 7 + 5;
		y1 = cursor / 8 * 7 + 5;
		x2 = x1 + 6;
		y2 = y1 + 6;
		OLED_DrawRectangle(x1, y1, x2, y2, 0);
		OLED_Refresh();
		
		OLED_ShowChinese(68,16,0,16,1);
		OLED_ShowChinese(84,16,1,16,1);
		OLED_ShowChinese(68,32,2,16,1);
		OLED_ShowChinese(84,32,3,16,1);
		OLED_ShowNum(106, 24, result, 1, 16, 0);
		OLED_Refresh();
		
		if(W == 0)
		{
			if(cursor >= 8)
				cursor -= 8;
			else
				cursor += 56;
			while(!W);
		}
		if(S == 0)
		{
			if(cursor <= 56)
				cursor += 8;
			else
				cursor -= 56;
			while(!S);
		}
		if(A == 0)
		{
			if(cursor % 8 != 0)
				cursor--;
			else
				cursor += 7;
			while(!A);
		}
		if(D == 0)
		{
			if(cursor % 8 != 7)
				cursor++;
			else
				cursor -= 7;
			while(!D);
		}
		if(R == 0)
		{
			input[0][cursor] = !input[0][cursor];
			while(!R);
		}
		delay_ms(100);
	}
}

void INT0_int(void) interrupt 0
{
	P17 = 1;
	forward(input, output);
	result = findResult(output);
	P17 = 0;
}
