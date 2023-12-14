#include "Visualizer.h"

Visualizer::Visualizer(List* _list)
	: list(_list), height(_list->max()), width(_list->size())
{ }

Visualizer::Visualizer(List* _list, char _bar)
	: Visualizer(_list)
{
	bar = _bar;
}

void Visualizer::updateHeightAndWidth()
{
	height = list->max();
	width = list->size();
}

void Visualizer::changeList(List* _list)
{
	list = _list;
	height = _list->max();
	width = _list->size();
}

void Visualizer::display()
{
	updateHeightAndWidth();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			char c = (list->at(x) > y) ? bar : empty;
			for (int barX = 0; barX < barWidth; barX++)
				mvaddch(height - 1 - y, barWidth * x + barX, c);
		}
	}
	refresh();
}