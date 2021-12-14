#pragma once
#include "Tool.h"
//#include <iostream>
#define POSSIBLE_MOVES 14

class Rook : public Tool
{
public:
    Rook(std::string pos, char type);
    int move(std::string _dst, Tool t);
    void set_valid_moves(std::string pos);
private:
    std::string valid_moves[POSSIBLE_MOVES];
};