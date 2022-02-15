#include "pch.h"
#include "CppUnitTest.h"
#include "..\polishnot\MathExpression.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

char* Concatenate(const char* str1, size_t number, const char* str2);

namespace courseworkunittests
{
	void NullStringException()
	{
		string MathString = "";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void SecondPointException()
	{
		string MathString = "2.,7+7.3";
		MathExpression expression;
		expression.FromString(MathString);
	}
	
	void FirstIsOperatorException()
	{
		string MathString = "*4+2";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void DoubleOperatorException()
	{
		string MathString = "4+*7";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void ClosingParenthesisFirstException()
	{
		string MathString = "5+6)/2";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void OuterDoubleParenthesisException()
	{
		string MathString = "3*(7+4)(6/2)";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void InnerDoubleParenthesisException()
	{
		string MathString = "sin()+1";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void NumberBeforeParenthesisException()
	{
		string MathString = "13(log(10))-5";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void OperatorBeforeParenthesisException()
	{
		string MathString = "4*(3-)/2";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void FunctionBeforeParenthesisException()
	{
		string MathString = "4*(sin)/2";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void NumberBeforeFunctionException()
	{
		string MathString = "4cos(pi/3)";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void NumberBeforeConstantException()
	{
		string MathString = "sec(2pi/3)*3/5";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void ConstantBeforeNumberException()
	{
		string MathString = "cosec(pi6)+11";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void UndefinedExpressionException()
	{
		string MathString = "func(9-25/4)";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void UndefinedConstantInTheEndException()
	{
		string MathString = "25/5+alpha";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void UnexpectedEndOfExpression_Operator()
	{
		string MathString = "3*sqrt(4)^";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void UnexpectedEndOfExpression_Function()
	{
		string MathString = "3*log";
		MathExpression expression;
		expression.FromString(MathString);
	}

	void UnexpectedEndOfExpression_Parenthesis()
	{
		string MathString = "((2-4)*(-1)+6";
		MathExpression expression;
		expression.FromString(MathString);
	}

	TEST_CLASS(courseworkunittests)
	{
	public:
		TEST_METHOD(NullString_Exception)
		{
			Assert::ExpectException<length_error>(NullStringException);
		}

		TEST_METHOD(SecondPoint_Exception)
		{
			Assert::ExpectException<logic_error>(SecondPointException);
		}

		TEST_METHOD(FirstIsOperator_Exception)
		{
			Assert::ExpectException<invalid_argument>(FirstIsOperatorException);
		}

		TEST_METHOD(DoubleOperator_Exception)
		{
			Assert::ExpectException<logic_error>(DoubleOperatorException);
		}

		TEST_METHOD(ClosingParenthesisFirst_Exception)
		{
			Assert::ExpectException<logic_error>(ClosingParenthesisFirstException);
		}

		TEST_METHOD(OuterDoubleParenthesis_Exception)
		{
			Assert::ExpectException<logic_error>(OuterDoubleParenthesisException);
		}

		TEST_METHOD(InnerDoubleParenthesis_Exception)
		{
			Assert::ExpectException<logic_error>(InnerDoubleParenthesisException);
		}

		TEST_METHOD(NumberBeforeParenthesis_Exception)
		{
			Assert::ExpectException<logic_error>(NumberBeforeParenthesisException);
		}

		TEST_METHOD(OperatorBeforeParenthesis_Exception)
		{
			Assert::ExpectException<logic_error>(OperatorBeforeParenthesisException);
		}

		TEST_METHOD(FunctionBeforeParenthesis_Exception)
		{
			Assert::ExpectException<logic_error>(FunctionBeforeParenthesisException);
		}

		TEST_METHOD(NumberBeforeFunction_Exception)
		{
			Assert::ExpectException<logic_error>(NumberBeforeFunctionException);
		}

		TEST_METHOD(NumberBeforeConstant_Exception)
		{
			Assert::ExpectException<logic_error>(NumberBeforeConstantException);
		}

		TEST_METHOD(ConstantBeforeNumber_Exception)
		{
			Assert::ExpectException<logic_error>(ConstantBeforeNumberException);
		}

		TEST_METHOD(UndefinedExpression_Exception)
		{
			Assert::ExpectException<invalid_argument>(UndefinedExpressionException);
		}

		TEST_METHOD(UndefinedConstantInTheEnd_Exception)
		{
			Assert::ExpectException<invalid_argument>(UndefinedConstantInTheEndException);
		}

		TEST_METHOD(UnexpectedEndOfExpression_Operator_Exception)
		{
			Assert::ExpectException<logic_error>(UnexpectedEndOfExpression_Operator);
		}

		TEST_METHOD(UnexpectedEndOfExpression_Function_Exception)
		{
			Assert::ExpectException<logic_error>(UnexpectedEndOfExpression_Function);
		}

		TEST_METHOD(UnexpectedEndOfExpression_Parenthesis_Exception)
		{
			Assert::ExpectException<logic_error>(UnexpectedEndOfExpression_Parenthesis);
		}

		TEST_METHOD(PolishNotation_Test1)
		{
			string MathString = "22*(4-sin(pi/6))+6/2";
			MathExpression expression, *polishNotation;
			expression.FromString(MathString);
			Assert::IsTrue(expression.ToString() == "22 * ( 4 - sin ( pi / 6 ) ) + 6 / 2");
			polishNotation = expression.PolishNotation();
			Assert::IsTrue(polishNotation->ToString() == "+ * 22 - 4 sin / pi 6 / 6 2");
			delete polishNotation;
		}

		TEST_METHOD(PolishNotation_Test2)
		{
			string MathString = "953*cos(pi/4)+e^(3-1/2)";
			MathExpression expression, * polishNotation;
			expression.FromString(MathString);
			Assert::IsTrue(expression.ToString() == "953 * cos ( pi / 4 ) + e ^ ( 3 - 1 / 2 )");
			polishNotation = expression.PolishNotation();
			Assert::IsTrue(polishNotation->ToString() == "+ * 953 cos / pi 4 ^ e - 3 / 1 2");
			delete polishNotation;
		}

		TEST_METHOD(GetResult_RegularExpression_Test)
		{
			string MathString = "22*(4-sin(pi/6))+6/2";
			MathExpression expression, * polishNotation;
			expression.FromString(MathString);
			polishNotation = expression.PolishNotation();
			double result = polishNotation->GetResult();
			Assert::IsTrue(result - 80 < 1e-6 && result - 80 > -1e-6);
		}

		TEST_METHOD(GetResult_FunctionComposition_Test)
		{
			string MathString = "cos(sin(4*pi))";
			MathExpression expression, * polishNotation;
			expression.FromString(MathString);
			polishNotation = expression.PolishNotation();
			double result = polishNotation->GetResult();
			Assert::IsTrue(result - 1 < 1e-6 && result - 1 > -1e-6);
		}

		TEST_METHOD(GetResult_UnaryMinuses_Test)
		{
			string MathString = "-(-(-(-5)))";
			MathExpression expression, * polishNotation;
			expression.FromString(MathString);
			polishNotation = expression.PolishNotation();
			double result = polishNotation->GetResult();
			Assert::IsTrue(result == 5);
		}

		TEST_METHOD(GetResult_Undefined_Tests)
		{
			const size_t count = 10;
			string MathString[count] = { "tg(pi/2)", "tg(3*pi/2)", "ctg(0)", "ctg(pi)", "sec(0)", "sec(pi)", "cosec(pi/2)", "cosec(3*pi/2)", "sqrt(-9)", "log(0)" };
			MathExpression expression[count], *(polishNotation)[count];
			for (size_t i = 0; i < count; i++)
			{
				expression[i].FromString(MathString[i]);
				polishNotation[i] = expression[i].PolishNotation();
				Assert::IsTrue(polishNotation[i]->GetResult() == INFINITY);
				delete polishNotation[i];
			}
		}
	};
}
