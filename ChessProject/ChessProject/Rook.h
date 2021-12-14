#pragma once
#include "Tool.h"
//#include <iostream>
#define POSSIBLE_MOVES 14
#define ROWS 8
#define COLUMNS 8 

class Rook : public Tool
{
public:
    Rook(std::string pos, char type);
    int move(std::string _dst, Tool t, std::string king_pos);
    void set_valid_moves(std::string pos);
private:
    std::string valid_moves[POSSIBLE_MOVES];
};