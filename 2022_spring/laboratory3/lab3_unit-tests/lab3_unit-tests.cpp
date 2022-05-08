#include "pch.h"
#include "CppUnitTest.h"
#include "../lab3/fordbellman.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab3unittests
{
	TEST_CLASS(lab3unittests)
	{
	public:
		
		TEST_METHOD(FordBellmanTest_Pass)
		{
			size_t size = 4;
			string* names = new string[size]{ "Санкт-Петербург", "Москва", "Хабаровск", "Владивосток" };
			double** values = new double* [size] {
				new double[size] {0, 10, 14, 20},
				new double[size] {20, 0, 40, INF},
				new double[size] {INF, 35, 0, 8},
				new double[size] {INF, INF, 13, 0}
			};
			AdjMatrix graph = AdjMatrix(size, names, values);

			double** expectedValues = new double* [size] {
				new double[size] {0, 10, 14, 20},
				new double[size] {20, 0, 34, 40},
				new double[size] {55, 35, 0, 8},
				new double[size] {68, 48, 13, 0}
			};

			AdjMatrix expectedResult = AdjMatrix(size, names, expectedValues);
			Assert::IsTrue(expectedResult == graph.FordBellman());
		}

		TEST_METHOD(FordBellmanTest_FailOnNullAdjMatrix)
		{
			AdjMatrix graph;
			Assert::ExpectException<logic_error>([&] { graph.FordBellman(); });
		}

		TEST_METHOD(FordBellmanTest_FailOnNegativeCycle)
		{
			size_t size = 2;
			string* names = new string[size]{ "Сан-Диего", "Сан-Франциско" };
			double** values = new double* [size] {
				new double [size] {0, -2},
				new double [size] {-1, 0}
			};

			AdjMatrix graph = AdjMatrix(size, names, values);
			Assert::ExpectException<logic_error>([&] { graph.FordBellman(); });
		}
	};
}
