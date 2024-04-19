#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cmath>
#include "CircularDynamicArray.h"
#include "HeapNode.cpp"
using namespace std;

/* TODO:
 * 1. The test with randomized numbers as keys is seg faulting, I isolated the code but I
      don't know what is causing it
 * 2. Merge needs to be implemented
 * 3. Print key needs to have its formatting fixed
 * 4. Print key is also giving me the wrong order of node elements, either that is something
 *    wrong with printKey or the consolidate function
 * 5. I need to make more test cases
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
        // TODO: Consolidate is supposed to start with the smallest rank child of the extracted node
        void consolidate() {
            // Create an array to store the roots of the trees according to their degree
            CircularDynamicArray<HeapNode<KeyType> *> degreeArray(log2(size) + 1);
            HeapNode<KeyType> *currentNode = rootNode;

            // Traverse the root list and merge trees of the same degree
            while (currentNode->getRightSibling() != rootNode) {
                int currentDegree = currentNode->getDegree();
                cout << "Current Node: " << currentNode->getKey() << endl;
                cout << "Current Degree: " << currentDegree << endl;

                while (degreeArray[currentDegree] != nullptr) {
                    HeapNode<KeyType> *otherNode = degreeArray[currentDegree];
                    if (currentNode->getKey() > otherNode->getKey()) {
                        HeapNode<KeyType> *temp = currentNode;
                        currentNode = otherNode;
                        otherNode = temp;
                    } 
                    currentNode->addChild(otherNode);
                    degreeArray[currentDegree] = nullptr;
                    currentDegree++;
                    cout << "Linked Nodes with keys " << currentNode->getKey() << " and " << otherNode->getKey() << endl;
                    printRootList(); // seg fault
                }
                degreeArray[currentDegree] = currentNode;
                currentNode = currentNode->getRightSibling();
            }

            // Find the minimum key in the heap
            HeapNode<KeyType>* first = nullptr;
            HeapNode<KeyType>* last = nullptr;
            rootNode = nullptr;

            for (int i = 0; i < degreeArray.length(); i++) {
                if (degreeArray[i] != nullptr) {
                    if (rootNode == nullptr) {
                        rootNode = degreeArray[i];
                        first = rootNode;
                        last = rootNode;
                    } else {
                        last->setRightSibling(degreeArray[i]);
                        degreeArray[i]->setLeftSibling(last);
                        last = degreeArray[i];
                    }
                }
            }

            if (last != nullptr && first != nullptr) {
                last->setRightSibling(first);
                first->setLeftSibling(last);
            }
            printNodeList(rootNode->getChildren().getFrontValue());
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
            rootNode = nullptr;

            // Insert all keys into the heap
            for (int i = 0; i < s; i++) {
                insert(K[i]);
            }

            cout << "Finished inserting keys" << endl;
            /*
            // Make sure the linked list is circular
            if (rootNode != nullptr) {
                HeapNode<KeyType> *rightTraverse = rootNode;
                HeapNode<KeyType> *leftTraverse = rootNode;
                
                while (rightTraverse->getRightSibling() != nullptr) {
                    //cout << "Traversing to right sibling with key " << rightTraverse->getRightSibling()->getKey() << endl;
                    rightTraverse = rightTraverse->getRightSibling();
                }
                while (leftTraverse->getLeftSibling() != nullptr) {
                    //cout << "Traversing to left sibling with key " << leftTraverse->getLeftSibling()->getKey() << endl;
                    leftTraverse = leftTraverse->getLeftSibling();
                }

                rightTraverse->setRightSibling(leftTraverse);
                leftTraverse->setLeftSibling(rightTraverse);
                cout << rightTraverse->getRightSibling()->getKey() << endl;
                cout << leftTraverse->getLeftSibling()->getKey() << endl;
            }
            cout << "Finished making linked list circular" << endl;*/
            cout << "Root Node: " << rootNode->getKey() << endl;
            printRootList();
        }

        /**
         * @brief Construct a new empty BHeap object
         */
        BHeap() {
            rootNode = nullptr;
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
            cout << "Inserting " << k << endl;

            if (rootNode == nullptr) {
                cout << "Root Node is null, setting new node as root" << endl;
                rootNode = newNode;
                rootNode->setRightSibling(rootNode);
                rootNode->setLeftSibling(rootNode);
            } else {
                // Insert new node next to rootNode
                if (rootNode->getLeftSibling() != nullptr) {
                    rootNode->getLeftSibling()->setRightSibling(newNode);
                    newNode->setLeftSibling(rootNode->getLeftSibling());
                }
                newNode->setRightSibling(rootNode);
                rootNode->setLeftSibling(newNode);

                // Update rootNode if necessary
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
            if (rootNode == nullptr) {
                throw runtime_error("Heap is empty");
            }

            KeyType minKey = peekKey();
            HeapNode<KeyType> *minNode = rootNode;
            minNode->shiftChildrenUp();

            if (minNode->getRightSibling() == minNode && minNode->getDegree() == 0) {
                rootNode = nullptr;
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


        /**
         * @brief Prints the keys in the heap in a modified preorder traversal
         */
        void printKey() {
            if (rootNode == nullptr) {
                return;
            }

            HeapNode<KeyType> *currentNode = rootNode;
            do {
                cout << "B" << currentNode->getDegree() << ": ";
                printKeyHelper(currentNode);
                cout << "\n";
                currentNode = currentNode->getRightSibling();
            } while (currentNode != rootNode);
        }

        /**
         * @brief Helper function to print the keys of the heap
         * 
         * @param node Node to start printing from
         */
        void printKeyHelper(HeapNode<KeyType> *node) {
            if (node == nullptr) {
                return;
            }

            // Print the key of the current node
            cout << node->getKey() << " ";

            // Recursively print the keys of the children of the current node
            HeapNode<KeyType> *child = node->getChildren().getFrontValue();
            if (child != nullptr) {
                HeapNode<KeyType> *currentChild = child;
                do {
                    printKeyHelper(currentChild);
                    currentChild = currentChild->getRightSibling();
                } while (currentChild != child);
            }
        }

        /**
         * @brief Returns the minimum key in the heap
         * 
         * @return KeyType Minimum key in the heap
         */
        KeyType peekKey() {
            if (rootNode == nullptr) {
                throw runtime_error("Heap is empty");
            }
            return rootNode->getKey();
        }

        /**
         * @brief Testing function that prints the keys in the root list
         */
        void printRootList() {
            cout << "Testing printRootList function" << endl;
            if (rootNode == nullptr) {
                cout << "Root Node is null" << endl;
                return;
            }
            if (rootNode->getRightSibling() == nullptr) {
                cout << "We have a problem" << endl;
            }

            HeapNode<KeyType> *currentNode = rootNode;
            cout << "Root List: ";
            while (currentNode->getRightSibling() != rootNode) {
                cout << currentNode->getKey() << " ";
                currentNode = currentNode->getRightSibling();
            }
            
            cout << currentNode->getKey() << endl;
        }
        
        /**
         * @brief Testing function that prints the keys in any list, children or root list
         * 
         * @param node 
         */
        void printNodeList(HeapNode<KeyType> *node) {
            HeapNode<KeyType> *currentNode = node;

            while (currentNode->getRightSibling() != node) {
                cout << currentNode->getKey() << " ";
                currentNode = currentNode->getRightSibling();
            }
            cout << currentNode->getKey() << endl;
        }

        void ensureLinkedCircularity() {
            if (rootNode != nullptr) {
                HeapNode<KeyType> *traverseNode = rootNode;

                while (traverseNode->getRightSibling() != rootNode) {
                    if (traverseNode->getRightSibling() == nullptr) {
                        cout << "We have a problem" << endl;
                        return;
                    }

                    traverseNode = traverseNode->getRightSibling();
                }
            } else cout << "Root Node is null" << endl;
        }
};