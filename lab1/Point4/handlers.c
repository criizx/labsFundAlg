#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "handlers.h"
#include "functions.h"
#include "error_codes.h"

int HandlerOptD(char* path, bool nFlag, char* res_path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    char outputFilePath[256];
	char *fileName = strrchr(path, '/');

	if (!fileName) {
        fileName = path;
	} else {
        fileName++;
    }
	if (!nFlag){
		snprintf(outputFilePath, sizeof(outputFilePath), "%.*sout_%s", (int)(fileName - path), path, fileName);
		strncpy(res_path, outputFilePath, 255);
	}
	res_path[255] = '\0';

    FILE *outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(file);
        return EXIT_FAILURE;
    }
	    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!isdigit((unsigned char)ch)) {
            fputc(ch, outputFile);
        }
    }

    fclose(file);
    fclose(outputFile);

    printf("Digits successfully removed, result saved to %s.\n", outputFilePath);
    return EXIT_SUCCESS;

}

int HandlerOptI(char* path, bool nFlag, char* res_path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    char outputFilePath[256];
    char *fileName = strrchr(path, '/');
    if (!fileName) {
        fileName = path;
    } else {
        fileName++;
    }
    if (!nFlag) {
        snprintf(outputFilePath, sizeof(outputFilePath), "%.*sout_%s", (int)(fileName - path), path, fileName);
        strncpy(res_path, outputFilePath, 255);
    }
    res_path[255] = '\0';

    FILE *outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(file);
        return EXIT_FAILURE;
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

    fclose(file);
    fclose(outputFile);

    printf("Latin letters counted and saved to %s.\n", outputFilePath);
    return EXIT_SUCCESS;
}


int HandlerOptS(char* path, bool nFlag, char* res_path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    char outputFilePath[256];
    char *fileName = strrchr(path, '/');
    if (!fileName) {
        fileName = path;
    } else {
        fileName++;
    }
    if (!nFlag) {
        snprintf(outputFilePath, sizeof(outputFilePath), "%.*sout_%s", (int)(fileName - path), path, fileName);
        strncpy(res_path, outputFilePath, 255);
    }
    res_path[255] = '\0';

    FILE *outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(file);
        return EXIT_FAILURE;
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
        fprintf(outputFile, "%d\n", special_count);
    }

    fclose(file);
    fclose(outputFile);

    printf("Non-Latin letters, digits, and spaces counted and saved to %s.\n", outputFilePath);
    return EXIT_SUCCESS;
}


int HandlerOptA(char* path, bool nFlag, char* res_path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    char outputFilePath[256];
    char *fileName = strrchr(path, '/');
    if (!fileName) {
        fileName = path;
    } else {
        fileName++;
    }
    if (!nFlag) {
        snprintf(outputFilePath, sizeof(outputFilePath), "%.*sout_%s", (int)(fileName - path), path, fileName);
        strncpy(res_path, outputFilePath, 255);
    }
    res_path[255] = '\0';

    FILE *outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(file);
        return EXIT_FAILURE;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isdigit((unsigned char)ch)) {
            fputc(ch, outputFile);
        } else {
            fprintf(outputFile, "%02X", (unsigned char)ch);
        }
    }

    fclose(file);
    fclose(outputFile);

    printf("Non-digit characters replaced with their ASCII codes and saved to %s.\n", outputFilePath);
    return EXIT_SUCCESS;
}
