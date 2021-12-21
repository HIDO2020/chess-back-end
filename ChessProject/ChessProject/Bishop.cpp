#include "Bishop.h"
#define ASCII_1 49
#define ASCII_a 97
#define ASCII_h 104
#define ASCII_8 56


Bishop::Bishop(std::string pos, char type) : Tool(pos, type)
{
    set_valid_moves(pos);
}

int Bishop::move(std::string _dst, Tool t, bool turn)
{
    int error = 0, i = 0;
    int numColumn = 0, numRow = 0;
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


void Bishop::set_valid_moves(std::string pos)
{
    this->valid_moves.clear();
    std::string start = pos, add = " ";
    char num = ' ';
    /////////
    /// I divided the bishop move into four parts:
    /// the up left, up right, down left and down right movement
    /// every while is adding the positions until its out of boundries
    /////////
    while (start[0] + 1 <= ASCII_h && start[1] + 1 <= ASCII_8) //up right 
    {
        start[0]++;
        start[1]++;
        this->valid_moves.push_back(start);
    }
    start = pos;
    while (start[0] - 1 >= ASCII_a && start[1] - 1 >= ASCII_1) //down left
    {
        start[0]--;
        start[1]--;
        this->valid_moves.push_back(start);
    }
    start = pos;
    while (start[0] - 1 >= ASCII_a && start[1] + 1 <= ASCII_8) //up left
    {
        start[0]--;
        start[1]++;
        this->valid_moves.push_back(start);
    }
    start = pos;
    while (start[0] + 1 <= ASCII_h && start[1] - 1 >= ASCII_1) //down right
    {
        start[0]++;
        start[1]--;
        this->valid_moves.push_back(start);
    }

}

void Bishop::setter_valid_moves(std::vector<std::string> valid)
{
    this->valid_moves = valid;
}

std::vector<std::string> Bishop::get_valid_moves()
{
    return this->valid_moves;
}

