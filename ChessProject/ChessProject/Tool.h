#pragma once
#include <iostream>
#include <cstring>

enum check_move { 
    valid_move,
    valid_check,
    no_src,
    invalid_dst,
    self_check,
    invalid_index,
    invalid_move,
    same_src_dst,
    mate };

class Tool 
{
public:

    Tool(std::string pos, char type);
    Tool();
    ~Tool();

    //setters
    void set_pos(const std::string pos);
    void set_type(const char type);

    int move_errors(std::string _dst, Tool t);

    char get_type();
    std::string get_pos();
    bool get_color();

    //moves checks
    int invalid_index_move(std::string _dst);
    int invalid_tool_move(std::string _dst);
    int invalid_check_move(std::string _pos);
private:
    //feilds
    std::string _pos;
    bool _color;
    char _type;
};