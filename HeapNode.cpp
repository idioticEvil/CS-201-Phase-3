#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "CircularDynamicArray.h"
using namespace std;

/**
 * @brief Class that represents a node in the Binomial Heap
 * 
 * @tparam KeyType Type of the key of the Heap Node
 */
template <typename KeyType> class HeapNode {
    private:
        KeyType key;
        CircularDynamicArray<HeapNode<KeyType> *> children;
        HeapNode<KeyType> *leftSibling;
        HeapNode<KeyType> *rightSibling;

    public:
        /**
         * @brief Construct a new empty Heap Node object
         */
        HeapNode() {
            leftSibling = NULL;
            rightSibling = NULL;
        }

        /**
         * @brief Construct a new Heap Node object with a key
         * 
         * @param k Key of the Heap Node
         */
        HeapNode(KeyType k) {
            key = k;
            leftSibling = NULL;
            rightSibling = NULL;
        }

        /**
         * @brief Construct a new Heap Node object with a key and left & right siblings
         * 
         * @param k Key of the Heap Node
         * @param ls Left Sibling of the Heap Node
         * @param rs Right Sibling of the Heap Node
         */
        HeapNode(KeyType k, HeapNode<KeyType> *ls, HeapNode<KeyType> *rs) {
            key = k;
            leftSibling = ls;
            rightSibling = rs;
        }

        /**
         * @brief Get the key of the node
         * 
         * @return KeyType 
         */
        KeyType getKey() {
            return key;
        }

        /**
         * @brief Get the left sibling of the node
         * 
         * @return HeapNode<KeyType>* 
         */
        HeapNode<KeyType> *getLeftSibling() {
            return leftSibling;
        }

        /**
         * @brief Get the right sibling of the node
         * 
         * @return HeapNode<KeyType>* 
         */
        HeapNode<KeyType> *getRightSibling() {
            return rightSibling;
        }

        /**
         * @brief Get the children of the node
         * 
         * @return CircularDynamicArray<HeapNode<KeyType>*> 
         */
        CircularDynamicArray<HeapNode<KeyType> *> getChildren() {
            return children;
        }

        /**
         * @brief Set the key of the node
         * 
         * @param k Key to be set
         */
        void setKey(KeyType k) {
            key = k;
        }

        /**
         * @brief Set the left sibling of the node
         * 
         * @param ls New left sibling
         */
        void setLeftSibling(HeapNode<KeyType> *ls) {
            leftSibling = ls;
        }

        /**
         * @brief Set the right sibling of the node
         * 
         * @param rs New right sibling
         */
        void setRightSibling(HeapNode<KeyType> *rs) {
            rightSibling = rs;
        }

        /**
         * @brief Constructs a new child for the node, inserts at correct place
         * 
         * @param k Key of the new child
         */
        void insertChild(KeyType k) {
            // IMPLEMENT THIS
        }
}