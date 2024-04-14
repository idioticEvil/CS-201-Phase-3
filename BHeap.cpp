// Don't do parent pointers, do a doubly linked list between children in heap level
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "HeapNode.cpp"
#include "CircularDynamicArray.h"
using namespace std;

template <typename KeyType> class BHeap {
    private:
        CircularDynamicArray<HeapNode<KeyType> *> rootList;
        HeapNode<KeyType> *minNode;
        int minIndex;
        int size;
        int maxDegree;
    
    public:
        BHeap(KeyType K[], int s) {
            size = s;
            maxDegree = 0;
            minIndex = 0;

            rootList = CircularDynamicArray<HeapNode<KeyType> *>(s);
            minNode = new HeapNode<KeyType>(K[0]);
            rootList.addFront(minNode);

            
            for (int i = 1; i < s; i++) {
                
            }
        }

        BHeap() {

        }
}