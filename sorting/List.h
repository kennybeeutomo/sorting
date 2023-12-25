#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <stdarg.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::swap;

class List
{
	public:
		List(string _name, int a, ...);
		List(string _name);
		void printList() const;

		int& operator[](int _index);
		int& at(int _index);
		List& operator<<(int _number);
		void operator=(vector <int> _list);
		
		vector <int> extract();
		int size() const;
		int max() const;
		int min() const;
		string getName() const;

		void orderedList(int _size);
		void reversedList(int _size);
		void randomize(int _randomizeSize = -1); //-1 = don't change list size
		void randomizeRange(int _min, int _max, int _randomizeSize = -1);

	private:
		string name = "Unnamed List";
		vector <int> list;
		void initRandom(int& _randomizeSize);
};