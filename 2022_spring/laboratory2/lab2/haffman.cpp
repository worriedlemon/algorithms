#include "map.h"

typedef List<bool> bitcode;

template <typename Type>
void /*Map<T, bitcode>*/ Encode(size_t argumentsCount, Type* arguments)
{
	CountingMap<Type> map;

	// Filling map with [arguments]
	for (size_t i = 0; i < argumentsCount; i++)
	{
		try {
			map[arguments[i]]++;
		}
		catch (invalid_argument&) {
			map.Insert(arguments[i], 1);
		}
	}

	List<Bundle<Type, size_t>>* elements = map.GetKeysAndValues();

	// Creating Haffman tree
	//while (elements->tail != elements->head)
	//{
		// Sorting
		const size_t count = elements->GetSize();
		for (size_t i = 0; i < count - 1; i++)
		{
			for (size_t j = 0; j < count - 1 - i; j++)
			{
				if (elements->GetData(j).value > elements->GetData(j+1).value)
				{
					Bundle<Type, size_t> temp = Bundle<Type, size_t>(elements->GetData(i));
					elements->PopIndex(j + 1);
					elements->PushIndex(j + 1, temp);
				}
			}
		}
		cout << *elements;
	//}
	return;
}