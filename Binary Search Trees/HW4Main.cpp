#include "Random.h"
#include "Vector.h"
#include "BST.h"
#include <iostream>

template <typename T>
void balance_BST(BinarySearchTree<T>&);
template <typename T>
void balance_BST_inner(Vector<T>&, int, int, BinarySearchTree<T>&);


int main()
{
	int amount = 0;
	std::cout << "How many random integers will the binary search tree have? ";
	std::cin >> amount;
	std::cout << endl << endl;

	rand_seed();
	BinarySearchTree<int> myBST;
	Vector<int> numVec;
	random_vector_norep(amount, 1, 300, numVec, 0);
	for (int i = 0; i < amount ; i++)
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
	balance_BST_inner(values, 0, values.size() - 1, mybst);
}

template <typename T>
void balance_BST_inner(Vector<T>& vec, int begin, int end, BinarySearchTree<T>& bst)
{
	int mid = int((end - begin) / 2);
	if (mid == begin)
	{
		bst.insert(vec[mid]);
	}
	else if (mid == end)
	{
		bst.insert(vec[mid]);
	}
	else if (mid != begin && mid != end)
	{
		balance_BST_inner(vec, begin, mid, bst);
		bst.insert(vec[mid]);
		balance_BST_inner(vec, mid, end, bst);
	}
	else
		;
}