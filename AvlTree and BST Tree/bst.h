#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value>* current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    bool balanceRecurs(Node<Key, Value>* root) const;
    int subHeight(Node<Key, Value>* root) const;
    static Node<Key, Value>* success(Node<Key, Value>* curr);

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() : current_(NULL)
{
    // TODO
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    bool isEqual;
    isEqual = (current_ == rhs.current_);
    return isEqual;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    bool isnEqual;
    isnEqual = (current_ != rhs.current_);
    return isnEqual;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    current_ = success(current_);
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/

//inserts node into tree, however, does not balance the tree as is not neccesary
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    //if empty, root = new node
    Node<Key, Value>* parent = NULL;
    if(empty()){
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        return;
    }
    Node<Key, Value>* curr = root_;
    bool wentLeft = true;
    int decider;
    while (curr)
    {
        parent = curr;
        
        if(keyValuePair.first < curr->getKey()){
            decider = 0;
        }     
        if(keyValuePair.first > curr->getKey()){
            decider = 1;
        }
        if(keyValuePair.first == curr->getKey()){
            decider = 2;
        }

        
        switch(decider){
            //if key less than current, current = left child, if greater,  = right child, if equal, overwrite w/ new value
            case 0:
                wentLeft = true;
                curr = curr->getLeft();
                break;
            case 1:
                wentLeft = false;
                curr = curr->getRight();
                break;
            default:
                curr->setValue(keyValuePair.second);
                return;
        }

        if(wentLeft == true){
            decider = 0;
        }
        else{
            decider = 1;
        }
    }

    //sets left child to new node if went left, if right, does same for right
    switch (decider){
        case 0:
            parent->setLeft(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent));                break;
        default:
            parent->setRight(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent)); 
            break;
    }
    
 
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
//removes node and swaps around as needed
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* rem = internalFind(key);
    if(rem == NULL){
        return;
    }
    bool top = false;


    if(key == root_->getKey())
    top = true;
    int decider;
    //checks to see if left and right are null to avoid overwrites or accidental removes
    if(rem->getRight() == NULL && NULL == rem->getLeft()){
        if(top){
            decider = 0;
        }
        else if(rem->getParent()->getRight() == rem){
            decider = 1;
        }
        else{
            decider = 2;
        }
        switch(decider){
            case 0:
                root_ = NULL;
                break;
            case 1:
                rem->getParent()->setRight(NULL);
                break;
            default:
                rem->getParent()->setLeft(NULL);
                break;
        }
    }

    //if both not null, processes differently because not just setting to nodes, must move around nodes
    else if(rem->getLeft() == NULL || NULL == rem->getRight()){
        int decider;
        if(rem->getRight()){
            rem->getRight()->setParent(rem->getParent());
            if(top != true){
                if(rem == rem->getParent()->getRight())
                    decider = 0;
                else
                    decider = 1;
                switch (decider)
                {
                case 0:
                    rem->getParent()->setRight(rem->getRight());
                    break;
                default:
                    rem->getParent()->setLeft(rem->getRight());
                    break;
                }
            }
            else{
                root_ = rem->getRight();
            }
        }
        else{
            rem->getLeft()->setParent(rem->getParent());
            if(top != true){
                if(rem == rem->getParent()->getRight())
                decider = 0;
                else
                decider = 1;
                switch(decider){
                    case 0:
                        rem->getParent()->setRight(rem->getLeft());
                        break;
                    default:
                        rem->getParent()->setLeft(rem->getLeft());
                        break;

                }
                
            }
            else{
                root_ = rem->getLeft();
            }
        }
    }

    else{
        nodeSwap(predecessor(rem),rem);
        int decider;
        if(rem->getLeft() == NULL && NULL == rem->getRight()){
            if(rem == rem->getParent()->getRight())
            decider = 0;
            else
            decider = 1;
            switch (decider)
            {
            case 0:
                rem->getParent()->setRight(NULL);
                break;
            
            default:
                rem->getParent()->setLeft(NULL);
                break;
            }
        }
        else{
            if(rem == rem->getParent()->getRight()){
                decider = 0;
            }
            else if(rem->getParent()->getLeft() == rem){
                decider = 1;
            }
            switch(decider){
                case 0:
                    rem->getLeft()->setParent(rem->getParent());
                    rem->getParent()->setRight(rem->getLeft());
                    break;
                case 1:
                    rem->getLeft()->setParent(rem->getParent());
                    rem->getParent()->setLeft(rem->getLeft());
                    break;
            }
        }
    }
    delete rem;
}


//helper function to locate the predecessor
template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if(current->getLeft()){
        current = current->getLeft();
        while (current->getRight())
        {
            current = current->getRight();
        }
        return current;
        
    }
    else{
        int decider;
        while(current->getParent()){
            if(current->getParent()->getRight() == current)
            decider = 0;
            else
            decider = 1;
            switch(decider){
                case 0:
                    return current->getParent();
                    break;
                default:
                    current = current->getParent();
            }
        }
        return NULL;
    }
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    while (empty() != true)
    {
        remove(root_->getKey());
    }
    
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key, Value>* temp = root_;
    while(temp->getLeft())
    temp = temp->getLeft();
    return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* temp = root_;
    int decider;
    while(temp != NULL){
        if(temp->getKey() < key)
        decider = 0;
        else if(key < temp->getKey())
        decider = 1;
        else
        decider = 2;
        switch (decider)
        {
        case 0:
            temp = temp->getRight();
            break;
        case 1:
            temp = temp->getLeft();
            break;
        default:
            return temp;
            break;
        }
    }
    return temp;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    return balanceRecurs(root_);
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

//
//self implemented helper functions
//

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balanceRecurs(Node<Key, Value>* root) const {
    int decider;
    if(root == NULL){
    decider = 0;
    return true;
    }
    if(abs(subHeight(root->getLeft()) - subHeight(root->getRight())) >= 2){
    decider = 1;
    return false;
    }
    else{
    decider = 2;
    return balanceRecurs(root->getLeft()) && balanceRecurs(root->getRight());
    }
    switch (decider)
    {
    case 3:
        return true;
        break;
    
    case 4:
        return false;
        break;
    }

}

//helper function to find height of subtree
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::subHeight(Node<Key, Value>* root) const {
    if (root == NULL)
    return 0;
    return std::max(subHeight(root->getLeft()), subHeight(root->getRight())) + 1;
}

//helper function to find the successor
template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::success(Node<Key, Value>* current) {
    int decider;
    
    if (current->getRight()) {
        decider = 0;
    }
    else {
        decider = 1;
    }
    switch (decider)
    {
    case 0:
        current = current->getRight();
        while (current->getLeft()) {
            current = current->getLeft();
        }
        return current;
        break;
    
    default:
        int decider2;
        while (current->getParent()) {
            if (current == current->getParent()->getLeft())
                decider2 = 0;
            else
                decider2 = 1;
            switch (decider2)
            {
            case 0:
                return current->getParent();
                break;
            
            default:
                current = current->getParent();
                break;
            }
        }
        return NULL;
        break;
    }
}
/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
