#include <bitset>

#include "BinaryInt.h"

BinaryInt::BinaryInt() : value(0) {}

BinaryInt::BinaryInt(int val) : value(val) {}

std::string BinaryInt::toBinaryString() const { return std::bitset<32>(value).to_string(); }

BinaryInt BinaryInt::operator-() const { return BinaryInt(bitwiseNegate(value)); }

BinaryInt& BinaryInt::operator++() {
	value = bitwiseAdd(value, 1);
	return *this;
}

BinaryInt BinaryInt::operator++(int) {
	BinaryInt temp = *this;
	++(*this);
	return temp;
}

BinaryInt& BinaryInt::operator--() {
	value = bitwiseAdd(value, bitwiseNegate(1));
	return *this;
}

BinaryInt BinaryInt::operator--(int) {
	BinaryInt temp = *this;
	--(*this);
	return temp;
}

BinaryInt& BinaryInt::operator+=(const BinaryInt& other) {
	value = bitwiseAdd(value, other.value);
	return *this;
}

BinaryInt BinaryInt::operator+(const BinaryInt& other) const {
	BinaryInt result = *this;
	result += other;
	return result;
}

BinaryInt& BinaryInt::operator-=(const BinaryInt& other) {
	value = bitwiseAdd(value, bitwiseNegate(other.value));
	return *this;
}

BinaryInt BinaryInt::operator-(const BinaryInt& other) const {
	BinaryInt result = *this;
	result -= other;
	return result;
}

unsigned int BinaryInt::bitwiseAdd(int a, int b) {
	while (b != 0) {
		unsigned int carry = a & b;
		a = a ^ b;
		b = carry << 1;
	}
	return a;
}

unsigned int BinaryInt::bitwiseNegate(int a) { return bitwiseAdd(~a, 1); }

std::ostream& operator<<(std::ostream& os, const BinaryInt& binInt) {
	os << "Value: " << binInt.value << ", Binary: " << binInt.toBinaryString();
	return os;
}

std::pair<BinaryInt, BinaryInt> BinaryInt::splitBits() const {
	BinaryInt highBits(value & 0xFFFF0000);
	BinaryInt lowBits(value & 0x0000FFFF);
	return std::make_pair(highBits, lowBits);
}
