#include "List.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

List::List(string name, int a, ...)
{
	this->name = name;
	int b = a;
	va_list value;
	va_start(value, a);

	while (b != -1)
	{
		this->size++;
		this->list.push_back(b);
		b = va_arg(value, int);
	}

	va_end(value);
}

void List::printList()
{
	cout << this->name << " (" << this->size << ") " << ": (";
	for (int i = 0 ; i < this->size ; i++)
	{
		cout << this->list.at(i);
		if (i != this->size-1 ) cout << " ";
	}
	cout << ")" << endl;
}

void List::shuffle(int times)
{
	for (int i = 0; i < times; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			swap(this->list.at(j), this->list.at(rand() % (this->size-1)));
		}
	}
}

void List::randomize(int rSize)
{
	if (rSize == -1) { rSize = this->size; }
	this->list.clear();
	this->list.reserve(rSize);
	this->size = rSize;
	for (int i = 0; i < rSize; i++)
	{
		int randomInt = rand() % rSize;
		this->list.push_back(randomInt);
	}
}

void List::bubbleSort()
{
	int swaps = 0;
	int comparisons = 0;

	int leastElementIndex;

	for (int iteration = 0; iteration < this->size; iteration++)
	{
		leastElementIndex = iteration;
		for (int i = iteration; i < this->size; i++)
		{
			if (this->list[i+1] < this->list[leastElementIndex])
			{
				leastElementIndex = i + 1;
			}
			comparisons++;
		}
		swap(this->list[leastElementIndex], this->list[iteration]);
		swaps++;
		int progress = ceil(iteration * 100 / this->size)+1;
		int nextProgress = ceil((iteration + 1) * 100 / this->size)+1;
		if (progress < nextProgress) cout << "Progress :" << progress << "%" << endl;
	}
}

void List::selectionSort()
{
	int swaps = 0;
	int comparisons = 0;

	int leastElementIndex;

	for (int iteration = 0; iteration < this->size; iteration++)
	{
		leastElementIndex = iteration;
		for (int i = iteration; i < this->size; i++)
		{
			if (this->list[i+1] < this->list[leastElementIndex])
			{
				leastElementIndex = i + 1;
			}
			comparisons++;
		}
		swap(this->list[leastElementIndex], this->list[iteration]);
		swaps++;
		int progress = ceil(iteration * 100 / this->size)+1;
		int nextProgress = ceil((iteration+1) * 100 / this->size)+1;
		if (progress < nextProgress) cout << "Progress :" << progress << "%" << endl;
	}
}
