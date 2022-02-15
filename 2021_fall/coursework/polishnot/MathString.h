#ifndef MathString_h
#define MathString_h
#include <iostream>
#include <cstring>
using namespace std;
#include <cmath>
class MathExpression
{
	class MathString
	{
		string expression;
		size_t priority;

	public:
		MathString(string expression = "")
		{
			this->expression = expression;
			priority = 0;
		}

		~MathString() {}

		friend ostream& operator<<(ostream& output, MathString& string)
		{
			output << string.expression;
		}

		friend istream& operator>>(istream& output, MathString& string)
		{
			output >> string.expression;
		}
	};

	MathString* parent;
	MathString* left;
	MathString* right;
	string _operator;
};

class IMathExpression
{
public:
	virtual double GetValue() = 0;
};
#endif
