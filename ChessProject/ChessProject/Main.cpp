#include <iostream>
#include "Game.h"
#include "Board.h"
#include "Tool.h"


void main()
{
	Board b;
	Game g("RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
	//Board b("RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr0");
	b = g.get_board();
	b.print_board();
	Tool t = b.get_tool("e1");
	std::cout << t.get_type() << std::endl << std::endl;
	b.move_piece("e5", t);
	b.print_board();
}