#include "knight.h"

Knight::Knight(std::string pos, char type) : Tool(pos, type)
{
	set_valid_moves(pos);
}

int Knight::move(std::string _dst, Tool t, bool turn)
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

void Knight::set_valid_moves(std::string pos)
{
	std::string tmp = "ab";
	int x[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	int y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
	for (int i = 0; i < 8; i++)
	{
		// Position of knight after move
		tmp[0] = pos[0] + x[i];
		tmp[1] = pos[1] + y[i];
		if ((tmp[1] <= ASCII_8 && tmp[1] >= ASCII_1) &&
			(tmp[0] <= ASCII_h && tmp[0] >= ASCII_a))
		{
			this->valid_moves.push_back(tmp);
		}
	}
}

void Knight::setter_valid_moves(std::vector<std::string> valid)
{
	this->valid_moves = valid;
}

std::vector<std::string> Knight::get_valid_moves()
{
	return this->valid_moves;
}
