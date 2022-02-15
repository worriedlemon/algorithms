#include <iostream>
#include <string>
using namespace std;
#include "MathExpression.h"

int main()
{
	string MathString;
	MathExpression *expression = new MathExpression(), *polishNotation;

	cout << "####################################################\n";
	cout << "####  MATH EXPRESSION PARSE TO POLISH NOTATION  ####\n";
	cout << "####################################################\n\n";

	cout << "Possible inputs:\n";
	cout << " * digits: \'0\'-\'9\', dots: \'.\' and \',\';\n";
	cout << " * arithmetical operations: \'+\', \'-\', \'/\', \'*\', \'^\' (power);\n";
	cout << " * math constants:\n";
	cout << "    + \'pi\' = 3.14...;\n    + \'e\' = 2.718...;\n    + \'phi\' = 1.618...;\n";
	cout << " * functions:\n";
	cout << "    + algebraic - \'sqrt\', \'log\' (decimal logarithm), \'ln\' (natural logarithm);\n";
	cout << "    + trigonometric - \'sin\', \'cos\', \'tg\', \'ctg\';\n";
	cout << "    + additional - \'sec\', \'cosec\'.\n\n";

	cout << "Enter your mathematical expression:\n\n";
	cin >> MathString;

	try
	{
		expression->FromString(MathString);
		cout << "\nYour input expression is:\n\n" << expression->ToString() << "\n\n";

		polishNotation = expression->PolishNotation();
		delete expression;
		cout << "Expression converted to Polish Notation:\n\n" << polishNotation->ToString() << "\n\n";

		double result = polishNotation->GetResult();
		delete polishNotation;
		cout << "The result of an expression is ";
		if (result != INFINITY) cout << fixed << result << endl;
		else cout << "undefined (function has critical argument)" << endl;
	}
	catch (exception& error)
	{
		delete expression;
		cout << "\n[!] Error caught: " << error.what() << endl;
	}

	return 0;
}