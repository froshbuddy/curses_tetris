#include "tetris.h"
#include <cstdlib>
#include <cstring>
#include <thread>
#include <mutex>
#include <chrono>

#define _GLIBCXX_USE_NANOSLEEP 1

block_t *b;
screen_t *scrn;
mutex screenLock;
bool run;
int type;
WINDOW *w;

void gravity();

int main(int argc, char *argv[])
{
	int winWidth=30;
	int winHeight=30;
	w=initscr();
	screen_t s(winWidth, winHeight);
	scrn=&s;
	run=true;
	type=0;
	b=new block_t((blockType) type, &s, run);
	s.draw(w);
	wrefresh(w);
	keypad(w, TRUE);
	
	thread t(gravity);
	t.detach();
	int inp=getch();
	while(inp!=(int)'c'&&run)
	{
		screenLock.lock();
		switch(inp)
		{
			case KEY_LEFT:
				b->shift(true);
				break;
			case KEY_RIGHT:
				b->shift(false);
				break;
			default:
				if(!b->fall())
				{
					type=(type+1)%7;
					delete b;
					b=new block_t((blockType) type, &s, run);
				}

		}
		werase(w);
		s.draw(w);
		wrefresh(w);
		screenLock.unlock();
		inp=getch();
	}
	run=false;
	keypad(w, FALSE);
	endwin();
}

void gravity()
{
	while(run)
	{
		this_thread::sleep_for(chrono::milliseconds(1500));
		screenLock.lock();
		if(!b->fall())
		{
			type=(type+1)%7;
			delete b;
			b=new block_t((blockType) type, scrn, run);
		}
		werase(w);
		scrn->draw(w);
		wrefresh(w);
		screenLock.unlock();
	}
}