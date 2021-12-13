#pragma once

#include <iostream>
#include <string>
#include "Board.h"
//#include <tool.h>

class Game
{
public:

	// Constructor
	Game(std::string _board_string);
	
	//getters
	bool get_black_check();
	bool get_white_check();
	bool get_turn();
	Board get_board();

	//setters
	void set_black_check(const bool b);
	void set_white_check(const bool w);
	void set_turn(const bool t);

private:
	//fields
	bool _is_check_white;
	bool _is_check_black;
	bool _turn;
	Board _board;
};