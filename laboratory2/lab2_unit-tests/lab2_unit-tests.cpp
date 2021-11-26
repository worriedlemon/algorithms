#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool BinarySearch(int* array, size_t size, int element);
void BubbleSort(int* array, size_t size);
void BogoSort(int* array, size_t size);
void QuickSort(int* array, size_t leftIndex, size_t rightIndex);
void CountingSort(unsigned char *array, size_t size);

const size_t array_size = 10;

template <typename T>
bool ArraysAreEqual(T* arr1, T* arr2, size_t size)
{
	for (size_t i = 0; i < size; i++)
		if (arr1[i] != arr2[i]) return false;
	return true;
}

namespace lab2unittests
{
	TEST_CLASS(lab2unittests)
	{
	public:
		
		TEST_METHOD(BinarySearch_Found_Test)
		{
			int test_array[array_size] = { 9, 10, 18, 49, 55, 59, 78, 78, 89, 91 };

			Assert::IsTrue(BinarySearch(test_array, array_size, 49));
		}

		TEST_METHOD(BinarySearch_NotFound_Test)
		{
			int test_array[array_size] = { 9, 10, 18, 49, 55, 59, 78, 78, 89, 91 };

			Assert::IsFalse(BinarySearch(test_array, array_size, 26));
		}

		TEST_METHOD(BubbleSort_Sorted_Test)
		{
			int original[array_size] = { 9, 10, 18, 49, 55, 59, 78, 78, 89, 91 };
			int expected[array_size] = { 9, 10, 18, 49, 55, 59, 78, 78, 89, 91 };

			BubbleSort(original, array_size);
			Assert::IsTrue(ArraysAreEqual(original, expected, array_size));
		}

		TEST_METHOD(BubbleSort_Random_Test)
		{
			int original[array_size] = { 78, 49, 18, 10, 59, 78, 55, 91, 9, 89 };
			int expected[array_size] = { 9, 10, 18, 49, 55, 59, 78, 78, 89, 91 };

			BubbleSort(original, array_size);
			Assert::IsTrue(ArraysAreEqual(original, expected, array_size));
		}

		TEST_METHOD(BubbleSort_Reversed_Test)
		{
			int original[array_size] = { 91, 89, 78, 78, 59, 55, 49, 18, 10, 9 };
			int expected[array_size] = { 9, 10, 18, 49, 55, 59, 78, 78, 89, 91 };

			BubbleSort(original, array_size);
			Assert::IsTrue(ArraysAreEqual(original, expected, array_size));
		}

		TEST_METHOD(QuickSort_Sorted_Test)
		{
			int original[array_size] = { 9, 10, 18, 49, 55, 59, 78, 78, 89, 91 };
			int expected[array_size] = { 9, 10, 18, 49, 55, 59, 78, 78, 89, 91 };

			QuickSort(original, 0, array_size - 1);
			Assert::IsTrue(ArraysAreEqual(original, expected, array_size));
		}

		TEST_METHOD(QuickSort_Random_Test)
		{
			int original[array_size] = { 78, 49, 18, 10, 59, 78, 55, 91, 9, 89 };
			int expected[array_size] = { 9, 10, 18, 49, 55, 59, 78, 78, 89, 91 };

			QuickSort(original, 0, array_size-1);
			Assert::IsTrue(ArraysAreEqual(original, expected, array_size));
		}

		TEST_METHOD(QuickSort_Reversed_Test)
		{
			int original[array_size] = { 91, 89, 78, 78, 59, 55, 49, 18, 10, 9 };
			int expected[array_size] = { 9, 10, 18, 49, 55, 59, 78, 78, 89, 91 };

			QuickSort(original, 0, array_size - 1);
			Assert::IsTrue(ArraysAreEqual(original, expected, array_size));
		}

		TEST_METHOD(BogoSort_Sorted_Test)
		{
			int original[array_size - 3] = { 10, 18, 49, 55, 59, 78, 91 };
			int expected[array_size - 3] = { 10, 18, 49, 55, 59, 78, 91 };

			BubbleSort(original, array_size - 3);
			Assert::IsTrue(ArraysAreEqual(original, expected, array_size - 3));
		}

		TEST_METHOD(BogoSort_Random_Test)
		{
			int original[array_size-3] = { 49, 18, 10, 59, 78, 55, 91 };
			int expected[array_size-3] = { 10, 18, 49, 55, 59, 78, 91 };

			BubbleSort(original, array_size-3);
			Assert::IsTrue(ArraysAreEqual(original, expected, array_size - 3));
		}

		TEST_METHOD(BogoSort_Reversed_Test)
		{
			int original[array_size - 3] = { 91, 78, 59, 55, 49, 18, 10 };
			int expected[array_size - 3] = { 10, 18, 49, 55, 59, 78, 91 };

			BubbleSort(original, array_size - 3);
			Assert::IsTrue(ArraysAreEqual(original, expected, array_size - 3));
		}

		TEST_METHOD(CountingSort_Sorted_Test)
		{
			unsigned char original[array_size] = { 42, 63, 69, 107, 145, 148, 185, 193, 220, 231 };
			unsigned char expected[array_size] = { 42, 63, 69, 107, 145, 148, 185, 193, 220, 231 };

			CountingSort(original, array_size);
			Assert::IsTrue(ArraysAreEqual(original, expected, array_size));
		}

		TEST_METHOD(CountingSort_Random_Test)
		{
			unsigned char original[array_size] = { 145, 185, 220, 63, 107, 193, 148, 69, 231, 42 };
			unsigned char expected[array_size] = { 42, 63, 69, 107, 145, 148, 185, 193, 220, 231 };

			CountingSort(original, array_size);
			Assert::IsTrue(ArraysAreEqual(original, expected, array_size));
		}

		TEST_METHOD(CountingSort_Reversed_Test)
		{
			unsigned char original[array_size] = { 231, 220, 193, 185, 148, 145, 107, 69, 63, 42};
			unsigned char expected[array_size] = { 42, 63, 69, 107, 145, 148, 185, 193, 220, 231 };

			CountingSort(original, array_size);
			Assert::IsTrue(ArraysAreEqual(original, expected, array_size));
		}
	};
}
