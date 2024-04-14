#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "HeapNode.cpp"
using namespace std;

/* TODO:
 * 1. Make sure all linked lists are circular
 * 2. Update sibling swapping function and logic, update insertion function
 * 3. Implement consolidate function
 * 4. Implement merge function
 * 5. Implement printKey function
*/

/**
 * @brief Class that represents a Binomial Heap
 * 
 * @tparam KeyType Type of the key of the Binomial Heap
 */
template <typename KeyType> class BHeap {
    private:
        HeapNode<KeyType> *rootNode;
        int size;
        int maxDegree;

        /**
         * @brief Consolidates the heap by merging trees of the same degree
         */
        void consolidate() {
            // IMPLEMENT THIS
        }

    public:
        /**
         * @brief Construct a new BHeap with a doubly linked root list
         * 
         * @param K keys to insert into the heap
         * @param s amount of keys to insert
         */
        BHeap(KeyType K[], int s) {
            size = 0;
            maxDegree = 0;
            rootNode = NULL;

            // Insert all keys into the heap
            for (int i = 0; i < s; i++) {
                insert(K[i]);
            }

            // Make sure the linked list is circular
            if (rootNode != NULL) {
                HeapNode<KeyType> *rightTraverse = rootNode;
                HeapNode<KeyType> *leftTraverse = rootNode;
                
                while (rightTraverse->getRightSibling() != rootNode) {
                    rightTraverse = rightTraverse->getRightSibling();
                }
                while (leftTraverse->getLeftSibling() != rootNode) {
                    leftTraverse = leftTraverse->getLeftSibling();
                }

                rightTraverse->setRightSibling(leftTraverse);
                leftTraverse->setLeftSibling(rightTraverse);
            }
        }

        /**
         * @brief Construct a new empty BHeap object
         */
        BHeap() {
            rootNode = NULL;
            size = 0;
            maxDegree = 0;
        }

        /**
         * @brief Inserts a key into the heap's root list
         * 
         * @param k Key to insert
         */
        void insert(KeyType k) {
            HeapNode<KeyType> *newNode = new HeapNode<KeyType>(k);

            if (rootNode == NULL) {
                rootNode = newNode;
            } else {
                rootNode->swapSibling(newNode, true); // FIXME: I'm not sure if the swapSibling function is correct
                if (newNode->getKey() < rootNode->getKey()) {
                    rootNode = newNode;
                }
            }
            size++;
        }

        /**
         * @brief Extracts the minimum key from the heap and consolidates the heap
         * 
         * @return KeyType Minimum key in the heap
         */
        KeyType extractMin() {
            if (rootNode == NULL) {
                throw runtime_error("Heap is empty");
            }

            KeyType minKey = peekKey();
            HeapNode<KeyType> *minNode = rootNode;
            minNode->shiftChildrenUp();

            if (minNode->getRightSibling() == minNode && minNode->getDegree() == 0) {
                rootNode = NULL;
            } else {
                rootNode = minNode->getRightSibling();
                minNode->disconnect();
                consolidate();
            }

            size--;
            delete minNode;
            return minKey; 
        }

        void merge(BHeap<KeyType> &H) {
            // IMPLEMENT THIS
        }

        void printKey() {
            // IMPLEMENT THIS
        }

        /**
         * @brief Returns the minimum key in the heap
         * 
         * @return KeyType Minimum key in the heap
         */
        KeyType peekKey() {
            if (rootNode == NULL) {
                throw runtime_error("Heap is empty");
            }
            return rootNode->getKey();
        }
};