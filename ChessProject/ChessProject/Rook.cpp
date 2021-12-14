#include "Rook.h"

Rook::Rook(std::string pos, char type) : Tool(pos, type)
{
}

int Rook::move(std::string _dst, Tool t)
{
    int error = 0;
    if (this->get_pos()[0] != t.get_pos()[0])
    {
        return invalid_move;
    }
    error = this->move_errors(_dst, t);
    if (error != 0)
        return error;
    //Tool tmp(this->get_pos(), this->get_type());
    //this->set_type('#');
    return 0;
}