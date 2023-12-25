#include <iostream>
#include <conio.h>
#include <curses.h>
#include "Sorter.h"

int main()
{
	initscr();
	noecho();
	srand(static_cast<unsigned>(time(0)));

	List l1("List1");
	l1.randomizeRange(1, 30, 20);

	Visualizer v1(&l1);
	Sorter s1(&l1, &v1);
	s1.pauseMode = true;
	s1.delay = 0;

	while (true)
	{
		s1.bubbleSort();
		s1.shuffle();
		s1.selectionSort();
		s1.shuffle();
	}

	refresh();
	endwin();
	return 0;
}