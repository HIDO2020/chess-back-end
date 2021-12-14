#pragma once
#include "Tool.h"

class Rook : public Tool
{
public:
    Rook(std::string pos, char type);
    int move(std::string _dst, Tool t);
};