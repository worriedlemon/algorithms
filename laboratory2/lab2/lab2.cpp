#include <iostream>
using namespace std;

typedef void _Func(int*, size_t);

template <typename T> void FillArray(T* array, size_t size);
double GetAverageExecutionTime(size_t sizeOfArray, _Func function);

bool BinarySearch(int* array, size_t size, int element);
void BubbleSort(int* array, size_t size);
void BogoSort(int* array, size_t size);
void QuickSort(int* array, size_t left, size_t right);

template <typename T>
void OutArray(T* array, size_t size)
{
	for (size_t i = 0; i < size; i++) cout << array[i] << " ";
	return;
}

int main()
{
	size_t sizes[] = { 10, 100, 1000, 10000};

	double avgTime;
	for (size_t i = 0; i < 4; i++)
	{
		avgTime = GetAverageExecutionTime(sizes[i], BubbleSort);
		cout << "The average execution time of a BubbleSort algorithm is " <<
			avgTime << " seconds (array consists of " << sizes[i] << " elements).\n";
	}
	
	return 0;
}