#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cmath>
#include "BHeap.cpp"
using namespace std;

int main() {
    char test1[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    char test2[6] = {'a','b','c','d','e','f'};
    int test3[20] = {10, 2, 21, 13, 9, 4, 15, 7, 12, 6, 8, 17, 1, 18, 3, 19, 5, 20, 11, 14};
    BHeap<char> heap1(test1, 10), heap2(test2, 6);
    BHeap<int> heap3, heap4;

    for (int i = 0; i < 20; i++) {
        heap3.insert(test3[i]);
    }

    for (int i = 1; i < 200; i++) {
        heap4.insert(i);
    }

    cout << "Test 1 Extract: " << heap1.extractMin() << endl;
    cout << "Test 1 Key Print: " << endl;
    heap1.printKey();

    cout << "Test 2 Extract: " << heap2.extractMin() << endl;
    cout << "Test 2 Key Print: " << endl;
    heap2.printKey();

    cout << "Test 3 Extract: " << heap3.extractMin() << endl;
    cout << "Test 3 Key Print: " << endl;
    heap3.printKey();

    cout << "Test 4 Extract: " << heap4.extractMin() << endl;
    cout << "Test 4 Key Print: " << endl;
    heap4.printKey();
}