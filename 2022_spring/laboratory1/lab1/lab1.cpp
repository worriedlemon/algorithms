#include <iostream>
using namespace std;

#include "map.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	Map<size_t, int> rbtree;

	rbtree.Insert(5, 10);
	rbtree.Insert(2, 5);
	rbtree.Insert(3, 15);
	rbtree.Insert(14, 6);
	rbtree.Insert(8, 11);
	rbtree.Insert(4, 2);

	cout << "Initial tree has " << rbtree.GetKeys()->GetSize() << " elements:\n" <<
		rbtree << "\n\nRemoving elements by keys \'3\' and \'2\'...\n\n";

	rbtree.Remove(3);
	rbtree.Remove(2);

	cout << "Left keys are " << *rbtree.GetKeys() << "\n";
	cout << "Left values are " << * rbtree.GetValues() << "\n" << endl;

	cout << "Found an element with a key \'8\': value = " << rbtree.Find(8) <<
		"\n\nTrying to find a removed element with a key \'3\'...\n";

	try
	{
		rbtree.Find(3);
	}
	catch (invalid_argument& error)
	{
		cout << "[!] " << error.what() << "\n";
	}

	cout << "\nThe tree looks like\n";

	rbtree.Print();
	rbtree.Clear();

	cout << "\n\nTree cleared: " << rbtree << endl;

	return 0;
}