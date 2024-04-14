// Don't do parent pointers, do a doubly linked list between children in heap level
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "HeapNode.cpp"
using namespace std;

template <typename KeyType> class BHeap {
    private:
        HeapNode<KeyType> *rootNode;
        int size;
        int maxDegree;
    
    public:
        /**
         * @brief Construct a new BHeap with a doubly linked root list
         * 
         * @param K keys to insert into the heap
         * @param s amount of keys to insert
         */
        BHeap(KeyType K[], int s) {
            size = s;
            maxDegree = 0;
            rootNode = NULL;

            // Insert all keys into the heap
            for (int i = 0; i < s; i++) {
                // First insertion into the heap
                if (rootNode == NULL) {
                    rootNode = new HeapNode<KeyType>(K[i]);
                } else {
                    HeapNode<KeyType> *newNode = new HeapNode<KeyType>(K[i]);
                    rootNode->swapSibling(newNode, true);
                    if (newNode->getKey() < rootNode->getKey()) {
                        rootNode = newNode;
                    }
                }
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
};