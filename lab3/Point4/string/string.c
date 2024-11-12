#include "string.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

String createString(const char* str) {
	String newString;
	newString.length = strlen(str);
	newString.data = (char*)malloc((newString.length + 1) * sizeof(char));
	if (newString.data) {
		strcpy(newString.data, str);
	}
	return newString;
}

void deleteString(String* str) {
	if (str->data) {
		free(str->data);
		str->data = NULL;
	}
	str->length = 0;
}

int compareStringLength(const String* str1, const String* str2) {
	if (str1->length != str2->length) {
		return str1->length - str2->length;
	}
	return compareStringLexicographically(str1, str2);
}

int compareStringLexicographically(const String* str1, const String* str2) { return strcmp(str1->data, str2->data); }

int areStringsEqual(const String* str1, const String* str2) { return strcmp(str1->data, str2->data) == 0; }

void copyString(String* destination, const String* source) {
	deleteString(destination);
	destination->length = source->length;
	destination->data = (char*)malloc((source->length + 1) * sizeof(char));
	if (destination->data) {
		strcpy(destination->data, source->data);
	}
}

String cloneString(const String* source) {
	String newString;
	newString.length = source->length;
	newString.data = (char*)malloc((source->length + 1) * sizeof(char));
	if (newString.data) {
		strcpy(newString.data, source->data);
	}
	return newString;
}

String concatenateStrings(const String* str1, const String* str2) {
	String result;
	result.length = str1->length + str2->length;
	result.data = (char*)malloc((result.length + 1) * sizeof(char));
	if (result.data) {
		strcpy(result.data, str1->data);
		strcat(result.data, str2->data);
	}
	return result;
}
