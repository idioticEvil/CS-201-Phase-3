#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cmath>
#include "BHeap.cpp"
using namespace std;

int main() {
    char test1[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    BHeap<char> heap1(test1, 10);

    cout << heap1.extractMin() << endl;
    heap1.printKey();
    
}