// BST_Set.h
// by KV, Fall 2021, for CSE 2020;
// essentially class BinarySearchTree with iterators


#ifndef BSTSET_H
#define BSTSET_H

#include <algorithm>
#include <cassert>
using namespace std;


template <typename T>
class Set
{
private:
	class  BinaryNode
	{
	public:
		T element;
		BinaryNode* left;
		BinaryNode* right;
		BinaryNode* parent; // added to support iterators

		BinaryNode(const T& theElement, BinaryNode* lt, BinaryNode* rt)
			: element(theElement), left(lt), right(rt), parent(nullptr) { }

		BinaryNode(const T& theElement, BinaryNode* lt, BinaryNode* rt,
			BinaryNode* par)
			: element(theElement), left(lt), right(rt), parent(par) { }

	};

public:

	class iterator
	{
	public:
		iterator() : current{ nullptr }
		{}

		iterator(BinaryNode* x) : current(x)
		{}

		T operator *()
		{
			return current->element;
		}

		iterator& operator ++()
		{
			go_to_next();
			return *this;
		}

		iterator operator ++(int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}

		bool operator ==(const iterator& rhs) const
		{
			return current == rhs.current;
		}

		bool operator !=(const iterator& rhs) const
		{
			return !(*this == rhs);
		}

	protected:

		BinaryNode* current;

		void go_to_next()
		{
			if (current == nullptr)
				return;

			T currval = current->element;
			if (current->right == nullptr)
			{
				// current node has no right subtree
				// go to closest larger valued ancester
				current = current->parent;
				while (current != nullptr && current->element < currval)
					current = current->parent;
				return;
			}
			// current node has right subtree
			// go leftmost in that subtree
			current = current->right;
			while (current->left != nullptr)
				current = current->left;
			return;
		}

		friend class Set<T>;
	}; // end class iterator

public:

	Set() : root(nullptr) {}

	Set(const Set& rhs) : root(nullptr)
	{
		root = clone(rhs.root);
	}

	~Set()
	{
		makeEmpty();
	}

	Set& operator=(const Set& rhs)
	{
		Set copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	const T& findMin() const
	{
		assert(!isEmpty());
		return findMin(root)->element;
	}

	const T& findMax() const
	{
		assert(!isEmpty());
		return findMax(root)->element;
	}

	bool contains(const T& x) const
	{
		return contains(x, root);
	}

	bool isEmpty() const
	{
		return root == nullptr;
	}

	void printSet(ostream& out = cout) const
	{
		if (isEmpty())
			out << "Empty Set" << endl;
		else
			printSet(root, out);
	}

	void printInternal() const
	{
		if (isEmpty())
			cout << "Empty tree" << endl;
		else
			printInternal(root, 0);
	}

	void makeEmpty()
	{
		makeEmpty(root);
	}


	void insert(const T& x)
	{
		insert(x, root, root);
	}

	void remove(const T& x)
	{
		remove(x, root);
	}

	// BST iterators

	iterator begin()
	{
		BinaryNode* beg = leftmost(root);
		iterator itr(beg);
		return itr;
	}

	iterator end()
	{
		iterator itr(nullptr);
		return itr;
	}

private:

	BinaryNode* root;

	void insert(const T& x, BinaryNode*& t, BinaryNode*& par)
	{
		if (t == nullptr)
		{
			t = new BinaryNode(x, nullptr, nullptr, par);
		}
		else if (x < t->element)
			insert(x, t->left, t);
		else if (t->element < x)
			insert(x, t->right, t);
		else
			;  // Duplicate; do nothing
	}

	void remove(const T& x, BinaryNode*& t)
	{
		if (t == nullptr)
			return;   // Item not found; do nothing
		if (x < t->element)
			remove(x, t->left);
		else if (t->element < x)
			remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr) // Two children
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			BinaryNode* oldNode = t;
			//t = ( t->left != nullptr ) ? t->left : t->right;
			if (t->left != nullptr)
			{
				t->left->parent = t->parent;
				t = t->left;
			}
			else
			{
				if (t->right != nullptr)
					t->right->parent = t->parent;
				t = t->right;
			}
			delete oldNode;
		}
	}

	BinaryNode* findMin(BinaryNode* t) const
	{
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr)
			return t;
		return findMin(t->left);
	}

	BinaryNode* findMax(BinaryNode* t) const
	{
		if (t != nullptr)
			while (t->right != nullptr)
				t = t->right;
		return t;
	}

	bool contains(const T& x, BinaryNode* t) const
	{
		if (t == nullptr)
			return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (t->element < x)
			return contains(x, t->right);
		else
			return true;    // Match
	}

	void makeEmpty(BinaryNode*& t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}

	void printSet(BinaryNode* t, ostream& out) const
	{
		if (t != nullptr)
		{
			printSet(t->left, out);
			out << t->element << endl;
			printSet(t->right, out);
		}
	}

	void printInternal(BinaryNode* t, int offset) const
	{
		for (int i = 1; i <= offset; i++)
			cout << "..";
		if (t == nullptr)
		{
			cout << "#" << endl;
			return;
		}
		cout << t->element << endl;
		printInternal(t->left, offset + 1);
		printInternal(t->right, offset + 1);
		return;
	}

	BinaryNode* clone(BinaryNode* t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new BinaryNode{ t->element, clone(t->left), clone(t->right),
		clone(t->parent) };
	}

	// added for iterator implementation;

	BinaryNode* leftmost(BinaryNode* t)
	{
		assert(t != nullptr);
		while (t->left != nullptr)
			t = t->left;
		return t;
	}

	BinaryNode* rightmost(BinaryNode* t)
	{
		assert(t != nullptr);
		while (t->right != nullptr)
			t = t->right;
		return t;
	}


};

#endif
