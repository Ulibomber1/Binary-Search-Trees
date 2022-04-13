// PARTIAL implementation of BinarySearchTree
// insert and printing only
// version for Lab10 ....

// STUDENT COMPLETER: Arius Ulibarri      SID: 007355797

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cassert>
#include "Vector.h"
using namespace std;


template <typename T>
class BinarySearchTree
{
private:
    struct BinaryNode
    {
        T element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode* parent;

        BinaryNode(const T & theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *par)
            : element{ theElement }, left{ lt }, right{ rt }, parent{par} {}

        BinaryNode(T && theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *par)
            : element{ std::move(theElement) }, left{ lt }, right{ rt }, parent{par} {}
    };

public:

    BinarySearchTree() : root{ nullptr } {}

    BinarySearchTree(const BinarySearchTree& rhs)
        : root{ nullptr }
    {
        root = clone(rhs.root);
    }

    BinarySearchTree(BinarySearchTree&& rhs)
        : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    ~BinarySearchTree()
    {
        makeEmpty();
    }

    BinarySearchTree& operator=(const BinarySearchTree& rhs)
    {
        BinarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    BinarySearchTree& operator=(BinarySearchTree&& rhs)
    {
        std::swap(root, rhs.root);
        return *this;
    }

    const T& findMin() const
    {
        return findMin(root)->element;
    }

    const T& findMax() const
    {
        return findMax(root)->element;
    }

    bool contains(const T& x) const
    {
        return contains(x, root);
    }

    // add memberfct isempty() ...
    bool isEmpty()
    {
        return root == 0;
    }

    bool isEmpty() const
    {
        return root == 0;
    }
    // add memberfct insert(const T& x) ... 
    void insert(const T& x)
    {
        insert(x, root, root);
    }

    void remove( const T & x )
    {
        remove(x, root);
    }

    // KV added; educational and demo purposes
    void printTree() const
    {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
    }

    void collect_values(Vector<T>& coll)
    {
        collect_values(root, coll);
    }

    void printInternal() const
    {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printInternal(root, 0);
    }

    // for destructor to call...
    void makeEmpty()
    {
        makeEmpty(root);
    }

    int depth() const
    {
        return depth(root);
    }

private:

    BinaryNode* root;

    void insert(const T & x, BinaryNode * & t, BinaryNode * & par)
    {
        if (t == nullptr)
            t = new BinaryNode(x, 0, 0, par);
        else if (x < t->element)
            insert(x, t->left, t);
        else if (t->element < x)
            insert(x, t->right, t);
        else
            ; // duplicate, do nothing
    }

    void remove(const T& x, BinaryNode*& t)
    {
        if (t == nullptr)
            return;
        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != nullptr and t->right != nullptr)
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            BinaryNode* oldNode = t;

            if (t->left != nullptr)
                t = t->left;
            else
                t = t->right;

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
            return true;  // found a match
    }

    void makeEmpty(BinaryNode*& t)
    {
        if (t != 0)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = 0;
    }

    void printTree(BinaryNode* t) const
    {
        if (t != 0)
        {
            printTree(t->left);
            cout << t->element << " ";
            printTree(t->right);
        }
    }

    void collect_values(BinaryNode* t, Vector<T>& vec)
    {
        if (t == nullptr)
            return;
        if (t->left == nullptr && t->right == nullptr)
        {
            vec.push_back(t->element);
            return;
        }
        else
        {
            collect_values(t->left, vec);
            vec.push_back(t->element);
            collect_values(t->right, vec);
        }
        return;
    }

    void printInternal(BinaryNode* t, int offset) const
    {
        for (int i = 1; i <= offset; i++)
            cout << "..";
        if (t == 0)
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
            return new BinaryNode{ t->element, clone(t->left), clone(t->right) };
    }

    int depth(BinaryNode* t) const
    {
        if (t == nullptr)
            return 0;
        if (t->left == nullptr && t->right == nullptr)
            return 1;
        int ld = depth(t->left);
        int rd = depth(t->right);
        if (ld >= rd)
            return 1 + ld;
        else
            return 1 + rd;
    }

};



#endif
