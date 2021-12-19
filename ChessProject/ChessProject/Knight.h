#pragma once
#include "Tool.h"
#include <vector>
//#include <iostream>
#define POSSIBLE_MOVES 8
#define ASCII_1 49
#define ASCII_a 97
#define ASCII_h 104
#define ASCII_8 56
#define ASCII_7 55

class Knight : public Tool
{
public:
    Knight(std::string pos, char type);
    int move(std::string _dst, Tool t, bool turn);
    void set_valid_moves(std::string pos);
    //setter
    void setter_valid_moves(std::vector<std::string> valid);
    ////getter
    std::vector<std::string> get_valid_moves();

protected:
    std::vector<std::string> valid_moves;
};

