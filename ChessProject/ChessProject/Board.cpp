#include "Board.h"
#include <iostream>


Board::Board(std::string _board) 
{
	char letterColumn = ' ';
	std::string pos = "ab";			//f3 for example
	int i = 0, j = 0;
	int count = 63;			//the amount of chars in the string from 0 - 63
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

/*
prints the current board
*/
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

/*
function thats changing the view of the board and moving pieces int the 2d array
also swapping them with '#'
*/
void Board::move_piece(std::string pos, Tool& t)
{
	int numColumn = 0, numRow = 0;
	//adds # instead
	numColumn = t.get_pos()[0] - 97;		//asci from 1 --> 0(int)		
	numRow = t.get_pos()[1] - 49;				
	this->_board[numRow][numColumn].set_type('#');

	numColumn = pos[0] - 97;    //asci from a --> 1(int)
	numRow = pos[1] - 49;		//asci from 1 --> 1(int)
	this->_board[numRow][numColumn] = t;
}

Tool Board::get_tool(std::string pos)
{
	int numColumn = 0, numRow = 0;

	numColumn = pos[0] - 97;    //asci from a --> 1(int)
	numRow = pos[1] - 49;		//asci from 1 --> 1(int)
	this->_board[numRow][numColumn].set_pos(pos);
	return this->_board[numRow][numColumn];
}


