#include "Rook.h"

Rook::Rook(std::string pos, char type) : Tool::Tool(pos, type)
{
    set_valid_moves(pos);
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

    //is it check?
    //if()
    return 0;
}

void Rook::set_valid_moves(std::string pos)
{
    std::string add = " ";
    char num = ' ';
    int count = 0; //counts the index of the array
    for (int i = 0; i < 8; i++) //a1, a2, a3...
    {
        num = i + 49; //to convert i to ascii
        add = pos[0];
        add += num;
        if (add == pos)
            continue;
        this->valid_moves[count] = add;
        count++;
    }

    for (int i = 0; i < 8; i++)
    {
        num = i + 97; //to convert i to letter ascii
        add = num;
        add += pos[1];
        if (add == pos)
            continue;
        this->valid_moves[count] = add;
        count++;
    }
    //return Tool();
}