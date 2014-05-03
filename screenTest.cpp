#include "screen.h"
#include <cstdlib>
#include <cstring>

int main(int argc, char *argv[])
{
	int winWidth;
	int winHeight;
	switch(argc)
	{
		case 2:
			winWidth=winHeight=atoi(argv[1]);
			break;
		case 3:
			winWidth=atoi(argv[1]);
			winHeight=atoi(argv[2]);
			break;
		default:
			winWidth=10;
			winHeight=20;
	}
	WINDOW *w=initscr();
	screen_t s(winWidth, winHeight);
	elt_t me('J',winWidth/2,winHeight/2,&s);
	s.draw();
	refresh();
	keypad(w, TRUE);
	int inp=getch();
	while(inp!=(int)'c')
	{
		switch(inp)
		{
			case KEY_UP:
				me.move(me.X,me.Y+1);
				break;
			case KEY_LEFT:
				me.move(me.X-1,me.Y);
				break;
			case KEY_DOWN:
				me.move(me.X,me.Y-1);
				break;
			case KEY_RIGHT:
				me.move(me.X+1,me.Y);
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
