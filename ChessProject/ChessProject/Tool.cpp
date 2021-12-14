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
    this->_type = '#';
}



Tool::~Tool()
{
}

void Tool::set_pos(std::string pos)
{
    this->_pos = pos;
}

void Tool::set_type(char type)
{
    this->_type = type;
}

int Tool::move_errors(std::string _dst, Tool t)
{
    int numColumn = 0, numRow = 0;

    //error 5 (first cause he checks for existence of the tool index)
    if (t.get_pos() == " " || this->get_pos() == " ")
    {
        return invalid_index;
    }

    //error 2 - can't move empty space
    if (this->get_type() == '#') //|| (isupper(this->get_type()) && isupper(dst.get_type())) ||
    {  //(!isupper(this->get_type()) && !isupper(dst.get_type())))

        return no_src;
    }

    //error 3 - can't move tool to the same square of other tool with same color
    if (t.get_color() == this->get_color() && t.get_type() != '#')
    {
        return invalid_dst;
    }

    //error 1 + 4
    //to do: if the king is in the valid array of the tool
    

    //error 7 - can't move tool to his current location)
    if (this->get_pos() == t.get_pos())
    {
        return same_src_dst;
    }

    return 0;
    //this->_pos = _dst;
}

char Tool::get_type()
{
    return this->_type;
}

std::string Tool::get_pos()
{
    return this->_pos;
}

bool Tool::get_color()
{
    return this->_color;
}

int Tool::invalid_index_move(std::string _dst)
{

    return 0;
}