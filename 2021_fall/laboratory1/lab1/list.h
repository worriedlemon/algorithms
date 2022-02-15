#ifndef ListElement_H
#define ListElement_H
#include <iostream>
using namespace std;
#include <stdexcept>
using namespace std;

// Double-linked List class
class List
{
private:
	struct ListElement
	{
		ListElement* previousElement;
		unsigned element;
		ListElement* nextElement;

		ListElement(unsigned element = 0, ListElement* previousElement = NULL, ListElement* nextElement = NULL)
		{
			this->previousElement = previousElement;
			this->element = element;
			this->nextElement = nextElement;
		}

		~ListElement(){ }
	};
	
	ListElement* head;
	ListElement* tail;

public:
	// Default constructor, creates an empty list
	List() : head(NULL), tail(NULL) { }

	// Destructor
	~List()
	{
		try
		{
			clear();
		}
		catch (logic_error error) {}
	}
	
	// Function, which pushes an element with $value to the end of the list
	void push_back(unsigned value = 0)
	{
		if (isEmpty())
		{
			head = new ListElement(value);
			tail = head;
		}
		else
		{
			tail->nextElement = new ListElement(value, tail);
			tail = tail->nextElement;
		}
		return;
	}

	// Function, which pushes an element with $value to the beginning of the list
	void push_front(unsigned value = 0)
	{
		if (isEmpty())
		{
			head = new ListElement(value);
			tail = head;
		}
		else
		{
			head->previousElement = new ListElement(value, NULL, head);
			head = head->previousElement;
		}
		return;
	}

	// Function, which removes an element from the end of the list
	void pop_back()
	{
		if (isEmpty()) throw logic_error("Empty list deletion");
		else
		{
			if (head != tail)
			{
				tail = tail->previousElement;
				delete tail->nextElement;
				tail->nextElement = NULL;
			}
			else
			{
				delete head;
				head = NULL;
			}
		}
		return;
	}

	// Function, which removes an element from the beginning of the list
	void pop_front()
	{
		if (isEmpty()) throw logic_error("Empty list deletion");
		else
		{
			if (head != tail)
			{
				head = head->nextElement;
				delete head->previousElement;
				head->previousElement = NULL;
			}
			else
			{
			delete head;
			head = NULL;
			}
		}
		return;
	}

	// Function for checking for any elements inside the list, if there in none - returns $true
	bool isEmpty()
	{
		return (head == NULL ? true : false);
	}

	// Function, which returns the length of the list in elements
	size_t get_size()
	{
		if (!isEmpty())
		{
			ListElement* currentElement = head;
			size_t currentElementIndex = 0;
			while (currentElement->nextElement != NULL)
			{
				currentElementIndex++;
				currentElement = currentElement->nextElement;
			}
			return currentElementIndex + 1;
		}
		return 0;
	}

	// Function, which inserts the element with $value on the $index's place in the list
	void insert(unsigned value, size_t index)
	{
		const size_t listSize = get_size();
		if (index > listSize) throw out_of_range("List index out of range");
		else if (index == listSize) push_back(value);
		else if (index == 0) push_front(value);
		else
		{
			ListElement* currentElement = head;
			size_t currentElementIndex = 0;
			while (currentElementIndex != index)
			{
				currentElementIndex++;
				currentElement = currentElement->nextElement;
			}
			ListElement* insertedElement = new ListElement(value, currentElement->previousElement, currentElement);
			currentElement->previousElement->nextElement = insertedElement;
			currentElement->previousElement = insertedElement;
		}
		return;
	}

	// Function, which returns the value of the $index's element
	unsigned at(size_t index)
	{
		if (index >= get_size())
		{
			throw out_of_range("List index out of range");
			return (unsigned)NAN;
		}
		else
		{
			ListElement* currentElement = head;
			size_t currentElementIndex = 0;
			while (currentElementIndex != index)
			{
				currentElementIndex++;
				currentElement = currentElement->nextElement;
			}
			return currentElement->element;
		}
	}

	// Function, which changes the value of the $index's element to $value
	void set(unsigned value, size_t index)
	{
		if (index >= get_size()) throw out_of_range("List index out of range");
		else
		{
			ListElement* currentElement = head;
			size_t currentElementIndex = 0;
			while (currentElementIndex != index)
			{
				currentElementIndex++;
				currentElement = currentElement->nextElement;
			}
			currentElement->element = value;
		}
		return;
	}

	// Function, which removes the $index's element
	void remove(size_t index)
	{
		const size_t listSize = get_size();
		if (index >= listSize) throw out_of_range("List index out of range");
		else if (index == listSize - 1) pop_back();
		else if (index == 0) pop_front();
		else
		{
			ListElement* currentElement = head;
			size_t currentElementIndex = 0;
			while (currentElementIndex != index)
			{
				currentElementIndex++;
				currentElement = currentElement->nextElement;
			}
			currentElement->previousElement->nextElement = currentElement->nextElement;
			currentElement->nextElement->previousElement = currentElement->previousElement;
			delete currentElement;
		}
		return;
	}

	// Function, which removes all elements
	void clear()
	{
		if (isEmpty()) throw logic_error("Clearing an empty list");
		else
		{
			while (head->nextElement != NULL)
			{
				head = head->nextElement;
				delete head->previousElement;
			}
			delete head;
			head = NULL;
		}
		return;
	}

	// Overloaded operator for printing the $outputList out
	friend ostream& operator<<(ostream& output, List & outputList)
	{
		ListElement* currentElement = outputList.head;
		output << "[";
		while (currentElement != NULL)
		{
			output << currentElement->element << (currentElement->nextElement == NULL ? "]" : ", ");
			currentElement = currentElement->nextElement;
		}
		if (outputList.isEmpty()) output << "] - list is empty";
		return output;
	}

	// Function, which pushes an other list to the beginning of an original list
	void push_front(List& otherList)
	{
		if (head == otherList.head) throw invalid_argument("Pushing the same list");
		else if (isEmpty() || otherList.isEmpty()) throw logic_error("Pushing an empty list");
		else
		{
			ListElement* currentElement = otherList.tail;
			while (currentElement != NULL)
			{
				push_front(currentElement->element);
				currentElement = currentElement->previousElement;
			}
		}
	}
};
#endif