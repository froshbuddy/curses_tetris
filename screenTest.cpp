#include "screen.h"

int main()
{
	WINDOW *w=initscr();
	screen_t s(30, 30);
	elt_t me('J',14,14,&s);
	s.draw();
	refresh();
	keypad(w, TRUE);
	int inp=getch();
	while(inp!=(int)'q')
	{
		switch(inp)
		{
			case KEY_UP:
				me.move(me.X-1,me.Y);
				break;
			case KEY_LEFT:
				me.move(me.X,me.Y-1);
				break;
			case KEY_DOWN:
				me.move(me.X+1,me.Y);
				break;
			case KEY_RIGHT:
				me.move(me.X,me.Y+1);
				break;
		}
		erase();
		s.draw();
		refresh();
		inp=getch();
	}
	keypad(w, FALSE);
	endwin();
}
