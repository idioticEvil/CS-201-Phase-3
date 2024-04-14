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
        int degree;
        bool isMarked;

    public:
        /**
         * @brief Construct a new empty Heap Node object
         */
        HeapNode() {
            leftSibling = nullptr;
            rightSibling = nullptr;
            degree = 0;
            isMarked = false;
        }

        /**
         * @brief Construct a new Heap Node object with a key
         * 
         * @param k Key of the Heap Node
         */
        HeapNode(KeyType k) {
            key = k;
            leftSibling = nullptr;
            rightSibling = nullptr;
            degree = 0;
            isMarked = false;
        }

        /**
         * @brief Construct a deep copy of the Heap Node
         * 
         * @param other Heap Node to copy
         */
        HeapNode(const HeapNode<KeyType>& other) {
            key = other.key;
            children = other.children;
            degree = other.degree;
            isMarked = other.isMarked;
            leftSibling = other.leftSibling ? new HeapNode<KeyType>(*other.leftSibling) : nullptr;
            rightSibling = other.rightSibling ? new HeapNode<KeyType>(*other.rightSibling) : nullptr;
        }

        /**
         * @brief Copy assignment operator for the Heap Node
         * 
         * @param other Heap Node to copy
         * @return HeapNode<KeyType>& Copy of the Heap Node
         */
        HeapNode<KeyType>& operator=(const HeapNode<KeyType>& other) {
            if (this != &other) {
                key = other.key;
                children = other.children;
                degree = other.degree;
                isMarked = other.isMarked;
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
         * @brief Get the degree of the node
         * 
         * @return int 
         */
        int getDegree() {
            return degree;
        }

        /**
         * @brief Get the isMarked property of the node
         * 
         * @return bool 
         */
        bool getIsMarked() {
            return isMarked;
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
         * @brief Set the degree of the node
         * 
         * @param d Degree to be set
         */
        void setDegree(int d) {
            degree = d;
        }

        /**
         * @brief Set the isMarked property of the node
         * 
         * @param marked Whether the node is marked or not
         */
        void setIsMarked(bool marked) {
            isMarked = marked;
        }

        /**
         * @brief Moves children of a node up to the root list
         */
        void shiftChildrenUp() {
            if (degree > 0) { // If the node has children
                children.getFrontValue()->setLeftSibling(leftSibling);
                leftSibling->setRightSibling(children.getFrontValue());
                children.getEndValue()->setRightSibling(rightSibling);
                rightSibling->setLeftSibling(children.getEndValue());
            } else { // If the node has no children
                leftSibling->setRightSibling(rightSibling);
                rightSibling->setLeftSibling(leftSibling);
            }
        }

        /**
         * @brief Disconnects the node from its siblings
         */
        void disconnect() {
            leftSibling = nullptr;
            rightSibling = nullptr;
        }

        /**
         * @brief Swaps the sibling of the node with another node
         * 
         * @param n Node to swap with
         * @param swapLeft Whether to swap left or right sibling
         */
        void swapSibling(HeapNode<KeyType> *n, bool swapLeft) {
            if (swapLeft) {
                HeapNode<KeyType> *temp = leftSibling;
                if (temp != nullptr) {
                    temp->rightSibling = n;
                }
                if (n != nullptr) {
                    // If n is a sibling of another node, update the siblings of n 
                    // and its old sibling
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
                    // If n is a sibling of another node, update the siblings of n 
                    // and its old sibling
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