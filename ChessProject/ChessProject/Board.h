#pragma once

#include <iostream>
#include <string>
#include "Tool.h"
#include "Rook.h"
#include "King.h"
#include "Empty.h"

#define ROWS 8
#define COLUMNS 8

class Board 
{
public:

	// Constructor
	Board(std::string _board);
	Board();
	//methods
	void print_board();
	void move_piece(std::string pos, Tool t);
	Tool get_tool(std::string pos);
	Tool get_king(bool color);

protected:
	//fields
	 Tool _board[ROWS][COLUMNS];
};