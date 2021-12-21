#pragma once

#include <iostream>
#include <string>
#include "Board.h"
#include <algorithm>
//#include <tool.h>


using std::cout;
using std::endl;
using std::string;

class Game
{
public:

	// Constructor
	Game(std::string _board_string);
	
	//getters
	bool get_black_check();
	bool get_white_check();
	int get_turn();
	Board get_board();

	//setters
	void set_black_check(const bool b);
	void set_white_check(const bool w);
	void set_turn(const int t);

	/*
	Functions
	*/
	int check_tool(Tool t, string adress_dst, string adress_src, char king_check, Board &b);
	std::vector<string> change_pawn_vector(Pawn p, Board b);
	std::vector<string> change_vector(std::vector<std::string> valid_moves, Tool t, Board b);
	std::vector<string> get_enemy_valid_moves(Board b);
	int check_check(std::vector<std::string> valid_moves, char king_check, Board b);
	


private:
	//fields
	bool _is_check_white;
	bool _is_check_black;
	bool _turn;
	Board _board;
};