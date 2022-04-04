// PARTIAL implementation of BinarySearchTree
// insert and printing only
// version for Lab10 ....

// STUDENT COMPLETER: ______________      SID:_______________________

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cassert>
#include "Vector.h"
using namespace std;


template <typename T>
class BinarySearchTree
{
private:
    // add BinaryNode structure
    struct BinaryNode
    {
        T element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const T & theElement, BinaryNode* lt, BinaryNode* rt)
            : element{theElement}, left{lt}, right{rt} {}

        BinaryNode(T && theElement, BinaryNode* lt, BinaryNode* rt)
            : element{std::move(theElement)}, left{lt}, right{rt} {}
    };

public:

    BinarySearchTree() : root(0) {}

    ~BinarySearchTree()
    {
        makeEmpty();
    }
    // add memberfct isempty() ...
    bool isempty()
    {
        return root == 0;
    }
    // add memberfct insert(const T& x) ... 
    void insert(const T& x)
    {
        insert(x, root);
    }

    // KV added; educational and demo purposes
    void printTree() const
    {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
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

private:

    BinaryNode* root;

    // Lab10: COMPLETE
    // 
    // add  private member fct that does the
    // work for public member fct insert(...)

    // here: ...
    void insert(const T& x, BinaryNode*& t)
    {
        if (t == 0)
            t = new BinaryNode(x, 0, 0);
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
            ; // duplicate, do nothing
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
};



#endif
