#ifndef HANDLERS_H
#define HANDLERS_H

#include <stdio.h>
#include <stdbool.h>

int HandlerOptD(char* path, bool n_flag, char* res_path);
int HandlerOptI(char* path, bool n_flag, char* res_path);
int HandlerOptS(char* path, bool n_flag, char* res_path);
int HandlerOptA(char* path, bool n_flag, char* res_path);
void CloseFiles(FILE* input_file, FILE* output_file);

#endif
