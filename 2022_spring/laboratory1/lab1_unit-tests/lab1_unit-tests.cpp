#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1/map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab1unittests
{
	TEST_CLASS(lab1unittests)
	{
	public:
		
		TEST_METHOD(InsertRootTest)
		{
			RBTree<size_t, int> rbtree;
			rbtree.Insert(1, 10);

			Assert::IsTrue(rbtree.GetKeys()->head->data == 1 && rbtree.GetValues()->head->data == 10);
		}

		TEST_METHOD(InsertTest_Pass)
		{
			RBTree<size_t, int> rbtree;
			rbtree.Insert(5, 10);
			rbtree.Insert(2, 5);
			rbtree.Insert(3, 15);
			rbtree.Insert(14, 6);

			List<size_t> expectedKeysList = { 4u, new size_t[4u]{ 3, 2, 5, 14 } };
			List<int> expectedValuesList = { 4u, new int[4u]{15, 5, 10, 6} };
			Assert::IsTrue(expectedKeysList == *rbtree.GetKeys() && expectedValuesList == *rbtree.GetValues());
		}

		TEST_METHOD(InsertSameTest_Fail)
		{
			RBTree<size_t, int> rbtree;
			rbtree.Insert(5, 10);
			rbtree.Insert(2, 5);

			Assert::ExpectException<invalid_argument>([&] { rbtree.Insert(2, 1); });
		}

		TEST_METHOD(RemoveEmptyTest_Fail)
		{
			RBTree<size_t, int> rbtree;

			Assert::ExpectException<logic_error>([&] { rbtree.Remove(5); });
		}

		TEST_METHOD(RemoveTest_Pass)
		{
			RBTree<size_t, int> rbtree;
			rbtree.Insert(5, 10);
			rbtree.Insert(2, 5);
			rbtree.Insert(3, 15);
			rbtree.Insert(14, 6);
			rbtree.Remove(2);

			List<size_t> expectedKeysList = { 3u, new size_t[3u]{ 3, 5, 14 } };
			List<int> expectedValuesList = { 3u, new int[3u]{15, 10, 6} };

			Assert::IsTrue(expectedKeysList == *rbtree.GetKeys() && expectedValuesList == *rbtree.GetValues());
		}

		TEST_METHOD(RemoveNonExistantTest_Fail)
		{
			RBTree<size_t, int> rbtree;
			rbtree.Insert(5, 10);
			rbtree.Insert(2, 5);
			rbtree.Insert(3, 15);
			rbtree.Insert(14, 6);

			Assert::ExpectException<invalid_argument>([&] { rbtree.Remove(7); });
		}

		TEST_METHOD(FindTest_Pass)
		{
			RBTree<size_t, int> rbtree;
			rbtree.Insert(5, 10);
			rbtree.Insert(2, 5);
			rbtree.Insert(3, 15);
			rbtree.Insert(10, 6);

			Assert::IsTrue(rbtree.Find(10) == 6);
		}

		TEST_METHOD(FindTest_Fail)
		{
			RBTree<size_t, int> rbtree;
			rbtree.Insert(5, 10);
			rbtree.Insert(2, 5);
			rbtree.Insert(3, 15);
			rbtree.Insert(10, 6);

			Assert::ExpectException<invalid_argument>([&] { rbtree.Find(7); });
		}

		TEST_METHOD(GetKeysTest)
		{
			RBTree<size_t, int> rbtree;
			rbtree.Insert(5, 10);
			rbtree.Insert(2, 5);
			rbtree.Insert(3, 15);
			rbtree.Insert(14, 6);

			List<size_t> expectedList = { 4u, new size_t[4u]{ 3, 2, 5, 14 } };
			Assert::IsTrue(expectedList == *rbtree.GetKeys());
		}

		TEST_METHOD(GetValuesTest)
		{
			RBTree<size_t, int> rbtree;
			rbtree.Insert(5, 10);
			rbtree.Insert(2, 5);
			rbtree.Insert(3, 15);
			rbtree.Insert(14, 6);

			List<int> expectedList = { 4u, new int[4u]{15, 5, 10, 6} };
			Assert::IsTrue(expectedList == *rbtree.GetValues());
		}

		TEST_METHOD(ClearTests)
		{
			RBTree<size_t, int> rbtree;
			rbtree.Insert(5, 10);
			rbtree.Insert(2, 5);
			rbtree.Insert(3, 15);
			rbtree.Insert(14, 6);
			rbtree.Clear();
			Assert::IsNull(rbtree.GetKeys()->head);
			Assert::ExpectException<logic_error>([&] { rbtree.Clear(); });
		}
	};
}
