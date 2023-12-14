#pragma once
#include <curses.h>
#include "List.h"

class Visualizer
{
public:
	unsigned int barWidth = 1;

	Visualizer(List* _list);
	Visualizer(List* _list, char _bar);

	void changeList(List* _list);

	void display();

private:
	List* list;
	int height;
	int width;
	char bar = '#';
	char empty = ' ';

	void updateHeightAndWidth();
};

