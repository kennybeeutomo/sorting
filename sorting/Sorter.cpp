#include "Sorter.h"

//void Sorter::bubbleSort()
//{
//	int swaps = 0;
//	int comparisons = 0;
//
//	int leastElementIndex;
//
//	for (int iteration = 0; iteration < this->list.size(); iteration++)
//	{
//		leastElementIndex = iteration;
//		for (int i = iteration; i < this->list.size(); i++)
//		{
//			if (this->list[i + 1] < this->list[leastElementIndex])
//			{
//				leastElementIndex = i + 1;
//			}
//			comparisons++;
//		}
//		swap(this->list[leastElementIndex], this->list[iteration]);
//		swaps++;
//		int progress = ceil(iteration * 100 / this->list.size()) + 1;
//		int nextProgress = ceil((iteration + 1) * 100 / this->list.size()) + 1;
//		if (progress < nextProgress) cout << "Progress :" << progress << "%" << endl;
//	}
//}
//
//void Sorter::selectionSort()
//{
//	int swaps = 0;
//	int comparisons = 0;
//
//	int leastElementIndex;
//
//	for (int iteration = 0; iteration < this->list.size(); iteration++)
//	{
//		leastElementIndex = iteration;
//		for (int i = iteration; i < this->list.size(); i++)
//		{
//			if (this->list[i + 1] < this->list[leastElementIndex])
//			{
//				leastElementIndex = i + 1;
//			}
//			comparisons++;
//		}
//		swap(this->list[leastElementIndex], this->list[iteration]);
//		swaps++;
//		int progress = ceil(iteration * 100 / this->list.size()) + 1;
//		int nextProgress = ceil((iteration + 1) * 100 / this->list.size()) + 1;
//		if (progress < nextProgress) cout << "Progress :" << progress << "%" << endl;
//	}
//}