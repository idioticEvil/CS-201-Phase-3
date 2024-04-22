#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cmath>
#include "CircularDynamicArray.h"
#include "HeapNode.cpp"
using namespace std;

/* TODO:
 * 1. Merge needs to be implemented
 * 2. Print key is also giving me the wrong order of node elements, either that is something
 *    wrong with printKey or the consolidate function
 * 3. I need to make more test cases
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
         * 
         * @param currentNode Node to start consolidating from
         */
        void consolidate() {
            // Create an array to store the roots of the trees according to their degree
            // Using the maximum possible degree plus one for safety
            int maxPossibleDegree = static_cast<int> (log2(size) + 1);
            vector<HeapNode<KeyType>*> degreeArray(maxPossibleDegree + 1, nullptr);
            HeapNode<KeyType>* current = rootNode;
            HeapNode<KeyType>* x = nullptr;
            HeapNode<KeyType>* next = nullptr;

            // Traverse the root list
            do {
                x = current;
                current = current->getRightSibling();
                int currentDegree = x->getDegree();

                // While there exists another node of the same degree
                while (degreeArray[currentDegree] != nullptr) {
                    HeapNode<KeyType>* y = degreeArray[currentDegree]; // another node of the same degree

                    // If x's key is greater than y's key, swap x and y
                    if (x->getKey() > y->getKey()) {
                        swap(x, y);
                    }

                    // Link y to x
                    x->addChild(y);

                    // Clear the slot in degreeArray for currentDegree
                    degreeArray[currentDegree] = nullptr;

                    // Increase the degree of x since we've added a new child to it
                    currentDegree++;
                    x->setDegree(currentDegree); // Update the degree of x
                }

                // Save x to degreeArray for the new degree
                degreeArray[currentDegree] = x;

                // Ensure current degree is within bounds
                if (currentDegree > maxPossibleDegree) {
                    // This should not happen, but we resize the array for safety in case of an unexpected condition
                    throw runtime_error("Degree exceeds maximum possible degree");
                }
                degreeArray[currentDegree] = x;

            } while (current != rootNode);

            // Reset the root list
            rootNode = nullptr;
            HeapNode<KeyType>* lastInserted = nullptr;

            // Reconstruct the root list from the degree array
            for (int i = 0; i <= maxPossibleDegree; i++) {
                if (degreeArray[i] != nullptr) {
                    if (rootNode == nullptr) {
                        rootNode = degreeArray[i];
                        lastInserted = rootNode;
                        rootNode->setLeftSibling(rootNode);
                        rootNode->setRightSibling(rootNode);
                    } else {
                        lastInserted->setRightSibling(degreeArray[i]);
                        degreeArray[i]->setLeftSibling(lastInserted);
                        lastInserted = degreeArray[i];
                        lastInserted->setRightSibling(rootNode);  // Maintain the circular list
                        rootNode->setLeftSibling(lastInserted);
                    }
                }
            }
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

            //cout << "Finished inserting keys" << endl;
            //cout << "Root Node: " << rootNode->getKey() << endl;
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
            //cout << "Inserting " << k << endl;

            if (rootNode == nullptr) {
                //cout << "Root Node is null, setting new node as root" << endl;
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

        /**
         * @brief Merges two binomial heaps and deletes the other heap
         * 
         * @param H Binomial heap to merge with
         */
        void merge(BHeap<KeyType>& H) {
            if (H.rootNode == nullptr) {
                return;  // Nothing to merge if H is empty
            }

            if (rootNode == nullptr) {
                rootNode = H.rootNode;  // If this heap is empty, just take over H's root list
                size = H.size;
                maxDegree = H.maxDegree;
                H.rootNode = nullptr;
                H.size = 0;
                H.maxDegree = 0;
                return;
            }

            // Linking the root lists
            HeapNode<KeyType>* thisLast = rootNode->getLeftSibling();
            HeapNode<KeyType>* hLast = H.rootNode->getLeftSibling();

            thisLast->setRightSibling(H.rootNode);
            H.rootNode->setLeftSibling(thisLast);
            hLast->setRightSibling(rootNode);
            rootNode->setLeftSibling(hLast);

            // Update the minimum node if necessary
            if (H.rootNode->getKey() < rootNode->getKey()) {
                rootNode = H.rootNode;
            }

            size += H.size;  // Update size
            maxDegree = max(maxDegree, H.maxDegree);  // Update the max degree

            // Clear H's root to avoid double deletion problems
            H.rootNode = nullptr;
            H.size = 0;
            H.maxDegree = 0;
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
                cout << "B" << currentNode->getDegree() << ": " << endl;
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
            if (node == nullptr) return;

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
            //cout << "Testing printRootList function" << endl;
            if (rootNode == nullptr) {
                //cout << "Root Node is null" << endl;
                return;
            }
            if (rootNode->getRightSibling() == nullptr) {
                //cout << "We have a problem" << endl;
            }

            HeapNode<KeyType> *currentNode = rootNode;
            //cout << "Root List: ";
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

        /**
         * @brief Testing function that ensures the root list is circular
         */
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