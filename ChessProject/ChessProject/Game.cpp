#include "Game.h"

Game::Game(std::string _board_string)
{
    this->_is_check_black = false;
    this->_is_check_white = false;
    if (_board_string[64] == '0')       //check who start
    {
        this->_turn = 0;
    }
    else
    {
        this->_turn = false;
    }
    this->_board = Board(_board_string);
}

bool Game::get_black_check()
{
    return this->_is_check_black;
}

bool Game::get_white_check()
{
    return this->_is_check_white;
}

int Game::get_turn()
{
    return this->_turn;
}

Board Game::get_board()
{
    return this->_board;
}

void Game::set_black_check(const bool b)
{
    this->_is_check_black = b;
}

void Game::set_white_check(const bool w)
{
    this->_is_check_white = w;
}

void Game::add_turn(const int t)
{
    this->_turn = this->_turn + 1;
}







