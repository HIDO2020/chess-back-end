#include "King.h"

King::King(std::string pos, char type) : Tool::Tool(pos, type)
{

}

int King::move(std::string _dst, Tool t, bool turn)
{
    int error = 0;

    if ( abs(this->get_pos()[0] - t.get_pos()[0]) > 1 || abs(this->get_pos()[1] - t.get_pos()[1]) > 1)
    {
        return invalid_move;
    }

    error = this->move_errors(_dst, t, turn);
    if (error != 0)
        return error;
    return 0;
}
