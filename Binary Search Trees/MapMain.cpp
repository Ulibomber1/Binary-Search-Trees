#include <iostream>
#include <string>
#include <cstdlib>
#include "Map.h"

using namespace std;

int main()
{
	Map<string, int> basket;
	string fruit;
	int count;
	for (int i = 1; i <= 5; ++i)
	{
		cout << "Which fruit and how many? ";
		cin >> fruit >> count;
		cout << endl << endl;
		basket[fruit] = count;
	}

	basket.printMap();
	cout << endl << endl;
	cout << "Change number of? ";
	cin >> fruit;
	cout << "To what new count? ";
	cin >> count;
	cout << endl << endl;

	basket[fruit] = count;
	basket.printMap();
	cout << endl << endl;

	string otherfruit;
	cout << "two fruits to remove? ";
	cin >> fruit >> otherfruit;
	cout << endl << endl;

	basket.remove(fruit);
	basket.remove(otherfruit);
	basket.printMap();

	return 0;
}
