#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cmath>
#include <vector>
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

        /**
         * @brief Consolidates the heap by merging trees of the same degree
         * 
         * @param currentNode Node to start consolidating from
         */
        void consolidate() {
            // Create an array to store the roots of the trees of each degree
            int maxPossibleDegree = static_cast<int>(log2(size) + 1);
            vector<HeapNode<KeyType>*> degreeArray(maxPossibleDegree + 1, NULL);
            HeapNode<KeyType>* current = rootNode;
            HeapNode<KeyType>* x = NULL;

            // Traverse the root list and consolidate trees of the same degree
            do {
                x = current;
                current = current->getRightSibling();
                int currentDegree = x->getDegree();

                // While there exists another node of the same degree, link them
                while (degreeArray[currentDegree] != NULL) {
                    HeapNode<KeyType>* y = degreeArray[currentDegree];

                    // If x's key is greater than y's key, swap x and y
                    if (x->getKey() > y->getKey()) {
                        swap(x, y);
                    }

                    // Link y to x
                    x->addChild(y);

                    // Clear the slot in degreeArray for currentDegree
                    degreeArray[currentDegree] = NULL;

                    // Increase the degree of x since we've added a new child to it
                    currentDegree++;
                    x->setDegree(currentDegree);
                }

                // Save x to degreeArray for the new degree
                degreeArray[currentDegree] = x;

                // Ensure current degree is within bounds
                if (currentDegree > maxPossibleDegree + 1) {
                    cout << "Current Degree: " << currentDegree << endl;
                    cout << "Max Possible Degree: " << maxPossibleDegree + 1 << endl;
                    throw runtime_error("Degree exceeds maximum possible degree");
                }
            } while (current != rootNode);

            // Reset the root list
            rootNode = NULL;
            HeapNode<KeyType>* lastInserted = NULL;

            // Reconstruct the root list from the degree array
            for (int i = 0; i <= maxPossibleDegree; i++) {
                if (degreeArray[i] != NULL) {
                    if (rootNode == NULL) {
                        rootNode = degreeArray[i];
                        lastInserted = rootNode;
                        rootNode->setLeftSibling(rootNode);
                        rootNode->setRightSibling(rootNode);
                    } else {
                        lastInserted->setRightSibling(degreeArray[i]);
                        degreeArray[i]->setLeftSibling(lastInserted);
                        
                        lastInserted = degreeArray[i];
                        lastInserted->setRightSibling(rootNode);
                        rootNode->setLeftSibling(lastInserted);

                        // Update the root node if a new minimum is discovered
                        if (degreeArray[i]->getKey() < rootNode->getKey()) {
                            rootNode = degreeArray[i];
                        }
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
        }

        /**
         * @brief Inserts a key into the heap's root list
         * 
         * @param k Key to insert
         */
        void insert(KeyType k) {
            HeapNode<KeyType> *newNode = new HeapNode<KeyType>(k);

            // Set rootNode to newNode if heap is empty
            if (rootNode == NULL) {
                rootNode = newNode;
                rootNode->setRightSibling(rootNode);
                rootNode->setLeftSibling(rootNode);
            } else {
                // Insert new node next to rootNode
                if (rootNode->getLeftSibling() != NULL) {
                    rootNode->getLeftSibling()->setRightSibling(newNode);
                    newNode->setLeftSibling(rootNode->getLeftSibling());
                }

                // Update rootNode's siblings
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
            // Throw an error if the heap is empty
            if (rootNode == NULL) {
                throw runtime_error("Heap is empty");
            }

            // Extract the minimum key
            KeyType minKey = peekKey();
            HeapNode<KeyType> *minNode = rootNode;

            // Find the new minimum node
            HeapNode<KeyType> *newMin;
            if (!rootNode->getChildren().empty()) {
                newMin = rootNode->getChildren().front();
            } else {
                newMin = rootNode->getRightSibling();
            }

            // Remove the minimum node from the root list
            minNode->shiftChildrenUp();
            if (minNode->getRightSibling() == minNode && minNode->getDegree() == 0) {
                rootNode = NULL;
            } else {
                rootNode = newMin;
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
            // If the other heap is empty, return
            if (H.rootNode == NULL) {
                return;
            }

            // If this heap is empty, take over the other heap's root list
            if (rootNode == NULL) {
                rootNode = H.rootNode;
                size = H.size;
                H.rootNode = NULL;
                H.size = 0;
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

            // Update size
            size += H.size;

            // Clear H's root to avoid double deletion problems
            H.rootNode = NULL;
            H.size = 0;
        }

        /**
         * @brief Prints the keys in the heap in a modified preorder traversal
         */
        void printKey() {
            // Throw an error if the heap is empty
            if (rootNode == NULL) throw runtime_error("Heap is empty");

            // Print the keys in the heap
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
            // Throw an error if the node is null
            if (node == NULL) throw runtime_error("Node is null");

            // Print the key of the current node
            cout << node->getKey() << " ";

            // Recursively print the keys of the children of the current node
            if (!node->getChildren().empty()) {
                HeapNode<KeyType> *currentChild = node->getChildren().front();
                HeapNode<KeyType> *firstChild = currentChild;
                do {
                    printKeyHelper(currentChild);
                    currentChild = currentChild->getRightSibling();
                } while (currentChild != firstChild);
            }
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

        /**
         * @brief Testing function that prints the keys in the root list
         */
        void printRootList() {
            if (rootNode == NULL) {
                throw runtime_error("Root list is empty");
                return;
            }

            HeapNode<KeyType> *currentNode = rootNode;
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
            if (rootNode != NULL) {
                HeapNode<KeyType> *traverseNode = rootNode;

                while (traverseNode->getRightSibling() != rootNode) {
                    if (traverseNode->getRightSibling() == NULL) {
                        cout << "We have a problem" << endl;
                        return;
                    }

                    traverseNode = traverseNode->getRightSibling();
                }
            } else cout << "Root Node is null" << endl;
        }
};
