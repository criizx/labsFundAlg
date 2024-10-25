#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buildPrefixArray(const char* pattern, int M, int* prefixArray) {
	int length = 0;
	prefixArray[0] = 0;
	int i = 1;

	while (i < M) {
		if (pattern[i] == pattern[length]) {
			length++;
			prefixArray[i] = length;
			i++;
		} else {
			if (length != 0) {
				length = prefixArray[length - 1];
			} else {
				prefixArray[i] = 0;
				i++;
			}
		}
	}
}

void KMPsearch(const char* pattern, const char* filePath) {
	FILE* file = fopen(filePath, "r");
	if (file == NULL) {
		printf("Failed to open file: %s\n", filePath);
		return;
	}

	int M = strlen(pattern);
	int* prefixArray = (int*)malloc(M * sizeof(int));
	buildPrefixArray(pattern, M, prefixArray);

	int j = 0;
	int lineNumber = 1;
	int startPosition = 0;
	int matchStartLine = 1;

	char* line = NULL;
	size_t lineBufferSize = 0;

	while (getline(&line, &lineBufferSize, file) != -1) {
		int lineLength = strlen(line);

		for (int i = 0; i < lineLength; i++) {
			while (j > 0 && line[i] != pattern[j]) {
				j = prefixArray[j - 1];
				startPosition = i - j;
				if (i < j) {
					lineNumber++;
				}
			}
			if (line[i] == pattern[j]) {
				if (j == 0) {
					startPosition = i + 1;
					matchStartLine = lineNumber;
				}
				j++;
			}

			if (j == M) {
				printf("Match found in file %s line %d at position %d\n", filePath, matchStartLine, startPosition);
				j = prefixArray[j - 1];
				matchStartLine = lineNumber;
			}
		}

		lineNumber++;
	}

	free(prefixArray);
	free(line);
	fclose(file);
}

void searchInFiles(const char* pattern, int fileCount, ...) {
	va_list files;
	va_start(files, fileCount);

	for (int i = 0; i < fileCount; i++) {
		const char* filePath = va_arg(files, const char*);
		KMPsearch(pattern, filePath);
	}

	va_end(files);
}

int main() {
	const char* pattern = "ab\nab";
	searchInFiles(pattern, 1, "file1.txt");

	return 0;
}
