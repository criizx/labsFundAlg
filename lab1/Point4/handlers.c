#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "handlers.h"
#include "error_codes.h"

void CloseFiles(FILE* input_file, FILE* output_file) {
	if (input_file != NULL) {
		fclose(input_file);
	}
	if (output_file != NULL) {
		fclose(output_file);
	}
}

bool is_digit(char ch) {
	return ch >= '0' && ch <= '9';
}

int HandlerOptD(char* path, bool n_flag, char* res_path) {
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		perror("Error opening input file");
		return E_INVALID_ARG;
	}

	FILE* output_file = fopen(res_path, "w");
	if (output_file == NULL) {
		perror("Error opening output file");
		CloseFiles(file, NULL);
		return E_BAD_ALLOC;
	}

	char ch;
	while ((ch = fgetc(file)) != EOF) {
		if (!is_digit((unsigned char)ch)) {
			fputc(ch, output_file);
		}
	}

	CloseFiles(file, output_file);

	printf("Digits successfully removed, result saved to %s.\n", res_path);
	return S_OK;
}

int HandlerOptI(char* path, bool n_flag, char* res_path) {
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		perror("Error opening input file");
		return E_INVALID_ARG;
	}

	FILE* output_file = fopen(res_path, "w");
	if (output_file == NULL) {
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
		fprintf(output_file, "%d\n", latin_count);
	}

	CloseFiles(file, output_file);

	printf("Latin letters counted and saved to %s.\n", res_path);
	return S_OK;
}

int HandlerOptS(char* path, bool n_flag, char* res_path) {
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		perror("Error opening input file");
		return E_INVALID_ARG;
	}

	FILE* output_file = fopen(res_path, "w");
	if (output_file == NULL) {
		perror("Error opening output file");
		CloseFiles(file, NULL);
		return E_BAD_ALLOC;
	}

	char line[1024];
	while (fgets(line, sizeof(line), file)) {
		int special_count = 0;
		for (int i = 0; line[i] != '\0'; i++) {
			if (!(line[i] >= 'A' && line[i] <= 'Z') &&
				!(line[i] >= 'a' && line[i] <= 'z') &&
				!(line[i] >= '0' && line[i] <= '9') &&
				line[i] != ' ') {
				special_count++;
			}
		}
		fprintf(output_file, "%d\n", special_count - 2);
	}

	CloseFiles(file, output_file);

	printf("Non-alphabetic, non-digit, and non-space characters counted and saved to %s.\n", res_path);
	return S_OK;
}

int HandlerOptA(char* path, bool n_flag, char* res_path) {
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		perror("Error opening input file");
		return E_INVALID_ARG;
	}

	FILE* output_file = fopen(res_path, "w");
	if (output_file == NULL) {
		perror("Error opening output file");
		CloseFiles(file, NULL);
		return E_BAD_ALLOC;
	}

	char ch;
	while ((ch = fgetc(file)) != EOF) {
		if (is_digit((unsigned char)ch)) {
			fputc(ch, output_file);
		} else {
			fprintf(output_file, "%02X", (unsigned char)ch);
		}
	}

	CloseFiles(file, output_file);

	printf("Non-digit characters replaced with their ASCII codes and saved to %s.\n", res_path);
	return S_OK;
}
