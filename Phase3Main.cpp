#include <iostream>
using namespace std;
#include "BHeap.cpp"

int main(){
	char K[6] = {'a','b','c','d','e','f'};
	// Equivalent to: int K[6] = {1, 2, 3, 4, 5, 6};
	
	BHeap<char> H1, H2;
	for(int i = 0; i < 6; i++) H1.insert(K[i]);
	
	cout << "Expected Output: a" << endl;
	cout << "Actual Output: " << H1.extractMin() << endl; //Should output a
	
	cout << "Expected Output:\nB2:\nb c d e\nB0:\nf" << endl;
	cout << "Actual Output:" << endl;
	H1.printKey();
	// Should output "B2:\n b c d e\n B0:\n f \n"
	// Equivalent to: "B2:\n 2 3 4 5\n B0:\n 6\n"
	
	H1.insert('g'); H1.insert('h'); H1.insert('a'); H1.insert('i');
	// Equivalent to inserting 7, 8, 1, 9
	
	cout << "Expected Output:\nB0:\na\nB2:\nb c d e\nB0:\nf\nB0:\ng\nB0:\nh\nB0:\ni" << endl;
	cout << "Actual Output:" << endl;
	H1.printKey();
	// Should output "B0:\n a\n B2:\n b c d e\n B0:\n f\n B0:\n g\n B0:\n h\n B0:\n i\n"
	// Equivalent to: "B0:\n 1\n B2:\n 2 3 4 5\n B0:\n 6\n B0:\n 7\n B0:\n 8\n B0:\n 9\n"
	
	cout << "Expected Output: a" << endl;
	cout << "Actual Output: " << H1.extractMin() << endl; 	//Should output a
	
	cout << "Expected Output:\nB3:\nb c d e f g h i" << endl;
	cout << "Actual Output:" << endl;
	H1.printKey();	
	// Should output "B3: b c d e f g h i\n"
	// Equivalent to: "B3: 2 3 4 5 6 7 8 9\n"
	
	H1.insert('j'); H1.insert('k'); H1.insert('l');
	cout << "Printing Root List" << endl;
	H1.printRootList();
	// Equivalent to inserting 10, 11, 12
    
	// Something went wrong here
	cout << "Expected Output: b" << endl;
	cout << "Actual Output: " << H1.extractMin() << endl; // Should output b / 2

	cout << "Expected Output:\nB3:\nc j d e f g h i\nB1:\nk l" << endl;
	cout << "Actual Output:" << endl;
	H1.printKey();
	// Should output "B3:\n c j d e f g h i\n B1:\n k l\n"
	// Equivalent to: "B3:\n 3 7 4 5 6 8 9\n B1:\n 10 11\n"
	
	H2.insert('A'); H2.insert('B'); H2.insert('C'); H2.insert('D');
	cout << "Expected Output: A" << endl;
	cout << "Actual Output: " << H2.extractMin() << endl;	// Should output A / 1

	cout << "Expected Output:\nB1:\nB C\nB0:\nD" << endl;
	cout << "Actual Output:" << endl;
	H2.printKey();
	// Should output "B1:\n B C\n B0:\n D\n"
	// Equivalent to: "B1:\n 2 3\n B0:\n 4\n"
	
	cout << "Expected Output:\nB1: B C\nB0:\nD\nB3:\nc j d e f g h i\nB1:\nk l" << endl;
	cout << "Actual Output:" << endl;
	H1.merge(H2); H1.printKey();
	// Should output "B1: B C\n B0:\n D\n B3:\n c j d e f g h i\n B1:\n k l\n"
	// Equivalent to: "B1: 2 3\n B0:\n 4\n B3:\n 3 7 4 5 6 8 9\n B1:\n 10 11\n"
	
	cout << "Expected Output: B" << endl;
	cout << "Actual Output: " << H1.extractMin() << endl; // Should output B / 2

	cout << "Expected Output:\nB2:\nC D k l\nB3:\nc j d e f g h i" << endl;
	cout << "Actual Output:" << endl;
	H1.printKey();
	// Should output "B2:\n C D k l\n B3:\n c j d e f g h i\n"
	// Equivalent to: "B2:\n 3 4 10 11\n B3:\n 3 7 4 5 6 8 9\n"
	
	return 0;
}