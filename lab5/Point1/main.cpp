#include <iostream>

#include "BinaryInt.h"

using namespace std;

int main() {
	BinaryInt a(5);  // 101
	BinaryInt b(3);  // 11

	BinaryInt c = a + b;
	cout << "a + b = " << c << endl;  // 1000

	BinaryInt d = a - b;
	cout << "a - b = " << d << endl;  // 10

	cout << "a (before increment): " << a << endl;  // 101
	cout << "++a: " << ++a << endl;                 // 110
	cout << "a++: " << a++ << endl;                 // 110
	cout << "a (after increment): " << a << endl;   // 111

	cout << "b (before decrement): " << b << endl;  // 11
	cout << "--b: " << --b << endl;                 // 10
	cout << "b--: " << b-- << endl;                 // 10
	cout << "b (after decrement): " << b << endl;   // 1

	auto splitResult = a.splitBits();
	cout << "High bits: " << splitResult.first << endl;
	cout << "Low bits: " << splitResult.second << endl;

	return 0;
}
