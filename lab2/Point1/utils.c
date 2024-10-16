#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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

void strCopy(char* dest, const char* src) {
	while (*src) {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

void strConcat(char* dest, const char* src) {
	while (*dest) {
		dest++;
	}
	strCopy(dest, src);
}

void shuffleStrings(char** array, int n) {
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		char* temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}