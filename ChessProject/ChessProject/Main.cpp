#include <iostream>
#include <string>
#include "Game.h"
#include "Board.h"
#include "Tool.h"

//full game
//"RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr0"

void error_switch(int e, Board &b, Tool &t, std::string adr, Game g);

void main()
{
	int error = 1, countTurns = 0;
	Board b;
	Game g("#######R#######K###########################################rk###0");
    std::string adress_dst = "ab";
    std::string adress_src = "ab";
    std::string adr = "abcd";

    bool turn = true; //true - white turn | false - black turn

    b = g.get_board();
    b.print_board();  

    while (adr != "exit" && adr != "Exit")
    {

        if (turn)
        {
            std::cout << "White turn.." << std::endl;
        }
        else
        {
            std::cout << "Black turn.." << std::endl;
        }
        
        std::cout << "Enter cordination or enter exit to end the program: ";
        std::cin >> adr;
        std::cout << std::endl;

        adress_src[0] = adr[0];
        adress_src[1] = adr[1];
        adress_dst[0] = adr[2];
        adress_dst[1] = adr[3];

        Tool t = b.get_tool(adress_src);
        
        if (t.get_type() == 'r' || t.get_type() == 'R') //rook
        {
            Rook r(t.get_pos(), t.get_type());
            error = r.move(adress_dst, b.get_tool(adress_dst), turn);
        }
        else if (t.get_type() == 'k' || t.get_type() == 'K') //king
        {
            King k(t.get_pos(), t.get_type());
            error = k.move(adress_dst, b.get_tool(adress_dst), turn);
        }
        else  
        {
            error = t.move_errors(adress_dst, b.get_tool(adress_dst), turn);
        }
        
        error_switch(error, b, t, adress_dst, g);
        if (error == 0 || error == 1 || error == 8)
        {
            g.add_turn(countTurns);
        }
        if (g.get_turn() % 2 == 0)
        {
            turn = true;
        }
        else
        {
            turn = false;
        }
    }
}

void error_switch(int e, Board &b, Tool &t, std::string adr, Game g)
{
    switch (e)
    {
    case valid_move:
        
        b.move_piece(adr, t);
        t.set_pos(adr);
        b.print_board();
        break;
    case valid_check:
        b.move_piece(adr, t);
        t.set_pos(adr);
        b.print_board();
        std::cout << "Check!" << std::endl;
        break;
    case no_src:
        std::cout << "Error: the position you chose is not your piece" << std::endl;
        break;
    case invalid_dst:
        std::cout << "Error: You can't eat yourself ;)" << std::endl;
        break;
    case self_check:
        std::cout << "Error: The move you just did cause self check" << std::endl;
        break;
    case invalid_index:
        std::cout << "Error: The index you chose is out of board range (8-8)" << std::endl;
        break;
    case invalid_move:
        std::cout << "Error: Invalid move of that tool " << std::endl;
        break;
    case same_src_dst:
        std::cout << "Error: You can't move to yout current spot" << std::endl;
        break;
    case mate:
        b.move_piece(adr, t);
        t.set_pos(adr);
        b.print_board();
        std::cout << "CheckMate!" << std::endl;
        if (g.get_turn() == true)
        {
            std::cout << "White Won!" << std::endl;
        }
        else
        {
            std::cout << "Black Won!" << std::endl;
        }
        break;
    default:
        break;
    }
}
