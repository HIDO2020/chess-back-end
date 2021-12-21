#include "Board.h"
#include <iostream>


Board::Board(std::string _board)
{
	char letterColumn = ' ';
	std::string pos = "ab";            //f3 for example
	int i = 0, j = 0;
	int count = 63;            //the amount of chars in the string from 0 - 63
	for (i = 0; i < ROWS; i++)
	{
		for (j = COLUMNS - 1; j >= 0; j--)
		{
			letterColumn = j + 97;        //asci from 1 --> a
			pos[0] = letterColumn;
			pos[1] = i + 49;
			//add to board by each peace
			if (_board[count] == 'r' || _board[count] == 'R')		
			{
				this->_board[i][j] = Rook(pos, _board[count]);
			}
			else if (_board[count] == 'k' || _board[count] == 'K')
			{
				this->_board[i][j] = King(pos, _board[count]);
			}
			else if (_board[count] == 'q' || _board[count] == 'Q')
			{
				this->_board[i][j] = Queen(pos, _board[count]);
			}
			else if (_board[count] == 'b' || _board[count] == 'B')
			{
				this->_board[i][j] = Bishop(pos, _board[count]);
			}
			else if (_board[count] == 'n' || _board[count] == 'N')
			{
				this->_board[i][j] = Knight(pos, _board[count]);
			}
			else if (_board[count] == 'p' || _board[count] == 'P')
			{
				this->_board[i][j] = Pawn(pos, _board[count]);
			}
			else
			{
				this->_board[i][j] = Empty(pos, _board[count]);
			}
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
void Board::move_piece(std::string pos, Tool t)
{
	int numColumn = 0, numRow = 0;
	//adds # instead
	numColumn = t.get_pos()[0] - 97;		//asci from 1 --> 0(int)		
	numRow = t.get_pos()[1] - 49;				
	this->_board[numRow][numColumn].set_type('#');

	numColumn = pos[0] - 97;    //asci from a --> 1(int)
	numRow = pos[1] - 49;		//asci from 1 --> 1(int)
	this->_board[numRow][numColumn].set_pos(pos);
	this->_board[numRow][numColumn].set_type(t.get_type());
	this->_board[numRow][numColumn] = t;
}

/*
get the tool from board by position
*/
Tool Board::get_tool(std::string pos)
{
	int numColumn = 0, numRow = 0;
	//check out of range 
	if ((pos[0] > 104 || pos[0] < 97) || (pos[1] < 49 || pos[1] > 56))
	{
		Tool invalid_tool(pos, '#');
		return invalid_tool;
	}

	numColumn = pos[0] - 97;    //asci from a --> 1(int)
	numRow = pos[1] - 49;		//asci from 1 --> 1(int)
	this->_board[numRow][numColumn].set_pos(pos);
	return this->_board[numRow][numColumn];
}

/*
get the position of the king by color
*/
Tool Board::get_king(bool color)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (this->_board[i][j].get_color() == WHITE && this->_board[i][j].get_type() == 'k' && this->_board[i][j].get_color() == color)
			{
				return this->_board[i][j];
			}
			else if (this->_board[i][j].get_color() == BLACK && this->_board[i][j].get_type() == 'K' && this->_board[i][j].get_color() == color)
			{
				return this->_board[i][j];
			}
		}
	}
}
