#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "CircularDynamicArray.h"
using namespace std;

/**
 * @brief Class that represents a node in a Binomial Heap
 * 
 * @tparam KeyType Type of the key of the node
 */
template <typename KeyType> class HeapNode {
    private:
        KeyType key;
        CircularDynamicArray<HeapNode<KeyType> *> children;
        HeapNode<KeyType> *leftSibling;
        HeapNode<KeyType> *rightSibling;
        int degree;

    public:
        /**
         * @brief Construct a new empty Heap Node object
         */
        HeapNode() {
            leftSibling = nullptr;
            rightSibling = nullptr;
            degree = 0;
        }

        /**
         * @brief Construct a new Heap Node object with a key
         * 
         * @param k Key of the node
         */
        HeapNode(KeyType k) {
            key = k;
            leftSibling = nullptr;
            rightSibling = nullptr;
            degree = 0;
        }

        /**
         * @brief Construct a new Heap Node object from another Heap Node object
         * 
         * @param other Heap Node object to copy
         */
        HeapNode(const HeapNode<KeyType>& other) {
            key = other.key;
            children = other.children;
            degree = other.degree;
            leftSibling = other.leftSibling ? new HeapNode<KeyType>(*other.leftSibling) : nullptr;
            rightSibling = other.rightSibling ? new HeapNode<KeyType>(*other.rightSibling) : nullptr;
        }

        /**
         * @brief Assignment operator for Heap Node objects
         * 
         * @param other Heap Node object to copy
         * @return HeapNode<KeyType>& Reference to the new Heap Node object
         */
        HeapNode<KeyType>& operator=(const HeapNode<KeyType>& other) {
            if (this != &other) {
                key = other.key;
                children = other.children;
                degree = other.degree;
                delete leftSibling;
                leftSibling = nullptr;
                delete rightSibling;
                rightSibling = nullptr;
                leftSibling = other.leftSibling ? new HeapNode<KeyType>(*other.leftSibling) : nullptr;
                rightSibling = other.rightSibling ? new HeapNode<KeyType>(*other.rightSibling) : nullptr;
            }
            return *this;
        }

        /**
         * @brief Destroy the Heap Node object
         */
        ~HeapNode() {
            delete leftSibling;
            leftSibling = nullptr;
            delete rightSibling;
            rightSibling = nullptr;
        }

        /**
         * @brief Get the key of the node
         * 
         * @return KeyType Key of the node
         */
        KeyType getKey() {
            return key;
        }

        /**
         * @brief Get the Left Sibling object
         * 
         * @return HeapNode<KeyType>* Pointer to the left sibling
         */
        HeapNode<KeyType> *getLeftSibling() {
            return leftSibling;
        }

        /**
         * @brief Get the Right Sibling of the node
         * 
         * @return HeapNode<KeyType>* Pointer to the right sibling
         */
        HeapNode<KeyType> *getRightSibling() {
            return rightSibling;
        }

        /**
         * @brief Get the Children of the node
         * 
         * @return CircularDynamicArray<HeapNode<KeyType> *> Children of the node
         */
        CircularDynamicArray<HeapNode<KeyType> *> getChildren() {
            return children;
        }

        /**
         * @brief Get the Degree of the node
         * 
         * @return int Degree of the node
         */
        int getDegree() {
            return degree;
        }

        /**
         * @brief Set the key of the node
         * 
         * @param k New key
         */
        void setKey(KeyType k) {
            key = k;
        }

        /**
         * @brief Set the Left Sibling object
         * 
         * @param ls The new left sibling
         */
        void setLeftSibling(HeapNode<KeyType> *ls) {
            leftSibling = ls;

            if (ls != nullptr) {
                ls->rightSibling = this;
            }
        }

        /**
         * @brief Set the Right Sibling object
         * 
         * @param rs The new right sibling
         */
        void setRightSibling(HeapNode<KeyType>* sibling) {
            rightSibling = sibling;

            if (sibling != nullptr) {
                sibling->leftSibling = this;
            }
        }

        /**
         * @brief Set the Degree object
         * 
         * @param d The new degree
         */
        void setDegree(int d) {
            degree = d;
        }

        /**
         * @brief Shifts the children of the node up one level
         */
        void shiftChildrenUp() {
            if (degree > 0) {
                children.getFrontValue()->setLeftSibling(leftSibling);
                leftSibling->setRightSibling(children.getFrontValue());
                children.getEndValue()->setRightSibling(rightSibling);
                rightSibling->setLeftSibling(children.getEndValue());
            } else {
                leftSibling->setRightSibling(rightSibling);
                rightSibling->setLeftSibling(leftSibling);
            }
        }

        /**
         * @brief Disconnects the node from its siblings
         */
        void disconnect() {
            if (leftSibling != nullptr) {
                leftSibling->rightSibling = rightSibling;
            }

            if (rightSibling != nullptr) {
                rightSibling->leftSibling = leftSibling;
            }

            leftSibling = nullptr;
            rightSibling = nullptr;
        }

        /**
         * @brief Swaps the sibling of the node with another node
         * 
         * @param n Node to swap with
         * @param swapLeft Whether to swap the left sibling or not
         */
        void swapSibling(HeapNode<KeyType> *n, bool swapLeft) {
            if (swapLeft) {
                HeapNode<KeyType> *temp = leftSibling;
                if (temp != nullptr) {
                    temp->rightSibling = n;
                }
                if (n != nullptr) {
                    if (n->leftSibling != nullptr) {
                        n->leftSibling->rightSibling = n->rightSibling;
                    }
                    if (n->rightSibling != nullptr) {
                        n->rightSibling->leftSibling = n->leftSibling;
                    }
                    n->rightSibling = this;
                    n->leftSibling = temp;
                }
                leftSibling = n;
            } else {
                HeapNode<KeyType> *temp = rightSibling;
                if (temp != nullptr) {
                    temp->leftSibling = n;
                }
                if (n != nullptr) {
                    if (n->leftSibling != nullptr) {
                        n->leftSibling->rightSibling = n->rightSibling;
                    }
                    if (n->rightSibling != nullptr) {
                        n->rightSibling->leftSibling = n->leftSibling;
                    }
                    n->leftSibling = this;
                    n->rightSibling = temp;
                }
                rightSibling = n;
            }
        }

        /**
         * @brief Adds a child to the node
         * 
         * @param n Child to add
         */
        void addChild(HeapNode<KeyType> *n) {
            n->disconnect();
            children.addFront(n);

            if (children.length() > 1) {
                n->rightSibling = children[1];
                children[children.length() - 1]->setRightSibling(children[0]);
            } else {
                n->rightSibling = n;
            }
            degree++;
        }
};
