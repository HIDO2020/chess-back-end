#include "Board.h"
#include "Game.h"
#include <iostream>


Board::Board(std::string _board) 
{
	char letterColumn = ' ';
	std::string pos = "";
	int i = 0, j = 0, count = 63;
	for (i = ROWS - 1; i >= 0; i--)
	{
		for (j = COLUMNS - 1; j >= 0; j--)
		{
			letterColumn = j + 30;
			pos[0] = letterColumn;
			pos[1] = i;
			this->_board[i][j] = Tool(pos, _board[count]);
			count--;
		}
	}
}

Board::Board() 
{
	int i = 0, j = 0;
	for (i = ROWS - 1; i >= 0; i--)
	{
		for (j = COLUMNS - 1; j >= 0; j--)
		{
			this->_board[i][j] = Tool();
		}
	}
}

void Board::print_board()
{
	int i = 0, j = 0;
	for (i = ROWS - 1; i >= 0; i--)
	{
		for (j = COLUMNS - 1; j >= 0; j--)
		{
			std::cout << this->_board[i][j].get_type();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::move_piece(std::string pos, Tool& t)
{
	int numColumn = pos[0] - 30;
	int numRow = pos[1];
	this->_board[numRow][numColumn] = t;
}

//Board Board::get_board()
//{
//	return this->_board;
//}
