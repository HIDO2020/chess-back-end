#include <iostream>
#include <string>
#include "Game.h"
#include "Board.h"
#include "Bishop.h"
#include "Queen.h"
#include "Tool.h"
#include <vector>

#define POSSIBLE_MOVES 14

//full game
//"RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr0"

void error_switch(int e, Board &b, Tool &t, std::string adr, Game g);
std::vector<std::string> change_vector(std::vector<std::string> rook_valid_moves, Board b, Tool t);
std::vector<std::string> get_enemy_valid_moves(bool turn, Board b);
int check_check(std::vector<std::string> valid_moves, char king_check, Board b, bool turn, Game& g);

void main()
{
	int error = 1, countTurns = 0;
	Board b;
	Game g("R#BQKB#R#########################################r########bqkb#r0");
    std::string adress_dst = "ab";
    std::string adress_src = "ab";
    std::string adr = "abcd";
    std::vector<std::string> king_valid_moves;
    std::vector<std::string> new_vector;
    std::vector<std::string> check_vector;
    std::vector<std::string> vector_valid_moves;

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
        error = 0;

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

        // error 5 (first cause he checks for existence of the tool index)
        if (adress_dst[0] < 97 || adress_dst[0] > 104 || adress_dst[1] < 49 || adress_dst[1] > 56)
        {
            error =  invalid_index;
        }

        if (error == 0)
        {
            if (t.get_type() == 'r' || t.get_type() == 'R') //rook
            {
                Rook r(t.get_pos(), t.get_type());
                //slicing
                vector_valid_moves.clear();
                r.set_valid_moves(r.get_pos());
                vector_valid_moves = r.get_valid_moves();
                vector_valid_moves.resize(14);

                for (auto i : vector_valid_moves)
                    std::cout << i << ' ';
                std::cout << std::endl;

                new_vector.clear();
                new_vector = change_vector(vector_valid_moves, b, t);

                for (auto i : new_vector)
                    std::cout << i << ' ';
                std::cout << std::endl;

                r.setter_valid_moves(new_vector);

                error = r.move(adress_dst, b.get_tool(adress_dst), turn);
                if (error == 0)
                {
                    b.move_piece(adress_dst, t);

                    check_vector = get_enemy_valid_moves(turn, b);

                    //checks if the pos of the king is in the valid moves of the enemy
                    if (std::find(check_vector.begin(), check_vector.end(), b.get_king(turn).get_pos()) != check_vector.end())
                    {
                        error = 4;
                        //back
                        b.move_piece(adress_src, t);
                        Tool t = b.get_tool(adress_dst);
                        t.set_type('#');
                        b.move_piece(adress_dst, t);
                    }


                    r.set_valid_moves(adress_dst);
                    vector_valid_moves = r.get_valid_moves();
                    vector_valid_moves.resize(14);

                    std::cout << std::endl;
                    //slice
                    r.set_pos(adress_dst);

                    for (std::string i : vector_valid_moves)
                        std::cout << i << ' ';
                    std::cout << std::endl;

                    vector_valid_moves = change_vector(vector_valid_moves, b, t);
                    std::cout << std::endl;

                    for (std::string i : vector_valid_moves)
                        std::cout << i << ' ';
                    std::cout << std::endl;

                    g.set_black_check(false);
                    g.set_white_check(false);
                    if (error == 0)
                    {
                        error = check_check(vector_valid_moves, king_check, b, turn, g);
                    }
                }
                
            }


            else if (t.get_type() == 'k' || t.get_type() == 'K') //king
            {
                King k(t.get_pos(), t.get_type());
                k.set_valid_moves(k.get_pos());
                king_valid_moves = k.get_valid_moves();
                king_valid_moves.resize(9);

                k.setter_valid_moves(king_valid_moves);

                error = k.move(adress_dst, b.get_tool(adress_dst), turn);

                if (error == 0)
                {
                    b.move_piece(adress_dst, t);
                    k.set_pos(adress_dst);

                    check_vector = get_enemy_valid_moves(turn, b);

                    //checks if the pos of the king is in the valid moves of the enemy
                    if (std::find(check_vector.begin(), check_vector.end(), adress_dst) != check_vector.end())
                    {
                        error = 4;
                        //back
                        b.move_piece(adress_src, t);
                        Tool t = b.get_tool(adress_dst);
                        t.set_type('#');
                        b.move_piece(adress_dst, t);
                    }
                }
            }

            else if (t.get_type() == 'b' || t.get_type() == 'B') //bishop
            {
                Bishop bi(t.get_pos(), t.get_type());
                //slicing
                bi.set_valid_moves(bi.get_pos());
                vector_valid_moves = bi.get_valid_moves();
                if (vector_valid_moves.size() > 14)
                {
                    vector_valid_moves.resize(14);
                }
                

                for (auto i : vector_valid_moves)
                    std::cout << i << ' ';
                std::cout << std::endl;

                new_vector = change_vector(vector_valid_moves, b, t);

                for (auto i : new_vector)
                    std::cout << i << ' ';
                std::cout << std::endl;

                bi.setter_valid_moves(new_vector);

                error = bi.move(adress_dst, b.get_tool(adress_dst), turn);
                if (error == 0)
                {
                    b.move_piece(adress_dst, t);

                    check_vector = get_enemy_valid_moves(turn, b);

                    //checks if the pos of the king is in the valid moves of the enemy
                    if (std::find(check_vector.begin(), check_vector.end(), b.get_king(turn).get_pos()) != check_vector.end())
                    {
                        error = 4;
                        //back
                        b.move_piece(adress_src, t);
                        Tool t = b.get_tool(adress_dst);
                        t.set_type('#');
                        b.move_piece(adress_dst, t);
                    }


                    bi.set_valid_moves(adress_dst);
                    vector_valid_moves = bi.get_valid_moves();
                    vector_valid_moves.resize(14);

                    std::cout << std::endl;
                    //slice
                    bi.set_pos(adress_dst);
                    vector_valid_moves = change_vector(vector_valid_moves, b, t);
                    std::cout << std::endl;

                    g.set_black_check(false);
                    g.set_white_check(false);
                    vector_valid_moves = vector_valid_moves;
                    if (error == 0)
                    {
                        error = check_check(vector_valid_moves, king_check, b, turn, g);
                    }
                }
            }


            else if (t.get_type() == 'q' || t.get_type() == 'Q') //Queen
            {
                Queen q(t.get_pos(), t.get_type());
                //slicing
                q.set_valid_moves(q.get_pos());
                vector_valid_moves = q.get_valid_moves();
                vector_valid_moves.resize(28);

                for (auto i : vector_valid_moves)
                    std::cout << i << ' ';
                std::cout << std::endl;

                new_vector = change_vector(vector_valid_moves, b, t);

                for (auto i : new_vector)
                    std::cout << i << ' ';
                std::cout << std::endl;

                q.setter_valid_moves(new_vector);

                error = q.move(adress_dst, b.get_tool(adress_dst), turn);
                //if (error == 0)
                //{
                //    b.move_piece(adress_dst, t);

                //    check_vector = get_enemy_valid_moves(turn, b);

                //    //checks if the pos of the king is in the valid moves of the enemy
                //    if (std::find(check_vector.begin(), check_vector.end(), b.get_king(turn).get_pos()) != check_vector.end())
                //    {
                //        error = 4;
                //        //back
                //        b.move_piece(adress_src, t);
                //        Tool t = b.get_tool(adress_dst);
                //        t.set_type('#');
                //        b.move_piece(adress_dst, t);
                //    }


                //    q.set_valid_moves(adress_dst);
                //    vector_valid_moves = q.get_valid_moves();
                //    vector_valid_moves.resize(14);

                //    std::cout << std::endl;
                //    //slice
                //    q.set_pos(adress_dst);
                //    vector_valid_moves = change_vector(vector_valid_moves, b, t);
                //    std::cout << std::endl;

                //    g.set_black_check(false);
                //    g.set_white_check(false);
                //    vector_valid_moves = vector_valid_moves;
                //    if (error == 0)
                //    {
                //        error = check_check(vector_valid_moves, king_check, b, turn, g);
                //    }
                //}
            }


            else
            {
                error = t.move_errors(adress_dst, b.get_tool(adress_dst), turn);
            }
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
std::vector<std::string> change_vector(std::vector<std::string> valid_moves, Board b, Tool t)
{
    std::vector<std::string> new_vector;
    std::string tmp_curr = "ab";
    int count = 0, counter = 0, queen_counter = 0;
    std::string pos = t.get_pos();
    new_vector.clear();

    //NORTH SOUTH WEST EAST
    int N = 0, S = 0, W = 0, E = 0;
    int Ne = 0, Se = 0, Nw = 0, Sw = 0;

    N = 8 - pos[1] + 48;
    S = pos[1] - 1 + -48;
    W = pos[0] - 'a';
    E = 'h' - pos[0];

    count = 0, counter = 0;
    Ne = std::min(N, E);

    if (t.get_type() == 'b' || t.get_type() == 'B' || t.get_type() == 'q' || t.get_type() == 'Q')
    {

        while (counter < Ne)
        {
            if (b.get_tool(valid_moves[count]).get_type() != '#')
            {
                new_vector.push_back(valid_moves[count]);    //skip
                break;
            }
            new_vector.push_back(valid_moves[count]);
            count++;
            counter++;
        }

        counter = 0;
        count = Ne;
        Sw = std::min(S, W);

        while (counter < Sw)
        {
            if (b.get_tool(valid_moves[count]).get_type() != '#')
            {
                new_vector.push_back(valid_moves[count]);    //skip
                break;
            }
            new_vector.push_back(valid_moves[count]);
            count++;
            counter++;
        }

        counter = 0;
        count = Sw + Ne;
        Nw = std::min(N, W);

        while (counter < Nw)
        {
            if (b.get_tool(valid_moves[count]).get_type() != '#')
            {
                new_vector.push_back(valid_moves[count]);    //skip
                break;
            }
            new_vector.push_back(valid_moves[count]);
            count++;
            counter++;
        }

        counter = 0;
        count = Se + Sw + Ne;
        Sw = std::min(S, E);

        while (counter < Sw)
        {
            if (b.get_tool(valid_moves[count]).get_type() != '#')
            {
                new_vector.push_back(valid_moves[count]);    //skip
                break;
            }
            new_vector.push_back(valid_moves[count]);
            count++;
            counter++;
        }
    }

    if (t.get_type() == 'r' || t.get_type() == 'R' || t.get_type() == 'q' || t.get_type() == 'Q')
    {
        queen_counter = count;

        counter = 0;
        count = queen_counter;
        while (counter < N)
        {
            if (b.get_tool(valid_moves[count]).get_type() != '#')
            {
                new_vector.push_back(valid_moves[count]);    //skip
                break;
            }
            new_vector.push_back(valid_moves[count]);
            count++;
            counter++;
        }

        counter = 0;
        count = N + queen_counter;

        while (counter < N)
        {
            if (b.get_tool(valid_moves[count]).get_type() != '#')
            {
                new_vector.push_back(valid_moves[count]);    //skip
                break;
            }
            new_vector.push_back(valid_moves[count]);
            count--;
            counter++;
        }

        counter = 0;
        count = 7 + queen_counter;

        while (counter < W)
        {
            if (b.get_tool(valid_moves[count]).get_type() != '#')
            {
                new_vector.push_back(valid_moves[count]);    //skip
                break;
            }
            new_vector.push_back(valid_moves[count]);
            count++;
            counter++;
        }

        counter = 0;
        count = 7 + W + queen_counter;

        while (counter < W)
        {
            if (b.get_tool(valid_moves[count]).get_type() != '#')
            {
                new_vector.push_back(valid_moves[count]);    //skip
                break;
            }
            new_vector.push_back(valid_moves[count]);
            count--;
            counter++;
        }
    }

    return new_vector;
}


//get enenmy valids moves
std::vector<std::string> get_enemy_valid_moves(bool turn, Board b)
{
    int i = 0, j = 0;
    std::vector<std::string> check_vector;
    std::vector<std::string> new_vector;
    check_vector.clear();
    std::string tmp_curr = "ab";

    for (j = 1; j <= 8; j++)
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
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(14);
                    new_vector = change_vector(new_vector, b, t);
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
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(14);
                    new_vector = change_vector(new_vector, b, t);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }
            }
        }
    }
    return check_vector;
}

int check_check(std::vector<std::string> valid_moves, char king_check, Board b, bool turn, Game &g)
{
    int error = 0;

    for (std::string i : valid_moves)
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
    }
    return error;
}
