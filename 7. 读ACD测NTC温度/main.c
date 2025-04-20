#include <Ai8051U.h>
#include <delay.h>
#include <oled.h>
#include <bmp.h>
#include <math.h>
#include <stdio.h>

// NTC, 10K @25℃, 3950
float Get_Temperature(int adc_value)
{
	float Rt = 10 * 0.0008 * (4096 - adc_value) / (0.0008 * adc_value);
	float R0 = 10.0;
	float Bn = 3950;
	float T0 = 298.15;
	
	return (Bn * T0) / (T0 * log(Rt/R0) + Bn);
}

int Get_ADC12bitResult(unsigned char channel)  // channel = 0~15
{
	ADC_RES  = 0;
	ADC_RESL = 0;

	ADC_CONTR = (ADC_CONTR & 0xf0) | channel;  // 设置ADC转换通道
	ADC_START = 1;                             // 启动ADC转换

	while(ADC_FLAG == 0);                      // 等待ADC完成
	ADC_FLAG = 0;                              // 清除ADC结束标志
	return (((u16)ADC_RES << 8) | ADC_RESL);
}

void main()
{
	int adc_value;
	unsigned char tempString[20] = "";
	float T;
	
	P2M0 = 0x00; P2M1 = 0x00;
	P1M0 &= ~0x8f; P1M1 = (P1M1 & ~0x0f) | 0x80;
	ADCTIM = 0x3f;		  //设置 ADC 内部时序，ADC采样时间建议设最大值
	ADCCFG = 0x2f;		  //设置 ADC 时钟为系统时钟/2/16/16
	ADC_CONTR = 0x80;
	
	
	OLED_Init();
	OLED_Clear();
	
	OLED_ColorTurn(0);
  OLED_DisplayTurn(0);
	
	OLED_Clear();
	
	while(1)
	{
		adc_value = Get_ADC12bitResult(7);
		
		T = Get_Temperature(adc_value);
		
		sprintf(tempString, "ADC Value: %4d", adc_value);
		OLED_ShowString(6, 6, tempString, 12, 1);
		
		OLED_ShowString(6, 20, "Temperature:", 12, 1);
		
		sprintf(tempString, "%5.1f", T - 273.15);
		OLED_ShowString(18, 34, tempString, 24, 1);
		
		OLED_ShowChinese(80, 36, 0, 24, 1);
		
		OLED_Refresh();
		
		delay_ms(500);
	}
}
