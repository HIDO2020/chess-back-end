#include "Rook.h"

Rook::Rook(std::string pos, char type) : Tool::Tool(pos, type)
{
    set_valid_moves(pos);
}

int Rook::move(std::string _dst, Tool t,std::string king_pos)
{
    int error = 0, i = 0;
    int numColumn = 0, numRow = 0;

    set_valid_moves(_dst);

    if (this->get_pos()[0] != t.get_pos()[0] && this->get_pos()[1] != t.get_pos()[1])
    {
        return invalid_move;
    }
    else
    {
        for (i = 0; i < POSSIBLE_MOVES; i++)
        {
            if (this->valid_moves[i] == king_pos)
            {
                return valid_check;
            }
        }
    }
    error = this->move_errors(_dst, t);
    if (error != 0)
        return error;
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