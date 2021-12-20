/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <thread>

#include <iostream>
#include <algorithm>
#include <string>
#include "Game.h"
#include "Board.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Tool.h"
#include "Pawn.h"
#include <vector>

using std::cout;
using std::endl;
using std::string;

#define POSSIBLE_MOVES 14

//full game
//"RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr0"

//void error_switch(int e, Board& b, Tool& t, std::string adr, Game g);
std::vector<string> change_pawn_vector(Pawn p, Board b);
std::vector<string> change_vector(std::vector<string> rook_valid_moves, Board b, Tool t);
std::vector<string> get_enemy_valid_moves(bool turn, Board b);
int check_check(std::vector<string> valid_moves, char king_check, Board b, bool turn, Game& g);



void main()
{
    int error = 1, countTurns = 0;
    Board b;
    Tool t;
    string adress_dst = "ab";
    string adress_src = "ab";
    string adr = "abcd";
    std::vector<string> king_valid_moves;
    std::vector<string> new_vector;
    std::vector<string> check_vector;
    std::vector<string> vector_valid_moves;

    bool turn = true; //true - white turn | false - black turn
    char king_check = 'K';  //K - white turn |k - black turn

    string tmp_curr = "ab";
    string tmp_king = "ab";
    string error_code = "ab";

    int num = 0, letter = 0;
    int i = 0, j = 0;

    //rand(time_t(NULL));

    Pipe p;
    bool isConnect = p.connect();

    string ans;
    while (!isConnect)
    {
        cout << "cant connect to graphics" << endl;
        cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
        std::cin >> ans;

        if (ans == "0")
        {
            cout << "trying connect again.." << endl;
            Sleep(5000);
            isConnect = p.connect();
        }
        else
        {
            p.close();
            return;
        }
    }

    char msgToGraphics[1024];
    // msgToGraphics should contain the board string accord the protocol
    // YOUR CODE

    strcpy_s(msgToGraphics, "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr1"); // just example...
    Game g("RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr1");
    b = g.get_board();

    p.sendMessageToGraphics(msgToGraphics);   // send the board string

    // get message from graphics
    adr = p.getMessageFromGraphics();

    while (msgToGraphics != "quit")
    {
        adress_src[0] = adr[0];
        adress_src[1] = adr[1];
        adress_dst[0] = adr[2];
        adress_dst[1] = adr[3];

        

        error = 0;
        check_vector.clear();
        new_vector.clear();
        vector_valid_moves.clear();

        t = b.get_tool(adress_src);

        // error 5 (first cause he checks for existence of the tool index)
        if (adress_dst[0] < 97 || adress_dst[0] > 104 || adress_dst[1] < 49 || adress_dst[1] > 56)
        {
            error = invalid_index;
        }

        if (error == 0)
        {

            if (t.get_type() == 'k' || t.get_type() == 'K') //king
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


            else if (t.get_type() == 'r' || t.get_type() == 'R') //rook
            {
                Rook r(t.get_pos(), t.get_type());
                //slicing
                vector_valid_moves.clear();
                r.set_valid_moves(r.get_pos());
                vector_valid_moves = r.get_valid_moves();
                vector_valid_moves.resize(14);

                new_vector.clear();



                new_vector = change_vector(vector_valid_moves, b, t);

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

                    //slice
                    r.set_pos(adress_dst);

                    vector_valid_moves = change_vector(vector_valid_moves, b, t);

                    g.set_black_check(false);
                    g.set_white_check(false);
                    if (error == 0)
                    {
                        error = check_check(vector_valid_moves, king_check, b, turn, g);
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

                new_vector = change_vector(vector_valid_moves, b, t);

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

                    for (auto i : vector_valid_moves)
                        std::cout << i << ' ';
                    std::cout << std::endl;

                    //slice
                    bi.set_pos(adress_dst);
                    vector_valid_moves = change_vector(vector_valid_moves, b, t);

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

                    q.set_valid_moves(adress_dst);
                    vector_valid_moves = q.get_valid_moves();
                    vector_valid_moves.resize(28);

                    std::cout << std::endl;
                    //slice

                    //b.move_piece(adress_dst, t);
                    t.set_pos(adress_dst);

                    new_vector = change_vector(vector_valid_moves, b, t);

                    g.set_black_check(false);
                    g.set_white_check(false);
                    if (error == 0)
                    {
                        error = check_check(new_vector, king_check, b, turn, g);
                    }
                }
            }


            else if (t.get_type() == 'n' || t.get_type() == 'N') //knight
            {
                Knight kn(t.get_pos(), t.get_type());
                //slicing
                vector_valid_moves.clear();
                kn.set_valid_moves(kn.get_pos());
                vector_valid_moves = kn.get_valid_moves();
                vector_valid_moves.resize(8);
                new_vector = vector_valid_moves;
                kn.setter_valid_moves(new_vector);

                error = kn.move(adress_dst, b.get_tool(adress_dst), turn);
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

                    kn.set_valid_moves(adress_dst);
                    vector_valid_moves = kn.get_valid_moves();
                    vector_valid_moves.resize(8);

                    //slice
                    kn.set_pos(adress_dst);

                    g.set_black_check(false);
                    g.set_white_check(false);
                    if (error == 0)
                    {
                        error = check_check(vector_valid_moves, king_check, b, turn, g);
                    }
                }
            }


            else if (t.get_type() == 'p' || t.get_type() == 'P') //Pawn
            {
                Pawn p(t.get_pos(), t.get_type());
                //slicing
                vector_valid_moves.clear();
                p.set_valid_moves(p.get_pos());
                vector_valid_moves = p.get_valid_moves();
                vector_valid_moves.resize(6);
                p.setter_valid_moves(vector_valid_moves);

                new_vector = change_pawn_vector(p, b);

                p.setter_valid_moves(new_vector);

                error = p.move(adress_dst, b.get_tool(adress_dst), turn);
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

                    p.set_valid_moves(adress_dst);
                    vector_valid_moves = p.get_valid_moves();
                    vector_valid_moves.resize(8);

                    //slice
                    p.set_pos(adress_dst);
                    new_vector = change_pawn_vector(p, b);

                    g.set_black_check(false);
                    g.set_white_check(false);
                    if (error == 0)
                    {
                        error = check_check(vector_valid_moves, king_check, b, turn, g);
                    }
                }
            }

            else //#
            {
                error = no_src;
            }

        }
        //error_switch(error, b, t, adress_dst, g);
        if (error == 0 || error == 1 || error == 8)
        {
            g.add_turn(countTurns);
        }
        else
        {
            for (auto i : new_vector)
                std::cout << i << ' ';
            std::cout << std::endl;
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

        /******* JUST FOR EREZ DEBUGGING ******/
        int r = rand() % 10; // just for debugging......
        msgToGraphics[0] = (char)(error + '0');
        msgToGraphics[1] = 0;
        /******* JUST FOR EREZ DEBUGGING ******/


        // return result to graphics		
        p.sendMessageToGraphics(msgToGraphics);

        // get message from graphics
        adr = p.getMessageFromGraphics();


    }
    p.close();
}

/*
slicing the vector of the pawn only 
*/
std::vector<std::string> change_pawn_vector(Pawn p, Board b)
{
    std::vector<std::string> moves = p.get_valid_moves();
    std::string tmp = "ab";
    moves.resize(4);
    if (p.get_pos() == "h4")
    {
        tmp = "sd";
    }
    for (int i = 0; i < 4; i++)
    {
        if (moves[i] != "")
        {
            if (p.get_color())
            {
                if ((moves[i][0] > p.get_pos()[0] || moves[i][0] < p.get_pos()[0]) &&
                    (b.get_tool(moves[i]).get_color() == p.get_color() || b.get_tool(moves[i]).get_type() == '#'))
                {
                    moves[i].erase();
                    continue;
                }

                if (moves[i][1] - 1 == p.get_pos()[1] && moves[i][0] == p.get_pos()[0] && b.get_tool(moves[i]).get_type() != '#')
                {
                    tmp[0] = moves[i][0];
                    tmp[1] = moves[i][1] + 1;
                    //if (std::find(moves.begin(), moves.end(), tmp) != moves.end())
                    //{
                    for (int j = 0; j < 4; j++)
                    {
                        if (moves[j] == tmp)
                            moves[j].erase();
                    }
                    //}
                    moves[i].erase();
                    //moves[i + 1].erase();
                    continue;
                }
                if (moves[i][1] - 2 == p.get_pos()[1] && moves[i][0] == p.get_pos()[0] && b.get_tool(moves[i]).get_type() != '#')
                {
                    moves[i].erase();
                }
            }
            else
            {
                if ((moves[i][0] > p.get_pos()[0] || moves[i][0] < p.get_pos()[0]) &&
                    (b.get_tool(moves[i]).get_color() == p.get_color() || b.get_tool(moves[i]).get_type() == '#'))
                {
                    moves[i].erase();
                    continue;
                }

                if (moves[i][1] + 1 == p.get_pos()[1] && moves[i][0] == p.get_pos()[0] && b.get_tool(moves[i]).get_type() != '#')
                {
                    tmp[0] = moves[i][0];
                    tmp[1] = moves[i][1] - 1;
                    //if (std::find(moves.begin(), moves.end(), tmp) != moves.end())
                    //{
                    for (int j = 0; j < 4; j++)
                    {
                        if (moves[j] == tmp)
                            moves[j].erase();
                    }
                    //}
                    moves[i].erase();
                    //moves[i + 1].erase();
                    continue;
                }
                if (moves[i][1] + 2 == p.get_pos()[1] && moves[i][0] == p.get_pos()[0] && b.get_tool(moves[i]).get_type() != '#')
                {
                    moves[i].erase();
                }
            }
        }
    }


    std::vector<std::string> fin_moves;
    for (int i = 0; i < moves.size(); i++)
    {
        if (moves[i] != "")
        {
            fin_moves.push_back(moves[i]);
        }
    }
    p.setter_valid_moves(fin_moves);
    return moves;
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
    Ne = min(N, E);
    Sw = min(S, W);
    Se = min(S, E);
    Nw = min(N, W);

    //bishop and queen
    if (t.get_type() == 'b' || t.get_type() == 'B' || t.get_type() == 'q' || t.get_type() == 'Q')
    {
        //north east
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

        //south west
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

        //north west
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
        count = Sw + Ne + Nw;


        //south east
        while (counter < Se)
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
        if (t.get_type() == 'q' || t.get_type() == 'Q')
        {
            queen_counter = Ne + Sw + Se + Nw;
        }
        counter = 0;
        count = S + queen_counter;

        //south
        while (counter < S)
        {
            count--;
            if (b.get_tool(valid_moves[count]).get_type() != '#')
            {
                new_vector.push_back(valid_moves[count]);    //skip
                break;
            }
            new_vector.push_back(valid_moves[count]);

            counter++;
        }

        counter = 0;
        count = S + queen_counter;

        //north
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
        count = 7 + W + queen_counter;

        //west
        while (counter < W)
        {
            count--;
            if (b.get_tool(valid_moves[count]).get_type() != '#')
            {
                new_vector.push_back(valid_moves[count]);    //skip
                break;
            }
            new_vector.push_back(valid_moves[count]);

            counter++;
        }
        counter = 0;
        count = 7 + W + queen_counter;

        //east
        while (counter < E)
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

                else if (t.get_type() == 'B')
                {
                    Bishop r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(14);
                    new_vector = change_vector(new_vector, b, t);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'Q')
                {
                    Queen r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(28);
                    new_vector = change_vector(new_vector, b, t);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'N')
                {
                    Knight r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(8);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'K')
                {
                    King r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(8);
                    new_vector = change_vector(new_vector, b, t);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'P')
                {
                    Pawn r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(6);
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

                else if (t.get_type() == 'b')
                {
                    Bishop r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(14);
                    new_vector = change_vector(new_vector, b, t);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'q')
                {
                    Queen r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(28);
                    new_vector = change_vector(new_vector, b, t);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'n')
                {
                    Knight r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(28);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'k')
                {
                    King r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(8);
                    new_vector = change_vector(new_vector, b, t);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'p')
                {
                    Pawn r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(6);
                    new_vector = change_vector(new_vector, b, t);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }
            }
        }
    }
    return check_vector;
}

int check_check(std::vector<std::string> valid_moves, char king_check, Board b, bool turn, Game& g)
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