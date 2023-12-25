#pragma once
#include <curses.h>
#include <cstdlib>
#include "List.h"

enum color
{
	RANDOM = -1,
	WHITE,
	RED,
	GREEN,
	YELLOW,
	BLUE
};

class Visualizer
{
public:
	Visualizer(List* _list);
	Visualizer(List* _list, char _bar);

	void changeList(List* _list);

	void display(bool _refresh = true);
	void setColor(int _color);
	void highlightBar(int _index, int _color, bool _refresh = true);

private:
	List* list;
	int width = 120;
	int height = 30;
	char bar = '#';
	char empty = ' ';
	int barWidth;
	int barHeightScale;
	int color = WHITE;

	void updateScale();
	void initColors();
	int selectColorPair(int _color);
	void displayBar(int _index);
	void displayEmptySpace();
};

