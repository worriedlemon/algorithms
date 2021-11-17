#include <random>
#include <ctime>

typedef void _Func(int*, size_t);

// Template for filling the array with random integer numbers
template <typename T>
void FillArray(T* array, size_t size)
{
	srand((unsigned)time(0));
	for (size_t i = 0; i < size; i++)
	{
		array[i] = rand();
	}
	return;
}

// Function for checking the average execution time of a $function (based on 10 starts)
double GetAverageExecutionTime(size_t sizeOfArray, _Func function)
{
	double overallTime = 0;
	for (size_t i = 0; i < 10; i++)
	{
		int* array = new int[sizeOfArray];
		FillArray(array, sizeOfArray);
		clock_t ticks = clock();
		function(array, sizeOfArray);
		ticks = clock() - ticks;
		overallTime += (double)ticks / CLOCKS_PER_SEC;
		delete[] array;
	}
	return overallTime / 10;
}