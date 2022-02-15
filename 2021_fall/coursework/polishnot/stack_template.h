#ifndef Stack_h
#define Stack_h

template <typename T>
class Stack // Stack structure of T
{
	// Stack Element
	class StackElement
	{
	public:
		T* data;
		StackElement* next;

		StackElement(T* data, StackElement* next)
			: data(data), next(next) {}
	};

public:
	StackElement* top;

	Stack() : top(nullptr) {}
	~Stack()
	{
		while (top != nullptr) Pop();
	}

	// Push to the top
	void Push(T* element)
	{
		StackElement* temp = new StackElement(element, top);
		top = temp;
		return;
	}

	// Pop out of the top
	void Pop()
	{
		if (top == nullptr) throw;
		StackElement* temp = top->next;
		delete top;
		top = temp;
		return;
	}
};
#endif
