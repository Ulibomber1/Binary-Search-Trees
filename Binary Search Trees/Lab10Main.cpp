#include <iostream>
#include "BST.h"
#include "Random.h"
using namespace std;

int main()
{
	rand_seed();
	BinarySearchTree<int> mybst;
	int how_many;
	cout << "How many random values? ";
	cin >> how_many;
	cout << endl << endl;

	for (int i = 1; i <= how_many; i++)
	{
		mybst.insert(rand_int(1, 250));
	}
	cout << how_many << " values entered" << endl << endl;

	mybst.printTree();
	cout << endl << endl;
	mybst.printInternal();
	cout << endl << endl;

	int next;
	cout << "Now 5 values will be removed." << endl << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << "Which value would you like to remove? ";
		cin >> next;
		cout << endl;
		mybst.remove(next);
	}
	mybst.printTree();
	cout << endl << endl;
	mybst.printInternal();
	cout << endl << endl;

	return 0;
}