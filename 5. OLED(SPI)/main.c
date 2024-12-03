#include <Ai8051U.h>
#include <delay.h>
#include <oled.h>
#include <bmp.h>

void main()
{
	unsigned char i = ' ';
	
	P2M0 = 0x00; P2M1 = 0x00;
	
	OLED_Init();
	OLED_Clear();
	
	OLED_ColorTurn(0);
  OLED_DisplayTurn(0);
	
	OLED_ShowPicture(0, 0, 128, 64, BMP1, 1);
	OLED_Refresh();
	delay_ms(2000);
	
	OLED_Clear();
	
	while(1)
	{
		OLED_ShowChar(100, 10, i, 16, 1);
		OLED_ShowNum(92, 26, i, 3, 16, 1);
		i++;
		if(i>'~') i=' ';
		
		OLED_ShowString(36, 6, "Ai8051U", 16, i%2);
		
		OLED_ShowChinese(10, 26, 0, 16, 1);  // 大
		OLED_ShowChinese(26, 26, 1, 16, 1);  // 国
		OLED_ShowChinese(42, 26, 2, 16, 1);  // 重
		OLED_ShowChinese(58, 26, 3, 16, 1);  // 器
		
		OLED_ShowChinese(18, 42, 4, 16, 1);  // 国
		OLED_ShowChinese(34, 42, 0, 16, 1);  // 之
		OLED_ShowChinese(50, 42, 5, 16, 1);  // 脊
		OLED_ShowChinese(66, 42, 6, 16, 1);  // 梁
		
		OLED_Refresh();
		
		delay_ms(500);
	}
}