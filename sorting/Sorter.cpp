#include "Sorter.h"

Sorter::Sorter(List* _list, Visualizer* _visualizer)
	: list(_list), visualizer(_visualizer)
{
	clearSelections();
}

void Sorter::displayStatus()
{
	mvprintw(0, 0, "Current action: %s", status);
	mvprintw(1, 0, "Comparisons: %d", comparisons);
	mvprintw(2, 0, "Swaps: %d", swaps);
}
void Sorter::display()
{
	visualizer->display(false);
	for (const auto& selection : selections)
		visualizer->highlightBar(selection.selectedIndex, selection.selectionColor, false);
	displayStatus();
	refresh();
	pause();
}
void Sorter::displayWithForcedPause()
{
	bool _pauseMode = pauseMode;
	pauseMode = true;
	display();
	pauseMode = _pauseMode;
}
void Sorter::togglePauseMode()
{
	if (pauseMode == false) pauseMode = true;
	else pauseMode = false;
}
void Sorter::shuffle()
{
	status = "shuffling";
	for (int j = 0; j < list->size(); j++)
	{
		makeSelection(j, GREEN, 1);
		makeSelection(-1, RED, 2);

		display();
		swapSelections(selection(1), selection(2));

		removeSelectionById(1);
		removeSelectionById(2);
	}
	status = "shuffling done";
	clearSelections();
	displayWithForcedPause();
	status = "idle";
}

//sorting algorithms
void Sorter::bubbleSort(bool _extraVisualization)
{
	startSort("bubble sort");

	for (int iterations = 1; iterations < list->size(); iterations++)
	{
		for (int i = 0; i < list->size() - iterations; i++)
		{
			makeSelection(i, GREEN, 1);
			makeSelection(i + 1, RED, 2);

			display();

			if (selection(1) > selection(2))
			{
				swapSelections(selection(1), selection(2));
				if (_extraVisualization) display();
			}

			removeSelectionById(1);
			removeSelectionById(2);
		}
		makeSelection(list->size() - iterations, BLUE);
		if (_extraVisualization) display();
	}

	endSort();
}
void Sorter::selectionSort(bool _extraVisualization)
{
	startSort("selection sort");

	for (int iterations = 1; iterations < list->size(); iterations++)
	{
		makeSelection(iterations - 1, YELLOW, 0);
		makeSelection(iterations - 1, GREEN, 1);

		for (int i = 0; i < list->size() - iterations; i++)
		{
			makeSelection(i + iterations, RED, 2);

			display();
			if (selection(1) > selection(2))
			{
				selection(1).selectInt(i + iterations);
			}

			removeSelectionById(2);
		}
		if (_extraVisualization) display();
		swapSelections(selection(0), selection(1));
		if (_extraVisualization) display();
		makeSelection(iterations - 1, BLUE, 3);

		removeSelectionById(0);
		removeSelectionById(1);
	}

	endSort();
}
void Sorter::insertionSort(bool _extraVisualization)
{
	startSort("insertion sort");

	for (int iterations = 0; iterations < list->size() - 1; iterations++)
	{
		makeSelection(iterations, GREEN, 1);
		makeSelection(iterations + 1, RED, 2);

		display();

		for (int i = iterations; selection(1) > selection(2);)
		{
			swapSelections(selection(1), selection(2));
			if (_extraVisualization) display();
			if (i != 0)
			{
				selection(1).selectInt(selection(1).selectedIndex - 1);
				selection(2).selectInt(selection(2).selectedIndex - 1);
				i--;
				display();
			}
		}

		removeSelectionById(1);
		removeSelectionById(2);
		makeSelection(iterations, BLUE, 3);
	}

	endSort();
}

//private
bool Sorter::checkSort()
{
	status = "checking";
	bool isSorted = true;

	for (int i = 0; i < list->size() - 1; i++)
	{
		makeSelection(i, GREEN, 1);
		makeSelection(i + 1, GREEN, 2);

		display();
		if (*selection(1).selectedInt > *selection(2).selectedInt)
		{
			status = "list not sorted properly";

			removeSelectionById(1);
			removeSelectionById(2);
			
			makeSelection(i, RED);
			makeSelection(i + 1, RED);
			
			isSorted = false;
			displayWithForcedPause();
			break;
		}

		removeSelectionById(1);
		removeSelectionById(2);
		makeSelection(i, GREEN, 3);
	}

	if (isSorted)
	{
		makeSelection(list->size() - 1, GREEN, 3);
		status = "list properly sorted";
		displayWithForcedPause();
	}
	clearSelections();
	status = "idle";
	return isSorted;
}
bool Sorter::pause()
{
	if (pauseMode == true)
	{
		if (getch() == 'c') exit(0);
		else return true;
	}
	else
	{
		napms(delay);
		return false;
	}
}
void Sorter::startSort(const char* _sortName)
{
	status = _sortName;
	comparisons = 0;
	swaps = 0;
}
void Sorter::endSort()
{
	clearSelections();
	status = "sorting done";
	display();
	status = "idle";
	checkSort();
	comparisons = 0;
	swaps = 0;
}

//struct Selection {
void Sorter::Selection::selectInt(int _index)
{
	selectedInt = &(list->at(_index));
	selectedIndex = _index;
}
void Sorter::Selection::selectRandomInt()
{
	selectInt( rand()%list->size() );
}

int Sorter::Selection::getInt()
{
	return *selectedInt;
}

bool Sorter::Selection::operator<(Selection& _selection)
{
	(*comparisons)++;
	return getInt() < _selection.getInt();
}
bool Sorter::Selection::operator>(Selection& _selection)
{
	(*comparisons)++;
	return getInt() > _selection.getInt();
}
bool Sorter::Selection::operator==(Selection& _selection)
{
	(*comparisons)++;
	return getInt() == _selection.getInt();
}
bool Sorter::Selection::operator<=(Selection& _selection)
{
	(*comparisons)++;
	return getInt() <= _selection.getInt();
}
bool Sorter::Selection::operator>=(Selection& _selection)
{
	(*comparisons)++;
	return getInt() >= _selection.getInt();
}
bool Sorter::Selection::operator!=(Selection& _selection)
{
	(*comparisons)++;
	return getInt() != _selection.getInt();
}

int Sorter::Selection::getIndex()
{
	for (int i = 0; i < selections->size(); i++)
		if (selections->at(i).id == this->id)
			return i;
	return -1;
}

Sorter::Selection::Selection(List* _list, vector <Selection>* _selections, int _index, int _color)
{
	list = _list;
	selections = _selections;
	selectionColor = _color;
	id = rand();
	if (_index == -1)
	{
		selectRandomInt();
		return;
	}
	selectInt(_index);
}
//struct Selection }

void Sorter::clearSelections()
{
	selections.clear();
	selections.reserve(list->size() * 3);
}
Sorter::Selection& Sorter::makeSelection(int _index, int _color, int _id)
{
	Selection newSelection(list, &selections, _index, _color);
	if (_id != -1) newSelection.id = _id;
	newSelection.comparisons = &comparisons;
	selections.push_back(newSelection);
	return selections.back();
}
void Sorter::eraseByIndex(int _index)
{
	vector<Selection>::iterator selectionIterator = selections.begin() + _index;
	selections.erase(selectionIterator);
}
bool Sorter::removeSelectionById(int _id)
{
	size_t i = selections.size();
	for (; i-- > 0;)
		if (selections.at(i).id == _id)
		{
			eraseByIndex(i);
			return true;
		}
	return false;
}
bool Sorter::removeSelectionByColor(int _color)
{
	size_t i = selections.size();
	for (; i-- > 0;)
		if (selections.at(i).selectionColor == _color)
		{
			eraseByIndex(i);
			return true;
		}
	return false;
}
bool Sorter::removeAllSelectionById(int _id)
{
	bool success = false;
	while (removeSelectionById(_id)) success = true;
	return success;
}
bool Sorter::removeAllSelectionByColor(int _color)
{
	bool success = false;
	while (removeSelectionByColor(_color)) success = true;
	return success;
}
Sorter::Selection& Sorter::selection(int _id)
{
	for (auto& selection : selections)
		if (selection.id == _id)
			return selection;
	return *selections.end();
}
void Sorter::removeRecentSelection(int _times)
{
	for (;_times!=0;_times--)
		selections.pop_back();
}
void Sorter::swapSelections(Selection& _left, Selection& _right)
{
	swap(*_left.selectedInt, *_right.selectedInt);
	swaps++;
}
void Sorter::swapSelections(Selection* _left, Selection* _right)
{
	swap(*_left->selectedInt, *_right->selectedInt);
	swaps++;
}
