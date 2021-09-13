#include <iostream>
using namespace std;
#include <fstream>
#include <cmath>

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите число: ";
	double number
	cin >> number;
	if (number >= 0)
	{
		cout << "\nКорень из числа " << number << " равен " << sqrtf(number) << ".";
	}
	else cout << "Введено неверное число: " << number << ".";
	return 0;
}
