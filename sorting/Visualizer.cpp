#include "Visualizer.h"

Visualizer::Visualizer(List* _list)
	: list(_list)
{
	updateScale();
}
Visualizer::Visualizer(List* _list, char _bar)
	: Visualizer(_list)
{
	bar = _bar;
}

void Visualizer::changeList(List* _list)
{
	list = _list;
}

void Visualizer::display(bool _refresh)
{
	initColors();
	attron(COLOR_PAIR(color));
	updateScale();
	clear();
	displayEmptySpace();
	for (int i = 0; i < list->size(); i++)
		displayBar(i);
	attroff(COLOR_PAIR(color));
	if (_refresh) refresh();
}
void Visualizer::setColor(int _color)
{
	color = selectColorPair(_color);
}
void Visualizer::highlightBar(int _index, int _color, bool _refresh)
{
	updateScale();
	initColors();
	attron(COLOR_PAIR(selectColorPair(_color)));
	displayBar(_index);
	attroff(COLOR_PAIR(selectColorPair(_color)));
	if (_refresh) refresh();
}

//private
void Visualizer::updateScale()
{
	barWidth = width / list->size();
	barHeightScale = height / list->max();
}
void Visualizer::initColors()
{
	if (has_colors() == FALSE)
	{
		endwin();
		exit(1);
	}

	start_color();
	init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
}
int Visualizer::selectColorPair(int _color)
{
	return (_color == RANDOM) ? rand() % 5 : _color;
}
void Visualizer::displayBar(int _index)
{
	for (int y = 0; y < list->at(_index) * barHeightScale; y++)
		for (int x = _index * barWidth; x < (_index + 1) * barWidth; x++)
			mvaddch(height - 1 - y, x, bar);
}
void Visualizer::displayEmptySpace()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			mvaddch(y, x, empty);
		}
	}
}