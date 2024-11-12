#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *name;
	int value;
} MemoryCell;

typedef struct {
	MemoryCell *cells;
	int size;
	int capacity;
} MemoryManager;

MemoryManager *createMemoryManager(int initialCapacity) {
	MemoryManager *manager = (MemoryManager *)malloc(sizeof(MemoryManager));
	if (!manager) {
		perror("Failed to allocate MemoryManager");
		return NULL;
	}

	manager->cells = (MemoryCell *)malloc(sizeof(MemoryCell) * initialCapacity);
	if (!manager->cells) {
		perror("Failed to allocate MemoryCell array");
		free(manager);
		return NULL;
	}

	manager->size = 0;
	manager->capacity = initialCapacity;
	return manager;
}

void cleanVariableName(char *name) {
	while (isspace((unsigned char)*name)) {
		name++;
	}

	char *end = name + strlen(name) - 1;
	while (end > name && (isspace((unsigned char)*end) || *end == ';')) {
		*end = '\0';
		end--;
	}
}

int compareMemoryCells(const void *a, const void *b) {
	return strcmp(((MemoryCell *)a)->name, ((MemoryCell *)b)->name);
}

int findVariableIndex(MemoryManager *manager, const char *name) {
	MemoryCell key = {(char *)name, 0};
	MemoryCell *found =
	    (MemoryCell *)bsearch(&key, manager->cells, manager->size, sizeof(MemoryCell), compareMemoryCells);
	return found ? (found - manager->cells) : -1;
}

int insertOrUpdateVariable(MemoryManager *manager, const char *name, int value) {
	int index = findVariableIndex(manager, name);
	if (index != -1) {
		manager->cells[index].value = value;
		return 0;
	}

	if (manager->size >= manager->capacity) {
		manager->capacity *= 2;
		manager->cells = (MemoryCell *)realloc(manager->cells, sizeof(MemoryCell) * manager->capacity);
		if (!manager->cells) {
			perror("Failed to reallocate MemoryCell array");
			return -1;
		}
	}

	manager->cells[manager->size].name = strdup(name);
	if (!manager->cells[manager->size].name) {
		perror("Failed to allocate memory for variable name");
		return -1;
	}
	manager->cells[manager->size].value = value;
	manager->size++;

	qsort(manager->cells, manager->size, sizeof(MemoryCell), compareMemoryCells);
	return 0;
}

int getValue(MemoryManager *manager, const char *name, int *value) {
	int index = findVariableIndex(manager, name);
	if (index != -1) {
		*value = manager->cells[index].value;
		return 0;
	} else {
		fprintf(stderr, "Error: Variable '%s' not found\n", name);
		return -1;
	}
}

int evaluateExpression(MemoryManager *manager, const char *operand1, char operatorChar, const char *operand2,
                       int *result) {
	int value1 = isdigit(operand1[0]) ? atoi(operand1) : 0;
	if (!isdigit(operand1[0])) {
		if (getValue(manager, operand1, &value1) != 0) return -1;
	}
	int value2 = isdigit(operand2[0]) ? atoi(operand2) : 0;
	if (!isdigit(operand2[0])) {
		if (getValue(manager, operand2, &value2) != 0) return -1;
	}

	switch (operatorChar) {
		case '+':
			*result = value1 + value2;
			break;
		case '-':
			*result = value1 - value2;
			break;
		case '*':
			*result = value1 * value2;
			break;
		case '/':
			if (value2 == 0) {
				fprintf(stderr, "Error: Division by zero\n");
				return -1;
			}
			*result = value1 / value2;
			break;
		case '%':
			if (value2 == 0) {
				fprintf(stderr, "Error: Modulo by zero\n");
				return -1;
			}
			*result = value1 % value2;
			break;
		default:
			fprintf(stderr, "Error: Unsupported operator '%c'\n", operatorChar);
			return -1;
	}
	return 0;
}

int executeInstruction(MemoryManager *manager, const char *instruction) {
	while (isspace(*instruction)) instruction++;
	if (*instruction == '\0') return 0;

	char *varName = malloc(100), *operand1 = malloc(100), *operand2 = malloc(100);
	if (!varName || !operand1 || !operand2) {
		perror("Failed to allocate memory for instruction parsing");
		free(varName);
		free(operand1);
		free(operand2);
		return -1;
	}

	char operatorChar = 0;
	int value = 0;

	if (sscanf(instruction, "%[^=]=%s", varName, operand1) == 2) {
		cleanVariableName(varName);
		cleanVariableName(operand1);

		char *operatorPos = strpbrk(operand1, "+-*/%");
		if (operatorPos) {
			operatorChar = *operatorPos;
			*operatorPos = '\0';
			strcpy(operand2, operatorPos + 1);
			cleanVariableName(operand1);
			cleanVariableName(operand2);
			if (evaluateExpression(manager, operand1, operatorChar, operand2, &value) != 0) {
				free(varName);
				free(operand1);
				free(operand2);
				return -1;
			}
		} else {
			if (isdigit(operand1[0]) || (operand1[0] == '-' && isdigit(operand1[1]))) {
				value = atoi(operand1);
			} else if (getValue(manager, operand1, &value) != 0) {
				free(varName);
				free(operand1);
				free(operand2);
				return -1;
			}
		}
		if (insertOrUpdateVariable(manager, varName, value) != 0) {
			free(varName);
			free(operand1);
			free(operand2);
			return -1;
		}
	} else if (strncmp(instruction, "print", 5) == 0) {
		if (strlen(instruction) > 6) {
			sscanf(instruction + 6, "%s", varName);
			cleanVariableName(varName);
			if (getValue(manager, varName, &value) == 0) {
				printf("%d\n", value);
			} else {
				free(varName);
				free(operand1);
				free(operand2);
				return -1;
			}
		} else {
			for (int i = 0; i < manager->size; i++) {
				printf("%s=%d\n", manager->cells[i].name, manager->cells[i].value);
			}
		}
	} else {
		fprintf(stderr, "Error: Unrecognized instruction '%s'\n", instruction);
		free(varName);
		free(operand1);
		free(operand2);
		return -1;
	}

	free(varName);
	free(operand1);
	free(operand2);
	return 0;
}

void freeMemoryManager(MemoryManager *manager) {
	for (int i = 0; i < manager->size; i++) {
		free(manager->cells[i].name);
	}
	free(manager->cells);
	free(manager);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return EXIT_FAILURE;
	}

	FILE *file = fopen(argv[1], "r");
	if (!file) {
		perror("Error opening file");
		return EXIT_FAILURE;
	}

	MemoryManager *manager = createMemoryManager(10);
	if (!manager) {
		fclose(file);
		return EXIT_FAILURE;
	}

	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, file) != -1) {
		line[strcspn(line, "\n")] = '\0';
		if (executeInstruction(manager, line) != 0) {
			fprintf(stderr, "Error executing instruction: %s\n", line);
		}
	}

	free(line);
	fclose(file);
	freeMemoryManager(manager);
	return EXIT_SUCCESS;
}
