#include "Game.h"

Game::Game(std::string _board_string)
{
    this->_is_check_black = false;
    this->_is_check_white = false;
    if (_board_string[64] == '1')       //check who start (and doing the opposite cause of the graphic problem)
    {
        this->_turn = true;
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

void Game::set_turn(const int turn)
{
    this->_turn = turn;
}


/*
function that checking wichh tool to handle and checking for errors
*/
int Game::check_tool(Tool t, string adress_dst, string adress_src, char king_check, Board &b)
{
    std::vector<string> king_valid_moves;
    std::vector<string> new_vector;
    std::vector<string> check_vector;
    std::vector<string> vector_valid_moves;
    int error = 0;

    if (t.get_type() == 'k' || t.get_type() == 'K') //king
    {
        //create king & get valid moves
        King k(t.get_pos(), t.get_type());
        k.set_valid_moves(k.get_pos());
        king_valid_moves = k.get_valid_moves();
        king_valid_moves.resize(9);
        k.setter_valid_moves(king_valid_moves);

        //check for errors
        error = k.move(adress_dst, b.get_tool(adress_dst), this->_turn);

        //error 4
        if (error == valid_move)
        {
            b.move_piece(adress_dst, t);
            k.set_pos(adress_dst);

            check_vector = get_enemy_valid_moves(b);

            //checks if the pos of the king is in the valid moves of the enemy
            if (std::find(check_vector.begin(), check_vector.end(), adress_dst) != check_vector.end())
            {
                error = self_check;
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
        //create rook & get valid moves
        Rook r(t.get_pos(), t.get_type());
        vector_valid_moves.clear();
        r.set_valid_moves(r.get_pos());
        vector_valid_moves = r.get_valid_moves();
        vector_valid_moves.resize(14);
        new_vector.clear();
        //get only the available moves (no skip pieces)
        new_vector = change_vector(vector_valid_moves, t, b);
        r.setter_valid_moves(new_vector);

        //check for errors
        error = r.move(adress_dst, b.get_tool(adress_dst), this->_turn);

        //error 4
        if (error == valid_move)
        {
            b.move_piece(adress_dst, t);

            check_vector = get_enemy_valid_moves(b);

            //checks if the pos of the king is in the valid moves of the enemy
            if (std::find(check_vector.begin(), check_vector.end(), b.get_king(this->_turn).get_pos()) != check_vector.end())
            {
                error = self_check;
                //back
                b.move_piece(adress_src, t);
                Tool t = b.get_tool(adress_dst);
                t.set_type('#');
                b.move_piece(adress_dst, t);
            }

            //check if doing check

            r.set_valid_moves(adress_dst);
            vector_valid_moves = r.get_valid_moves();
            vector_valid_moves.resize(14);
            r.set_pos(adress_dst);

            //get only the available moves (no skip pieces)
            vector_valid_moves = change_vector(vector_valid_moves, t, b);

            //reset check
            this->set_black_check(false);
            this->set_white_check(false);
            if (error == valid_move)
            {
                error = check_check(vector_valid_moves, king_check, b);
            }
        }

    }


    else if (t.get_type() == 'b' || t.get_type() == 'B') //bishop
    {
        //create bishop & get valid moves
        Bishop bi(t.get_pos(), t.get_type());
        bi.set_valid_moves(bi.get_pos());
        vector_valid_moves = bi.get_valid_moves();
        if (vector_valid_moves.size() > 14)
        {
            vector_valid_moves.resize(14);
        }

        //get only the available moves (no skip pieces)
        new_vector = change_vector(vector_valid_moves, t, b);
        bi.setter_valid_moves(new_vector);

        //check for errors
        error = bi.move(adress_dst, b.get_tool(adress_dst), this->_turn);
        //error 4
        if (error == valid_move)
        {
            b.move_piece(adress_dst, t);

            check_vector = get_enemy_valid_moves(b);

            //checks if the pos of the king is in the valid moves of the enemy
            if (std::find(check_vector.begin(), check_vector.end(), b.get_king(this->_turn).get_pos()) != check_vector.end())
            {
                error = self_check;
                //back
                b.move_piece(adress_src, t);
                Tool t = b.get_tool(adress_dst);
                t.set_type('#');
                b.move_piece(adress_dst, t);
            }

            //check if doing check

            bi.set_valid_moves(adress_dst);
            vector_valid_moves = bi.get_valid_moves();
            vector_valid_moves.resize(14);
            bi.set_pos(adress_dst);
            //get only the available moves (no skip pieces)
            vector_valid_moves = change_vector(vector_valid_moves, t, b);

            //reset check
            this->set_black_check(false);
            this->set_white_check(false);
            vector_valid_moves = vector_valid_moves;
            if (error == valid_move)
            {
                error = check_check(vector_valid_moves, king_check, b);
            }
        }
    }


    else if (t.get_type() == 'q' || t.get_type() == 'Q') //Queen
    {
        //create queen & get valid moves
        Queen q(t.get_pos(), t.get_type());
        //slicing
        q.set_valid_moves(q.get_pos());
        vector_valid_moves = q.get_valid_moves();
        vector_valid_moves.resize(28);
        //get only the available moves (no skip pieces)
        new_vector = change_vector(vector_valid_moves, t, b);
        q.setter_valid_moves(new_vector);
        //check for errors
        error = q.move(adress_dst, b.get_tool(adress_dst), this->_turn);
        //error 4
        if (error == valid_move)
        {
            b.move_piece(adress_dst, t);

            check_vector = get_enemy_valid_moves(b);

            //checks if the pos of the king is in the valid moves of the enemy
            if (std::find(check_vector.begin(), check_vector.end(), b.get_king(this->_turn).get_pos()) != check_vector.end())
            {
                error = self_check;
                //back
                b.move_piece(adress_src, t);
                Tool t = b.get_tool(adress_dst);
                t.set_type('#');
                b.move_piece(adress_dst, t);
            }

            //check if doing check

            q.set_valid_moves(adress_dst);
            vector_valid_moves = q.get_valid_moves();
            vector_valid_moves.resize(28);

            t.set_pos(adress_dst);
            //get only the available moves (no skip pieces)
            new_vector = change_vector(vector_valid_moves, t, b);

            //reset check
            this->set_black_check(false);
            this->set_white_check(false);
            if (error == valid_move)
            {
                error = check_check(new_vector, king_check, b);
            }
        }
    }


    else if (t.get_type() == 'n' || t.get_type() == 'N') //knight
    {
        //create knight & get valid moves
        Knight kn(t.get_pos(), t.get_type());
        vector_valid_moves.clear();
        kn.set_valid_moves(kn.get_pos());
        vector_valid_moves = kn.get_valid_moves();
        vector_valid_moves.resize(8);
        //the knight can skip ove pieces
        new_vector = vector_valid_moves;
        kn.setter_valid_moves(new_vector);
        //check for errors
        error = kn.move(adress_dst, b.get_tool(adress_dst), this->_turn);
        //error 4
        if (error == valid_move)
        {
            b.move_piece(adress_dst, t);

            check_vector = get_enemy_valid_moves(b);

            //checks if the pos of the king is in the valid moves of the enemy
            if (std::find(check_vector.begin(), check_vector.end(), b.get_king(this->_turn).get_pos()) != check_vector.end())
            {
                error = self_check;
                //back
                b.move_piece(adress_src, t);
                Tool t = b.get_tool(adress_dst);
                t.set_type('#');
                b.move_piece(adress_dst, t);
            }

            //check if doing check

            kn.set_valid_moves(adress_dst);
            vector_valid_moves = kn.get_valid_moves();
            vector_valid_moves.resize(8);

            //slice
            kn.set_pos(adress_dst);
            //reset check
            this->set_black_check(false);
            this->set_white_check(false);
            if (error == valid_move)
            {
                error = check_check(vector_valid_moves, king_check, b);
            }
        }
    }


    else if (t.get_type() == 'p' || t.get_type() == 'P') //Pawn
    {
        //create pawn & get valid moves
        Pawn p(t.get_pos(), t.get_type());
        vector_valid_moves.clear();
        p.set_valid_moves(p.get_pos());
        vector_valid_moves = p.get_valid_moves();
        vector_valid_moves.resize(6);
        p.setter_valid_moves(vector_valid_moves);
        //get only the available moves (no skip pieces)
        new_vector = change_pawn_vector(p, b);
        p.setter_valid_moves(new_vector);
        //check for errors
        error = p.move(adress_dst, b.get_tool(adress_dst), this->_turn);
        //error 4
        if (error == valid_move)
        {
            b.move_piece(adress_dst, t);

            check_vector = get_enemy_valid_moves(b);

            //checks if the pos of the king is in the valid moves of the enemy
            if (std::find(check_vector.begin(), check_vector.end(), b.get_king(this->_turn).get_pos()) != check_vector.end())
            {
                error = self_check;
                //back
                b.move_piece(adress_src, t);
                Tool t = b.get_tool(adress_dst);
                t.set_type('#');
                b.move_piece(adress_dst, t);
            }
            
            //check if doing check
            p.set_valid_moves(adress_dst);
            vector_valid_moves = p.get_valid_moves();
            vector_valid_moves.resize(8);

            p.set_pos(adress_dst);
            new_vector = change_pawn_vector(p, b);
            //reset check
            this->set_black_check(false);
            this->set_white_check(false);
            if (error == valid_move)
            {
                error = check_check(vector_valid_moves, king_check, b);
            }
        }
    }

    else //#
    {
        error = no_src;
    }

    return error;
}


/*
slicing the vector of the pawn only
*/
std::vector<std::string> Game::change_pawn_vector(Pawn p, Board b)
{
    std::vector<std::string> moves = p.get_valid_moves();
    std::string tmp = "ab";
    moves.resize(4);
    
    for (int i = 0; i < 4; i++)
    {
        if (moves[i] != "")
        {
            /// pawn algorithem:
            /// I have 4 'if' condition for each of the pawn's possible moves
            /// each of the 'if' checks if theres a tool in that positions
            /// and make the right changes according to that
            /// we have one for white (goes up) 
            /// and one for black (only move down
     
            if (p.get_color()) //if white
            {
                if ((moves[i][0] > p.get_pos()[0] || moves[i][0] < p.get_pos()[0]) &&
                    (b.get_tool(moves[i]).get_color() == p.get_color() || b.get_tool(moves[i]).get_type() == '#'))
                {
                    moves[i].erase();
                    continue; //if we erase we need to skip to the beginning otherwise the code will crash
                }

                if (moves[i][1] - 1 == p.get_pos()[1] && moves[i][0] == p.get_pos()[0] && b.get_tool(moves[i]).get_type() != '#')
                {
                    tmp[0] = moves[i][0];
                    tmp[1] = moves[i][1] + 1;
                    
                    for (int j = 0; j < 4; j++)
                    {
                        if (moves[j] == tmp)
                            moves[j].erase();
                    }

                    moves[i].erase();
                    continue;
                }
                if (moves[i][1] - 2 == p.get_pos()[1] && moves[i][0] == p.get_pos()[0] && b.get_tool(moves[i]).get_type() != '#')
                {
                    moves[i].erase();
                }
            }
            else //if black
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
                   
                    for (int j = 0; j < 4; j++)
                    {
                        if (moves[j] == tmp)
                            moves[j].erase();
                    }

                    moves[i].erase();
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
    for (int i = 0; i < moves.size(); i++) //takes the possible moves after their check
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
working by going throught the vector in each direction and push to the other vector 
until tool pops up in the vector and then going into other direction
*/
std::vector<std::string> Game::change_vector(std::vector<std::string> valid_moves, Tool t, Board b)
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
    Sw = std::min(S, W);
    Se = std::min(S, E);
    Nw = std::min(N, W);

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
std::vector<std::string> Game::get_enemy_valid_moves(Board b)
{
    int i = 0, j = 0;
    std::vector<std::string> check_vector;
    std::vector<std::string> new_vector;
    check_vector.clear();
    std::string tmp_curr = "ab";

    //going throught the board
    for (j = 1; j <= 8; j++)
    {
        for (i = 1; i <= 8; i++)
        {
            tmp_curr[0] = j + 96;
            tmp_curr[1] = i + 48;
            Tool t = b.get_tool(tmp_curr);
            //gets only the enemy
            if (this->_turn == WHITE)
            {
                if (t.get_type() == 'R')
                {
                    Rook r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(14);
                    new_vector = change_vector(new_vector, t, b);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'B')
                {
                    Bishop r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(14);
                    new_vector = change_vector(new_vector, t, b);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'Q')
                {
                    Queen r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(28);
                    new_vector = change_vector(new_vector, t, b);
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
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'P')
                {
                    Pawn r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(6);
                    new_vector = change_pawn_vector(r_tmp, b);
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
                    new_vector = change_vector(new_vector, t, b);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'b')
                {
                    Bishop r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(14);
                    new_vector = change_vector(new_vector, t, b);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'q')
                {
                    Queen r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(28);
                    new_vector = change_vector(new_vector, t, b);
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
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }

                else if (t.get_type() == 'p')
                {
                    Pawn r_tmp(t.get_pos(), t.get_type());
                    //slicing
                    r_tmp.set_valid_moves(r_tmp.get_pos());
                    new_vector = r_tmp.get_valid_moves();
                    new_vector.resize(6);
                    new_vector = change_pawn_vector(r_tmp, b);
                    std::copy(new_vector.begin(), new_vector.end(), std::back_inserter(check_vector));
                }
            }
        }
    }
    return check_vector;
}

/*
checking if there king in the valid moves
*/
int Game::check_check(std::vector<std::string> valid_moves, char king_check, Board b)
{
    int error = 0;

    for (std::string i : valid_moves)
    {
        if (b.get_tool(i).get_type() == king_check)
        {
            if (error == valid_move) //valid
            {

                error = valid_check;
                if (this->_turn)
                {
                    this->set_black_check(true);
                }
                else
                {
                    this->set_white_check(true);
                }
            }
        }
    }
    return error;
}