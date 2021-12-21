/*
 Nativ & Ido 
CHESS PROJECT
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


void main()
{
    int error = 0, countTurns = 0, i = 0;
    Board b;
    Tool t;
    string adress_dst = "ab";
    string adress_src = "ab";
    string adr = "abcd";  

    bool turn = WHITE; //true - white turn | false - black turn
    char king_check = 'K';  //K - white turn |k - black turn

    string error_code = "ab";

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
    // msgToGraphics contain the board string accord the protocol

    strcpy_s(msgToGraphics, "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr1"); 
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

        t = b.get_tool(adress_src);

        // error 5 (first cause he checks for existence of the tool index) - only dst 
        if (adress_dst[0] < 97 || adress_dst[0] > 104 || adress_dst[1] < 49 || adress_dst[1] > 56)
        {
            error = invalid_index;
        }

        if (error == valid_move)
        {
            error = g.check_tool(t, adress_dst, adress_src, king_check, b);  //handle with error 
        }

        if (error == valid_move || error == valid_check || error == mate)         //valid move 
        {
            countTurns++;
        }

        if (countTurns % 2 == 0)      //change turn
        {
            g.set_turn(WHITE);
            king_check = 'K';
        }
        else
        {
            g.set_turn(BLACK);
            king_check = 'k';
        }

        /******* JUST FOR EREZ DEBUGGING ******/
        int r = rand() % 10; // just for debugging......
        msgToGraphics[0] = (char)(error + '0');             //error number --> char
        msgToGraphics[1] = 0;
        /******* JUST FOR EREZ DEBUGGING ******/

        // return result to graphics		
        p.sendMessageToGraphics(msgToGraphics);

        // get message from graphics
        adr = p.getMessageFromGraphics();

    }
    p.close();
}
