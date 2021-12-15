#pragma once
#include "Tool.h"
#include <cmath>

//#include <iostream>
#define POSSIBLE_MOVES 14
#define ROWS 8
#define COLUMNS 8 

class King : public Tool
{
public:
    King(std::string pos, char type);
    int move(std::string _dst, Tool t, bool turn);
    //void set_valid_moves(std::string pos);
private:
    std::string valid_moves[8];
};