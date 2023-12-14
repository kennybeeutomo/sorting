#include "List.h"

List::List(string _name, int a, ...)
{
	name = _name;
	int b = a;
	va_list value;
	va_start(value, a);

	while (b != -1)
	{
		list.push_back(b);
		b = va_arg(value, int);
	}

	va_end(value);
}

void List::printList()
{
	cout << name << " (" << size() << ") " << ": (";
	for (int i = 0 ; i < size() ; i++)
	{
		cout << list.at(i);
		if (i != size() - 1) cout << " ";
	}
	cout << ")" << endl;
}

int& List::operator[](int _index)
{
	return list.at(_index);
}

int& List::at(int _index)
{
	return list.at(_index);
}

List& List::operator<<(int _number)
{
	list.push_back(_number);
	return *this;
}

void List::operator=(vector<int> _list)
{
	list = _list;
}

vector<int> List::extract()
{
	return list;
}

int List::size()
{
	return list.size();
}

int List::max()
{
	int maxInt = list[0];
	for (int& i : list)
		if (i > maxInt) maxInt = i;
	return maxInt;
}

int List::min()
{
	int minInt = list[0];
	for (int& i : list)
		if (i < minInt) minInt = i;
	return minInt;
}

void List::shuffle(int _times)
{
	for (int i = 0; i < _times; i++)
	{
		for (int j = 0; j < size(); j++)
		{
			swap(list.at(j), list.at(rand() % (size() - 1)));
		}
	}
}

void List::randomize(int _randomizeSize)
{
	initRandom(_randomizeSize);
	for (int i = 0; i < _randomizeSize; i++)
	{
		int randomInt = 1 + (rand() % (_randomizeSize-1));
		list.push_back(randomInt);
	}
}

void List::randomizeRange(int _min, int _max, int _randomizeSize)
{
	initRandom(_randomizeSize);
	for (int i = 0; i < _randomizeSize; i++)
	{
		int randomInt = _min + (rand() % (_max - _min));
		list.push_back(randomInt);
	}
}

void List::initRandom(int& _randomizeSize)
{
	if (_randomizeSize < -1) return;
	if (_randomizeSize == -1) _randomizeSize = size();
	list.clear();
	list.reserve(_randomizeSize);
}
