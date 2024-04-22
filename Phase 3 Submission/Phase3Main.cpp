#include <iostream>
using namespace std;
#include "BHeap.cpp"

int main(){
	char K[6] = {'a','b','c','d','e','f'};
	// Equivalent to: int K[6] = {1, 2, 3, 4, 5, 6};
	
	BHeap<char> H1, H2;
	for(int i = 0; i < 6; i++) H1.insert(K[i]);
	
	cout << H1.extractMin() << endl; //Should output a
	
	H1.printKey();
	// Should output "B2:\n b c d e\n B0:\n f \n"
	// Equivalent to: "B2:\n 2 3 4 5\n B0:\n 6\n"
	
	H1.insert('g'); H1.insert('h'); H1.insert('a'); H1.insert('i');
	// Equivalent to inserting 7, 8, 1, 9
	
	H1.printKey();
	// Should output "B0:\n a\n B2:\n b c d e\n B0:\n f\n B0:\n g\n B0:\n h\n B0:\n i\n"
	// Equivalent to: "B0:\n 1\n B2:\n 2 3 4 5\n B0:\n 6\n B0:\n 7\n B0:\n 8\n B0:\n 9\n"
	
	cout << H1.extractMin() << endl; 	//Should output a

	H1.printKey();	
	// Should output "B3: b c d e f g h i\n"
	// Equivalent to: "B3: 2 3 4 5 6 7 8 9\n"
	
	H1.insert('j'); H1.insert('k'); H1.insert('l');
	// Equivalent to inserting 10, 11, 12
    
	cout << H1.extractMin() << endl; // Should output b / 2

	H1.printKey();
	// Should output "B3:\n c j d e f g h i\n B1:\n k l\n"
	// Equivalent to: "B3:\n 3 7 4 5 6 8 9\n B1:\n 10 11\n"
	
	H2.insert('A'); H2.insert('B'); H2.insert('C'); H2.insert('D');
	cout<< H2.extractMin() << endl;	// Should output A / 1

	H2.printKey();
	// Should output "B1:\n B C\n B0:\n D\n"
	// Equivalent to: "B1:\n 2 3\n B0:\n 4\n"
	
	H1.merge(H2); H1.printKey();
	// Should output "B1: B C\n B0:\n D\n B3:\n c j d e f g h i\n B1:\n k l\n"
	// Equivalent to: "B1: 2 3\n B0:\n 4\n B3:\n 3 7 4 5 6 8 9\n B1:\n 10 11\n"
	
	cout << H1.extractMin() << endl; // Should output B / 2

	H1.printKey();
	// Should output "B2:\n C D k l\n B3:\n c j d e f g h i\n"
	// Equivalent to: "B2:\n 3 4 10 11\n B3:\n 3 7 4 5 6 8 9\n"
	
	return 0;
}