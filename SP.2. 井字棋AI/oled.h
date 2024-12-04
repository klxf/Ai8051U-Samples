#ifndef __OLED_H
#define __OLED_H 

#include "Ai8051U.h"
#include "stdlib.h"	

#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned int

sbit OLED_SCL = P2^4;
sbit OLED_SDA = P2^3;
sbit OLED_RES = P2^5;
sbit OLED_DC  = P2^6;
sbit OLED_CS  = P2^7;

#define OLED_SCL_Clr() OLED_SCL = 0
#define OLED_SCL_Set() OLED_SCL = 1

#define OLED_SDA_Clr() OLED_SDA = 0
#define OLED_SDA_Set() OLED_SDA = 1

#define OLED_RES_Clr() OLED_RES = 0
#define OLED_RES_Set() OLED_RES = 1

#define OLED_DC_Clr()  OLED_DC  = 0
#define OLED_DC_Set()  OLED_DC  = 1
 		     
#define OLED_CS_Clr()  OLED_CS  = 0
#define OLED_CS_Set()  OLED_CS  = 1


#define OLED_CMD  0
#define OLED_DATA 1

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawRectangle(u8 x1, u8 y1, u8 x2, u8 y2, u8 t);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_Init(void);

#endif
