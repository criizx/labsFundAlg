#ifndef STRING_H
#define STRING_H

typedef struct {
	char* data;
	int length;
} String;

String createString(const char* str);
void deleteString(String* str);
int compareStringLength(const String* str1, const String* str2);
int compareStringLexicographically(const String* str1, const String* str2);
int areStringsEqual(const String* str1, const String* str2);
void copyString(String* destination, const String* source);
String cloneString(const String* source);
String concatenateStrings(const String* str1, const String* str2);

#endif