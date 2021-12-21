#include "King.h"

King::King(std::string pos, char type) : Tool::Tool(pos, type)
{
    set_valid_moves(pos);
    this->valid_moves.resize(POSSIBLE_MOVES);
}

int King::move(std::string _dst, Tool t, bool turn)
{
    int error = 0;
    this->valid_moves.resize(POSSIBLE_MOVES);

    //if dst is not in the possible moves
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

void King::set_valid_moves(std::string pos)
{
    int i = -1, j = -1;
    this->valid_moves.clear();
    std::string add = "ab";
    
    for (i = -1; i <= 1; i++)
    {
        add[0] = pos[0] + i;
        for (j = -1; j <= 1; j++)
        {
            add[1] = pos[1] + j;
            // error 5 (first cause he checks for existence of the tool index)
            if (!(add[0] > 104 || add[0] < 97
                || add[1] > 56 || add[1] < 49))
            {
                this->valid_moves.push_back(add);
            }
        }
    }
}

void King::setter_valid_moves(std::vector<std::string> valid)
{
    this->valid_moves = valid;
}

std::vector<std::string> King::get_valid_moves()
{
    return this->valid_moves;
}
