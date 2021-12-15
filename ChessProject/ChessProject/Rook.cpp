#include "Rook.h"

Rook::Rook(std::string pos, char type) : Tool::Tool(pos, type)
{
    set_valid_moves(pos);
    this->valid_moves.resize(POSSIBLE_MOVES);
}

int Rook::move(std::string _dst, Tool t, bool turn)
{
    int error = 0, i = 0;
    int numColumn = 0, numRow = 0;
    this->valid_moves.clear();
    set_valid_moves(_dst);

    if (this->get_pos()[0] != t.get_pos()[0] && this->get_pos()[1] != t.get_pos()[1])
    {
        return invalid_move;
    }

    error = this->move_errors(_dst, t, turn);
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
        this->valid_moves.push_back(add);
        count++;
    }

    for (int i = 0; i < 8; i++)
    {
        num = i + 97; //to convert i to letter ascii
        add = num;
        add += pos[1];
        if (add == pos)
            continue;
        this->valid_moves.push_back(add);
        count++;
    }
}

std::vector<std::string> Rook::get_valid_moves()
{
    return this->valid_moves;
}
