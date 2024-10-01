#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "fileProcessing.h"

void printError(ErrorCode errorCode);

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printError(ERROR_INVALID_ARGUMENTS);
		return ERROR_INVALID_ARGUMENTS;
	}

	char *flag = argv[1];
	ErrorCode result;

	if (strcmp(flag, "-r") == 0) {
		if (argc != 5) {
			printError(ERROR_INVALID_ARGUMENTS);
			return ERROR_INVALID_ARGUMENTS;
		}
		char *file1 = argv[2];
		char *file2 = argv[3];
		char *outputFile = argv[4];
		if (strcmp(file1, outputFile) == 0 || strcmp(file2, outputFile) == 0 || (strcmp(file1, file2) == 0)) {
			printf("Input files are the same\n");
			return ERROR_INVALID_ARGUMENTS;
		}
		result = processFilesForFlagR(file1, file2, outputFile);
	} else if (strcmp(flag, "-a") == 0) {
		if (argc != 4) {
			printError(ERROR_INVALID_ARGUMENTS);
			return ERROR_INVALID_ARGUMENTS;
		}
		char *inputFile = argv[2];
		char *outputFile = argv[3];
		if (strcmp(inputFile, outputFile) == 0) {
			printf("Input files are the same\n");
			return ERROR_INVALID_ARGUMENTS;
		}
		result = processFileForFlagA(inputFile, outputFile);
	} else {
		printError(ERROR_UNKNOWN_FLAG);
		return ERROR_UNKNOWN_FLAG;
	}

	if (result != ERROR_NONE) {
		printError(result);
	}

	return result;
}

void printError(ErrorCode errorCode) {
	switch (errorCode) {
		case ERROR_NONE:
			break;
		case ERROR_FILE_NOT_FOUND:
			printf("Error: File not found.\n");
			break;
		case ERROR_INVALID_ARGUMENTS:
			printf("Error: Invalid arguments provided.\n");
			break;
		case ERROR_FILE_READ:
			printf("Error: Could not read from file.\n");
			break;
		case ERROR_FILE_WRITE:
			printf("Error: Could not write to file.\n");
			break;
		case ERROR_MEMORY_ALLOCATION:
			printf("Error: Memory allocation failed.\n");
			break;
		case ERROR_LEXEM_MISMATCH:
			printf("Error: Lexem count mismatch.\n");
			break;
		case ERROR_UNKNOWN_FLAG:
			printf("Error: Unknown flag.\n");
			break;
	}
}
