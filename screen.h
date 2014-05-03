#define MAXWIDTH 500
#define MAXHEIGHT 400
#include <ncurses.h>



struct screen_t{
	char elts[MAXWIDTH][MAXHEIGHT];
	int width;
	int height;
	screen_t(int w, int h);
	void draw();
};

struct elt_t{
	char rep;
	screen_t *screen;
	int X;
	int Y;
	elt_t(char r, int x, int y, screen_t *scr)
	{
		screen =scr;
		rep=r;
		int h=screen->height-1;
		X=x;
		Y=y;
		screen->elts[y][x]=rep;
	}
	void move(int x, int y)
	{
		int h=screen->height-1;
		if(screen->elts[y][x]=='%') return;
		screen->elts[Y][X]=' ';
		X=x;
		Y=y;

		screen->elts[Y][X]=rep;
	}
};

screen_t::screen_t(int w, int h)
{
	width=w+2;
	height=h+2;
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

void screen_t::draw()
{
	for(int i=height-1; i>=0; i--)
	{
		for(int j=0; j<width; j++)
		{
			addch(elts[i][j]);
		}
		addch('\n');
	}
}
