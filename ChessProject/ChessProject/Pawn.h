#pragma once
#include "Tool.h"
#include <vector>
//#include <iostream>
#define POSSIBLE_MOVES 2
#define ROWS 8
#define COLUMNS 8 

class Pawn : public Tool
{
public:
    Pawn(std::string pos, char type);
    int move(std::string _dst, Tool t, bool turn);
    void set_valid_moves(std::string pos);
    //setters
    void setter_valid_moves(std::vector<std::string> valid);
    void set_first_move();
    ////getter
    std::vector<std::string> get_valid_moves();
    bool get_first_move();

protected:
    std::vector<std::string> valid_moves;
    bool first_move;
};