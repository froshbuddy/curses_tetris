#define MAXWIDTH 500
#define MAXHEIGHT 400
#include <ncurses.h>

#ifndef __TETRIS_H__

#define __TETRIS_H__
using namespace std;

struct coords
{
	int x;
	int y;
};

struct screen_t{
	char elts[MAXWIDTH][MAXHEIGHT];
	int width;
	int height;
	coords top;
	screen_t(int w, int h);
	void draw(WINDOW *w);
};

enum blockType{
	LINE,
	SQUARE,
	TBLOCK,
	RIGHTL,
	LEFTL,
	RIGHTS,
	LEFTS
};


struct block_t
{
	blockType type;
	coords points[4]; //points[0] is the pivot pt
	screen_t *s;
	block_t(blockType t, screen_t *scr, bool &flag)
	{
		type=t;
		s=scr;
		int topx=s->top.x;
		int topy=s->top.y;
		switch(t)//Block initialization
		{
			case LINE:
				points[3]=s->top;

				points[2].x=topx;
				points[2].y=topy-1;

				points[0].y=topy-2;
				points[0].x=topx;

				points[1].y=topy-3;
				points[1].x=topx;
				break;
			case SQUARE:
				points[3]=s->top;

				points[2].x=topx-1;
				points[2].y=topy;

				points[0].y=topy-1;
				points[0].x=topx;

				points[1].y=topy-1;
				points[1].x=topx-1;
				break;
			case TBLOCK:
				points[3]=s->top;

				points[0].y=topy-1;
				points[0].x=topx;

				points[1].y=topy-2;
				points[1].x=topx;

				points[2].y=topy-1;
				points[2].x=topx+1;
				break;
			case RIGHTL:
				points[3]=s->top;

				points[2].x=topx;
				points[2].y=topy-1;

				points[0].y=topy-2;
				points[0].x=topx;

				points[1].y=topy-2;
				points[1].x=topx-1;
				break;
			case LEFTL:
				points[3]=s->top;

				points[2].x=topx;
				points[2].y=topy-1;

				points[0].y=topy-2;
				points[0].x=topx;

				points[1].y=topy-2;
				points[1].x=topx+1;
				break;
			case RIGHTS:
				points[0]=s->top;

				points[1].y=topy;
				points[1].x=topx+1;

				points[2].y=topy-1;
				points[2].x=topx;

				points[3].y=topy-1;
				points[3].x=topx-1;
				break;
			case LEFTS:
				points[0]=s->top;

				points[1].y=topy-1;
				points[1].x=topx+1;

				points[2].y=topy-1;
				points[2].x=topx;

				points[3].y=topy;
				points[3].x=topx-1;
				break;
		}	
		for(int i=0; i<4; i++)
		{
			int bx=points[i].x;
			int by=points[i].y;
			if(s->elts[by][bx]=='H')
			{
				flag=false;
				break;
			}
			s->elts[by][bx]='H';
		}
	}

	bool fall() //basic functionality, to be improved
	{
		
		for(int i=0; i<4; i++)
		{
			int bx=points[i].x;
			int by=points[i].y;
			s->elts[by][bx]=' ';
		}
		for(int i=0; i<4; i++)
		{
			int bx=points[i].x;
			int by=points[i].y;
			if((by-1<=0) || (s->elts[by-1][bx]=='H'))
			{
				for(int j=0; j<4; j++)
				{
					int Bx=points[j].x;
					int By=points[j].y;
					s->elts[By][Bx]='H';
				}
				return false;
			}
		}
		for(int i=0; i<4; i++)
		{
			points[i].y--;
			int bx=points[i].x;
			int by=points[i].y;
			s->elts[by][bx]='H';
		}
		return true;
	}

	void shift(bool left)
	{
		int off=(left ? -1 : 1);
		for(int i=0; i<4; i++)
		{
			int bx=points[i].x;
			int by=points[i].y;
			s->elts[by][bx]=' ';
		}
		for(int i=0; i<4; i++)
		{
			int bx=points[i].x;
			int by=points[i].y;

			if((s->elts[by][bx+off]=='H')||(s->elts[by][bx+off]=='X'))
			{
				for(int j=0; j<4; j++)
				{
					int Bx=points[j].x;
					int By=points[j].y;
					s->elts[By][Bx]='H';
				}
				return;
			}
		}
		for(int i=0; i<4; i++)
		{
			points[i].x+=off;
			int bx=points[i].x;
			int by=points[i].y;
			s->elts[by][bx]='H';
		}
		return;
	}

	void rotate()
	{
		return;
	}
};

screen_t::screen_t(int w, int h)
{
	width=w+2;
	height=h+2;
	top.x=w/2;
	top.y=h;
	for(int i=0; i<width; i++)
	{
		for(int j=0; j<height; j++)
		{
			elts[j][i]=' ';
		}
	}
	for(int i=0; i<width; i++)
	{
		elts[0][i]='X';
		elts[height-1][i]='X';
	}
	for(int i=0; i<height; i++)
	{
		elts[i][0]='X';
		elts[i][width-1]='X';
	}
}

void screen_t::draw(WINDOW *w)
{
	for(int i=height-1; i>=0; i--)
	{
		for(int j=0; j<width; j++)
		{
			waddch(w,elts[i][j]);
		}
		waddch(w,'\n');
	}
}

#endif //__TETRIS_H__