#include <AI8051U.H>

#ifndef __MINIMAX_H
#define __MINIMAX_H

#define INFINITY 32767
#define BOARD_SIZE 3

// 拷贝棋盘状态
void copy_board(char board[BOARD_SIZE][BOARD_SIZE], char new_board[BOARD_SIZE][BOARD_SIZE]);
// 检查玩家是否获胜
unsigned char is_winner(char board[BOARD_SIZE][BOARD_SIZE], char player);
// 检查是否平局
unsigned char is_draw(char board[BOARD_SIZE][BOARD_SIZE]);
// 检查移动是否有效
unsigned char is_valid_move(unsigned char board[BOARD_SIZE][BOARD_SIZE], unsigned char move);
// 极小化极大算法
int minimax(char board[BOARD_SIZE][BOARD_SIZE], int depth, int is_maximizing, int alpha, int beta) reentrant;
// 寻找最优移动
int find_best_move(char board[BOARD_SIZE][BOARD_SIZE]);

#endif
