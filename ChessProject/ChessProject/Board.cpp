#include "Board.h"
#include "Game.h"
#include <iostream>


Board::Board(std::string _board) 
{
	char letterColumn = ' ';
	std::string pos = "ab";			//f3 for example
	int i = 0, j = 0, count = 63;
	for (i = 0 ; i < ROWS; i++)
	{
		for (j = COLUMNS -1 ; j >= 0; j--)
		{
			letterColumn = j + 48;		//asci from 1 --> a
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
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLUMNS; j++)
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
		for (j = 0; j < COLUMNS; j++)
		{
			std::cout << this->_board[i][j].get_type();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::move_piece(std::string pos, Tool& t)
{
	int numColumn = 0, numRow = 0;
	//adds # instead
	numColumn = t.get_pos()[0];
	numRow = t.get_pos()[1];
	this->_board[numRow][numColumn] = Tool();

	numColumn = pos[0] - 96;    //asci from a --> 1(int)
	numRow = pos[1];
	this->_board[numRow][numColumn] = t;
}

Tool Board::get_tool(std::string pos)
{
	int numColumn = 0, numRow = 0;

	numColumn = pos[0] - 97;    //asci from a --> 1(int)
	numRow = pos[1] - 49;		//asci from 1 --> 1(int)

	return this->_board[numRow][numColumn];
}


