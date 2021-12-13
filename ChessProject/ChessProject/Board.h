#pragma once

#include <iostream>
#include <string>
#include "Game.h"
#include "Tool.h"

#define ROWS 8
#define COLUMNS 8

class Board 
{
public:

	// Constructor
	Board(std::string _board);
	Board();
	void print_board();
	void move_piece(std::string pos, Tool& t);
	//Board get_board();

private:
	//fields
	 Tool _board[ROWS][COLUMNS];
};