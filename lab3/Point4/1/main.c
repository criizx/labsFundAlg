#include <stdio.h>

#include "../string/string.h"

int main() {
	String str1 = createString("Hello ");
	String str2 = createString("World");

	printf("String 1: %s\n", str1.data);
	printf("String 2: %s\n", str2.data);

	String str3 = concatenateStrings(&str1, &str2);
	printf("Concatenated: %s\n", str3.data);

	printf("Length comparison: %d\n", compareStringLength(&str1, &str2));
	printf("Lexicographical comparison: %d\n", compareStringLexicographically(&str1, &str2));
	printf("Are strings equal: %d\n", areStringsEqual(&str1, &str2));

	copyString(&str1, &str2);
	printf("After copying, String 1: %s\n", str1.data);

	String str4 = cloneString(&str1);
	printf("Cloned String 4: %s\n", str4.data);

	deleteString(&str1);
	deleteString(&str2);
	deleteString(&str3);
	deleteString(&str4);

	return 0;
}
