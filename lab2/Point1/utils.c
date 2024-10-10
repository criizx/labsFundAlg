#include <stdio.h>

int myStrcmp(const char* str1, const char* str2) {
	while (*str1 && (*str1 == *str2)) {
		str1++;
		str2++;
	}
	return *(unsigned char*)str1 - *(unsigned char*)str2;
}

int strLen(const char* str) {
	int length = 0;
	while (str[length] != '\0') {
		length++;
	}
	return length;
}
