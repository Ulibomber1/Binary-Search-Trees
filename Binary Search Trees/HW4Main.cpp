#include "Random.h"
#include "Vector.h"
#include "BST.h"
#include <iostream>

int main()
{
	int amount;
	std::cout << "How many random integers will the binary search tree have? ";
	std::cin >> amount;

	rand_seed();

	for (int i; i < amount; i++)
	{
		rand_int(1, 300);
		
	}
	return 0;
}