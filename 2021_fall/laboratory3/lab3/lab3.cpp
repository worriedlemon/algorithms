#include <iostream>
#include <stdexcept>
using namespace std;
#include "BinaryHeap.h"
#include "Iterator.h"

int main()
{
	cout << "######################################################\n";
	cout << "############   BINARY HEAP METHODS TEST   ############\n";
	cout << "######################################################\n\n";

	cout << "Initializing heap...\n";
    BinaryHeap heap;
	cout << "Inserting elements: 2, 6, 11, 4, 19, 3\n\n";
	heap.insert(2);
	heap.insert(6);
	heap.insert(11);
	heap.insert(4);
	heap.insert(19);
	heap.insert(3);
	cout << "Initializing breadth-first traversal iterator...\n";

	IIterator* iterator = heap.create_bft_iterator();
	cout << "Launching the BFT... Heap looks like:\n";
	while (iterator->has_next())
	{
		cout << iterator->next() << " ";
	}
	cout << "\n\n" << "Comparing output with the overriden ostream operator function:\n" << heap << "\n\nEqual.\n";
	delete iterator;
	cout << "Initializing depth-first traversal iterator...\n";
	iterator = heap.create_dft_iterator();
	cout << "Launching the DFT... Heap looks like:\n";
	while (iterator->has_next())
	{
		cout << iterator->next() << " ";
	}
	delete iterator;
	cout << "\n\nChecking whether heap has \"6\" element: " << (heap.contains(6) ? "YES" : "NO");
	cout << "\n\nRemoving element \"6\" from the heap:\n";
	heap.remove(6);
	cout << heap << "\n\nChecking whether heap has \"6\" element: " << (heap.contains(6) ? "YES" : "NO");
	try
	{
		cout << "\n\nTrying to remove \"6\" element from the heap...\n";
		heap.remove(6);
	}
	catch (invalid_argument error)
	{
		cout << "[!] Exception caught: " << error.what() << "\n";
	}
    return 0;
}
