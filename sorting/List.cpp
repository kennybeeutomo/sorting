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
List::List(string _name)
{
	name = _name;
}
void List::printList() const
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
int List::size() const
{
	return list.size();
}
int List::max() const
{
	int maxInt = list[0];
	for (const int& i : list)
		if (i > maxInt) maxInt = i;
	return maxInt;
}
int List::min() const
{
	int minInt = list[0];
	for (const int& i : list)
		if (i < minInt) minInt = i;
	return minInt;
}
string List::getName() const
{
	return name;
}

void List::orderedList(int _size)
{
	if (_size > 30) _size = 30;
	list.clear();
	list.reserve(_size);
	for (int i = 0; i < _size; i++)
		list.push_back(i+1);
}
void List::reversedList(int _size)
{
	if (_size > 30) _size = 30;
	list.clear();
	list.reserve(_size);
	for (int i = 0; i < _size; i++)
		list.push_back(_size-i);
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

//private
void List::initRandom(int& _randomizeSize)
{
	if (_randomizeSize < -1) return;
	if (_randomizeSize == -1) _randomizeSize = size();
	list.clear();
	list.reserve(_randomizeSize);
}
