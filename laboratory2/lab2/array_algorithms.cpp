#include <algorithm>

bool BinarySearch(int* array, size_t size, int element)
{
	size_t left = 0, right = size - 1;
	while (1)
	{
		size_t middle = (right + left) / 2;
		if (array[middle] == element) return true;
		else if (array[middle] > element) right = middle - 1;
		else left = middle + 1;
		if (left == right) break;
	}
	return false;
}

// Ineffective sorting algorithm
void BogoSort(int* array, size_t size)
{
	bool unsorted = true;
	while (unsorted)
	{
		size_t i;
		for (i = 0; i < size - 1; i++)
		{
			if (array[i] > array[i + 1])
			{
				std::random_shuffle(array, array + size - 1);
				break;
			}
		}
		if (i == size - 1) unsorted = false;
	}
	return;
}

// Simple O(n^2) sorting algorithm
void BubbleSort(int *array, size_t size)
{
	for (size_t i = 0; i < size - 1; i++)
	for (size_t j = i; j < size; j++)
	{
		if (array[i] > array[j])
		{
			int temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
	return;
}

// Standart quick O(n*log n) sorting algorithm
void QuickSort(int* array, size_t left, size_t right)
{	
	
	return;
}