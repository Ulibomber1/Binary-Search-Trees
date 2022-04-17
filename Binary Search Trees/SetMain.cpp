#include <iostream>
#include <Windows.h>
#include "BST_Set.h"
#include "Random.h"
#include "Vector.h"

template <typename T>
Set<T> set_union(const Set<T>&, const Set<T>&);

template <typename T>
Set<T> set_intersection(const Set<T>&, const Set<T>&);

int main()
{
	//Generate two sets of random numbers of size 10
	Vector<int> vec;
	Set<int> set1;
	random_vector_norep(10, 1, 30, vec, 0);
	for (int i = 0; i < vec.size(); i++)
		set1.insert(vec[i]);
	vec.clear();
	Set<int> set2;
	Sleep(1000);
	random_vector_norep(10, 1, 30, vec, 0);
	for (int i = 0; i < vec.size(); i++)
		set2.insert(vec[i]);

	//Compute the union and intersection of those sets
	Set<int> setUnion = set_union(set1, set2);
	Set<int> setIntersection = set_intersection(set1, set2);

	//Print out the resulting sets as lists of numbers and as internal tree structures
	std::cout << "Set 1: ";
	set1.printSet();
	set1.printInternal();
	std::cout << endl << "Set 2: ";
	set2.printSet();
	set2.printInternal();
	std::cout << endl << "Union: ";
	setUnion.printSet();
	setUnion.printInternal();
	std::cout << endl << "Intersection: ";
	setIntersection.printSet();
	setIntersection.printInternal();

	return 0;
}

template <typename T>
Set<T> set_union(const Set<T>& set1, const Set<T>& set2)
{
	Set<T> uSet;
	typename Set<T>::iterator itr1 = set1.begin();
	typename Set<T>::iterator itr2 = set2.begin();
	for (itr1, itr2; itr1 != set1.end() || itr2 != set2.end(); ++itr1, ++itr2)
	{
		uSet.insert(*itr1);
		uSet.insert(*itr2);
	}
	return uSet;
}

template <typename T>
Set<T> set_intersection(const Set<T>& set1, const Set<T>& set2)
{
	Set<T> iSet;
	typename Set<T>::iterator itr1 = set1.begin();
	for (itr1; itr1 != set1.end(); ++itr1)
	{
		if (set2.contains(*itr1) == true)
		{
			iSet.insert(*itr1);
		}
	}
	return iSet;
}