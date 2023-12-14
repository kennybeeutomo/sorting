#include <iostream>
#include <conio.h>
#include <curses.h>
#include "List.h"
#include "Visualizer.h"

int main()
{
	initscr();
	noecho();
	srand(time(0));

	List l1("List1",
		2,20,11,14,1,7,9,17
		, -1);

	Visualizer v1(&l1);
	v1.barWidth = 5;
	l1.randomizeRange(1, 31, 23);
	v1.display();

	while (getch()!='c')
	{
		clear();
		l1.shuffle();
		v1.display();
	}

	refresh();
	endwin();
	return 0;
}