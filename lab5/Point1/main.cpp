#include <iostream>

#include "BinaryInt.h"

using namespace std;

int main() {
	BinaryInt a(5);  // 101
	BinaryInt b(3);  // 11

	// Сложение
	BinaryInt c = a + b;
	cout << "a + b = " << c << endl;  // 1000

	// Вычитание
	BinaryInt d = a - b;
	cout << "a - b = " << d << endl;  // 10

	// Инкремент (префиксный и постфиксный)
	cout << "a (before increment): " << a << endl;  // 101
	cout << "++a: " << ++a << endl;                 // 110
	cout << "a++: " << a++ << endl;                 // 110
	cout << "a (after increment): " << a << endl;   // 111

	// Декремент (префиксный и постфиксный)
	cout << "b (before decrement): " << b << endl;  // 11
	cout << "--b: " << --b << endl;                 // 10
	cout << "b--: " << b-- << endl;                 // 10
	cout << "b (after decrement): " << b << endl;   // 1

	// Разделение битов
	auto splitResult = a.splitBits();
	cout << "High bits: " << splitResult.first << endl;
	cout << "Low bits: " << splitResult.second << endl;

	return 0;
}
