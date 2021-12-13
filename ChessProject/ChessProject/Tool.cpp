#include "Tool.h"
#include <iostream>

Tool::Tool(std::string pos, char type)
{
    if (isupper(type))
    {
        this->_color = false;
    }
    else
    {
        this->_color = true;
    }
    this->_pos = pos;
    this->_type = type;
}

Tool::Tool()
{
    this->_color = false;
    this->_pos = " ";
    this->_type = ' ';
}



Tool::~Tool()
{
}

void Tool::set_pos(std::string pos)
{
    this->_pos = pos;
}

int Tool::move(std::string _dst)
{
    switch (0)
    {
    case valid_move:

        break;
    case valid_check:
        break;
    case no_src:
        break;
    case invalid_dst:
        break;
    case self_check:
        break;
    case invalid_index:
        break;
    case invalid_move:
        break;
    case same_src_dst:
        break;
    case mate:
        break;
    default:
        break;
    }
    this->_pos = _dst;
    return 0;
}

char Tool::get_type()
{
    return this->_type;
}

std::string Tool::get_pos()
{
    return this->_pos;
}

int Tool::invalid_index_move(std::string _dst)
{

    return 0;
}