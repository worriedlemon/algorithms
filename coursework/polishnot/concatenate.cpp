char* Concatenate(const char* str1, size_t number, const char* str2 = "")
{
	size_t numberCharsCount = 0, str1Count = 0, str2Count = 0, num = number, index = 0;
	// calculate the size of new string
	for (index = 0; str1[index] != '\0'; index++) str1Count++;
	while (num != 0)
	{
		num /= 10;
		numberCharsCount++;
	}
	for (index = 0; str2[index] != '\0'; index++) str2Count++;
	str2Count++;

	// parse number into string
	char* numberInChars = new char[numberCharsCount];
	num = number;

	index = 0;
	while (num != 0)
	{
		numberInChars[index] = num % 10 + 48;
		index++;
		num /= 10;
	}

	// create new string for known
	char* result = new char[str1Count + numberCharsCount + str2Count];
	for (index = 0; index < str1Count + numberCharsCount + str2Count; index++)
	{
		if (index < str1Count)
		{
			result[index] = str1[index];
		}
		else if (index < str1Count + numberCharsCount)
		{
			result[index] = numberInChars[index - str1Count];
		}
		else result[index] = str2[index - (str1Count + numberCharsCount)];
	}
	delete[] numberInChars;
	return result;
}