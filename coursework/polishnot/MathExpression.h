#ifndef MathExpression_h
#define MathExpression_h
#include <string>
#include <cmath>
#include <stdexcept>
#include "stack_template.h"
using namespace std;

const size_t functionCount = 9, constCount = 3;
const string possibleFunc[functionCount] = { "sin", "cos", "tg", "ctg", "sqrt", "ln", "log", "sec", "cosec"};
const string possibleConst[constCount] = { "pi", "e", "phi" };
const double possibleDoubleConst[constCount] = { 3.141592653589793, 2.718281828459045, ((sqrt(5) + 1) / 2) };

// Function for concatenating text with number (used for throwing exceptions with certain string index)
char* Concatenate(const char* str1, size_t number, const char* str2 = "");

enum class MathType
{
	Number,
	Operator,
	Parenthesis,
	Function,
	Undefined
};

class MathElement
{
public:
	MathType type;
	char priority;
	string data;

	MathElement(string data = "", MathType type = MathType::Undefined, char priority = 0)
		: data(data), type(type), priority(priority){}
	~MathElement() {}
};

class MathExpression
{
	class ExpressionNode
	{
	public:
		MathElement* data;
		ExpressionNode* previous;
		ExpressionNode* next;

		ExpressionNode(MathElement* data, ExpressionNode* previous, ExpressionNode* next)
			: data(data), previous(previous), next(next) {}
		~ExpressionNode() { delete data; }
	};

	// Function for defining the function, if it exists
	bool CheckFunction(MathType& type, string& str)
	{
		for (size_t i = 0; i < functionCount; i++)
		{
			if (str == possibleFunc[i])
			{
				type = MathType::Function;
				return true;
			}
		}
		for (size_t i = 0; i < constCount; i++)
		{
			if (str == possibleConst[i])
			{
				type = MathType::Number;
				return true;
			}
		}
		return false;
	}

	// Function for comparing two doubles
	bool AreEqual(double left, double right)
	{
		// epsilon value
		double eps = 1e-6;
		if (left - right < eps && left - right > -eps) return true;
		else return false;
	}

	// Function for calculating functions for string
	double CalculateFunction(string& func, double* value)
	{
		double result, realValue = fmod(*value, 2 * possibleDoubleConst[0]); // values for result and for periodic functions
		
		// calculate the value using certain functions
		if (func == "sin") result = sin(*value);
		else if (func == "cos") result = cos(*value);
		else if (func == "tg")
		{
			// check for critical values
			if (AreEqual(realValue, possibleDoubleConst[0] / 2) || AreEqual(realValue, 3 * possibleDoubleConst[0] / 2))
				return INFINITY; // these values are undefined, return computer infinity
			result = tan(*value);
		}
		else if (func == "ctg")
		{
			if (AreEqual(realValue, 0) || AreEqual(realValue, possibleDoubleConst[0]))
				return INFINITY;
			result = 1 / tan(*value);
		}
		else if (func == "sqrt")
		{
			if (*value < 0) return INFINITY;
			result = sqrt(*value);
		}
		else if (func == "log")
		{
			if (*value <= 0) return INFINITY;
			result = log(*value);
		}
		else if (func == "ln")
		{
			if (*value <= 0) return INFINITY;
			result = ln(*value);
		}
		else if (func == "sec")
		{
			if (AreEqual(realValue, 0) || AreEqual(realValue, possibleDoubleConst[0]))
				return INFINITY;
			result = 1 / sin(*value);
		}
		else if (func == "cosec")
		{
			if (AreEqual(realValue, possibleDoubleConst[0] / 2) || AreEqual(realValue, 3 * possibleDoubleConst[0] / 2))
				return INFINITY;
			result = 1 / cos(*value);
		}
		else if (func == "\'-\'") result = -(*value);
		else result = DBL_EPSILON;
		return result;
	}

	// Function for searching for unary minuses
	void UnaryMinusProcessing()
	{
		ExpressionNode* current = head->next;
		if (head->data->type == MathType::Operator && head->data->data == "-")
		{
			head->data->data = "\'-\'";
			head->data->type = MathType::Function;
		}
		while (current != nullptr)
		{
			if (current->data->type == MathType::Operator && current->data->data == "-" && current->previous->data->data == "(")
			{
				current->data->data = "\'-\'";
				current->data->type = MathType::Function;
			}
			current = current->next;
		}
		return;
	}

	// Function for converting string into double
	double* ToDouble(string& str)
	{
		for (char i = 0; i < constCount; i++)
			if (str == possibleConst[i]) return new double(possibleDoubleConst[i]);

		double* result = new double(0);
		bool point = false;
		size_t power = 1;
		const size_t size = str.length();
		for (size_t i = 0; i < size; i++)
		{
			if (str[i] == '.') point = true;
			else
			{
				if (point)
				{
					power *= 10;
					*result += ((int)str[i] - 48)/power;
				}
				else *result = (*result) * 10 + (int)str[i] - 48;
			}
		}
		return result;
	}

	ExpressionNode* head;
	ExpressionNode* tail;

public:
	MathExpression(ExpressionNode* head = nullptr, ExpressionNode* tail = nullptr)
		: head(head), tail(tail) {}
	~MathExpression()
	{
		while (head != nullptr)
		{
			ExpressionNode* temp = head->next;
			delete head;
			head = temp;
		}
		tail = nullptr;
	}

	// Method for converting math expression as string into MathExpression list class
	void FromString(string& mathString)
	{
		const size_t size = mathString.length(); // how much symbols in mathString
		if (!size) throw length_error("Input string is empty"); //check if string isn't null
		size_t index = 0; // current index
		int parenthesis = 0; // parenthesis counter (increment for opening, decrement for closing) - should be 0 by the end of expression; if it is negative, then expression is wrong anyways
		string buffer = ""; // buffer string, contains current math type
		MathType type = MathType::Undefined, prevType = MathType::Undefined; // math types for separating different symbols into categories
		bool typeChanged = false, point = false; // typeChange define detection of different math types
		char priority = 0; // priority for an operator

		while (index < size)
		{
			if (mathString[index] > ' ' || mathString[index] < '\0') // skipping the control characters
			{
				// defining numbers
				if ((mathString[index] >= '0' && mathString[index] <= '9') || mathString[index] == '.' || mathString[index] == ',')
				{
					// check for point
					if (mathString[index] == '.' || mathString[index] == ',')
					{
						// the second point is erroneous
						if (point) throw logic_error(Concatenate("Second point in real number at position ", index));
						else
						{
							point = true; // set the flag dot for the only point in true
							mathString[index] = '.';
						}
					}
					type = MathType::Number;
				}
				// defining operators
				else if (mathString[index] == '+' || mathString[index] == '-' || mathString[index] == '*' || mathString[index] == '/' || mathString[index] == '^')
				{
					// check if first is minus, if else - expression is wrong
					if (index == 0 && mathString[index] != '-')
						throw invalid_argument("Unexpected operator at position 0");
					// check for double operators
					else if (index != 0 && prevType == MathType::Operator)
						throw logic_error(Concatenate("Ambiguous operator definition at position ", index));

					const char _operator = mathString[index]; // operator priority definition, the greater the value - the 'firster' the action
					switch (_operator)
					{
					case '+':
						priority = 1;
						break;
					case '-':
						priority = 1;
						break;
					case '*':
						priority = 2;
						break;
					case '/':
						priority = 2;
						break;
					case '^':
						priority = 3;
					}
					type = MathType::Operator;
				}
				// defining parenthesis
				else if (mathString[index] == '(' || mathString[index] == ')')
				{
					mathString[index] == '(' ? parenthesis++ : parenthesis--; // parenthesis counter
					// check for negative value - if it is, then expression is wrong
					if (parenthesis < 0) throw logic_error(Concatenate("Closing parenthesis before an opening one at position ", index));
					
					if (index != 0)
					{
						// check for different double parenthesis )( and () and missing expressions
						if ((mathString[index-1] == ')' && mathString[index] == '(') || (prevType == MathType::Number && mathString[index] == '('))
							throw logic_error(Concatenate("Missing operator at position ", index));
						else if ((mathString[index - 1] == '(' && mathString[index] == ')') || ((prevType == MathType::Operator && mathString[index] == ')')))
							throw logic_error(Concatenate("Missing expression at position ", index));
					}

					type = MathType::Parenthesis;
				}
				// defining functions or constants, which are represented by the text
				else
				{
					if (prevType == MathType::Number) throw logic_error(Concatenate("Missing operator at position ", index));
					type = MathType::Undefined;
				}

				typeChanged = (index == 0 ? false : (type != prevType)); // check if type changed
				if (index != 0 && (typeChanged || prevType == MathType::Operator || prevType == MathType::Parenthesis))
				{
					if (prevType == MathType::Undefined && !CheckFunction(prevType, buffer)) // if type is undefined, then check it
						throw invalid_argument(Concatenate("Undefined function or constant at position ", index-1));
					if (prevType == MathType::Function && mathString[index] == ')')
						throw logic_error(Concatenate("Missing expression at position ", index));
					if (prevType == MathType::Number && type == prevType)
						throw logic_error(Concatenate("Missing operator at position ", index));

					char tempPriority = (prevType == MathType::Operator ? priority : 0); // priority for operator
					if (tail != nullptr)
					{
						tail->next = new ExpressionNode(new MathElement(buffer, prevType, tempPriority), tail, nullptr);
						tail = tail->next;
					}
					else
					{
						tail = new ExpressionNode(new MathElement(buffer, prevType, tempPriority), nullptr, nullptr);
						head = tail;
					}

					point = false;
					buffer.clear();
				}
				prevType = type;
				if (buffer == "" && point) buffer.push_back('0'); // the first dot is deprecated, though it can be converted as '0.'
				buffer.push_back(mathString[index]);
			}
			index++;
		}
		if (type == MathType::Undefined && !CheckFunction(type, buffer))
			throw invalid_argument(Concatenate("Undefined constant at position ", size - 1));
		if (type == MathType::Operator || type == MathType::Function || parenthesis)
			throw logic_error(Concatenate("Unexpected end of expression (position: ", size - 1, ")"));
		if (tail != nullptr)
		{
			tail->next = new ExpressionNode(new MathElement(buffer, prevType, 0), tail, nullptr);
			tail = tail->next;
		}
		else
		{
			tail = new ExpressionNode(new MathElement(buffer, prevType, 0), nullptr, nullptr);
			head = tail;
		}
		buffer.clear();

		UnaryMinusProcessing(); // search for unary minuses
		return;
	}

	// Method for converting MathExpression into Polish Notation MathExpression
	MathExpression* PolishNotation()
	{
		MathExpression* newMathExpression = new MathExpression();
		ExpressionNode* current = tail;
		Stack<ExpressionNode> stack;
		while (current != nullptr)
		{
			if (current->data->type == MathType::Operator)
			{
				if (stack.top != nullptr)
				{
					if (stack.top->data->data->priority > current->data->priority)
					{
						newMathExpression->head->previous = new ExpressionNode(new MathElement(stack.top->data->data->data, stack.top->data->data->type, stack.top->data->data->priority), nullptr, newMathExpression->head);
						newMathExpression->head = newMathExpression->head->previous;
						stack.Pop();
						stack.Push(current);
					}
					else stack.Push(current);
				}
				else stack.Push(current);
			}
			else if (current->data->type == MathType::Parenthesis)
			{
				if (current->data->data == ")") stack.Push(current);
				else
				{
					while (stack.top->data->data->data != ")")
					{
						newMathExpression->head->previous = new ExpressionNode(new MathElement(stack.top->data->data->data, stack.top->data->data->type, stack.top->data->data->priority), nullptr, newMathExpression->head);
						newMathExpression->head = newMathExpression->head->previous;
						stack.Pop();
					}
					stack.Pop();
				}
			}
			else
			{
				if (newMathExpression->head == nullptr)
				{
					newMathExpression->head = new ExpressionNode(new MathElement(current->data->data, current->data->type), nullptr, nullptr);
					newMathExpression->tail = newMathExpression->head;
				}
				else
				{
					newMathExpression->head->previous = new ExpressionNode(new MathElement(current->data->data, current->data->type), nullptr, newMathExpression->head);
					newMathExpression->head = newMathExpression->head->previous;
				}
			}
			current = current->previous;
		}
		while (stack.top != nullptr)
		{
			newMathExpression->head->previous = new ExpressionNode(new MathElement(stack.top->data->data->data, stack.top->data->data->type, stack.top->data->data->priority), nullptr, newMathExpression->head);
			newMathExpression->head = newMathExpression->head->previous;
			stack.Pop();
		}
		return newMathExpression;
	}

	// Function for calculating result based on a polish notation
	double GetResult()
	{
		Stack<ExpressionNode> _operator;
		Stack<double> leftOperand, rightOperand;
		ExpressionNode* current = head;
		bool rightIsAvailable = false;
		while (current != nullptr)
		{
			if (current->data->type == MathType::Operator || current->data->type == MathType::Function)
			{
				_operator.Push(current);
				rightIsAvailable = false;
			}
			else
			{
				if (!rightIsAvailable)
				{
					leftOperand.Push(ToDouble(current->data->data));
					rightIsAvailable = true;
				}
				else
				{
					rightOperand.Push(ToDouble(current->data->data));
					while (rightOperand.top != nullptr)
					{
						double* value = new double();
						if (_operator.top->data->data->type == MathType::Operator)
						{
							if (leftOperand.top == nullptr) break;
							const char oper = _operator.top->data->data->data[0];
							switch (oper)
							{
							case '+':
								*value = *leftOperand.top->data + *rightOperand.top->data;
								break;
							case '-':
								*value = *leftOperand.top->data - *rightOperand.top->data;
								break;
							case '*':
								*value = *leftOperand.top->data * *rightOperand.top->data;
								break;
							case '/':
								*value = *leftOperand.top->data / *rightOperand.top->data;
								break;
							case '^':
								*value = pow(*leftOperand.top->data, *rightOperand.top->data);
							}
							leftOperand.Pop();
							rightOperand.Pop();
						}
						else
						{
							if (rightOperand.top != nullptr)
							{
								*value = CalculateFunction(_operator.top->data->data->data, rightOperand.top->data);
								rightOperand.Pop();
							}
							else
							{
								*value = CalculateFunction(_operator.top->data->data->data, leftOperand.top->data);
								leftOperand.Pop();
							}
							if (*value == INFINITY) return *value;
						}
						if (leftOperand.top == nullptr) leftOperand.Push(value);
						else rightOperand.Push(value);
						_operator.Pop();
					}
				}
			}
			current = current->next;
		}
		while (_operator.top != nullptr)
		{
			double *value = new double(CalculateFunction(_operator.top->data->data->data, leftOperand.top->data));
			leftOperand.Pop();
			leftOperand.Push(value);
			_operator.Pop();
		}
		return *leftOperand.top->data;
	}

	// MathExpression output override
	string ToString()
	{
		ExpressionNode* current = head;
		string result = "";
		while (current != nullptr)
		{
			result.append(current->data->data);
			if (current->next != nullptr) result.push_back(' ');
			current = current->next;
		}
		return result;
	}
};
#endif
