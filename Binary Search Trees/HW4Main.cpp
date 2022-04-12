#include "Random.h"
#include "Vector.h"
#include "BST.h"
#include <iostream>

template <typename T>
void balance_BST(BinarySearchTree<T>&);

int main()
{
	int amount;
	std::cout << "How many random integers will the binary search tree have? ";
	std::cin >> amount;

	rand_seed();
	BinarySearchTree<int> myBST;
	Vector<int> numVec;
	random_vector_norep(amount, 1, 300, numVec, 0);
	for (int i = 0; i < amount; i++)
		myBST.insert(numVec[i]);
	numVec.empty();

	myBST.printTree();
	myBST.printInternal();
	myBST.depth();
	
	balance_BST(myBST);
	myBST.printTree();
	myBST.depth();

	return 0;
}

template <typename T>
void balance_BST(BinarySearchTree<T>& mybst)
{
	Vector<T> values;
	mybst.collect_values(values);
	mybst.makeEmpty();
	
}