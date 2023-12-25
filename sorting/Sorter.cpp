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

			if (*selection(1).selectedInt > *selection(2).selectedInt)
			{
				swapSelections(selection(1), selection(2));
				swaps++;
				if (_extraVisualization) display();
			}
			comparisons++;

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
			if (*selection(1).selectedInt > *selection(2).selectedInt)
			{
				selection(1).selectInt(i + iterations);
			}
			comparisons++;

			removeSelectionById(2);
		}
		if (_extraVisualization) display();
		swapSelections(selection(0), selection(1));
		if (_extraVisualization) display();
		swaps++;
		makeSelection(iterations - 1, BLUE, 3);
		removeSelectionById(0);
		removeSelectionById(1);
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
		Selection selection1 = makeSelection(i, GREEN);
		Selection selection2 = makeSelection(i + 1, WHITE);

		display();
		if (*selection1.selectedInt > *selection2.selectedInt)
		{
			status = "list not sorted properly";
			selections.pop_back();
			selections.pop_back();
			makeSelection(i, RED);
			makeSelection(i + 1, RED);
			isSorted = false;
			displayWithForcedPause();
			break;
		}

		selections.pop_back();
	}

	if (isSorted)
	{
		status = "list properly sorted";
		displayWithForcedPause();
	}
	status = "idle";
	selections.clear();
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
	selections.push_back(newSelection);
	return selections.back();
}
void Sorter::removeSelectionById(int _id)
{
	int index = 0;
	for (auto& selection : selections)
	{
		if (selection.id == _id)
			break;
		index++;
	}

	vector<Selection>::iterator selectionIterator = selections.begin() + index;
	selections.erase(selectionIterator);
}
void Sorter::removeSelectionByColor(int _color, bool removeAll)
{
	for (auto& selection : selections)
		if (selection.selectionColor == _color)
		{
			removeSelectionById(selection.id);
			if (!removeAll) break;
		}
}
Sorter::Selection& Sorter::selection(int _id)
{
	for (auto& selection : selections)
		if (selection.id == _id)
			return selection;
}
void Sorter::removeRecentSelection()
{
	selections.pop_back();
}
void Sorter::swapSelections(Selection& _left, Selection& _right)
{
	swap(*_left.selectedInt, *_right.selectedInt);
}
void Sorter::swapSelections(Selection* _left, Selection* _right)
{
	swap(*_left->selectedInt, *_right->selectedInt);
}