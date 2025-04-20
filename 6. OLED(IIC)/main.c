#include <Ai8051U.h>
#include <oled.h>
#include <delay.h>
#include <bmp.h>

void main()
{
	unsigned char i = ' ';
	
	P2M0 = 0x00; P2M1 = 0x00;
	
	OLED_Init();
	OLED_Clear();
	OLED_DrawBMP(0, 0, 128, 6, BMP1);
	delay_ms(2000);
	
	OLED_Clear();
	
	while(1)
	{
		OLED_ShowChar(0, 0, i, 16);
		OLED_ShowNum(100, 0, i, 3, 16);
		i++;
		if(i>'~') i=' ';
		
		OLED_ShowString(32, 1, "Ai8051U", 16);
		
		OLED_ShowChinese(10, 4, 0);  // 国
		OLED_ShowChinese(26, 4, 1);  // 之
		OLED_ShowChinese(42, 4, 2);  // 重
		OLED_ShowChinese(58, 4, 3);  // 器
		
		OLED_ShowChinese(34, 6, 4);  // 国
		OLED_ShowChinese(48, 6, 0);  // 之
		OLED_ShowChinese(64, 6, 5);  // 脊
		OLED_ShowChinese(80, 6, 6);  // 梁
		
		
		delay_ms(500);
	}
}
