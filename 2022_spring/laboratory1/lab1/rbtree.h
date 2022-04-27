#ifndef RBTREE
#define RBTREE

#include <iostream>
#include <stdexcept>
#include "linear.h"
using namespace std;

#define NIL new TreeNode(this)

template <typename T1, typename T2>
class RBTree
{
	enum class NodeColor
	{
		Black, Red
	};

	struct TreeNode
	{
		TreeNode* parent, * left, * right;
		NodeColor color;
		T1* key; T2* value;

		TreeNode(TreeNode* parent) : parent(parent), left(nullptr), right(nullptr), color(NodeColor::Black), key(nullptr), value(nullptr) {}
		TreeNode(T1* key, T2* value, TreeNode* parent = nullptr) : parent(parent), left(NIL), right(NIL), color(NodeColor::Red), key(key), value(value) {}
		~TreeNode()
		{
			if (key != nullptr) delete key;
			if (value != nullptr) delete value;
		}

		friend ostream& operator<<(ostream& stream, TreeNode*& treeNode)
		{
			stream << "{" << *treeNode->key << ", " << *treeNode->value << "}";
			return stream;
		}

		inline bool isNil() { return value == nullptr; }
		inline void SwitchColor(NodeColor newColor) { color = newColor; }
	};

	TreeNode* root;

	void RotateLeft(TreeNode* x)
	{
		TreeNode* y = x->right, * p = x->parent;
		if (y->left != nullptr)
		{
			x->right = y->left;
			x->right->parent = x;
		}
		if (p == nullptr)
		{
			root = y;
		}
		else
		{
			if (p->left == x) p->left = y;
			else p->right = y;
		}
		y->parent = p;
		y->left = x;
		x->parent = y;
	}

	void RotateRight(TreeNode* y)
	{
		TreeNode* x = y->left, * p = y->parent;
		if (x->right != nullptr)
		{
			y->left = x->right;
			y->left->parent = y;
		}
		if (p == nullptr)
		{
			root = x;
		}
		else
		{
			if (p->right == y) p->right = x;
			else p->left = x;
		}
		x->parent = p;
		x->right = y;
		y->parent = x;
	}

	void RecoverAfterInsert(TreeNode* insertedNode)
	{
		TreeNode* cur = insertedNode, * p, * gp;
		while (cur->parent != nullptr && cur->parent->color == NodeColor::Red)
		{
			p = cur->parent;
			gp = p->parent;
			if (gp == nullptr) break;
			if (p == gp->left)
			{
				if (gp->right->color == NodeColor::Red)
				{
					gp->right->SwitchColor(NodeColor::Black);
					gp->left->SwitchColor(NodeColor::Black);
					gp->SwitchColor(NodeColor::Red);
					cur = gp;
				}
				else if (p->right == cur)
				{
					cur = p;
					RotateLeft(cur);
				}
				else
				{
					p->SwitchColor(NodeColor::Black);
					gp->SwitchColor(NodeColor::Red);
					RotateRight(gp);
				}
			}
			else
			{
				if (gp->left->color == NodeColor::Red)
				{
					gp->right->SwitchColor(NodeColor::Black);
					gp->left->SwitchColor(NodeColor::Black);
					gp->SwitchColor(NodeColor::Red);
					cur = gp;
				}
				else if (p->left == cur)
				{
					cur = p;
					RotateRight(cur);
				}
				else
				{
					
					p->SwitchColor(NodeColor::Black);
					gp->SwitchColor(NodeColor::Red);
					RotateLeft(gp);
				}
			}
		}
		root->SwitchColor(NodeColor::Black);
	}

	void RecoverAfterRemove(TreeNode* removedNode)
	{
		TreeNode* x = removedNode, * w;
		while (x->parent != nullptr && x->color != NodeColor::Black)
		{
			if (x->parent->left == x)
			{
				w = x->parent->right;
				if (w->color == NodeColor::Red)
				{
					w->SwitchColor(NodeColor::Black);
					x->parent->SwitchColor(NodeColor::Red);
					RotateLeft(x->parent);
					w = x->parent->right;
				}
				else if (w->left->color == NodeColor::Black && w->right->color == NodeColor::Black)
				{
					w->SwitchColor(NodeColor::Red);
					x = x->parent;
				}
				else if (w->right->color == NodeColor::Black)
				{
					w->left->SwitchColor(NodeColor::Black);
					w->SwitchColor(NodeColor::Red);
					RotateRight(w);
					w = x->parent->right;
				}
				else
				{
					w->SwitchColor(x->parent->color);
					x->parent->SwitchColor(NodeColor::Black);
					w->right->SwitchColor(NodeColor::Black);
					RotateLeft(x->parent);
					x = root;
				}
			}
			else
			{
				w = x->parent->left;
				if (w->color == NodeColor::Red)
				{
					w->SwitchColor(NodeColor::Black);
					x->parent->SwitchColor(NodeColor::Red);
					RotateRight(x->parent);
					w = x->parent->left;
				}
				else if (w->left->color == NodeColor::Black && w->right->color == NodeColor::Black)
				{
					w->SwitchColor(NodeColor::Red);
					x = x->parent;
				}
				else if (w->left->color == NodeColor::Black)
				{
					w->right->SwitchColor(NodeColor::Black);
					w->SwitchColor(NodeColor::Red);
					RotateLeft(w);
					w = x->parent->left;
				}
				else
				{
					w->SwitchColor(x->parent->color);
					x->parent->SwitchColor(NodeColor::Black);
					w->left->SwitchColor(NodeColor::Black);
					RotateRight(x->parent);
					x = root;
				}
			}
			x->SwitchColor(NodeColor::Black);
		}
	}

	List<TreeNode*>* DFT()
	{
		TreeNode* current = root;
		Stack<TreeNode*> stack;
		List<TreeNode*>* result = new List<TreeNode*>;
		while (current != nullptr && !current->isNil())
		{
			result->PushBack(current);
			if (current->right->value != nullptr) stack.Push(current->right);
			if (current->left->value != nullptr) current = current->left;
			else
			{
				if (stack.head != nullptr)
				{
					current = (TreeNode*)stack.GetData(0);
					stack.Pop();
				}
				else current = nullptr;
			}
		}
		return result;
	}

	TreeNode& FindTreeNode(T1 key)
	{
		TreeNode* current = root;
		while (!current->isNil())
		{
			if (*(current->key) == key) return *current;
			current = (key > *(current->key)) ? current->right : current->left;
		}
		throw invalid_argument("There are no elements with such key");
	}

public:
	RBTree() : root(new TreeNode(nullptr)) {}
	~RBTree()
	{
		try { Clear(); }
		catch (logic_error&) {}
		delete root;
	}

	friend ostream& operator<<(ostream& stream, RBTree<T1, T2>& rbtree)
	{
		List<TreeNode*>* list = rbtree.DFT();
		stream << *list;
		return stream;
	}

	void Clear()
	{
		TreeNode* current = root, * temp;
		if (current->value == nullptr) throw logic_error("Tree doesn't have any nodes");
		Stack<TreeNode*> stack;
		while (!current->isNil() || stack.head != nullptr)
		{
			if (current->right != nullptr) stack.Push(current->right);
			if (current->left != nullptr)
			{
				temp = current->left;
				delete current;
				current = temp;
			}
			else if (stack.head != nullptr)
			{
				current = stack.head->data;
				stack.Pop();
			}
		}
		current->parent = nullptr;
		root = current;
		return;
	}

	T2 Find(T1 key)
	{
		TreeNode* current = root;
		while (!current->isNil())
		{
			if (*(current->key) == key) return *(current->value);
			current = (key > *(current->key)) ? current->right : current->left;
		}
		throw invalid_argument("There are no elements with such key");
	}

	void Insert(T1 key, T2 value)
	{
		if (root->isNil())
		{
			delete root;
			root = new TreeNode(new T1(key), new T2(value));
			root->SwitchColor(NodeColor::Black);
		}
		else
		{
			TreeNode* current = root;
			while (!current->isNil())
			{
				if (key == *(current->key)) throw invalid_argument("Element with such key already exists");
				current = (key > *(current->key)) ? current->right : current->left;
			}
			TreeNode* newNode = new TreeNode(new T1(key), new T2(value), current->parent);
			delete current;
			current = newNode;
			if (key > *(current->parent->key)) current->parent->right = current;
			else current->parent->left = current;
			RecoverAfterInsert(current);
		}
	}

	void Remove(T1 key)
	{
		TreeNode* nodeToBeDeleted = &FindTreeNode(key), * x;
		NodeColor originalColor = nodeToBeDeleted->color;
		if (nodeToBeDeleted->left->isNil())
		{
			delete nodeToBeDeleted->left;
			x = nodeToBeDeleted->right;
			if (nodeToBeDeleted->parent->right == nodeToBeDeleted)
			{
				nodeToBeDeleted->parent->right = x;
			}
			else nodeToBeDeleted->parent->left = x;
			x->parent = nodeToBeDeleted->parent;
		}
		else if (nodeToBeDeleted->right->isNil())
		{
			delete nodeToBeDeleted->right;
			x = nodeToBeDeleted->left;
			if (nodeToBeDeleted->parent->right == nodeToBeDeleted) nodeToBeDeleted->parent->right = x;
			else nodeToBeDeleted->parent->left = x;
			x->parent = nodeToBeDeleted->parent;
		}
		else
		{
			TreeNode* y = nodeToBeDeleted->right;
			while (!y->left->isNil()) y = y->left;
			originalColor = y->color;
			x = y->right;
			if (nodeToBeDeleted->left == y || nodeToBeDeleted->right == y)
			{
				x->parent = y;
			}
			else
			{
				if (y->parent->right == y) y->parent->right = x;
				else y->parent->left = x;
			}
			if (nodeToBeDeleted->parent->right == nodeToBeDeleted) nodeToBeDeleted->parent->right = y;
			else nodeToBeDeleted->parent->left = y;
			y->parent = nodeToBeDeleted->parent;
			y->SwitchColor(originalColor);
		}
		if (originalColor == NodeColor::Black) RecoverAfterRemove(x);
		delete nodeToBeDeleted;
	}

	List<T1>* GetKeys()
	{
		List<TreeNode*>* list = DFT();
		List<T1>* keys = new List<T1>;
		while (list->head != nullptr)
		{
			keys->PushBack(T1(*((TreeNode*)list->head->data)->key));
			list->PopFront();
		}
		return keys;
	}

	List<T2>* GetValues()
	{
		List<TreeNode*>* list = DFT();
		List<T2>* values = new List<T2>;
		while (list->head != nullptr)
		{
			values->PushBack(T2(*((TreeNode*)list->head->data)->value));
			list->PopFront();
		}
		return values;
	}

	inline void Print() { cout << *this; }
};
#endif // RBTREE
