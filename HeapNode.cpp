#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <vector>
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
        vector<HeapNode<KeyType> *> children;
        HeapNode<KeyType> *leftSibling;
        HeapNode<KeyType> *rightSibling;
        int degree;

    public:
        /**
         * @brief Construct a new Heap Node object with a key
         * 
         * @param k Key of the node
         */
        HeapNode(KeyType k) {
            key = k;
            leftSibling = NULL;
            rightSibling = NULL;
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
            leftSibling = other.leftSibling;
            rightSibling = other.rightSibling;
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
                leftSibling = NULL;
                delete rightSibling;
                rightSibling = NULL;
                if (other.leftSibling) {
                    leftSibling = new HeapNode<KeyType>(*other.leftSibling);
                }
                if (other.rightSibling) {
                    rightSibling = new HeapNode<KeyType>(*other.rightSibling);
                }
            }
            return *this;
        }

        /**
         * @brief Destroy the Heap Node object
         */
        ~HeapNode() {
            leftSibling = NULL;
            rightSibling = NULL;
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
         * @return vector<HeapNode<KeyType> *> Children of the node
         */
        vector<HeapNode<KeyType> *> getChildren() {
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
         * @brief Increase the degree of the node
         */
        void increaseDegree() {
            degree++;
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

            if (ls != NULL) {
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

            if (sibling != NULL) {
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
                children.front()->setLeftSibling(leftSibling);
                leftSibling->setRightSibling(children.front());
                children.back()->setRightSibling(rightSibling);
                rightSibling->setLeftSibling(children.front());
            } else {
                leftSibling->setRightSibling(rightSibling);
                rightSibling->setLeftSibling(leftSibling);
            }
        }

        /**
         * @brief Adds a child to the node and disconnects the node from its siblings
         * 
         * @param n Child to add
         */
        void addChild(HeapNode<KeyType> *n) {
            if (!n) return;

            if (n == this) {
                throw invalid_argument("Cannot add a node as a child of itself");
            }

            if (n->getLeftSibling() != NULL) {
                n->getLeftSibling()->setRightSibling(n->getRightSibling());
            }

            if (n->getRightSibling() != NULL) {
                n->getRightSibling()->setLeftSibling(n->getLeftSibling());
            }

            if (n->getLeftSibling() == this) {
                leftSibling = n->getLeftSibling();
            }

            if (n->getRightSibling() == this) {
                rightSibling = n->getRightSibling();
            }

            n->setLeftSibling(NULL);
            n->setRightSibling(NULL);

            children.push_back(n);

            if (children.size() > 1) {
                n->setLeftSibling(children[children.size() - 2]);
                n->setRightSibling(children[0]);
                children[children.size() - 2]->setRightSibling(n);
                children[0]->setLeftSibling(n);
            } else {
                n->setRightSibling(n);
                n->setLeftSibling(n);
            }
            degree++;
        }

        /**
         * @brief Swaps two Heap Node objects
         * 
         * @param x First node
         * @param y Second node
         */
        static void swap(HeapNode*& x, HeapNode*& y) {
            HeapNode* temp = x;
            x = y;
            y = temp;
        }
};
