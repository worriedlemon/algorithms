#ifndef HAFFMAN_ENCODER
#define HAFFMAN_ENCODER
#include "map.h"

typedef List<bool> bitcode;

class HaffmanEncoder
{
	struct EncoderElement
	{
		Bundle<char*, size_t> info;
		EncoderElement* left, * right, *parent;

		EncoderElement(char* arg, size_t weight) : info(Bundle<char*, size_t>(arg, weight)),
			left(nullptr), right(nullptr), parent(nullptr), hasBeenVisited(false) {}
		~EncoderElement() {}

		EncoderElement operator+(EncoderElement& second)
		{
			return EncoderElement(nullptr, info.value + second.info.value);
		}

		bool hasBeenVisited;
	};

	struct HaffmanTree
	{
		string charset;
		EncoderElement* root;

		HaffmanTree() : root(nullptr), charset("") {}

		~HaffmanTree()
		{
			try { Clear(); }
			catch (logic_error&) {}
		}

		void ResetVisits()
		{
			EncoderElement* current = root;
			Stack<EncoderElement*> stack;
			while (current != nullptr || stack.head != nullptr)
			{
				if (current != nullptr)
				{
					current->hasBeenVisited = false;
					if (current->right != nullptr) stack.Push(current->right);
					current = current->left;
				}
				else if (stack.head != nullptr)
				{
					current = stack.head->data;
					stack.Pop();
				}
			}
			return;
		}
		
		// Clearing the tree
		void Clear()
		{
			if (root == nullptr) throw logic_error("Haffman tree is already empty");
			EncoderElement* current = root, * temp;
			Stack<EncoderElement*> stack;
			while (current != nullptr || stack.head != nullptr)
			{
				if (current != nullptr)
				{
					if (current->right != nullptr) stack.Push(current->right);
					temp = current->left;
					delete current;
					current = temp;
				}
				else
				{
					current = stack.head->data;
					stack.Pop();
				}
			}
			root = nullptr;
		}
	};

	HaffmanTree codeTree;

public:
	HaffmanEncoder() {}
	HaffmanEncoder(string text)
	{
		Encode(text);
	}
	~HaffmanEncoder() {}

	// Clearing previous Haffman tree
	inline void Reset()
	{
		codeTree.Clear();
	}

	// Returns an associative array of pairs [symbol] and its [count]
	CountingMap<char>& GetSymbolsCount(string& text)
	{
		CountingMap<char>* map = new CountingMap<char>;
		const size_t textLength = text.length();

		// Filling map with [arguments]
		for (size_t i = 0; i < textLength; i++)
		{
			try {
				(*map)[text[i]]++;
			}
			catch (invalid_argument&) {
				map->Insert(text[i], 1);
			}
		}
		return *map;
	}

	// Encoding a string (creating or remaking a Haffman tree)
	void Encode(string& text)
	{
		if (text == "") throw length_error("String is blank");
		try { Reset(); }
		catch (logic_error&) {}
		codeTree.charset = text;

		CountingMap<char> map = GetSymbolsCount(text);

		List<Bundle<char, size_t>>* elements = map.GetKeysAndValues();
		List<EncoderElement*>* freeNodes = new List<EncoderElement*>();
		const size_t count = elements->GetSize();
		for (size_t i = 0; i < count; i++)
		{
			EncoderElement* newElement = new EncoderElement(new char(elements->GetData().name), size_t(elements->GetData().value));
			freeNodes->PushBack(newElement);
			elements->PopFront();
		}
		delete elements;

		// Creating Haffman tree
		while (freeNodes->tail != freeNodes->head)
		{
			// Sorting
			const size_t count = freeNodes->GetSize();
			for (size_t i = 0; i < count - 1; i++)
			{
				for (size_t j = 0; j < count - 1 - i; j++)
				{
					size_t value1 = freeNodes->GetData(j)->info.value,
						value2 = freeNodes->GetData(j + 1)->info.value;
					if (value1 > value2)
					{
						EncoderElement* temp = new EncoderElement(*(freeNodes->GetData(j)));
						freeNodes->PopIndex(j);
						freeNodes->PushIndex(j + 1, temp);
					}
				}
			}

			// Making a new free node out of the least two
			EncoderElement* newFreeNode = new EncoderElement(*freeNodes->GetData(0) + *freeNodes->GetData(1));

			newFreeNode->left = freeNodes->GetData();
			newFreeNode->left->parent = newFreeNode;
			freeNodes->PopFront();

			newFreeNode->right = freeNodes->GetData();
			newFreeNode->right->parent = newFreeNode;
			freeNodes->PopFront();

			freeNodes->PushBack(newFreeNode);
		}
		codeTree.root = freeNodes->GetData();
	}

	// Decodes a bitcode based on Haffman tree of this encoder
	string& Decode(bitcode& code)
	{
		if (codeTree.root == nullptr) throw logic_error("Encoder doesn't have a coding yet");

		const size_t bitsCount = code.GetSize();
		string* result = new string("");
		EncoderElement* currentElem = codeTree.root;

		for (size_t i = 0; i < bitsCount + 1; i++)
		{
			if (currentElem == nullptr) throw invalid_argument("Unable to decode");
			if (currentElem->info.name != nullptr)
			{
				result->push_back(*currentElem->info.name);
				currentElem = codeTree.root;
				if (i != bitsCount) i--;
			}
			else if (code.GetData(i) == 0) currentElem = currentElem->left;
			else currentElem = currentElem->right;
		}
		return *result;
	}

	// Returns codes for every symbol
	Map<char, bitcode>& GetCodes()
	{
		if (codeTree.root == nullptr) throw logic_error("Encoder doesn't have a coding yet");
		Map<char, bitcode>* result = new Map<char, bitcode>;
		EncoderElement* current = codeTree.root;
		bitcode* currentBitcode = new bitcode();
		while (current != nullptr)
		{
			if (current->info.name != nullptr)
			{
				result->Insert(*current->info.name, currentBitcode);

				// Instantiating new bitcode
				bitcode* temp = new bitcode();
				for (size_t i = 0; i < currentBitcode->GetSize() - 1; i++) temp->PushBack(currentBitcode->GetData(i));
				currentBitcode = temp;

				current->hasBeenVisited = true;
				current = current->parent;
			}
			else
			{
				if (!current->left->hasBeenVisited)
				{
					currentBitcode->PushBack(0);
					current = current->left;
				}
				else if (!current->right->hasBeenVisited)
				{
					currentBitcode->PushBack(1);
					current = current->right;
				}
				else
				{
					current->hasBeenVisited = true;
					current = current->parent;
					if (currentBitcode->tail != nullptr) currentBitcode->PopBack();
				}
			}
		}
		delete currentBitcode;
		codeTree.ResetVisits();
		return *result;
	}

	// Returns Haffman bitcode
	bitcode& GetEncodingResult()
	{
		if (codeTree.root == nullptr) throw logic_error("Encoder doesn't have a coding yet");

		const size_t textLength = codeTree.charset.length();
		Map<char, bitcode> codes = GetCodes();
		List<bool>* result = new List<bool>;

		for (size_t i = 0; i < textLength; i++)
		{
			*result += codes.Find(codeTree.charset[i]);
		}

		return *result;
	}

	// Compresses bitcode into binary character format
	string& Serialize(bitcode& code)
	{
		const size_t count = code.GetSize();
		string* result = new string("");
		size_t i = 0;
		char symbol = 0;
		for (i; i < count; i++)
		{
			if (code.GetData(i) == 0) symbol = symbol << 1;
			else symbol = (symbol << 1) + 1;
			if (i % 8 == 7)
			{
				result->push_back(symbol);
				symbol = 0;
			}
		}
		if (symbol != 0) result->push_back(symbol << (8 - (i % 8)));
		return *result;
	}

	// Returns pair, containing used memory for string and its encoded variant
	Bundle<size_t, size_t> UsedBits()
	{
		return Bundle<size_t, size_t>(codeTree.charset.length() * sizeof(char) * 8, GetEncodingResult().GetSize());
	}

	// Returns compression rate (original/encoded memory ratio), which should be more than one
	double CompressionRate()
	{
		Bundle<size_t, size_t> used = UsedBits();
		return double(used.name) / used.value;
	}

	inline void OutputCodes()
	{
		cout << GetCodes();
	}
};
#endif // HAFFMAN_ENCODER