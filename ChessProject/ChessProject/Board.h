#pragma once

#include <iostream>
#include <string>
#include "Tool.h"
#include "Rook.h"
#include "King.h"
#include "Empty.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Pawn.h"

#define ASCII_1 49
#define ASCII_a 97
#define ASCII_h 104
#define ASCII_8 56
#define ASCII_7 55

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