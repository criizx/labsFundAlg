#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H

#include "errors.h"

ErrorCode processFilesForFlagR(const char *file1Path, const char *file2Path, const char *outputFilePath);
ErrorCode processFileForFlagA(const char *filePath, const char *outputFilePath);

#endif
