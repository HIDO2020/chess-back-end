#include <iostream>
#include "Game.h"
#include "Board.h"
#include "Tool.h"


void main()
{
	//Game g("RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
	Board b("RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr0");
	b.print_board();
	Tool t = b.get_tool("e4");
	std::cout << t.get_type() << std::endl << std::endl;
	//b.move_piece("e4", t);
	b.print_board();
}