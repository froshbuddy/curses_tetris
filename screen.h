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
		X=x;
		Y=y;
		screen->elts[x][y]=rep;
	}
	void move(int x, int y)
	{
		if(screen->elts[x][y]=='%') return;
		screen->elts[X][Y]=' ';
		X=x;
		Y=y;
		screen->elts[x][y]=rep;
	}
};

screen_t::screen_t(int w, int h)
{
	width=w;
	height=h;
	for(int i=0; i<width; i++)
	{
		for(int j=0; j<height; j++)
		{
			elts[i][j]=' ';
		}
	}
	for(int i=0; i<width; i++)
	{
		elts[i][0]='%';
		elts[i][height-1]='%';
	}
	for(int i=0; i<height; i++)
	{
		elts[0][i]='%';
		elts[width-1][i]='%';
	}
}

void screen_t::draw()
{
	for(int i=0; i<width; i++)
	{
		for(int j=0; j<height; j++)
		{
			addch(elts[i][j]);
		}
		addch('\n');
	}
}
