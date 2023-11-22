#pragma once
#include <vector>
#include <string>
#include <stdarg.h>
using namespace std;

class List
{
	public:
		List(string name, int a, ...);
		void printList();
		void shuffle(int times = 1);
		void randomize(int randomizeSize = -1);

		void bubbleSort();
		void selectionSort();

	private:
		string name = "Unnamed List";
		vector <int> list;
		int size;

};