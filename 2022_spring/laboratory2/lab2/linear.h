#ifndef LINEAR_STRUCT
#define LINEAR_STRUCT
#include <iostream>
using namespace std;

template <class T>
class List
{
protected:
	struct ListElement
	{
		ListElement* previous, * next;
		T data;

		ListElement(T& data, ListElement* next = nullptr, ListElement* previous = nullptr) : data(data), previous(previous), next(next) {}
		~ListElement() {}
	};

public:
	ListElement* head, * tail;

	List() : head(nullptr), tail(nullptr) {}

	List(const size_t size, T* arr) : head(nullptr), tail(nullptr)
	{
		for (size_t i = 0; i < size; i++) this->PushBack(arr[i]);
	}

	List(List<T>& ref) : head(nullptr), tail(nullptr)
	{
		const size_t size = ref.GetSize();
		for (size_t i = 0; i < size; i++)
		{
			T newElem = ref.GetData(i);
			this->PushBack(newElem);
		}
	}

	template <typename... Args> List(Args... list) : head(nullptr), tail(nullptr) { this->PushBack(list...); }

	template <typename... Args>
	void PushBack(T first, Args&... rest)
	{
		this->PushBack(first);
		this->PushBack(rest...);
	}

	~List()
	{
		if (head != nullptr) Clear();
	}

	List<T>& operator+(List<T>& l)
	{
		List<T>* newList = new List<T>();
		for (size_t i = 0; i < GetSize(); i++) newList->PushBack(GetData(i));
		for (size_t i = 0; i < l.GetSize(); i++) newList->PushBack(l.GetData(i));
		return *newList;
	}

	void operator+=(List<T>& l)
	{
		*this = *this + l;
	}

	friend bool operator==(List<T>& list1, List<T>& list2)
	{
		ListElement* current1 = list1.head;
		ListElement* current2 = list2.head;
		while (current1 != nullptr)
		{
			if (current2 != nullptr)
			{
				if (current1->data != current2->data) return false;
			}
			else return false;
			current1 = current1->next;
			current2 = current2->next;
		}
		if (current2 != nullptr) return false;
		return true;
	}

	friend ostream& operator<<(ostream& stream, List<T>& list)
	{
		ListElement* current = list.head;
		stream << "[";
		while (current != nullptr)
		{
			stream << current->data;
			if (current->next != nullptr) stream << " ";
			current = current->next;
		}
		stream << "]";
		return stream;
	}

	void Clear()
	{
		if (head == nullptr) throw logic_error("List is already empty");
		while (head != nullptr)
		{
			if (head->next == nullptr) break;
			head = head->next;
			delete head->previous;
		}
		delete head;
	}

	size_t GetSize()
	{
		int size = 0;
		ListElement* current = head;
		while (current != nullptr)
		{
			size++;
			current = current->next;
		}
		return size;
	}

	virtual void PushFront(T element)
	{
		ListElement* newElement = new ListElement(element, head);
		if (head == nullptr)
		{
			head = newElement;
			tail = head;
		}
		else
		{
			head->previous = newElement;
			head = head->previous;
		}
		return;
	}

	virtual void PushBack(T element)
	{
		ListElement* newElement = new ListElement(element, nullptr, tail);
		if (tail == nullptr)
		{
			tail = newElement;
			head = tail;
		}
		else
		{
			tail->next = newElement;
			tail = tail->next;
		}
		return;
	}

	virtual void Push(T element)
	{
		throw logic_error("Push is undefinable, use PushFront/PushBack/PushIndex");
	}

	virtual void PushIndex(int index, T element)
	{
		const int lastIndex = GetSize() - 1;
		if (index == 0) PushFront(element);
		else if (index == lastIndex + 1) PushBack(element);
		else if (index > lastIndex + 1 || index < 0) throw out_of_range("Stated index is invalid");
		else
		{
			int currentIndex = 1;
			ListElement* current = head->next;
			while (currentIndex != index)
			{
				current = current->next;
				currentIndex++;
			}
			ListElement* newElement = new ListElement(element, current, current->previous);
			current->previous->next = newElement;
			current->previous = newElement;
		}
	}

	virtual void PopFront()
	{
		if (head == nullptr) throw logic_error("List is already empty");
		if (head->next == nullptr)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			head = head->next;
			delete head->previous;
			head->previous = nullptr;
		}
		return;
	}

	virtual void PopBack()
	{
		if (tail == nullptr) throw logic_error("List is already empty");
		if (tail->previous == nullptr)
		{
			delete tail;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			tail = tail->previous;
			delete tail->next;
			tail->next = nullptr;
		}
		return;
	}

	virtual void PopIndex(int index)
	{
		const int lastIndex = GetSize() - 1;
		if (index == 0) PopFront();
		else if (index == lastIndex) PopBack();
		else if (index > lastIndex || index < 0) throw out_of_range("Stated index is invalid");
		else
		{
			int currentIndex = 1;
			ListElement* current = head->next;
			while (currentIndex != index)
			{
				current = current->next;
				currentIndex++;
			}
			ListElement* next = current->next, * previous = current->previous;
			delete current;
			next->previous = previous;
			previous->next = next;
		}
	}

	virtual void Pop()
	{
		throw logic_error("Push is undefinable, use PopFront/PopBack/PopIndex");
	}

	T& GetData(size_t index = 0)
	{
		ListElement* current = head;
		size_t i = 0;
		while (current != nullptr)
		{
			if (i == index) return current->data;
			i++;
			current = current->next;
		}
		throw out_of_range("Index is incorrect");
	}

	inline void PrintData() { cout << *this; }
};

template <typename T>
class Queue : public List<T>
{
public:
	List<T>::Clear;

	List<T>::GetSize;

	void PushFront(T element) override
	{
		throw logic_error("Queue structure has no access to execute PushFront");
	}

	List<T>::PushBack;

	void PushIndex(int index, T element) override
	{
		if (index == GetSize()) PushBack(element);
		else throw logic_error("In queue structure pushing index can only be the last one");
		return;
	}

	void Push(T element) override
	{
		PushBack(element);
		return;
	}

	List<T>::PopFront;

	void PopBack() override
	{
		throw logic_error("Queue structure has no access to execute PopBack");
	}

	void PopIndex(int index) override
	{
		if (index == 0) PopFront();
		else throw logic_error("In queue structure popping index can only be zero");
		return;
	}

	void Pop() override
	{
		PopFront();
		return;
	}

	List<T>::GetData;

	List<T>::PrintData;
};

template <typename T>
class Stack : public List<T>
{
public:
	List<T>::Clear;

	List<T>::GetSize;

	List<T>::PushFront;

	void PushBack(T element) override
	{
		throw logic_error("Stack structure has no access to execute PushFront");
	}

	void PushIndex(int index, T element) override
	{
		if (index == 0) PushFront(element);
		else throw logic_error("In stack structure pushing index can only be zero");
		return;
	}

	void Push(T element) override
	{
		PushFront(element);
		return;
	}

	List<T>::PopFront;

	void PopBack() override
	{
		throw logic_error("Stack structure has no access to execute PopBack");
	}

	void PopIndex(int index) override
	{
		if (index == 0) PopFront();
		else throw logic_error("In stack structure popping index can only be zero");
		return;
	}

	void Pop() override
	{
		PopFront();
		return;
	}

	List<T>::GetData;

	List<T>::PrintData;
};
#endif // LINEAR_STRUCT