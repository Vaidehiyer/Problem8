/** Implementation file for BinaryNode class */

#include "BinaryNode.h"

// Default constructor
template <class ItemType>
BinaryNode<ItemType>::BinaryNode() : leftChildPtr(nullptr), rightChildPtr(nullptr) {}

// Constructor with item initialization
template <class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType &anItem) : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr) {}

// Constructor with item and child pointers initialization
template <class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType &anItem, BinaryNode<ItemType> *leftPtr, BinaryNode<ItemType> *rightPtr)
    : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr) {}

// Setter for item
template <class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType &anItem)
{
    item = anItem;
}

// Getter for item
template <class ItemType>
ItemType BinaryNode<ItemType>::getItem() const
{
    return item;
}

// Check if the node is a leaf (has no children)
template <class ItemType>
bool BinaryNode<ItemType>::isLeaf() const
{
    return (leftChildPtr == nullptr && rightChildPtr == nullptr);
}

// Getter for left child pointer
template <class ItemType>
BinaryNode<ItemType> *BinaryNode<ItemType>::getLeftChildPtr() const
{
    return leftChildPtr;
}

// Getter for right child pointer
template <class ItemType>
BinaryNode<ItemType> *BinaryNode<ItemType>::getRightChildPtr() const
{
    return rightChildPtr;
}

// Setter for left child pointer
template <class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(BinaryNode<ItemType> *leftPtr)
{
    leftChildPtr = leftPtr;
}

// Setter for right child pointer
template <class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(BinaryNode<ItemType> *rightPtr)
{
    rightChildPtr = rightPtr;
}
