#include <iostream>
#include "Game.h"
#include "Board.h"
#include "Tool.h"


void main()
{
	Board b;
	//Board b("RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr0");
	Game g("#######R#######K###########################################rk###0");
	b = g.get_board();
	b.print_board();
	Tool t = b.get_tool("e1");
	
	t.move("e5", b.get_tool("e5"));
	b.move_piece("e5", t);
	t.set_pos("e5");

	b.print_board();

	//Tool t2 = b.get_tool("e5");
	t.move("e8", b.get_tool("e8"));
	b.move_piece("e8", t);
	t.set_pos("e8");

	b.print_board();
}
