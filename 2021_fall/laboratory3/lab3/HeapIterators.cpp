#include "BinaryHeap.h"

int BinaryHeap::HeapDepthIterator::next()
{
	if (!has_next())
	{
		throw out_of_range("No elements left");
	}
	previous = current;
	int temp = current->element;
	if (current->right != nullptr) stackOfNodes->Push(current->right);
	if (current->left != nullptr) current = current->left;
	else
	{
		if (stackOfNodes->top != nullptr)
		{
			current = stackOfNodes->top->node;
			stackOfNodes->Pop();
		}
		else current = nullptr;
	}
	return temp;
}

int BinaryHeap::HeapBreadthIterator::next()
{
	if (!has_next())
	{
		throw out_of_range("No elements left");
	}
	previous = current;
	int temp = current->element;
	if (current->left != nullptr) queueOfNodes->Push(current->left);
	if (current->right != nullptr) queueOfNodes->Push(current->right);
	if (queueOfNodes->first != nullptr)
	{
		current = queueOfNodes->first->node;
		queueOfNodes->Pop();
	}
	else current = nullptr;
	return temp;
}