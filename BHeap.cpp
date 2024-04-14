// Don't do parent pointers, do a doubly linked list between children in heap level
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "HeapNode.cpp"
using namespace std;

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
                rootNode->swapSibling(newNode, true);
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
            // IMPLEMENT THIS
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