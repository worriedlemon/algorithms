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

		~ListElement()
		{
			cout << "Deleting list element (" << element << ")\n";
		}
	};
	
	ListElement* head;
	ListElement* currentElement;
	
	// Function that reset the current list element to the start
	void Reset()
	{
		currentElement = head;
		return;
	}

public:
	// Default constructor, creates an empty list
	List() : head(NULL), currentElement(NULL) { }

	// Destructor
	~List()
	{
		if (head != NULL)
		{
			Reset();
			cout << "Initializing list deletion...\n";
			ListElement* temporaryElement;
			while (currentElement != NULL)
			{
				temporaryElement = currentElement->nextElement;
				delete currentElement;
				currentElement = temporaryElement;
			}
		}
		else cout << "List is already empty.\n";
	}
	
	// Function, which pushes an element with $value to the end of the ListElement
	void push_back(unsigned value = 0)
	{
		Reset();
		if (isEmpty()) head = new ListElement(value);
		else
		{
			while (currentElement->nextElement != NULL)
				currentElement = currentElement->nextElement;
			currentElement->nextElement = new ListElement(value, currentElement);
		}
		return;
	}

	// Function, which pushes an element with $value to the beginning of the ListElement
	void push_front(unsigned value = 0)
	{
		if (isEmpty()) head = new ListElement(value);
		else
		{
			head->previousElement = new ListElement(value, NULL, head);
			head = head->previousElement;
		}
		return;
	}

	// Function, which removes an element from the end of the ListElement
	void pop_back()
	{
		if (isEmpty()) throw logic_error("Empty list deletion");
		else
		{
			while (currentElement->nextElement != NULL)
				currentElement = currentElement->nextElement;
			currentElement = currentElement->previousElement;
			delete currentElement->nextElement;
			currentElement->nextElement = NULL;
		}
		return;
	}

	// Function, which removes an element from the beginning of the ListElement
	void pop_front()
	{
		if (isEmpty()) throw logic_error("Empty list deletion");
		else
		{
			head = head->nextElement;
			delete head->previousElement;
			head->previousElement = NULL;
		}
		return;
	}

	// Function for checking for any elements inside the ListElement, if there in none - returns $true
	bool isEmpty()
	{
		return (head == NULL ? true : false);
	}

	// Function, which returns the length of the ListElement in elements
	size_t get_size()
	{
		if (!isEmpty())
		{
			Reset();
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

	// Function, which inserts the element with $value on the $index's place in the ListElement
	void insert(unsigned value, size_t index)
	{
		const size_t listSize = get_size();
		if (index > listSize) throw out_of_range("List index out of range");
		else if (index == listSize) push_back(value);
		else if (index == 0) push_front(value);
		else
		{
			Reset();
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
			Reset();
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
			Reset();
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
			Reset();
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
			Reset();
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

	// Overloaded operator for printing the $outputListElement out
	friend ostream& operator<<(ostream& output, List & outputList)
	{
		outputList.Reset();
		output << "[";
		while (outputList.currentElement != NULL)
		{
			output << outputList.currentElement->element << (outputList.currentElement->nextElement == NULL ? "]" : ", ");
			outputList.currentElement = outputList.currentElement->nextElement;
		}
		if (outputList.isEmpty()) output << "] - list is empty";
		return output;
	}

	// Function, which pushes an other ListElement to the beginning of a start ListElement
	void push_front(List& otherList)
	{
		Reset();
		otherList.Reset();
		while (otherList.currentElement->nextElement != NULL)
			otherList.currentElement = otherList.currentElement->nextElement;
		otherList.currentElement->nextElement = head;
		head->previousElement = otherList.currentElement;
		return;
	}
};
#endif