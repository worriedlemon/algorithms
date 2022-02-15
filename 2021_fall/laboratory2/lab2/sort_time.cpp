#include <random>
#include <ctime>
#include "sorting_enum.h"

void BubbleSort(int* array, size_t size);
void BogoSort(int* array, size_t size);
void QuickSort(int* array, size_t leftIndex, size_t rightIndex);
void CountingSort(unsigned char *array, size_t size);

// Template for filling the array with random integer numbers
template <typename T>
void FillArray(T* array, size_t size)
{
	srand(time(0));
	for (size_t i = 0; i < size; i++)
		array[i] = (sizeof(T) == 1 ? (rand() % 224) + 32 : rand());
	return;
}

// Function for checking the average execution time of a $function (based on 10 starts)
double GetAverageExecutionTime(size_t sizeOfArray, SortingAlgorithm function)
{
	double overallTime = 0;
	for (size_t i = 0; i < 10; i++)
	{
		clock_t ticks;
		if (function == SortingAlgorithm::CountingSort)
		{
			unsigned char *array = new unsigned char[sizeOfArray];
			FillArray(array, sizeOfArray);
			ticks = clock();
			CountingSort(array, sizeOfArray);
			ticks = clock() - ticks;
			delete[] array;
		}
		else
		{
			int* array = new int[sizeOfArray];
			FillArray(array, sizeOfArray);
			if (function == SortingAlgorithm::QuickSort)
			{
				ticks = clock();
				QuickSort(array, 0, sizeOfArray - 1);
				ticks = clock() - ticks;
			}
			else if (function == SortingAlgorithm::BubbleSort)
			{
				ticks = clock();
				BubbleSort(array, sizeOfArray);
				ticks = clock() - ticks;
			}
			else if (function == SortingAlgorithm::BogoSort)
			{
				ticks = clock();
				BogoSort(array, sizeOfArray);
				ticks = clock() - ticks;
			}
			else ticks = -1;
			delete[] array;
		}
		overallTime += (double)ticks / CLOCKS_PER_SEC;
	}
	return overallTime / 10;
}