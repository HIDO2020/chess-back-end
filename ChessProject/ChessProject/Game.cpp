#include "Game.h"

Game::Game(std::string _board_string)
{
    this->_is_check_black = false;
    this->_is_check_white = false;
    if (_board_string[64] == '0')
    {
        this->_turn = true;
    }
    else
    {
        this->_turn = false;
    }
    //this->_board = Board(_board_string);
}

bool Game::get_black_check()
{
    return this->_is_check_black;
}

bool Game::get_white_check()
{
    return this->_is_check_white;
}

bool Game::get_turn()
{
    return this->_turn;
}

void Game::set_black_check(const bool b)
{
    this->_is_check_black = b;
}

void Game::set_white_check(const bool w)
{
    this->_is_check_white = w;
}

void Game::set_turn(const bool t)
{
    this->_turn = t;
}







