#ifndef BINARYINT_H
#define BINARYINT_H

#include <iostream>
#include <string>

class BinaryInt {
   private:
	int value;

	std::string toBinaryString() const;
	static unsigned int bitwiseAdd(int a, int b);
	static unsigned int bitwiseNegate(int a);

   public:
	BinaryInt();
	BinaryInt(int val);

	BinaryInt operator-() const;
	BinaryInt& operator++();
	BinaryInt operator++(int);
	BinaryInt& operator--();
	BinaryInt operator--(int);

	BinaryInt& operator+=(const BinaryInt& other);
	BinaryInt operator+(const BinaryInt& other) const;
	BinaryInt& operator-=(const BinaryInt& other);
	BinaryInt operator-(const BinaryInt& other) const;

	friend std::ostream& operator<<(std::ostream& os, const BinaryInt& binInt);

	std::pair<BinaryInt, BinaryInt> splitBits() const;
};

#endif
