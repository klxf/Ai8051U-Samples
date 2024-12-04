#include <Ai8051U.h>
#include <delay.h>
#include <oled.h>
#include <bmp.h>
#include <minimax.h>
#include <stdio.h>

sbit W = P1^0;  // 上移光标
sbit S = P1^1;  // 下移光标
sbit A = P1^2;  // 左移光标
sbit D = P1^3;  // 右移光标

sbit R = P4^7;  // 确认

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
	int i, j;
	unsigned char cursor = 0;
	unsigned char bestStr[12];
	unsigned char board[BOARD_SIZE][BOARD_SIZE] = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '}
	};
	int best_move = -1;
	unsigned char current_player, first_hand;
	unsigned char winner = 0, draw = 0;
	
	P4M0 = 0x00; P4M1 = 0x00;
	P2M0 = 0x00; P2M1 = 0x00;
	P1M0 &= ~0x8f; P1M1 = (P1M1 & ~0x0f) | 0x80;
	ADCTIM = 0x3f;		  //设置 ADC 内部时序，ADC采样时间建议设最大值
	ADCCFG = 0x2f;		  //设置 ADC 时钟为系统时钟/2/16/16
	ADC_CONTR = 0x80;
	
	OLED_Init();
	OLED_Clear();
	
	OLED_ColorTurn(0);
  OLED_DisplayTurn(0);
	
	OLED_ShowPicture(0, 0, 128, 64, BMP1, 1);
	OLED_Refresh();
	delay_ms(1000);
	OLED_Clear();
	
	// 根据ADC采集到的数据随机决定先手
	first_hand = current_player = Get_ADC12bitResult(7) % 2 == 0 ? 'X' : 'O';
	
	while(1)
	{
		OLED_Clear();
		
		// 画棋盘
		OLED_DrawRectangle(8, 8, 59, 59, 0);
		OLED_DrawLine(8, 25, 59, 25, 1);
		OLED_DrawLine(8, 42, 59, 42, 1);
		OLED_DrawLine(25, 8, 25, 59, 1);
		OLED_DrawLine(42, 8, 42, 59, 1);
		
		// 画棋子
		for(i = 0; i < BOARD_SIZE; i++)
		{
			for(j = 0; j < BOARD_SIZE; j++)
			{
				if(board[i][j] == 'X')
					OLED_ShowChinese(16*j+9+j,16*i+9+i,7,16,1);
				else if(board[i][j] == 'O')
					OLED_ShowChinese(16*j+9+j,16*i+9+i,8,16,1);
			}
		}
		
		OLED_Refresh();
		
		// 判决输赢
		if(winner || draw)
		{
			best_move = -1;
			if(draw)
			{
				draw = 0;
				OLED_ShowChinese(62,26,13,16,1);
				OLED_ShowChinese(78,26,14,16,1);
				OLED_ShowChinese(94,26,15,16,1);
				OLED_ShowChinese(110,26,16,16,1);
				OLED_Refresh();
			}
			else
			{
				winner = 0;
				OLED_ShowChinese(68,26,0,16,1);
				if(winner == 'X')
					OLED_ShowChinese(84,26,18,16,1);
				else
					OLED_ShowChinese(84,26,17,16,1);
				OLED_ShowChinese(100,26,3,16,1);
				OLED_Refresh();
			}
			while(1)
			{
				if(R == 0)
				{
					for(i = 0; i < BOARD_SIZE; i++)
						for(j = 0; j < BOARD_SIZE; j++)
							board[i][j] = ' ';
					first_hand = current_player = Get_ADC12bitResult(7) % 2 == 0 ? 'X' : 'O';
					while(!R);
					break;
				}
			}
		}
		else
		{
			if(is_winner(board, 'O')) winner = 'O';
			else if(is_winner(board, 'X')) winner = 'X';
			else if(is_draw(board)) draw = 1;
		}
		
		// 显示最佳移动
		sprintf(bestStr, "BestMove:%d", best_move);
		OLED_ShowString(62,30,bestStr,8,1);
		//OLED_ShowNum(96, 26, bestStr, 1, 16, 1);
		//OLED_ShowNum(64, 26, cursor, 1, 16, 1);
		
		// 显示玩家先后手
		OLED_ShowChinese(60,108,0,16,1);
		OLED_ShowChinese(76,108,1,16,1);
		if(first_hand == 'X') OLED_ShowChinese(92,108,11,16,1);
		else OLED_ShowChinese(92,108,9,16,1);
		OLED_ShowChinese(108,108,10,16,1);
		
		OLED_Refresh();
		
		if(current_player == 'X')
		{
			// 若是玩家局：在棋盘显示光标
			OLED_ShowChinese(62,8,2,16,1);
			OLED_ShowChinese(78,8,0,16,1);
			OLED_ShowChinese(94,8,3,16,1);
			OLED_ShowChinese(110,8,12,16,1);
			OLED_Refresh();
			i = cursor / 3;
			j = cursor % 3;
			OLED_DrawRectangle(16*j+9+j,16*i+9+i,16*j+24+j,16*i+24+i, 0);
		}
		else
		{
			// 若是机器局：以当前棋局进行决策
			OLED_ShowChinese(62,8,4,16,1);
			OLED_ShowChinese(78,8,5,16,1);
			OLED_ShowChinese(94,8,6,16,1);
			OLED_ShowChinese(110,8,12,16,1);
			OLED_Refresh();
			//copy_board(board, board_copy);
			best_move = find_best_move(board);
			i = best_move / 3;
			j = best_move % 3;
			board[i][j] = 'O';
			current_player = 'X';
		}
		
		OLED_Refresh();
		
		// 按键事件
		if(W == 0)
		{
			if(cursor >= 3)
				cursor -= 3;
			else
				cursor += 6;
			while(!W);
		}
		if(S == 0)
		{
			if(cursor <= 5)
				cursor += 3;
			else
				cursor -= 6;
			while(!S);
		}
		if(A == 0)
		{
			if(cursor % 3 != 0)
				cursor--;
			else
				cursor += 2;
			while(!A);
		}
		if(D == 0)
		{
			if(cursor % 3 != 2)
				cursor++;
			else
				cursor -= 2;
			while(!D);
		}
		if(R == 0)
		{
			if(current_player == 'X' && is_valid_move(board, cursor))
			{
				i = cursor / 3;
				j = cursor % 3;
				board[i][j] = 'X';
				current_player = 'O';
			}
			while(!R);
		}
		
		delay_ms(100);
	}
}