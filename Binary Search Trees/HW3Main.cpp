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
	for (int i = 0; i < numVec.size(); i++)
		myBST.insert(numVec[i]);
	numVec.empty();

	myBST.printTree();
	std::cout << endl;
	myBST.printInternal();
	std::cout << myBST.depth() << endl << endl;
	
	balance_BST(myBST);
	myBST.printTree();
	std::cout << endl;
	myBST.printInternal();
	std::cout << myBST.depth() << endl << endl;

	return 0;
}

template <typename T>
void balance_BST(BinarySearchTree<T>& mybst)
{
	Vector<T> values;
	mybst.collect_values(values);
	mybst.makeEmpty();
	balance_BST_inner(values, 0, values.size(), mybst);
}

template <typename T>
void balance_BST_inner(Vector<T>& vec, int begin, int end, BinarySearchTree<T>& bst)
{
	if (begin == end - 1) // At the first element in segment, insert it now
	{
		bst.insert(vec[begin]);
		return;
	}

	if (end  == begin + 1) // At the last element in segment, insert it now
	{
		bst.insert(vec[end-1]);
		return;
	}

	int mid = begin + (end - begin) / 2;
	if (mid != begin && mid != end) // At the middle element in segment, insert then recurse for both branches
	{
		bst.insert(vec[mid]);
		balance_BST_inner(vec, begin, mid, bst);
		balance_BST_inner(vec, mid, end, bst);
	}
	else
		;
}