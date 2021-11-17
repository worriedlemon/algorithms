#include "BinaryHeap.h"

void BinaryHeap::siftUp(Node* startNode)
{
	Node* currentNode = startNode;
	while (1)
	{
		if (currentNode == root) break;
		else
		{
			if (currentNode->element > currentNode->parent->element)
			{
				int temporaryData = currentNode->element;
				currentNode->element = currentNode->parent->element;
				currentNode->parent->element = temporaryData;
				currentNode = currentNode->parent;
			}
			else break;
		}
	}
	return;
}

void BinaryHeap::siftDown(Node* startNode)
{
	Node* currentNode = startNode;
	while (1)
	{
		if (currentNode != nullptr)
		{
			if (currentNode->left == nullptr) break;
			Node* swapNode;
			if (currentNode->right == nullptr)
			{
				swapNode = currentNode->left;
			}
			else
			{
				if (currentNode->left->element > currentNode->right->element) swapNode = currentNode->left;
				else swapNode = currentNode->right;
			}
			int temporaryData = currentNode->element;
			currentNode->element = swapNode->element;
			swapNode->element = temporaryData;
			currentNode = swapNode;
		}
	}
	return;
}