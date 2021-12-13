#include <iostream>
#include "Game.h"
#include "Board.h"
#include "Tool.h"


void main()
{
	//Tool t("e2", 'p');
	//Game g("RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
	Board b("RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr0");
	b.print_board();
	//b.move_piece("e4", t);
	//b.print_board();
}