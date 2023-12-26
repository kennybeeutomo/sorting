#pragma once
#include "List.h"
#include "Visualizer.h"

class Sorter
{
public:
	bool pauseMode = false;
	int delay = 0;

	Sorter(List* _list, Visualizer* _visualizer);
	void displayStatus();
	void display();
	void displayWithForcedPause();
	void togglePauseMode();
	void shuffle();

	void bubbleSort(bool _extraVisualization = false);
	void selectionSort(bool _extraVisualization = false);
	void insertionSort(bool _extraVisualization = false);

private:
	List* list;
	Visualizer* visualizer;
	const char* status = "idle";
	int comparisons = 0;
	int swaps = 0;
	bool checkSort();
	bool pause();
	void startSort(const char* _sortName);
	void endSort();
	
	struct Selection
	{
		List* list;
		vector <Selection>* selections;
		int id;
		int* comparisons;

		int* selectedInt;
		int selectedIndex;
		int selectionColor;

		int getInt();
		void selectInt(int _index);
		void selectRandomInt();

		bool operator<(Selection& _selection);
		bool operator>(Selection& _selection);
		bool operator==(Selection& _selection);
		bool operator<=(Selection& _selection);
		bool operator>=(Selection& _selection);
		bool operator!=(Selection& _selection);

		int getIndex();

		Selection(List* _list, vector <Selection>* _selections, int _index, int _color);
	};

	vector <Selection> selections;
	void clearSelections();
	Selection& makeSelection(int _index, int _color, int _id = -1);
	void eraseByIndex(int _index);
	bool removeSelectionById(int _id);
	bool removeSelectionByColor(int _color);
	bool removeAllSelectionById(int _id);
	bool removeAllSelectionByColor(int _color);
	void removeRecentSelection(int _times = 1);
	Selection& selection(int _id); //gets selection by Id
	void swapSelections(Selection& _left, Selection& _right);
	void swapSelections(Selection* _left, Selection* _right);
};