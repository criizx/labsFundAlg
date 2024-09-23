#ifndef HANDLERS_H
#define HANDLERS_H
#include <stdbool.h>
#include <stdio.h>

int HandlerOptD(char* path, bool nFlag, char* res_path);
int HandlerOptI(char* path, bool nFlag, char* res_path);
int HandlerOptS(char* path, bool nFlag, char* res_path);
int HandlerOptA(char* path, bool nFlag, char* res_path);
void CloseFiles(FILE* inputFile, FILE* outputFile);

#endif
