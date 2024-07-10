#include "BinaryNodeTree.h"

template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr)
{
} // end default constructor

template <class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
    clear();
}

template <class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const
{
    return rootPtr == nullptr;
}

template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType &rootItem)
{
    rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
} // end constructor

template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType &rootItem,
                                         const BinaryNodeTree<ItemType> *leftTreePtr,
                                         const BinaryNodeTree<ItemType> *rightTreePtr)
{
    rootPtr = new BinaryNode<ItemType>(rootItem,
                                       copyTree(leftTreePtr->rootPtr),
                                       copyTree(rightTreePtr->rootPtr));
} // end constructor

template <class ItemType>
BinaryNode<ItemType> *BinaryNodeTree<ItemType>::
    copyTree(const BinaryNode<ItemType> *treePtr) const
{
    BinaryNode<ItemType> *newTreePtr = nullptr;
    // Copy tree nodes during a preorder traversal
    if (treePtr != nullptr)
    {
        // Copy node
        newTreePtr = new BinaryNode<ItemType>(treePtr->getItem(),
                                              nullptr, nullptr);
        newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
        newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
    } // end if
    // Else tree is empty (newTreePtr is nullptr)
    return newTreePtr;
} // end copyTree

template <class ItemType>
BinaryNodeTree<ItemType>::
    BinaryNodeTree(const BinaryNodeTree<ItemType> &treePtr)
{
    rootPtr = copyTree(treePtr.rootPtr);
} // end copy constructor

template <class ItemType>
void BinaryNodeTree<ItemType>::
    destroyTree(BinaryNode<ItemType> *subTreePtr)
{
    if (subTreePtr != nullptr)
    {
        destroyTree(subTreePtr->getLeftChildPtr());
        destroyTree(subTreePtr->getRightChildPtr());
        delete subTreePtr;
    } // end if
} // end destroyTree

template <class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
    return getHeightHelper(rootPtr);
}

template <class ItemType>
int BinaryNodeTree<ItemType>::
    getHeightHelper(BinaryNode<ItemType> *subTreePtr) const
{
    if (subTreePtr == nullptr)
        return 0;
    else
        return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()),
                       getHeightHelper(subTreePtr->getRightChildPtr()));
} // end getHeightHelper

template <class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType &newData)
{
    BinaryNode<ItemType> *newNodePtr = new BinaryNode<ItemType>(newData);
    rootPtr = balancedAdd(rootPtr, newNodePtr);
    return true;
} // end add

template <class ItemType>
BinaryNode<ItemType> *BinaryNodeTree<ItemType>::
    balancedAdd(BinaryNode<ItemType> *subTreePtr,
                BinaryNode<ItemType> *newNodePtr)
{
    if (subTreePtr == nullptr)
        return newNodePtr;
    else
    {
        BinaryNode<ItemType> *leftPtr = subTreePtr->getLeftChildPtr();
        BinaryNode<ItemType> *rightPtr = subTreePtr->getRightChildPtr();
        if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
        {
            rightPtr = balancedAdd(rightPtr, newNodePtr);
            subTreePtr->setRightChildPtr(rightPtr);
        }
        else
        {
            leftPtr = balancedAdd(leftPtr, newNodePtr);
            subTreePtr->setLeftChildPtr(leftPtr);
        } // end if
        return subTreePtr;
    } // end if
} // end balancedAdd

template <class ItemType>
void BinaryNodeTree<ItemType>::
    inorder(void visit(ItemType &), BinaryNode<ItemType> *treePtr) const
{
    if (treePtr != nullptr)
    {
        inorder(visit, treePtr->getLeftChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        inorder(visit, treePtr->getRightChildPtr());
    } // end if
} // end inorder

template <class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType &)) const
{
    inorder(visit, rootPtr);
}

// Get the number of nodes in the tree
template <class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const
{
    return getNumberOfNodesHelper(rootPtr);
} // end getNumberOfNodes

// Recursive function to get the number of nodes in a subtree
template <class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType> *subTreePtr) const
{
    if (subTreePtr == nullptr)
        return 0;
    else
        return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) +
               getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
} // end getNumberOfNodesHelper

// Get the data of the root node
template <class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const noexcept(false)
{
    if (rootPtr == nullptr)
    {
        throw PrecondViolatedExcep("getRootData() called with empty tree.");
    }
    return rootPtr->getItem();
} // end getRootData

// Set the data of the root node
template <class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType &newData)
{
    if (rootPtr != nullptr)
    {
        rootPtr->setItem(newData);
    }
    else
    {
        rootPtr = new BinaryNode<ItemType>(newData);
    }
} // end setRootData

// Remove a node from the tree
template <class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType &data)
{
    bool success = false;
    rootPtr = removeValue(rootPtr, data, success);
    return success;
} // end remove

// Recursive function to remove a value from the tree
template <class ItemType>
BinaryNode<ItemType> *BinaryNodeTree<ItemType>::removeValue(BinaryNode<ItemType> *subTreePtr,
                                                            const ItemType target,
                                                            bool &success)
{
    if (subTreePtr == nullptr)
    {
        success = false;
        return nullptr;
    }
    if (subTreePtr->getItem() == target)
    {
        subTreePtr = moveValuesUpTree(subTreePtr);
        success = true;
        return subTreePtr;
    }
    else
    {
        BinaryNode<ItemType> *tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
        subTreePtr->setLeftChildPtr(tempPtr);
        if (!success)
        {
            tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
            subTreePtr->setRightChildPtr(tempPtr);
        }
        return subTreePtr;
    }
} // end removeValue

// Move values up the tree to overwrite value with value from child
template <class ItemType>
BinaryNode<ItemType> *BinaryNodeTree<ItemType>::moveValuesUpTree(BinaryNode<ItemType> *subTreePtr)
{
    if (subTreePtr->getLeftChildPtr() == nullptr && subTreePtr->getRightChildPtr() == nullptr)
    {
        delete subTreePtr;
        return nullptr;
    }
    else if (subTreePtr->getLeftChildPtr() == nullptr)
    {
        BinaryNode<ItemType> *tempPtr = subTreePtr->getRightChildPtr();
        delete subTreePtr;
        return tempPtr;
    }
    else if (subTreePtr->getRightChildPtr() == nullptr)
    {
        BinaryNode<ItemType> *tempPtr = subTreePtr->getLeftChildPtr();
        delete subTreePtr;
        return tempPtr;
    }
    else
    {
        ItemType newNodeValue;
        BinaryNode<ItemType> *tempPtr = moveValuesUpTree(subTreePtr->getLeftChildPtr());
        subTreePtr->setLeftChildPtr(tempPtr);
        subTreePtr->setItem(newNodeValue);
        return subTreePtr;
    }
} // end moveValuesUpTree

// Clear the tree
template <class ItemType>
void BinaryNodeTree<ItemType>::clear()
{
    destroyTree(rootPtr);
    rootPtr = nullptr;
} // end clear

// Get an entry from the tree
template <class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType &anEntry) const noexcept(false)
{
    bool success = false;
    BinaryNode<ItemType> *result = findNode(rootPtr, anEntry, success);
    if (success)
        return result->getItem();
    else
        throw NotFoundException("Entry not found in tree.");
} // end getEntry

// Check if an entry exists in the tree
template <class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType &anEntry) const
{
    bool success = false;
    findNode(rootPtr, anEntry, success);
    return success;
} // end contains

// Recursive function to find a node containing target value
template <class ItemType>
BinaryNode<ItemType> *BinaryNodeTree<ItemType>::findNode(BinaryNode<ItemType> *treePtr,
                                                         const ItemType &target,
                                                         bool &success) const
{
    if (treePtr == nullptr)
    {
        success = false;
        return nullptr;
    }
    if (treePtr->getItem() == target)
    {
        success = true;
        return treePtr;
    }
    else
    {
        BinaryNode<ItemType> *resultNodePtr = findNode(treePtr->getLeftChildPtr(), target, success);
        if (!success)
        {
            resultNodePtr = findNode(treePtr->getRightChildPtr(), target, success);
        }
        return resultNodePtr;
    }
} // end findNode

// Perform preorder traversal using a visitor function
template <class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType &), BinaryNode<ItemType> *treePtr) const
{
    if (treePtr != nullptr)
    {
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        preorder(visit, treePtr->getLeftChildPtr());
        preorder(visit, treePtr->getRightChildPtr());
    } // end if
} // end preorder

// Public method to perform preorder traversal
template <class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType &)) const
{
    preorder(visit, rootPtr);
} // end preorderTraverse

// Perform postorder traversal using a visitor function
template <class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType &), BinaryNode<ItemType> *treePtr) const
{
    if (treePtr != nullptr)
    {
        postorder(visit, treePtr->getLeftChildPtr());
        postorder(visit, treePtr->getRightChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
    } // end if
} // end postorder

// Public method to perform postorder traversal
template <class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType &)) const
{
    postorder(visit, rootPtr);
} // end postorderTraverse

// Assignment operator
template <class ItemType>
BinaryNodeTree<ItemType> &BinaryNodeTree<ItemType>::operator=(const BinaryNodeTree &rightHandSide)
{
    if (this != &rightHandSide)
    {
        clear();
        rootPtr = copyTree(rightHandSide.rootPtr);
    }
    return *this;
} // end operator=
