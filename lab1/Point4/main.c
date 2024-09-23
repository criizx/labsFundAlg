#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_codes.h"
#include "handlers.h"

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Usage: program <flag> <input_file> [output_file]\n");
		return E_INVALID_ARG;
	}

	char *firstArg = argv[1];
	bool nFlag = false;
	char a;
	char resPath[256];
	char *inputPath = argv[2];

	if (firstArg[0] == '-' || firstArg[0] == '/') {
		if (firstArg[1] == 'n') {
			nFlag = true;
			a = firstArg[2];
			if (argc > 3) {
				strncpy(resPath, argv[3], sizeof(resPath) - 1);
				resPath[sizeof(resPath) - 1] = '\0';
			} else {
				printf("Error: Output file path is required when using the 'n' flag.\n");
				return E_INVALID_ARG;
			}
		} else {
			a = firstArg[1];
			// Генерация имени выходного файла
			char *fileName = strrchr(inputPath, '/');
			if (!fileName) {
				fileName = inputPath;
			} else {
				fileName++;
			}
			snprintf(resPath, sizeof(resPath), "out_%s", fileName);
		}

		switch (a) {
			case 'd':
				return HandlerOptD(inputPath, nFlag, resPath);
			case 'i':
				return HandlerOptI(inputPath, nFlag, resPath);
			case 's':
				return HandlerOptS(inputPath, nFlag, resPath);
			case 'a':
				return HandlerOptA(inputPath, nFlag, resPath);
			default:
				printf("Error: Unknown flag.\n");
				return E_UNKNOWN_OPT;
		}
	} else {
		printf("Error: Invalid flag format.\n");
		return E_INVALID_ARG;
	}
}
