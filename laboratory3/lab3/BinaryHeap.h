#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include <iostream>
using namespace std;
#include <stdexcept>
using namespace std;
#include "Iterator.h"

// Heap Node structure
class Node
{
public:
	Node* parent;
	Node* left;
	Node* right;
	int element;

	Node(int element = 0, Node* parent = nullptr)
		: element(element), parent(parent), left(nullptr), right(nullptr) {}

	~Node()
	{
		if (left != nullptr) delete left;
		if (right != nullptr) delete right;
	}
};

// Element of a linear structure (stack or queue)
class LinearStrElement
{
public:
	Node* node;
	LinearStrElement* next;

	LinearStrElement(Node* current = nullptr, LinearStrElement* prev = nullptr)
		: node(current), next(nullptr) {}

	~LinearStrElement() {}
};

// Stack structure (First In - Last Out)
class Stack
{
public:
	LinearStrElement* top;

	Stack() : top(nullptr) {}
	~Stack()
	{
		while (top != nullptr) Pop();
	}

	void Push(Node* node)
	{
		LinearStrElement* element = new LinearStrElement(node);
		element->next = top;
		top = element;
		return;
	}

	void Pop()
	{
		if (top == nullptr) throw out_of_range("Stack is empty");
		LinearStrElement* next = top->next;
		delete top;
		top = next;
		return;
	}
};

// Queue structure (First In - First Out)
class Queue
{
public:
	LinearStrElement* first;
	LinearStrElement* last;

	Queue() : first(nullptr), last(nullptr) {}
	~Queue()
	{
		while (first != nullptr) Pop();
		last = nullptr;
	}

	void Push(Node* node)
	{
		if (last != nullptr)
		{
			last->next = new LinearStrElement(node, last);
			last = last->next;
		}
		else
		{
			first = new LinearStrElement(node);
			last = first;
		}
		return;
	}

	void Pop()
	{
		if (first == nullptr) throw out_of_range("Queue is empty");
		LinearStrElement* next = first->next;
		delete first;
		first = next;
		return;
	}
};

// Maximum Binary Heap class
class BinaryHeap
{
	Node* root;
	size_t size;
	size_t height;

	// Function for obtaining the size of a complete full heap defined from height
	size_t GetFullSize(size_t heapHeight)
	{
		size_t fullSize = 1;
		for (size_t i = 0; i < heapHeight; i++) fullSize += fullSize + 1;
		return fullSize;
	}

	// Function for sifting the heap up to the root
	void siftUp(Node* startNode);

	// Function for sifting the heap down to the leaves
	void siftDown(Node* startNode);

	// Recovery of heap properties
	void Heapify(bool up, Node* startNode) { up ? siftUp(startNode) : siftDown(startNode); }

public:
	// Constructor with an empty heap
	BinaryHeap() : root(nullptr), height(0), size(0) {}

	// Destructor
	~BinaryHeap()
	{
		if (root) delete root;
	}

	// FUNCTIONS

	// Function which searches an $element in the heap
	bool contains(int element)
	{
		HeapBreadthIterator iterator(root);
		while (iterator.has_next())
		{
			if (iterator.next() == element) return true;
		}
		return false;
	}

	void insert(int element)
	{
		if (size == 0) root = new Node(element);
		else
		{
			Node* current = root;
			const size_t desiredIndex = size + 1;
			size_t iterations = (GetFullSize(height) > size ? height - 1 : height);
			for (size_t i = 0; i < iterations; i++)
			{
				if ((desiredIndex >> (iterations - i)) % 2 == 0) current = current->left;
				else current = current->right;
			}
			if (desiredIndex % 2 == 0)
			{
				current->left = new Node(element, current);
				current = current->left;
			}
			else
			{
				current->right = new Node(element, current);
				current = current->right;
			}
			if (GetFullSize(height) == size) height++;
			Heapify(true, current);
		}
		size++;
		return;
	}

	void remove(int element)
	{
		HeapBreadthIterator iterator(root);
		while (iterator.has_next())
		{
			if (iterator.next() == element)
			{
				if (size == 1)
				{
					delete root;
					root = nullptr;
				}
				else
				{
					Node* current = root;
					bool condition, last = false;
					size_t iterations = (GetFullSize(height) > size ? height - 1 : height);
					for (size_t i = 0; i < iterations; i++)
					{
						if ((size >> (iterations - i)) % 2 == 0) current = current->left;
						else current = current->right;
					}
					if (size % 2 == 0)
					{
						condition = (iterator.previous->element <= current->left->element);
						iterator.previous->element = current->left->element;
						if (current->left == iterator.previous) last = true;
						delete current->left;
						current->left = nullptr;
					}
					else
					{
						condition = (iterator.previous->element <= current->right->element);
						iterator.previous->element = current->right->element;
						if (current->right == iterator.previous) last = true;
						delete current->right;
						current->right = nullptr;
					}
					if (GetFullSize(height - 1) == size - 1) height--;
					if (!last) Heapify(condition, iterator.previous);	
				}
				size--;
				return;
			}
		}
		throw invalid_argument("No such element");
	}

	// ITERATOR INTERFACES
	
	// Iterator interface inheritance for binary heap depth traversal
	class HeapDepthIterator : public IIterator
	{
		Node* current;
		Stack* stackOfNodes;

	public:
		Node* previous;

		HeapDepthIterator(Node* root) : current(root), stackOfNodes(new Stack), previous(nullptr) {}
		~HeapDepthIterator() { delete stackOfNodes; }

		// Get the next node element
		int next() override;

		// Check if Heap has the next element
		bool has_next() override { return current != nullptr; }
	};

	// Iterator interface inheritance for binary heap breadth traversal
	class HeapBreadthIterator : public IIterator
	{
		Node* current;
		Queue* queueOfNodes;

	public:
		Node* previous;

		HeapBreadthIterator(Node* root) : current(root), queueOfNodes(new Queue), previous(nullptr) {}
		~HeapBreadthIterator() { delete queueOfNodes; }

		// Get the next node element
		int next() override;

		// Check if Heap has the next element
		bool has_next() override { return current != nullptr; }
	};

	// Function for creating a depth-first-traversal iterator
	IIterator* create_dft_iterator()
	{
		return new HeapDepthIterator(root);
	}

	// Function for creating a breadth-first-traversal iterator
	IIterator* create_bft_iterator()
	{
		return new HeapBreadthIterator(root);
	}

	// OUTPUT

	friend ostream& operator<<(ostream& output, BinaryHeap& heap)
	{
		HeapBreadthIterator iterator(heap.root);
		while (iterator.has_next())
		{
			output << iterator.next() << " ";
		}
		return output;
	}
};
#endif