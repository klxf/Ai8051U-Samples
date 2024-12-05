#include <minimax.h>

// 复制棋盘状态
void copy_board(char board[BOARD_SIZE][BOARD_SIZE], char new_board[BOARD_SIZE][BOARD_SIZE])
{
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			new_board[i][j] = board[i][j];
		}
	}
}

// 检查玩家是否获胜
unsigned char is_winner(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
	int i;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		// Check rows
		if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return 1;
		// Check columns
		if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return 1;
	}
	// Check diagonals
	if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return 1;
	if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return 1;
	return 0;
}

// 检查是否平局
unsigned char is_draw(char board[BOARD_SIZE][BOARD_SIZE])
{
	int i,j;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == ' ') return 0;
		}
	}
	return 1;
}

// 检查移动是否有效
unsigned char is_valid_move(unsigned char board[BOARD_SIZE][BOARD_SIZE], unsigned char move)
{
	unsigned char i = move / 3;
	unsigned char j = move % 3;
	if(board[i][j] != ' ')
		return 0;
	return 1;
}

// 极小化极大算法
int minimax(char board[BOARD_SIZE][BOARD_SIZE], int depth, int is_maximizing, int alpha, int beta) reentrant
{
	int i, j, score, best_score;
	unsigned char new_board[BOARD_SIZE][BOARD_SIZE];
	if (is_winner(board, 'X')) return -1;
	if (is_winner(board, 'O')) return 1;
	if (is_draw(board)) return 0;

	if (is_maximizing)
	{
		best_score = -INFINITY;
		for (i = 0; i < BOARD_SIZE; i++)
		{
			for (j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j] == ' ')
				{
					board[i][j] = 'O';
					copy_board(board, new_board);
					score = minimax(new_board, depth + 1, 0, alpha, beta);
					board[i][j] = ' ';
					best_score = (score > best_score) ? score : best_score;
					if (score > alpha) alpha = score;
					if (alpha >= beta) break;
				}
			}
			if (alpha >= beta) break;
		}
		return best_score;
	}
	else
	{
		best_score = INFINITY;
		for (i = 0; i < BOARD_SIZE; i++)
		{
			for (j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j] == ' ')
				{
					board[i][j] = 'X';
					copy_board(board, new_board);
					score = minimax(new_board, depth + 1, 1, alpha, beta);
					board[i][j] = ' ';
					best_score = (score < best_score) ? score : best_score;
					if (score < beta) beta = score;
					if (alpha >= beta) break;
				}
			}
			if (alpha >= beta) break;
		}
		return best_score;
	}
}

// 寻找最优移动
int find_best_move(char board[BOARD_SIZE][BOARD_SIZE]) {
	int best_score = -INFINITY;
	int best_move, score;
	int i, j;
	int alpha = -INFINITY;
	int beta = INFINITY;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = 'O';
				score = minimax(board, 0, 0, alpha, beta);
				board[i][j] = ' ';
				if (score > best_score)
				{
					best_score = score;
					best_move = i * 3 + j;
					alpha = (best_score > alpha) ? best_score : alpha;
				}
			}
		}
	}
	return best_move;
}
