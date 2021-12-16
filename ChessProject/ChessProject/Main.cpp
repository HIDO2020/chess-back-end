#include <iostream>
#include <string>
#include "Game.h"
#include "Board.h"
#include "Tool.h"
#include <vector>

#define POSSIBLE_MOVES 14

//full game
//"RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr0"

void error_switch(int e, Board &b, Tool &t, std::string adr, Game g);
std::vector<std::string> change_vector(std::vector<std::string> rook_valid_moves, Board b, Tool t, Rook r);

void main()
{
	int error = 1, countTurns = 0;
	Board b;
	Game g("K#######R#######################################r#######k########0");
    std::string adress_dst = "ab";
    std::string adress_src = "ab";
    std::string adr = "abcd";
    std::vector<std::string> rook_valid_moves;
    std::vector<std::string> new_vector;
    std::vector<std::string> check_vector;

    bool turn = true; //true - white turn | false - black turn
    char king_check = 'K';  //K - white turn |k - black turn

    std::string tmp_curr = "ab";
    std::string tmp_king = "ab";

    int num = 0, letter = 0;
    int i = 0, j = 0;

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
            //slicing
            r.set_valid_moves(r.get_pos());
            rook_valid_moves = r.get_valid_moves();
            rook_valid_moves.resize(14);
            new_vector = change_vector(rook_valid_moves, b, t, r);

            r.setter_valid_moves(new_vector);

            error = r.move(adress_dst, b.get_tool(adress_dst), turn);
            b.move_piece(adress_dst, t);


            //check error4
            check_vector.clear();
            //check_vector = new_vector;
            
            for (j = 1; j<= 8; j++)
            {
                for (i = 1; i <= 8; i++)
                {
                    tmp_curr[0] = j + 96;
                    tmp_curr[1] = i + 48;
                    Tool t = b.get_tool(tmp_curr);
                    if (turn)
                    {
                        if (t.get_type() == 'R')
                        {
                            Rook r_tmp(t.get_pos(), t.get_type());
                            //slicing
                            r_tmp.set_valid_moves(r_tmp.get_pos());
                            rook_valid_moves = r_tmp.get_valid_moves();
                            rook_valid_moves.resize(14);
                            new_vector = change_vector(rook_valid_moves, b, t, r_tmp);
                            std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                        }
                    }
                    else
                    {
                        if (t.get_type() == 'r')
                        {
                            Rook r_tmp(t.get_pos(), t.get_type());
                            //slicing
                            r_tmp.set_valid_moves(r_tmp.get_pos());
                            rook_valid_moves = r_tmp.get_valid_moves();
                            rook_valid_moves.resize(14);
                            new_vector = change_vector(rook_valid_moves, b, t, r_tmp);
                            std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                        }
                    }   
                }
            }

            if (std::find(check_vector.begin(), check_vector.end(), b.get_king(turn).get_pos()) != check_vector.end())
            {
                error = 4;
                //r.move(adress_src, b.get_tool(adress_src), turn);       //back
                b.move_piece(adress_src, t);
                Tool t = b.get_tool(adress_dst);
                t.set_type('#');
                b.move_piece(adress_dst, t);
            }


            r.set_valid_moves(adress_dst);
            rook_valid_moves = r.get_valid_moves();
            rook_valid_moves.resize(14);

            std::cout << std::endl;
            //slice
            r.set_pos(adress_dst);
            rook_valid_moves = change_vector(rook_valid_moves, b, t, r);
            std::cout << std::endl;

            g.set_black_check(false);
            g.set_white_check(false);
            for (std::string i : rook_valid_moves)
            {
                if (b.get_tool(i).get_type() == king_check)
                {
                    if (error == 0) //valid
                    {

                        error = 1;
                        if (turn)
                        {
                            g.set_black_check(true);
                        }
                        else
                        {
                            g.set_white_check(true);
                        }
                    }
                }
                //std::cout << i << ' ';
            }
            std::cout << std::endl;
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
            king_check = 'K';
        }
        else
        {
            turn = false;
            king_check = 'k';
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

/*
slicing the vector soo you can't jump over pieces
*/
std::vector<std::string> change_vector(std::vector<std::string> rook_valid_moves, Board b, Tool t, Rook r)
{
    std::vector<std::string> new_vector;

    std::string tmp_curr = "ab";

    int num = 0, letter = 0;

    new_vector.clear();
    num = r.get_pos()[1] - 48;  //asci from 1 --> 1(int)
    letter = r.get_pos()[0];    //asci from a --> 1(int)

    while (num > 1)
    {
        num--;
        tmp_curr[0] = letter;
        tmp_curr[1] = num + 48;
        if (b.get_tool(tmp_curr).get_type() != '#')
        {
            num = 1;    //skip
        }
        new_vector.push_back(tmp_curr);
    }

    num = r.get_pos()[1] - 48;  //asci from 1 --> 1(int)
    letter = r.get_pos()[0];    //asci from a --> 1(int)

    while (num < 8)
    {
        num++;
        tmp_curr[0] = letter;
        tmp_curr[1] = num + 48;
        if (b.get_tool(tmp_curr).get_type() != '#')
        {
            num = 8;    //skip
        }
        new_vector.push_back(tmp_curr);
    }

    num = r.get_pos()[1];  //asci from 1 --> 1(int)
    letter = r.get_pos()[0] - 96;    //asci from a --> 1(int)

    while (letter > 1)
    {
        letter--;
        tmp_curr[0] = letter + 96;
        tmp_curr[1] = num;
        if (b.get_tool(tmp_curr).get_type() != '#')
        {
            letter = 1;    //skip
        }
        new_vector.push_back(tmp_curr);
    }

    num = r.get_pos()[1];  //asci from 1 --> 1(int)
    letter = r.get_pos()[0] - 96;    //asci from a --> 1(int)

    while (letter < 8)
    {
        letter++;
        tmp_curr[0] = letter + 96;
        tmp_curr[1] = num;
        if (b.get_tool(tmp_curr).get_type() != '#')
        {
            letter = 8;    //skip
        }
        new_vector.push_back(tmp_curr);
    }

    return new_vector;
}
