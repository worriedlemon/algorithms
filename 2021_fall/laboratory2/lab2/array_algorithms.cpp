#include <algorithm>

// Effective search algorithm based on splitting the sorted array in halves until the element is found
bool BinarySearch(int* array, size_t size, int element)
{
	size_t left = 0, right = size - 1;
	while (left != right)
	{
		size_t middle = (right + left) / 2;
		if (array[middle] > element) right = --middle;
		else if (array[middle] < element) left = ++middle;
		if (array[middle] == element) return true;
	}
	return false;
}

// Ineffective sorting algorithm, just for an example
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
				std::random_shuffle(array, array + size);
				break;
			}
		}
		if (i == size - 1) unsorted = false;
	}
	return;
}

// Simple O(n^2) sorting algorithm, which swaps "lighter" elements with "heavier", so "lighter" elements pop up like bubbles
void BubbleSort(int *array, size_t size)
{
	for (size_t i = 0; i < size - 1; i++)
	for (size_t j = 0; j < size - 1 - i; j++)
	{
		if (array[j] > array[j+1])
		{
			int temp = array[i];
			array[j] = array[j+1];
			array[j+1] = temp;
		}
	}
	return;
}

// Standart quick O(n*log n) sorting algorithm based on recurrence
void QuickSort(int* array, size_t leftIndex, size_t rightIndex)
{
	size_t left = leftIndex, right = rightIndex;
	int pivot = array[(left + right) / 2];
	while (left < right)
	{
		while (array[left] < pivot)
		{
			if (left >= right) break;
			left++;
		}
		while (array[right] > pivot)
		{
			if (left >= right || right == 0) break;
			right--;
		}
		if (left <= right)
		{
			int temporaryElement = array[left];
			array[left] = array[right];
			array[right] = temporaryElement;
			left++;
			if (right != 0) right--;
		}
	}
	if (leftIndex < right) QuickSort(array, leftIndex, right);
	if (left < rightIndex) QuickSort(array, left, rightIndex);
	return;
}

// Very effective sorting algorithm applied on big arrays with a lot of repeating elements
void CountingSort(unsigned char *array, size_t size)
{
	unsigned char countSize = 0;
	for (unsigned char i = 0; i < size; i++)
	{
		countSize = (array[i] > countSize ? array[i] : countSize);
	}
	countSize -= 31;

	size_t* count = new size_t[countSize], k = 0;
	for (size_t i = 0; i < countSize; i++) count[i] = 0;
	for (size_t i = 0; i < size; i++) count[array[i] - 32]++;
	for (unsigned char i = 0; i < countSize; i++)
	{
		for (size_t j = 0; j < count[i]; j++)
		{
			array[k] = i + 32;
			k++;
		}
	}
	delete[] count;
	return;
}
