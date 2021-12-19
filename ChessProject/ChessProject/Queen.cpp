#include "Queen.h"
#define ASCII_1 49
#define ASCII_a 97
#define ASCII_h 104
#define ASCII_8 56

Queen::Queen(std::string pos, char type) : Tool(pos, type)
{
    set_valid_moves(pos);
    this->valid_moves.resize(28);
}

int Queen::move(std::string _dst, Tool t, bool turn)
{
    int error = 0;
    this->valid_moves.resize(28);

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



void Queen::set_valid_moves(std::string pos)
{
    this->valid_moves.clear();
    /// The queen moving technique is built out of
    /// the moving techniques of the bishop and rook

    ////////////////
    ////BISHOP PART:
    ////////////////

    std::string start = pos, add = " ";
    char num = ' ';
    while (start[0] + 1 <= ASCII_h && start[1] + 1 <= ASCII_8)
    {
        start[0]++;
        start[1]++;
        this->valid_moves.push_back(start);
    }
    start = pos;
    while (start[0] - 1 >= ASCII_a && start[1] - 1 >= ASCII_1)
    {
        start[0]--;
        start[1]--;
        this->valid_moves.push_back(start);
    }
    start = pos;
    while (start[0] - 1 >= ASCII_a && start[1] + 1 <= ASCII_8)
    {
        start[0]--;
        start[1]++;
        this->valid_moves.push_back(start);
    }
    start = pos;
    while (start[0] + 1 <= ASCII_h && start[1] - 1 >= ASCII_1)
    {
        start[0]++;
        start[1]--;
        this->valid_moves.push_back(start);
    }

    ////////////////
    ////ROOK PART:
    ////////////////

    add = " ";
    num = ' ';
    for (int i = 0; i < 8; i++) //a1, a2, a3...
    {
        num = i + 49; //to convert i to ascii
        add = pos[0];
        add += num;
        if (add == pos)
            continue;
        this->valid_moves.push_back(add);
    }

    for (int i = 0; i < 8; i++)
    {
        num = i + 97; //to convert i to letter ascii
        add = num;
        add += pos[1];
        if (add == pos)
            continue;
        this->valid_moves.push_back(add);
    }

}

void Queen::setter_valid_moves(std::vector<std::string> valid)
{
    this->valid_moves = valid;
}

std::vector<std::string> Queen::get_valid_moves()
{
    return this->valid_moves;
}
