#include <iostream>
using namespace std;
#include "sorting_enum.h"

template <typename T> void FillArray(T* array, size_t size);
double GetAverageExecutionTime(size_t sizeOfArray, SortingAlgorithm function);

bool BinarySearch(int* array, size_t size, int element);
void BubbleSort(int* array, size_t size);
void BogoSort(int* array, size_t size);
void QuickSort(int* array, size_t leftIndex, size_t rightIndex);
void CountingSort(unsigned char *array, size_t size);

template <typename T>
void OutArray(T* array, size_t size)
{
	for (size_t i = 0; i < size; i++) cout << array[i] << " ";
	return;
}

int main()
{
	size_t sizes[] = { 10, 100, 1000, 10000, 100000 };

	cout << "########################################################\n";
	cout << "##########  ALGORITHMS AND SORT METHODS TEST  ##########\n";
	cout << "########################################################\n\n";

	cout << "Initialize random array of 20 ASCII characters:\n";
	unsigned char *arrChar = new unsigned char[20];
	FillArray(arrChar, 20);
	OutArray(arrChar, 20);
	cout << "\n\nSorted array with CountingSort:\n";
	CountingSort(arrChar, 20);
	OutArray(arrChar, 20);
	delete[] arrChar;

	cout << "\n\nInitialize random array of 8 integer numbers:\n";
	int* arrInt = new int[8];
	FillArray(arrInt, 8);
	OutArray(arrInt, 8);
	cout << "\n\nTrying to sort it with BogoSort...\n";
	BogoSort(arrInt, 8);
	cout << "Success! Sorted array looks like\n";
	OutArray(arrInt, 8);

	cout << "\n\nThe average execution algoritm of a BogoSort algorithm is ";
	cout << GetAverageExecutionTime(8, SortingAlgorithm::BogoSort);
	cout << " seconds (8 elements).\n\n";

	cout << "Let's find elements 1825, 271 and " << arrInt[5] << " within the array...\n";
	cout << "1825: " << (BinarySearch(arrInt, 8, 1825) ? "FOUND" : "NOT FOUND") << ",\n"
		<< "271: " << (BinarySearch(arrInt, 8, 271) ? "FOUND" : "NOT FOUND") << ",\n"
		<< arrInt[5] << ": " << (BinarySearch(arrInt, 8, arrInt[5]) ? "FOUND" : "NOT FOUND") << "\n" << endl;
	delete[] arrInt;

	cout << "Comparison of an average execution time of BubbleSort and QuickSort algorithms:\n\n";

	for (size_t i = 0; i < 5; i++)
	{
		cout << "The average execution time of a BubbleSort algorithm is ";
		cout << GetAverageExecutionTime(sizes[i], SortingAlgorithm::BubbleSort);
		cout << " seconds (" << sizes[i] << " elements).\n";


		cout << "The average execution time of a QuickSort algorithm is ";
		cout << GetAverageExecutionTime(sizes[i], SortingAlgorithm::QuickSort);
		cout << " seconds (" << sizes[i] << " elements).\n\n";
	}

	cout << "QuickSort is much faster than BubbleSort on big arrays,\n"
		<< "though it isn't noticeable at 10 and 100 elements." << endl;

	return 0;
}