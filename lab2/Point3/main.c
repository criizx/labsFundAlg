#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void search_in_file(const char *substr, const char *file_path) {
	FILE *file = fopen(file_path, "r");
	if (!file) {
		perror("Failed to open file");
		return;
	}

	int line = 1, col = 1;
	int substr_len = 0;
	while (substr[substr_len] != '\0') {
		substr_len++;
	}

	int index = 0;
	int ch;
	int start_col = 1;
	int possible_match = 0;

	while ((ch = fgetc(file)) != EOF) {
		if (ch == substr[index]) {
			if (index == 0) {
				start_col = col;
			}
			index++;
			if (index == substr_len) {
				printf("Found match at line %d, col %d in file %s\n", line, start_col, file_path);
				index = 0;
				possible_match = 0;
			}
		} else {
			if (index > 0) {
				fseek(file, -(index), SEEK_CUR);
				col -= index;
				index = 0;
			}
		}

		if (ch == '\n') {
			line++;
			col = 1;
		} else {
			col++;
		}
	}

	fclose(file);
}

void search_in_files(const char *substr, int num_files, ...) {
	va_list files;
	va_start(files, num_files);

	for (int i = 0; i < num_files; i++) {
		const char *file_path = va_arg(files, const char *);
		search_in_file(substr, file_path);
	}

	va_end(files);
}

int main() {
	const char *substr = "ab\nab";
	search_in_files(substr, 2, "file1.txt", "file2.txt", "file3.txt");

	return 0;
}
