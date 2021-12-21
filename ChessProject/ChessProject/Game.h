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
	void add_turn(const int t);

	/*
	Functions
	*/
	int check_tool(Tool t, Board& b, Game& g, string adress_dst, string adress_src, bool turn, char king_check);
	static std::vector<string> change_pawn_vector(Pawn p, Board b);
	static std::vector<string> change_vector(std::vector<string> rook_valid_moves, Board b, Tool t);
	static std::vector<string> get_enemy_valid_moves(bool turn, Board b);
	static int check_check(std::vector<string> valid_moves, char king_check, Board b, bool turn, Game& g);
	


private:
	//fields
	bool _is_check_white;
	bool _is_check_black;
	int _turn = 0;
	Board _board;
};