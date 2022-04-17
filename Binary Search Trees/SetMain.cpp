#include <iostream>
#include <Windows.h>
#include "BST_Set.h"
#include "Random.h"
#include "Vector.h"

template <typename T>
Set<T> set_union(const Set<T>&, const Set<T>&);

template <typename T>
Set<T> set_intersection(const Set<T>&, const Set<T>&);

template <typename T>
Set<T> set_difference(const Set<T>&, const Set<T>&);

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
	Set<int> setDifference1 = set_difference(set1, set2);
	Set<int> setDifference2 = set_difference(set2, set1);

	//Print out the resulting sets with their cardinality
	std::cout
		<< "Set 1 with cardinality " << set1.cardinality() << ":" 
		<< endl;
	set1.printSet();
	std::cout << endl << endl
		<< "Set 2 with cardinality " << set2.cardinality() << ":" 
		<< endl;
	set2.printSet();
	std::cout << endl << endl
		<< "Union of Set 1 and Set 2 with cardinality " << setUnion.cardinality() << ":"
		<< endl;
	setUnion.printSet();
	std::cout << endl << endl
		<< "Intersection of Set 1 and Set 2 with cardinality " << setIntersection.cardinality() << ":"
		<< endl;
	setIntersection.printSet();
	std::cout << endl << endl
		<< "Difference of Set 1 - Set 2 with cardinality " << setDifference1.cardinality() << ":"
		<< endl;
	setDifference1.printSet();
	std::cout << endl << endl
		<< "Difference of Set 2 - Set 1 with cardinality " << setDifference2.cardinality() << ":"
		<< endl;
	setDifference2.printSet();
	std::cout << endl << endl;

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

template <typename T>
Set<T> set_difference(const Set<T>& set1, const Set<T>& set2)
{
	Set<T> dSet = set1;
	typename Set<T>::iterator itr2 = set2.begin();
	for (itr2; itr2 != set2.end(); ++itr2)
	{
		if (dSet.contains(*itr2) == true)
			dSet.remove(*itr2);
	}
	return dSet;
}