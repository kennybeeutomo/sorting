#include <iostream>
#include <conio.h>
#include "List.h"

using namespace std;

int main()
{
	srand(time(0));

	List l1("List1",
		2, 4, 5, 3, 1, 3, 1, 6, 8, 2, 0, 1
		, -1);

	int rSize;
	cin >> rSize;

	cout << "randomizing..." << endl;
	l1.randomize(rSize);
	//l1.printList();
	cout << "randomized" << endl << endl;
	_getch();
	cout << "sorting..." << endl;
	l1.selectionSort();
	//l1.printList();
	cout << "sorted" << endl;

	return 0;
}