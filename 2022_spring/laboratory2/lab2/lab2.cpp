#include "haffman.h"

const size_t presets_count = 3;
const string presets[presets_count] = {
	"green green green green green", // 5 unique symbol
	"The darkest nights make the brightest stars", // 17 unique symbols
	"The quick brown fox jumps over the lazy dog" // 28 unique symbols
};

int main()
{
	HaffmanEncoder encoder;
	string s;
	size_t mode;
	cout << "#############  HAFFMAN ENCODER  #############\n";
	cout << "Presets are:\n";

	for (size_t i = 0; i < presets_count; i++)
	{
		cout << "(" << i + 1 << ") \'" << presets[i] << "\'\n";
	}
	cout << "Choose one: > "; cin >> mode;

	if (mode > 0 && mode <= presets_count)
	{
		s = presets[mode - 1];
	}
	else
	{
		cout << "No such option. Chosen 1.\n";
		s = presets[0];
	};

	cout << "\nYour string to encode by Haffman algorithm is\n\'" << s << "\'\n\n";
	cout << "Total symbols occurency rate:\n" << encoder.GetSymbolsCount(s) << "\n" << endl;

	encoder.Encode(s);

	bitcode code = encoder.GetEncodingResult();
	Bundle<size_t, size_t> usedBits = encoder.UsedBits();
	double compRate = encoder.CompressionRate();
	string s2 = encoder.Decode(code);

	cout << "\nEncoded bitcode is\n" << code << "\n\n";
	cout << "String uses " << usedBits.name << " bits, encoded string uses " << usedBits.value << " bits\n\n";
	cout << "Compression Rate is \'" << compRate << "\'\n" << endl;
	
	cout << "Codes are:\n" << encoder.GetCodes() << "\n\n";

	cout << "Recovering a string out of bitcode and Haffman Tree...\nAnswer is: \"" << s2 << "\"\n";
	cout << "Is it the same: " << (s == s2 ? "yes" : "no") << "\n\n";
	cout << "Serialized string: " << encoder.Serialize(code) << endl;

	return 0;
}