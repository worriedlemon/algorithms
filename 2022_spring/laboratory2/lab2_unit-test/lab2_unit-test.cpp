#include "pch.h"
#include "CppUnitTest.h"
#include "../lab2/haffman.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab2unittest
{
	TEST_CLASS(lab2unittest)
	{
	public:
		string test_string = "Hello world!";

		TEST_METHOD(GetSymbolsCountTest)
		{
			HaffmanEncoder encoder;
			CountingMap<char> symbolsCount = encoder.GetSymbolsCount(test_string);

			List<Bundle<char, size_t>> expectedList = {
				Bundle<char, size_t>('e', 1), Bundle<char, size_t>('H', 1), Bundle<char, size_t>(' ', 1),
				Bundle<char, size_t>('!', 1), Bundle<char, size_t>('d', 1), Bundle<char, size_t>('o', 2),
				Bundle<char, size_t>('l', 3), Bundle<char, size_t>('w', 1), Bundle<char, size_t>('r', 1) };

			Assert::IsTrue(expectedList == *symbolsCount.GetKeysAndValues());
		}

		TEST_METHOD(EncodeTest_EmptyStringFail)
		{
			HaffmanEncoder encoder;
			string blank_str = "";
			Assert::ExpectException<length_error>([&] { encoder.Encode(blank_str); }); // Nothing to encode if string is blank
		}

		TEST_METHOD(EncodeTest_Pass)
		{
			HaffmanEncoder encoder;

			try
			{
				encoder.Encode(test_string); // Fictional test, at leat Encode shouldn't throw exceptions
				Assert::IsTrue(true);
			}
			catch (exception&) {
				Assert::IsTrue(false);
			}
		}

		TEST_METHOD(ResetTest_Pass)
		{
			HaffmanEncoder encoder(test_string);
			encoder.Reset(); // Resetting
			Assert::ExpectException<logic_error>([&] { encoder.Reset(); }); // Reset repeated, so exception should ne thrown
		}

		TEST_METHOD(ResetTest_Fail)
		{
			HaffmanEncoder encoder;
			Assert::ExpectException<logic_error>([&] { encoder.Reset(); }); // Reset on empty Haffman tree
		}

		TEST_METHOD(GetEncodingResultTest_Pass)
		{
			HaffmanEncoder encoder(test_string);
			bitcode expectedResult = {
				1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0,
				0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1 };

			Assert::IsTrue(expectedResult == encoder.GetEncodingResult());
		}

		TEST_METHOD(GetEncodingResultTest_Fail)
		{
			HaffmanEncoder encoder;
			Assert::ExpectException<logic_error>([&] { encoder.GetEncodingResult(); }); // Getting results on empty Haffman tree
		}

		TEST_METHOD(DecodeTest_Pass)
		{
			HaffmanEncoder encoder(test_string);
			Assert::IsTrue(test_string == encoder.Decode(encoder.GetEncodingResult())); // Decoding an encoded string should be original string 
		}

		TEST_METHOD(DecodeTest_Fail)
		{
			HaffmanEncoder encoder;
			Assert::ExpectException<logic_error>([&] { encoder.Decode(bitcode{ 1, 0, 1, 1, 0, 0 }); }); // Decode on empty Haffman tree
		}

		TEST_METHOD(GetCodesTest_Pass)
		{
			HaffmanEncoder encoder(test_string);
			Map<char, bitcode> codes = encoder.GetCodes();
			Bundle<char, bitcode> bundles[9] = {
				Bundle<char, bitcode>('l', new bitcode{0, 1}),
				Bundle<char, bitcode>('d', new bitcode{ 0, 0, 0 }),
				Bundle<char, bitcode>('!', new bitcode{ 1, 1, 1, 1 }),
				Bundle<char, bitcode>(' ', new bitcode{ 1, 1, 1, 0 }),
				Bundle<char, bitcode>('H', new bitcode{ 1, 1, 0, 1 }),
				Bundle<char, bitcode>('e', new bitcode{ 1, 1, 0, 0 }),
				Bundle<char, bitcode>('r', new bitcode{ 1, 0, 0 }),
				Bundle<char, bitcode>('o', new bitcode{ 1, 0, 1 }),
				Bundle<char, bitcode>('w', new bitcode{ 0, 0, 1 })};

			 Assert::IsTrue(List<Bundle<char, bitcode>>{ 9u, bundles } == *codes.GetKeysAndValues());
		}

		TEST_METHOD(GetCodesTest_Fail)
		{
			HaffmanEncoder encoder;
			Assert::ExpectException<logic_error>([&] { encoder.GetCodes(); }); // Getting codes on empty Haffman tree
		}

		TEST_METHOD(SerializeTest_Pass)
		{
			HaffmanEncoder encoder(test_string);
			char expectedResult[] = { -36, 91, -58, -60, 120, 0 };
			Assert::IsTrue(string(expectedResult) == encoder.Serialize(encoder.GetEncodingResult()));
		}

		TEST_METHOD(SerializeTest_Null)
		{
			HaffmanEncoder encoder(test_string);
			bitcode null = {};
			Assert::IsTrue("" == encoder.Serialize(null)); // Serializing empty bitcode
		}

		TEST_METHOD(UsedBitsTest_Pass)
		{
			HaffmanEncoder encoder(test_string);
			Bundle<size_t, size_t> usedBits = encoder.UsedBits();
			Assert::IsTrue(usedBits.name == 96 && usedBits.value == 37);
		}

		TEST_METHOD(UsedBitsTest_Fail)
		{
			HaffmanEncoder encoder;
			Assert::ExpectException<logic_error>([&] { encoder.UsedBits(); }); // Getting memory results on empty Haffman tree
		}

		TEST_METHOD(CompressionTest_Pass)
		{
			HaffmanEncoder encoder(test_string);
			Assert::IsTrue(encoder.CompressionRate() == 96.0/37.0);
		}

		TEST_METHOD(CompressionRateTest_Fail)
		{
			HaffmanEncoder encoder;
			Assert::ExpectException<logic_error>([&] { encoder.CompressionRate(); }); // Getting compression rate on empty Haffman tree
		}
	};
}
