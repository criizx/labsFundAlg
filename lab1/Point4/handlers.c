#include "handlers.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_codes.h"

void CloseFiles(FILE *inputFile, FILE *outputFile) {
	if (inputFile != NULL) {
		fclose(inputFile);
	}
	if (outputFile != NULL) {
		fclose(outputFile);
	}
}

int HandlerOptD(char *path, bool nFlag, char *res_path) {
	FILE *file = fopen(path, "r");
	if (file == NULL) {
		perror("Error opening input file");
		return E_INVALID_ARG;
	}

	FILE *outputFile = fopen(res_path, "w");
	if (outputFile == NULL) {
		perror("Error opening output file");
		CloseFiles(file, NULL);
		return E_BAD_ALLOC;
	}

	char ch;
	while ((ch = fgetc(file)) != EOF) {
		if (!isdigit((unsigned char)ch)) {
			fputc(ch, outputFile);
		}
	}

	CloseFiles(file, outputFile);

	printf("Digits successfully removed, result saved to %s.\n", res_path);
	return S_OK;
}

int HandlerOptI(char *path, bool nFlag, char *res_path) {
	FILE *file = fopen(path, "r");
	if (file == NULL) {
		perror("Error opening input file");
		return E_INVALID_ARG;
	}

	FILE *outputFile = fopen(res_path, "w");
	if (outputFile == NULL) {
		perror("Error opening output file");
		CloseFiles(file, NULL);
		return E_BAD_ALLOC;
	}

	char line[1024];
	while (fgets(line, sizeof(line), file)) {
		int latin_count = 0;
		for (int i = 0; line[i] != '\0'; i++) {
			if ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z')) {
				latin_count++;
			}
		}
		fprintf(outputFile, "%d\n", latin_count);
	}

	CloseFiles(file, outputFile);

	printf("Latin letters counted and saved to %s.\n", res_path);
	return S_OK;
}

int HandlerOptS(char *path, bool nFlag, char *res_path) {
	FILE *file = fopen(path, "r");
	if (file == NULL) {
		perror("Error opening input file");
		return E_INVALID_ARG;
	}

	FILE *outputFile = fopen(res_path, "w");
	if (outputFile == NULL) {
		perror("Error opening output file");
		CloseFiles(file, NULL);
		return E_BAD_ALLOC;
	}

	char line[1024];
	while (fgets(line, sizeof(line), file)) {
		int special_count = 0;
		for (int i = 0; line[i] != '\0'; i++) {
			if (!(line[i] >= 'A' && line[i] <= 'Z') && !(line[i] >= 'a' && line[i] <= 'z') &&
			    !(line[i] >= '0' && line[i] <= '9') && line[i] != ' ') {
				special_count++;
			}
		}
		fprintf(outputFile, "%d\n", special_count - 2);
	}

	CloseFiles(file, outputFile);

	printf("Non-alphabetic, non-digit, and non-space characters counted and saved to %s.\n", res_path);
	return S_OK;
}

// Функция для замены символов на их ASCII коды в 16-ричном формате
int HandlerOptA(char *path, bool nFlag, char *res_path) {
	FILE *file = fopen(path, "r");
	if (file == NULL) {
		perror("Error opening input file");
		return E_INVALID_ARG;
	}

	FILE *outputFile = fopen(res_path, "w");
	if (outputFile == NULL) {
		perror("Error opening output file");
		CloseFiles(file, NULL);
		return E_BAD_ALLOC;
	}

	char ch;
	while ((ch = fgetc(file)) != EOF) {
		if (isdigit((unsigned char)ch)) {
			fputc(ch, outputFile);
		} else {
			fprintf(outputFile, "%02X", (unsigned char)ch);
		}
	}

	CloseFiles(file, outputFile);

	printf("Non-digit characters replaced with their ASCII codes and saved to %s.\n", res_path);
	return S_OK;
}
