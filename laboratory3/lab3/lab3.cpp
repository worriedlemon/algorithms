#include <iostream>
using namespace std;
#include "BinaryHeap.h"

enum TestValues
{
	TEST_1 = 2,
	TEST_2 = 6,
	TEST_3 = 11,
	TEST_4 = 4
};

int main()
{
    BinaryHeap heap;
	heap.insert(TEST_1);
	cout << heap << "\n";
	heap.insert(TEST_2);
	cout << heap << "\n";
	heap.insert(TEST_3);
	cout << heap << "\n";
	heap.insert(TEST_4);
	cout << heap << "\n";
	heap.remove(TEST_1);
	cout << heap << "\n";
    return 0;
}
