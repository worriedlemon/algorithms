#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1/list.h"

#define TESTVALUE_1 42U
#define TESTVALUE_2 228U

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void AtException()
{
	List list;
	list.push_back(TESTVALUE_1);
	list.push_front(TESTVALUE_2);
	list.at(2);
	return;
}

void InsertException()
{
	List list;
	list.push_back(TESTVALUE_1);
	list.insert(TESTVALUE_2, 2);
	return;
}

void PopBackException()
{
	List list;
	list.pop_back();
	return;
}

void PopFrontException()
{
	List list;
	list.pop_front();
	return;
}

void ClearException()
{
	List list;
	list.clear();
	return;
}

void SetException()
{
	List list;
	list.set(TESTVALUE_1, 0);
	return;
}

void RemoveException()
{
	List list;
	list.remove(1);
	return;
}

void PushListFrontLogicException()
{
	List list1, list2;
	list1.push_back(TESTVALUE_1);
	list2.push_front(list1);
	return;
}

void PushListFrontInvalidException()
{
	List list;
	list.push_back(TESTVALUE_1);
	list.push_front(list);
	return;
}

bool AreEqualArrays(unsigned *array1, unsigned *array2, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (array1[i] != array2[i]) return false;
	}
	return true;
}

namespace lab1unittests
{
	TEST_CLASS(lab1unittests)
	{
	public:
		//push_back() test
		TEST_METHOD(PushBack)
		{
			List list;
			list.push_back(TESTVALUE_1);
			list.push_back(TESTVALUE_2);
			unsigned expected[2] = { list.at(0), list.at(1) }, actual[2] = { TESTVALUE_1, TESTVALUE_2 };
			Assert::IsTrue(AreEqualArrays(expected, actual, 2));
		}

		//push_front() test
		TEST_METHOD(PushElementFront)
		{
			List list;
			list.push_front(TESTVALUE_1);
			list.push_front(TESTVALUE_2);
			unsigned expected[2] = { list.at(0), list.at(1) }, actual[2] = { TESTVALUE_2, TESTVALUE_1 };
			Assert::IsTrue(AreEqualArrays(expected, actual, 2));
		}

		//pop_back() test
		TEST_METHOD(PopBack_Pass)
		{
			List list;
			list.push_back(TESTVALUE_1);
			list.push_back(0);
			list.push_front(TESTVALUE_2);

			list.pop_back();
			unsigned expected[2] = { list.at(0), list.at(1) }, actual[2] = {TESTVALUE_2, TESTVALUE_1};
			Assert::IsTrue(AreEqualArrays(expected, actual, 2));
		}

		//pop_back(), catches exception
		TEST_METHOD(PopBack_Fail)
		{
			Assert::ExpectException<logic_error>(PopBackException);
		}
		
		//pop_front() test
		TEST_METHOD(PopFront)
		{
			List list;
			list.push_back(TESTVALUE_1);
			list.push_back(0);
			list.push_front(TESTVALUE_2);

			list.pop_front();
			unsigned expected[2] = { list.at(0), list.at(1) }, actual[2] = { TESTVALUE_1, 0U };
			Assert::IsTrue(AreEqualArrays(expected, actual, 2));
		}

		//pop_front(), catches exception
		TEST_METHOD(PopFront_Fail)
		{
			Assert::ExpectException<logic_error>(PopFrontException);
		}

		//get_size() test function
		TEST_METHOD(GetSize)
		{
			List list;
			list.push_back();
			list.push_back();
			Assert::IsTrue(list.get_size() == 2);
		}

		//at() function, returns value
		TEST_METHOD(AtFunction_Pass)
		{
			List list;
			list.push_back(TESTVALUE_1);
			list.push_front(TESTVALUE_2);
			Assert::AreEqual(list.at(0), TESTVALUE_2);
		}

		//at() function, catches exception
		TEST_METHOD(AtFunction_Fail)
		{
			Assert::ExpectException<out_of_range>(AtException);
		}

		//insert() in the beginning of the list
		TEST_METHOD(Insert_FrontNull)
		{
			List list;
			list.insert(TESTVALUE_1, 0);
			Assert::AreEqual(list.at(0), TESTVALUE_1);
		}

		//insert() in the middle of the list
		TEST_METHOD(Insert_Middle)
		{
			List list;
			list.push_back(TESTVALUE_1);
			list.push_back(TESTVALUE_2);
			list.insert(0, 1);
			Assert::AreEqual(list.at(1), 0U);
		}

		//insert() in the end of the list
		TEST_METHOD(Insert_Back)
		{
			List list;
			list.push_back(TESTVALUE_1);
			list.insert(TESTVALUE_2, list.get_size());
			Assert::AreEqual(list.at(list.get_size()-1), TESTVALUE_2);
		}

		//insert(), catches exception
		TEST_METHOD(Insert_Fail)
		{
			Assert::ExpectException<out_of_range>(InsertException);
		}

		//isEmpty() with an empty list
		TEST_METHOD(EmptyList_True)
		{
			List list;
			Assert::IsTrue(list.isEmpty());
		}

		//isEmpty() with not an empty list
		TEST_METHOD(EmptyList_False)
		{
			List list;
			list.push_back(0);
			Assert::IsFalse(list.isEmpty());
		}

		//clear() test
		TEST_METHOD(Clear_Pass)
		{
			List list;
			list.push_back(TESTVALUE_1);
			list.clear();
			Assert::IsTrue(list.isEmpty());
		}

		//clear() test, catches exception
		TEST_METHOD(Clear_Fail)
		{
			Assert::ExpectException<logic_error>(ClearException);
		}

		//set() test, changes value
		TEST_METHOD(Set_Pass)
		{
			List list;
			list.push_back(TESTVALUE_1);
			list.set(TESTVALUE_2, 0);
			Assert::AreEqual(list.at(0), TESTVALUE_2);
		}

		//set() test, catches exception
		TEST_METHOD(Set_Fail)
		{
			Assert::ExpectException<logic_error>(SetException);
		}

		//remove() test, deletes element
		TEST_METHOD(Remove_Pass)
		{
			List list;
			list.push_back(TESTVALUE_1);
			list.push_back(0);
			list.push_back(TESTVALUE_2);
			list.remove(1);
			unsigned expected[2] = { list.at(0), list.at(1) }, actual[2] = { TESTVALUE_1, TESTVALUE_2 };
			Assert::IsTrue(AreEqualArrays(expected, actual, 2));
		}

		//remove() test, catches exception
		TEST_METHOD(Remove_Fail)
		{
			Assert::ExpectException<logic_error>(RemoveException);
		}

		TEST_METHOD(PushListFront_Pass)
		{
			List list1, list2;
			list1.push_back(TESTVALUE_1);
			list1.push_back(TESTVALUE_2);
			list2.push_front(TESTVALUE_1);
			list2.push_front(TESTVALUE_2);
			list1.push_front(list2);
			unsigned expected[4] = { list1.at(0), list1.at(1), list1.at(2), list1.at(3) },
				actual[4] = { TESTVALUE_2, TESTVALUE_1, TESTVALUE_1, TESTVALUE_2 };
			Assert::IsTrue(AreEqualArrays(expected, actual, 4));
		}	

		TEST_METHOD(PushListFront_LogicFail)
		{
			Assert::ExpectException<logic_error>(PushListFrontLogicException);
		}

		TEST_METHOD(PushListFront_InvalidFail)
		{
			Assert::ExpectException<invalid_argument>(PushListFrontInvalidException);
		}
	};
}
