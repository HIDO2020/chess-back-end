#include "Rook.h"

Rook::Rook(std::string pos, char type) : Tool::Tool(pos, type)
{
    set_valid_moves(pos);
    this->valid_moves.resize(POSSIBLE_MOVES);
}

int Rook::move(std::string _dst, Tool t, bool turn)
{
    int error = 0;
    this->valid_moves.resize(14);

    if (std::find(this->valid_moves.begin(), this->valid_moves.end(), _dst) != this->valid_moves.end())
    {
        error = this->move_errors(_dst, t, turn);
        if (error != 0)
            return error;
    }
    else
    {
        return invalid_move;
    }
    return 0;
}

void Rook::set_valid_moves(std::string pos)
{
    this->valid_moves.clear();
    std::string add = " ";
    char num = ' ';
    int count = 0; //counts the index of the array
    for (int i = 0; i < 8; i++) //add the possible x part
    {
        num = i + 49; //to convert i to ascii
        add = pos[0];
        add += num;
        if (add == pos)
            continue;
        this->valid_moves.push_back(add);
        count++;
    }

    for (int i = 0; i < 8; i++) //add the possible y part
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

void Rook::setter_valid_moves(std::vector<std::string> valid)
{
    this->valid_moves = valid;
}

std::vector<std::string> Rook::get_valid_moves()
{
    return this->valid_moves;
}
