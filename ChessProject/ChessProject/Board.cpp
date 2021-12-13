#include "Board.h"
#include <iostream>


void Board::print_board()
{
	int i = 0, j = 0;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			std::cout << this->_board[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
