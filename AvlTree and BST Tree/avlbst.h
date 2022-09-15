#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    bool isBalanced(AVLNode<Key, Value>* item) const;
    void rotateL(AVLNode<Key, Value>* item);
    void rotateR(AVLNode<Key, Value>* item);
    void fixIns(AVLNode<Key, Value>* val1, AVLNode<Key, Value>* val2);
    AVLNode<Key, Value>* tallerKid(AVLNode<Key, Value>* item) const;
    void fixRem(AVLNode<Key, Value>* item);
    char findBalance(AVLNode<Key, Value>* item) const;
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */

//function to insert node into the AVL tree, also calls neccesary helper functions in order to balance the tree
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    AVLNode<Key, Value>* parent = NULL;
    if (this->empty()) {
        
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        return;
    }
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->root_);
    
    //checks if should go left or right and then processes insert based upon that
    bool wentLeft = true;  
    int decider;
    while (curr) {
        parent = curr;
        if (new_item.first < curr->getKey()) {
            decider = 0;
            
        }
        else if (new_item.first > curr->getKey()) {
            decider = 1; 
        }
        else {
            decider = 2;
            
        }
        switch (decider)
        {
        case 0:
            wentLeft = true;
            curr = curr->getLeft();
            break;
        case 1:
            wentLeft = false;
            curr = curr->getRight(); 
            break;
        default:
            curr->setValue(new_item.second);
            return;
            break;
        }
    }
    if (wentLeft == true) {
        decider = 6;
        
    }
    else {
        decider = 7;
        
    }
    switch (decider)
    {
    case 6:
        parent->setLeft(new AVLNode<Key, Value>(new_item.first, new_item.second, parent));
        if (parent->getBalance() == 1) {
            parent->setBalance(2);
            fixIns(parent, parent->getLeft());
        }
        break;
    
    default:
        parent->setRight(new AVLNode<Key, Value>(new_item.first, new_item.second, parent));
        if (parent->getBalance() == 1) {
            parent->setBalance(2);
            fixIns(parent, parent->getRight());
        }
        break;
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */

//function to remove a node from the avl tree, also calls neccesary helper functions to rebalance the tree
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    //removes node and checks to see if in proper position if not moves around
    AVLNode<Key, Value>* remItem = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    if (remItem == NULL)
        return;

    bool isAbove = false;
    if (key == this->root_->getKey()) {
        isAbove = true;
    }
    int decider;
    if (remItem->getLeft() == NULL && remItem->getRight() == NULL) {
        if (isAbove) {
            decider = 0;
            
        }
        else if (remItem->getParent()->getRight() == remItem) {
            decider = 1;
            
        }
        else {
            decider = 2;
        }
        switch (decider)
        {
        case 0:
            this->root_ = NULL;
            break;
        case 1:
            remItem->getParent()->setRight(NULL);
            break;
        default:
            remItem->getParent()->setLeft(NULL);
            break;
        }
    }

    //checks if left or right are null to refrain from segfaulting
    else if (remItem->getLeft() == NULL || remItem->getRight() == NULL) {
        if (remItem->getRight()) {
            remItem->getRight()->setParent(remItem->getParent());
            if (isAbove == false) {
                if (remItem == remItem->getParent()->getRight()) {
                    decider = 0;
                }
                else {
                    decider = 1;
                }
                switch (decider)
                {
                case 0:
                    remItem->getParent()->setRight(remItem->getRight());
                    break;
                default:
                    remItem->getParent()->setLeft(remItem->getRight());
                    break;
                }
            }
            else {
                this->root_ = remItem->getRight();
            }
        }

        else {
            remItem->getLeft()->setParent(remItem->getParent());
            if (isAbove == false) {
                if (remItem == remItem->getParent()->getRight()) {
                    decider = 0;
                    
                }
                else {
                    decider = 1;
                }
                switch (decider)
                {
                case 0:
                    remItem->getParent()->setRight(remItem->getLeft());
                    break;
                default:
                    remItem->getParent()->setLeft(remItem->getLeft());
                    break;
                }
            }
            else {
                this->root_ = remItem->getLeft();
            }
        }
    }

    else {
        nodeSwap(static_cast<AVLNode<Key, Value>*>(this->predecessor(remItem)), remItem);
        if (remItem->getLeft() == NULL && remItem->getRight() == NULL) {
            if (remItem == remItem->getParent()->getRight()) {
                decider = 0;
            }
            else {
                decider = 1;
            }
            switch (decider)
            {
            case 0:
                remItem->getParent()->setRight(NULL);
                break;
            
            default:
                remItem->getParent()->setLeft(NULL);
                break;
            }
        }
        else {
            if (remItem == remItem->getParent()->getRight()) {
                decider = 0;
                
            }
            else if (remItem == remItem->getParent()->getLeft()) {
                decider = 1;
            
            }
            switch (decider)
            {
            case 0:
                remItem->getLeft()->setParent(remItem->getParent());
                remItem->getParent()->setRight(remItem->getLeft());
                break;
            
            case 1:
                remItem->getLeft()->setParent(remItem->getParent());
                remItem->getParent()->setLeft(remItem->getLeft());
                break;
            }
        }
    }
    AVLNode<Key, Value>* parental = remItem->getParent();
    delete remItem;
    fixRem(parental);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

//helper function to check if the tree below the node is balanced
template<class Key, class Value>
bool AVLTree<Key, Value>::isBalanced(AVLNode<Key, Value>* item) const {
    if (item == NULL)
        return true;

    return (abs(findBalance(item->getRight()) - findBalance(item->getLeft())) <= 1);
}

//helper function to rotate nodes left
template<class Key, class Value>
void AVLTree<Key, Value>::rotateL(AVLNode<Key, Value>* item) {
    AVLNode<Key, Value>* val1 = item->getParent();
    AVLNode<Key, Value>* val2 = item->getRight();
    
    item->setRight(val2->getLeft());
    
    if (val2->getLeft()) {
        val2->getLeft()->setParent(item);
    }
    
    int decider;
    if (val1 == NULL) {   
        decider = 0;  
    }
    
    else if (item == val1->getLeft()) {
        decider = 1;
    }
    else {
        decider = 2;
    }
    switch (decider)
    {
    case 0:
        this->root_ = val2;
        val2->setParent(NULL);
        break;
    case 1:
        val1->setLeft(val2);
        val2->setParent(val1);
        break;
    default:
        val1->setRight(val2);
        val2->setParent(val1);
        break;

    }
    val2->setLeft(item);
    
    item->setParent(val2);
}

//helper function to rotate nodes right
template<class Key, class Value>
void AVLTree<Key, Value>::rotateR(AVLNode<Key, Value>* item) {
    AVLNode<Key, Value>* val1 = item->getParent();
    AVLNode<Key, Value>* val2 = item->getLeft();
    item->setLeft(val2->getRight());

    if (val2->getRight()) {
        val2->getRight()->setParent(item);
    }
    int decider;

    if (val1 == NULL) {
        decider = 0;
    }
    else if (item == val1->getLeft()) {
        decider = 1;
    }
    else {
        decider = 2;
        
    }

    switch (decider)
    {
    case 0:
        this->root_ = val2;
        val2->setParent(NULL);
        break;
    case 1:
        val1->setLeft(val2);
        val2->setParent(val1);
        break;
    default:
        val1->setRight(val2);
        val2->setParent(val1);
        break;
    }
    val2->setRight(item);
    item->setParent(val2);
}

//helper function to rebalance tree after inserting a node
template<class Key, class Value>
void AVLTree<Key, Value>::fixIns(AVLNode<Key, Value>* val1, AVLNode<Key, Value>* val2) {
    
    AVLNode<Key, Value>* val3 = val1->getParent();
    if (val1 == NULL || val3 == NULL)
        return;

    if (val3->getBalance() == findBalance(val3)) {
        return;
    }
    val3->setBalance(findBalance(val3));

    if (isBalanced(val3)) {
        fixIns(val3, val1);
    }

    else {
        int decider;
        if (val2 == val1->getLeft() && val1 == val3->getLeft()) {
            decider = 0;
        }
        else if (val2 == val1->getRight() && val1 == val3->getRight()) {
            decider = 1;
        }
        else if (val2 == val1->getRight() && val1 == val3->getLeft()) {
            decider = 2;
        }
        else {
            decider = 3;
        }
        switch (decider)
        {
        case 0:
            rotateR(val3);
            val3->setBalance(findBalance(val3));
            val1->setBalance(findBalance(val1));
            break;
        case 1:
            rotateL(val3);
            val3->setBalance(findBalance(val3));
            val1->setBalance(findBalance(val1));
            break;
        case 2:
            rotateL(val1);
            rotateR(val3);
            val2->setBalance(findBalance(val2));
            val3->setBalance(findBalance(val3));
            val1->setBalance(findBalance(val1));
            break;
        default:
            rotateR(val1);
            rotateL(val3);
            val2->setBalance(findBalance(val2));
            val3->setBalance(findBalance(val3));
            val1->setBalance(findBalance(val1));
            break;
        }
    }
}

//helper function to find which of the roots is taller
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::tallerKid(AVLNode<Key, Value>* item) const {
    int decider;
    if (item->getRight() && !item->getLeft()) {
        decider = 0;
        
    }
    else if (!item->getRight() && item->getLeft()) {
        decider = 1;

    }
    else if (findBalance(item->getRight()) > findBalance(item->getLeft())) {
        decider = 2;
        
    }
    else if (findBalance(item->getRight()) < findBalance(item->getLeft())) {
        decider = 3;
        
    }
    else {
        decider = 4;
        
    }
    switch(decider){
        case 0:
            return item->getRight();
            break;
        case 1:
            return item->getLeft();
            break;
        case 2:
            return item->getRight();
            break;
        case 3:
            return item->getLeft();
            break;
        case 4:
            if (item->getParent()) {
                if (item == item->getParent()->getRight()) {
                    return item->getRight();
                }
            else {
                return item->getLeft();
            }
        }

    }
    return NULL;
}

//helper function to rebalance tree after running remove function
template<class Key, class Value>
void AVLTree<Key, Value>::fixRem(AVLNode<Key, Value>* item) {
    if (item == NULL)
        return;
    int decider;
    if (isBalanced(item) == false) {
        AVLNode<Key, Value>* val1 = tallerKid(item);
        AVLNode<Key, Value>* val2 = tallerKid(val1);
        if (val2 == val1->getLeft() && val1 == item->getLeft()) {
            decider = 0;
            
        }
        else if (val2 == val1->getRight() && val1 == item->getRight()) {
            decider = 1;
            
        }
        else if (val2 == val1->getRight() && val1 == item->getLeft()) {
            decider = 2;
        }
        else if (val2 == val1->getLeft() && val1 == item->getRight()) {
            decider = 3;
        }
        switch (decider)
        {
        case 0:
            rotateR(item);
            item->setBalance(findBalance(item));
            val1->setBalance(findBalance(val1));
            fixRem(item->getParent());
            break;
        case 1:
            rotateL(item);
            item->setBalance(findBalance(item));
            val1->setBalance(findBalance(val1));
            fixRem(item->getParent());
            break;
        case 2:
            rotateL(val1);
            rotateR(item);
            item->setBalance(findBalance(item));
            val1->setBalance(findBalance(val1));
            val2->setBalance(findBalance(val2));
            fixRem(item->getParent());
            break;
        case 3:
            rotateR(val1);
            rotateL(item);
            item->setBalance(findBalance(item));
            val1->setBalance(findBalance(val1));
            val2->setBalance(findBalance(val2));
            fixRem(item->getParent());
            break;
        }
    }
    else if (item->getBalance() == findBalance(item)) {
        return;
    }
    else {
        item->setBalance(findBalance(item));
        fixRem(item->getParent());
    }
}

//helper function to find the balance
template<class Key, class Value>
char AVLTree<Key, Value>::findBalance(AVLNode<Key, Value>* item) const {
    if (item == NULL)
        return 0;
    int balanceLeft = 0;
    int balanceRight = 0;
    
    if (item->getLeft())
        balanceLeft = item->getLeft()->getBalance();
    
    if (item->getRight())
        balanceRight = item->getRight()->getBalance();
    
    

    if(balanceLeft > balanceRight){
        return ++balanceLeft;
    }
    else if(balanceLeft < balanceRight)
        return ++balanceRight;
    
    return ++balanceLeft;
}
#endif
