#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_MAX 4096
#define INITIAL_LINE_LENGTH 1024

typedef struct Node {
	char data;
	struct Node** children;
	int childCount;
} Node;

void freeTree(Node* root);

Node* createNode(char data) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (!node) {
		printf("Memory allocation failed for node\n");
		return NULL;
	}
	node->data = data;
	node->children = NULL;
	node->childCount = 0;
	return node;
}

int addChild(Node* parent, Node* child) {
	Node** newChildren = (Node**)realloc(parent->children, (parent->childCount + 1) * sizeof(Node*));
	if (!newChildren) {
		printf("Memory reallocation failed for children\n");
		return -1;
	}
	parent->children = newChildren;
	parent->children[parent->childCount++] = child;
	return 0;
}

char* normalizeExpression(const char* expr) {
	int len = strlen(expr);
	char* result = (char*)malloc(len * 2);
	if (!result) {
		printf("Memory allocation failed for result buffer\n");
		return NULL;
	}

	int start = 0, end = len - 1;
	while (expr[start] == ' ') start++;
	while (expr[end] == ' ') end--;

	if (expr[start] == '(' && expr[end] == ')') {
		int depth = 1, balanced = 1;
		for (int i = start + 1; i < end; i++) {
			if (expr[i] == '(') depth++;
			if (expr[i] == ')') depth--;
			if (depth == 0) {
				balanced = 0;
				break;
			}
		}
		if (balanced) {
			start++;
			end--;
		}
	}

	int i = start, j = 0;
	while (i <= end) {
		if (isspace(expr[i])) {
			i++;
			continue;
		}
		if ((expr[i] == '(' || expr[i] == ',') && j > 0 && result[j - 1] != ' ') {
			result[j++] = ' ';
		}
		result[j++] = expr[i];
		if (expr[i] == ')' && (i + 1 <= end && !isspace(expr[i + 1]))) {
			result[j++] = ' ';
		}
		i++;
	}

	result[j] = '\0';
	return result;
}

Node* parseExpression(const char* expr, int* index) {
	while (expr[*index] == ' ') (*index)++;

	if (expr[*index] == '\0' || expr[*index] == ')') return NULL;

	if (expr[*index] == '(') {
		(*index)++;
	}

	if (expr[*index] == ' ' || expr[*index] == ',') {
		(*index)++;
		return parseExpression(expr, index);
	}

	Node* node = createNode(expr[*index]);
	if (!node) return NULL;

	(*index)++;
	while (expr[*index] == ' ') (*index)++;

	if (expr[*index] == '(') {
		(*index)++;
		while (expr[*index] != ')' && expr[*index] != '\0') {
			Node* child = parseExpression(expr, index);
			if (child) {
				if (addChild(node, child) != 0) {
					freeTree(node);
					return NULL;
				}
			}
			while (expr[*index] == ' ' || expr[*index] == ',') (*index)++;
		}
		if (expr[*index] == ')') (*index)++;
	}

	return node;
}

void printTree(Node* root, FILE* file, int level) {
	if (root == NULL) return;

	if (root->childCount > 0) printTree(root->children[0], file, level + 1);

	for (int i = 0; i < level * 4; i++) fprintf(file, " ");
	fprintf(file, "%c\n", root->data);

	for (int i = 1; i < root->childCount; i++) {
		printTree(root->children[i], file, level + 1);
	}
}

void freeTree(Node* root) {
	for (int i = 0; i < root->childCount; i++) {
		freeTree(root->children[i]);
	}
	free(root->children);
	free(root);
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Usage: %s <input_file> <output_file>\n", argv[0]);
		return 1;
	}

	FILE* inputFile = fopen(argv[1], "r");
	if (!inputFile) {
		printf("Failed to open input file\n");
		return 1;
	}

	FILE* outputFile = fopen(argv[2], "w");
	if (!outputFile) {
		printf("Failed to open output file\n");
		fclose(inputFile);
		return 1;
	}

	size_t lineLength = INITIAL_LINE_LENGTH;
	char* line = (char*)malloc(lineLength);
	if (!line) {
		printf("Memory allocation failed for line buffer\n");
		fclose(inputFile);
		fclose(outputFile);
		return 1;
	}

	while (fgets(line, lineLength, inputFile)) {
		line[strcspn(line, "\n")] = 0;
		if (strlen(line) == 0 || strspn(line, " ") == strlen(line)) {
			continue;
		}

		char* normalizedLine = normalizeExpression(line);
		if (!normalizedLine) {
			printf("Error normalizing expression\n");
			free(line);
			break;
		}

		int index = 0;
		Node* root = parseExpression(normalizedLine, &index);
		if (root) {
			printTree(root, outputFile, 0);
			fprintf(outputFile, "\n");
			freeTree(root);
		} else {
			printf("Error parsing expression: %s\n", normalizedLine);
		}

		free(normalizedLine);
	}

	free(line);
	fclose(inputFile);
	fclose(outputFile);
	return 0;
}
