#include "Pawn.h"
#define ASCII_1 49
#define ASCII_a 97
#define ASCII_h 104
#define ASCII_8 56

Pawn::Pawn(std::string pos, char type) : Tool(pos, type)
{
	this->first_move = true;
	set_valid_moves(pos);
}

int Pawn::move(std::string _dst, Tool t, bool turn)
{
	int error = 0, i = 0;
	int numColumn = 0, numRow = 0;
	this->valid_moves.resize(6);

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

void Pawn::set_valid_moves(std::string pos)
{
    this->valid_moves.clear();
    std::string tmp = "ab";
    if (this->_color) //if white
    {
        if (pos[1] == '2') //if pawn is at his starting point
            this->first_move = true;
        else
            this->first_move = false;


        if (pos[0] + 1 <= ASCII_h && pos[1] + 1 <= ASCII_8) // if pos one up and one right is not out of boundries
        {
            tmp[0] = pos[0] + 1;
            tmp[1] = pos[1] + 1;
            this->valid_moves.push_back(tmp);
        }

        if (pos[1] + 1 <= ASCII_8) //if one up is in boundries
        {
            tmp = pos;
            tmp[1]++;
            this->valid_moves.push_back(tmp);
        }

        if (pos[0] - 1 >= ASCII_a && pos[1] + 1 <= ASCII_8) // if pos one up and one left is not out of boundries
        {
            tmp[0] = pos[0] - 1;
            tmp[1] = pos[1] + 1;
            this->valid_moves.push_back(tmp);
        }

        if (this->first_move && pos[1] + 2 <= ASCII_8) //if pawn can move two forward and is not out of boundries
        {
            tmp = pos;
            tmp[1] += 2;
            this->valid_moves.push_back(tmp);
        }
    }
    else //if black
    {
        if (pos[1] == '7') //if pawn is at his starting point
            this->first_move = true;
        else
            this->first_move = false;


        if (pos[0] + 1 <= ASCII_h && pos[1] - 1 >= ASCII_1) // if pos one down and one right is not out of boundries
        {
            tmp[0] = pos[0] + 1;
            tmp[1] = pos[1] - 1;
            this->valid_moves.push_back(tmp);
        }

        if (pos[1] - 1 >= ASCII_1) //if one down is in boundries
        {
            tmp = pos;
            tmp[1]--;
            this->valid_moves.push_back(tmp);
        }

        if (pos[0] - 1 >= ASCII_a && pos[1] - 1 >= ASCII_1) // if pos one down and one left is not out of boundries
        {
            tmp[0] = pos[0] - 1;
            tmp[1] = pos[1] - 1;
            this->valid_moves.push_back(tmp);
        }

        if (this->first_move && pos[1] - 2 >= ASCII_1) //if pawn can move two downwards and is not out of boundries
        {
            tmp = pos;
            tmp[1] -= 2;
            this->valid_moves.push_back(tmp);
        }
    }
}

void Pawn::setter_valid_moves(std::vector<std::string> valid)
{
	this->valid_moves = valid;
}

void Pawn::set_first_move()
{
	this->first_move = false;
}

std::vector<std::string> Pawn::get_valid_moves()
{
	return this->valid_moves;
}

bool Pawn::get_first_move()
{
	return this->first_move;
}
