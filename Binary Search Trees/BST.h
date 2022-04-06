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
    // add BinaryNode structure
    struct BinaryNode
    {
        T element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const T & theElement, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, left{lt}, right{rt} {}

        BinaryNode(T && theElement, BinaryNode *lt, BinaryNode *rt)
            : element{std::move(theElement)}, left{lt}, right{rt} {}
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
        insert(x, root);
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
    void insert(const T & x, BinaryNode * & t)
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
};



#endif
