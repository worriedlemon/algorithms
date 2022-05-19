#include "pch.h"
#include "CppUnitTest.h"
#include "../maximumflow/flownetwork.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define CONCAT(str1, str2) # str1##str2
#define TEST_FILE(str) testDirectory + str

const string GetTestDirectory(string path)
{
	const size_t lastSlash = path.rfind('\\');
	if (std::string::npos != lastSlash)
	{
		return path.substr(0, lastSlash + 1) + "tests\\test_";
	}
	else return "";
}

double FordFulkerson(FlowNetwork& graph);

const string testDirectory = GetTestDirectory(__FILE__);

namespace courseworkunittests
{
	TEST_CLASS(courseworkunittests)
	{

		FlowNetwork& CreateFlowNetworkFromFile(string file)
		{
			FlowNetwork* graph = new FlowNetwork();
			ifstream fin;
			fin.open(file);
			if (!fin.good()) throw bad_exception();
			fin >> *graph;
			fin.close();
			return *graph;
		}

	public:
		
		TEST_METHOD(FlowNetworkLiteTest_Pass)
		{
			FlowNetwork graph = CreateFlowNetworkFromFile(TEST_FILE("lite.txt"));
			Assert::IsTrue(FordFulkerson(graph) == 5);
		}
		
		TEST_METHOD(FlowNetworkHardTest_Pass)
		{
			FlowNetwork graph = CreateFlowNetworkFromFile(TEST_FILE("hard.txt"));
			Assert::IsTrue(FordFulkerson(graph) == 24);
		}

		TEST_METHOD(FlowNetworkTest_FailOnNoSource)
		{
			Assert::ExpectException<logic_error>([&] { CreateFlowNetworkFromFile(TEST_FILE("no_source.txt")); });
		}

		TEST_METHOD(FlowNetworkTest_FailOnNoDrain)
		{
			Assert::ExpectException<logic_error>([&] { CreateFlowNetworkFromFile(TEST_FILE("no_drain.txt")); });
		}

		TEST_METHOD(FlowNetworkTest_FailOnSourceIncome)
		{
			Assert::ExpectException<logic_error>([&] { CreateFlowNetworkFromFile(TEST_FILE("source_incomes.txt")); });
		}

		TEST_METHOD(FlowNetworkTest_FailOnDrainOutcome)
		{
			Assert::ExpectException<logic_error>([&] { CreateFlowNetworkFromFile(TEST_FILE("drain_outcomes.txt")); });
		}
	};
}
