#include "fileProcessing.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "fileProcessing.h"

void toLowerCase(char *str) {
	while (*str) {
		*str = tolower(*str);
		str++;
	}
}

void toBase4(char *str, char *output) {
	char buffer[50];
	output[0] = '\0';

	while (*str) {
		int value = (int)(*str);
		int base4[20];
		int index = 0;

		buffer[0] = '\0';

		do {
			base4[index++] = value % 4;
			value /= 4;
		} while (value > 0);

		for (int i = index - 1; i >= 0; i--) {
			sprintf(buffer + strlen(buffer), "%d", base4[i]);
		}

		if (output[0] != '\0') {
			strcat(output, " ");
		}

		strcat(output, buffer);
		str++;
	}
}

void toBase8(char *str, char *output) {
	char buffer[50];
	while (*str) {
		sprintf(buffer, "%o ", tolower(*str));
		strcat(output, buffer);
		str++;
	}
}

ErrorCode processFilesForFlagR(const char *file1Path, const char *file2Path, const char *outputFilePath) {
	FILE *file1 = fopen(file1Path, "r");
	FILE *file2 = fopen(file2Path, "r");
	FILE *outputFile = fopen(outputFilePath, "w");

	if (!file1 || !file2 || !outputFile) {
		if (file1) {
			fclose(file1);
		}
		if (file2) {
			fclose(file2);
		}
		if (outputFile) {
			fclose(outputFile);
		}
		return ERROR_FILE_NOT_FOUND;
	}

	char buffer1[256], buffer2[256];
	while (fscanf(file1, "%s", buffer1) != EOF && fscanf(file2, "%s", buffer2) != EOF) {
		fprintf(outputFile, "%s %s ", buffer1, buffer2);
	}

	while (fscanf(file1, "%s", buffer1) != EOF) {
		fprintf(outputFile, "%s ", buffer1);
	}
	while (fscanf(file2, "%s", buffer2) != EOF) {
		fprintf(outputFile, "%s ", buffer2);
	}

	fclose(file1);
	fclose(file2);
	fclose(outputFile);

	return ERROR_NONE;
}

ErrorCode processFileForFlagA(const char *inputFilePath, const char *outputFilePath) {
	FILE *inputFile = fopen(inputFilePath, "r");
	FILE *outputFile = fopen(outputFilePath, "w");

	if (!inputFile || !outputFile) {
		fclose(outputFile);
		fclose(inputFile);
		return ERROR_FILE_NOT_FOUND;
	}

	char *word = malloc(100);
	char *result = malloc(10000);

	if (!word || !result) {
		free(word);
		free(result);
		fclose(inputFile);
		fclose(outputFile);
		return ERROR_FILE_NOT_FOUND;
	}

	int wordCount = 0;
	result[0] = '\0';

	while (fscanf(inputFile, "%s", word) != EOF) {
		wordCount++;

		if (wordCount % 10 == 0) {
			char temp[100] = "";
			toLowerCase(word);
			toBase4(word, temp);
			strcat(result, temp);
		} else if (wordCount % 2 == 0 && wordCount % 10 != 0) {
			toLowerCase(word);
			strcat(result, word);
		} else if (wordCount % 5 == 0 && wordCount % 10 != 0) {
			char temp[100] = "";
			toBase8(word, temp);
			strcat(result, temp);
		} else {
			strcat(result, word);
		}
		strcat(result, " ");
	}

	fprintf(outputFile, "%s", result);

	free(word);
	free(result);
	fclose(inputFile);
	fclose(outputFile);

	return ERROR_NONE;
}
