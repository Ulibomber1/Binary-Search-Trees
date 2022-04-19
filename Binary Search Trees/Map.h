#ifndef MAP_H_
#define MAP_H_

#include "Map_Set.h"
#include "Pair.h"

using namespace std;

template <typename K, typename V>
class Map
{
public:
	Map() {}

	V& operator [] (K index)
	{
		typename Set<Pair<K, V> >::iterator here;
		
		Pair<K, V> probe(index, V());

		here = themap.insert(probe);

		return (*here).second;
	}

	void remove(K key)
	{
		Pair<K, V> probe;

		probe.first = key;

		themap.remove(probe);

		return;
	}

	void printMap()
	{
		typename Set<Pair<K, V> >::iterator itr = themap.begin();
	
		for (; itr != themap.end(); ++itr)
		{
			cout << (*itr).first << ": " << (*itr).second << endl;
		}

	}

	//returns set of all keys of Set
	Set<K> keys()
	{
		Set<K> thekeys;
		typename Set<Pair<K, V> >::iterator itr = themap.begin();

		for (; itr != themap.end(); ++itr)
			thekeys.insert((*itr).first);
		return thekeys;
	}

	//return set of all values of Set
	Set<V> values()
	{
		Set<V> thevalues;
		typename Set<Pair<K, V> >::iterator itr = themap.begin();

		for (; itr != themap.end(); ++itr)
			thevalues.insert((*itr).second);
		return thevalues;
	}

private:

	Set<Pair<K, V> > themap;
};

#endif // ! MAP_H_

