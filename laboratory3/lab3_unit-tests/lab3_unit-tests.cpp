#include "pch.h"
#include "CppUnitTest.h"
#include "../lab3/BinaryHeap.h"
#include "../lab3/Iterator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab3unittests
{
	enum TestValues
	{
		TEST_1 = 2,
		TEST_2 = 6,
		TEST_3 = 11,
		TEST_4 = 4
	};

	void RemoveException()
	{
		BinaryHeap heap;
		heap.insert(TEST_1);
		heap.insert(TEST_2);
		heap.insert(TEST_3);
		
		heap.remove(TEST_4);
		return;
	}

	void NextDFTException()
	{
		BinaryHeap heap;

		IIterator* iterator = heap.create_dft_iterator();
		iterator->next();
		return;
	}

	void NextBFTException()
	{
		BinaryHeap heap;

		IIterator* iterator = heap.create_bft_iterator();
		iterator->next();
		return;
	}

	TEST_CLASS(lab3unittests)
	{
	public:
		
		TEST_METHOD(HasNext_DFT_Test)
		{
			BinaryHeap heap;
			heap.insert(TEST_1);

			IIterator* iterator = heap.create_dft_iterator();
			Assert::IsTrue(iterator->has_next());
			iterator->next();
			Assert::IsFalse(iterator->has_next());
			delete iterator;
		}

		TEST_METHOD(HasNext_BFT_Test)
		{
			BinaryHeap heap;
			heap.insert(TEST_1);

			IIterator* iterator = heap.create_bft_iterator();
			Assert::IsTrue(iterator->has_next());
			iterator->next();
			Assert::IsFalse(iterator->has_next());
			delete iterator;
		}

		TEST_METHOD(Next_DFT_Exception)
		{
			Assert::ExpectException<out_of_range>(NextDFTException);
		}

		TEST_METHOD(Next_BFT_Exception)
		{
			Assert::ExpectException<out_of_range>(NextBFTException);
		}

		TEST_METHOD(Contains_Test)
		{
			BinaryHeap heap;
			heap.insert(TEST_1);
			heap.insert(TEST_2);
			Assert::IsTrue(heap.contains(TEST_1));
			Assert::IsFalse(heap.contains(TEST_3));
		}

		TEST_METHOD(Insert_DFT_Test)
		{
			BinaryHeap heap;
			heap.insert(TEST_1);
			heap.insert(TEST_2);
			heap.insert(TEST_3);
			heap.insert(TEST_4);
			IIterator* iterator = heap.create_dft_iterator();
			int arr[4];
			for (char i = 0; i < 4; i++)
				arr[i] = iterator->next();
			Assert::IsTrue(arr[0] == TEST_3 && arr[1] == TEST_4 && arr[2] == TEST_1 && arr[3] == TEST_2);
			delete iterator;
		}

		TEST_METHOD(Insert_BFT_Test)
		{
			BinaryHeap heap;
			heap.insert(TEST_1);
			heap.insert(TEST_2);
			heap.insert(TEST_3);
			heap.insert(TEST_4);

			IIterator* iterator = heap.create_bft_iterator();
			int arr[4];
			for (char i = 0; i < 4; i++)
				arr[i] = iterator->next();
			Assert::IsTrue(arr[0] == TEST_3 && arr[1] == TEST_4 && arr[2] == TEST_2 && arr[3] == TEST_1);
			delete iterator;
		}

		TEST_METHOD(InsertEqual_BFT_Test)
		{
			BinaryHeap heap;
			heap.insert(TEST_1);
			heap.insert(TEST_2);
			heap.insert(TEST_3);
			heap.insert(TEST_3);

			IIterator* iterator = heap.create_bft_iterator();
			int arr[4];
			for (char i = 0; i < 4; i++)
				arr[i] = iterator->next();
			Assert::IsTrue(arr[0] == TEST_3 && arr[1] == TEST_3 && arr[2] == TEST_2 && arr[3] == TEST_1);
			delete iterator;
		}

		TEST_METHOD(InsertEqual_DFT_Test)
		{
			BinaryHeap heap;
			heap.insert(TEST_1);
			heap.insert(TEST_2);
			heap.insert(TEST_3);
			heap.insert(TEST_3);

			IIterator* iterator = heap.create_bft_iterator();
			int arr[4];
			for (char i = 0; i < 4; i++)
				arr[i] = iterator->next();
			Assert::IsTrue(arr[0] == TEST_3 && arr[1] == TEST_3 && arr[2] == TEST_2 && arr[3] == TEST_1);
			delete iterator;
		}

		TEST_METHOD(RemoveRoot_Test)
		{
			BinaryHeap heap;
			heap.insert(TEST_1);
			heap.insert(TEST_2);
			heap.insert(TEST_3);
			heap.insert(TEST_4);

			heap.remove(TEST_3);
			IIterator* iterator = heap.create_bft_iterator();
			int arr[3];
			for (char i = 0; i < 3; i++)
				arr[i] = iterator->next();
			Assert::IsTrue(arr[0] == TEST_2 && arr[1] == TEST_4 && arr[2] == TEST_1);
			delete iterator;
		}

		TEST_METHOD(RemoveMiddle_Test)
		{
			BinaryHeap heap;
			heap.insert(TEST_1);
			heap.insert(TEST_2);
			heap.insert(TEST_3);
			heap.insert(TEST_4);

			heap.remove(TEST_2);
			IIterator* iterator = heap.create_bft_iterator();
			int arr[3];
			for (char i = 0; i < 3; i++)
				arr[i] = iterator->next();
			Assert::IsTrue(arr[0] == TEST_3 && arr[1] == TEST_4 && arr[2] == TEST_1);
			delete iterator;
		}

		TEST_METHOD(RemoveFirstInNewLayer_Test)
		{
			BinaryHeap heap;
			heap.insert(TEST_1);
			heap.insert(TEST_2);
			heap.insert(TEST_3);
			heap.insert(TEST_4);

			heap.remove(TEST_1);
			IIterator* iterator = heap.create_bft_iterator();
			int arr[3];
			for (char i = 0; i < 3; i++)
				arr[i] = iterator->next();
			Assert::IsTrue(arr[0] == TEST_3 && arr[1] == TEST_4 && arr[2] == TEST_2);
			delete iterator;
		}

		TEST_METHOD(RemoveEqual_Test)
		{
			BinaryHeap heap;
			heap.insert(TEST_1);
			heap.insert(TEST_2);
			heap.insert(TEST_3);
			heap.insert(TEST_3);

			heap.remove(TEST_3);
			IIterator* iterator = heap.create_bft_iterator();
			int arr[3];
			for (char i = 0; i < 3; i++)
				arr[i] = iterator->next();
			Assert::IsTrue(arr[0] == TEST_3 && arr[1] == TEST_1 && arr[2] == TEST_2);
			delete iterator;
		}

		TEST_METHOD(RemoveLast_Test)
		{
			BinaryHeap heap;
			heap.insert(TEST_1);

			heap.remove(TEST_1);
			IIterator* iterator = heap.create_bft_iterator();
			Assert::IsFalse(iterator->has_next());
		}

		TEST_METHOD(Remove_Test_Fail)
		{
			Assert::ExpectException<invalid_argument>(RemoveException);
		}
	};
}
