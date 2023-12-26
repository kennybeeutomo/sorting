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
	l1.randomizeRange(1, 30, 40);

	Visualizer v1(&l1);
	Sorter s1(&l1, &v1);

	s1.pauseMode = false;
	s1.delay = 0;
	bool extraVisualization = false;

	while (true)
	{
		l1.randomizeRange(1, 30, 40);
		s1.displayWithForcedPause();
		s1.bubbleSort(extraVisualization);
		s1.shuffle();
		s1.selectionSort(extraVisualization);
		s1.shuffle();
		s1.insertionSort(extraVisualization);
		s1.shuffle();
	}

	refresh();
	endwin();
	return 0;
}