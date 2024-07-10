#include "BinarySearchTree.h"

// Constructor
template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : rootPtr(nullptr)
{
} // end default constructor

template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType &rootItem)
{
    rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
} // end constructor

template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType> &tree)
{
    rootPtr = this->copyTree(tree.rootPtr);
} // end copy constructor

template <class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
    this->destroyTree(rootPtr);
} // end destructor

// Public methods
template <class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
    return rootPtr == nullptr;
} // end isEmpty

template <class ItemType>
int BinarySearchTree<ItemType>::getHeight() const
{
    return this->getHeightHelper(rootPtr);
} // end getHeight

template <class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const
{
    return this->getNumberOfNodesHelper(rootPtr);
} // end getNumberOfNodes

template <class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const noexcept(false)
{
    return this->getRootData();
} // end getRootData

template <class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType &newData) const noexcept(false)
{
    throw PrecondViolatedExcep("Cannot change root value in a BST.");
} // end setRootData

template <class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType &newEntry)
{
    BinaryNode<ItemType> *newNodePtr = new BinaryNode<ItemType>(newEntry);
    rootPtr = insertInorder(rootPtr, newNodePtr);
    return true;
} // end add

template <class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &anEntry)
{
    bool success = false;
    rootPtr = removeValue(rootPtr, anEntry, success);
    return success;
} // end remove

template <class ItemType>
void BinarySearchTree<ItemType>::clear()
{
    this->destroyTree(rootPtr);
    rootPtr = nullptr;
} // end clear

template <class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType &anEntry) const noexcept(false)
{
    BinaryNode<ItemType> *result = findNode(rootPtr, anEntry);
    if (result == nullptr)
        throw NotFoundException("Entry not found in tree.");
    else
        return result->getItem();
} // end getEntry

template <class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType &anEntry) const
{
    return (findNode(rootPtr, anEntry) != nullptr);
} // end contains

template <class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType &)) const
{
    this->preorder(visit, rootPtr);
} // end preorderTraverse

template <class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType &)) const
{
    this->inorder(visit, rootPtr);
} // end inorderTraverse

template <class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType &)) const
{
    this->postorder(visit, rootPtr);
} // end postorderTraverse

template <class ItemType>
BinarySearchTree<ItemType> &BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType> &rightHandSide)
{
    if (this != &rightHandSide)
    {
        clear();
        rootPtr = this->copyTree(rightHandSide.rootPtr);
    }
    return *this;
} // end operator=

// Protected utility methods
template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType> *subTreePtr,
                                                                BinaryNode<ItemType> *newNode)
{
    if (subTreePtr == nullptr)
        return newNode;
    else if (newNode->getItem() < subTreePtr->getItem())
    {
        BinaryNode<ItemType> *tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNode);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else
    {
        BinaryNode<ItemType> *tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNode);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
} // end insertInorder

template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType> *subTreePtr,
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
        subTreePtr = removeNode(subTreePtr);
        success = true;
    }
    else if (subTreePtr->getItem() > target)
    {
        BinaryNode<ItemType> *tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else
    {
        BinaryNode<ItemType> *tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
} // end removeValue

template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType> *nodePtr)
{
    if (nodePtr->getLeftChildPtr() == nullptr && nodePtr->getRightChildPtr() == nullptr)
    {
        delete nodePtr;
        nodePtr = nullptr;
        return nullptr;
    }
    else if (nodePtr->getLeftChildPtr() == nullptr)
    {
        BinaryNode<ItemType> *nodeToConnectPtr = nodePtr->getRightChildPtr();
        delete nodePtr;
        nodePtr = nullptr;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightChildPtr() == nullptr)
    {
        BinaryNode<ItemType> *nodeToConnectPtr = nodePtr->getLeftChildPtr();
        delete nodePtr;
        nodePtr = nullptr;
        return nodeToConnectPtr;
    }
    else
    {
        ItemType newNodeValue;
        BinaryNode<ItemType> *tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue);
        nodePtr->setRightChildPtr(tempPtr);
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
} // end removeNode

template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType> *subTreePtr,
                                                                     ItemType &inorderSuccessor)
{
    if (subTreePtr->getLeftChildPtr() == nullptr)
    {
        inorderSuccessor = subTreePtr->getItem();
        return removeNode(subTreePtr);
    }
    else
    {
        BinaryNode<ItemType> *tempPtr = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
        subTreePtr->setLeftChildPtr(tempPtr);
        return subTreePtr;
    }
} // end removeLeftmostNode

template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType> *treePtr,
                                                           const ItemType &target) const
{
    if (treePtr == nullptr)
        return nullptr;
    else if (treePtr->getItem() == target)
        return treePtr;
    else if (treePtr->getItem() > target)
        return findNode(treePtr->getLeftChildPtr(), target);
    else
        return findNode(treePtr->getRightChildPtr(), target);
} // end findNode

// End of implementation file
