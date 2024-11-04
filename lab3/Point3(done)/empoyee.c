#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "employee.h"

int compareEmployeesAsc(const void *a, const void *b) {
	Employee *emp1 = (Employee *)a;
	Employee *emp2 = (Employee *)b;
	if (emp1->salary != emp2->salary) return (emp1->salary > emp2->salary) - (emp1->salary < emp2->salary);
	int lastNameCmp = strcmp(emp1->lastName, emp2->lastName);
	if (lastNameCmp != 0) return lastNameCmp;
	int firstNameCmp = strcmp(emp1->firstName, emp2->firstName);
	if (firstNameCmp != 0) return firstNameCmp;
	return emp1->id - emp2->id;
}

int compareEmployeesDesc(const void *a, const void *b) {
	Employee *emp1 = (Employee *)a;
	Employee *emp2 = (Employee *)b;
	if (emp1->salary != emp2->salary) return (emp1->salary < emp2->salary) - (emp1->salary > emp2->salary);
	int lastNameCmp = strcmp(emp1->lastName, emp2->lastName);
	if (lastNameCmp != 0) return -lastNameCmp;
	int firstNameCmp = strcmp(emp1->firstName, emp2->firstName);
	if (firstNameCmp != 0) return -firstNameCmp;
	return emp2->id - emp1->id;
}

int sortEmployees(Employee *employees, int count, int ascending) {
	if (employees == NULL || count <= 0) {
		return -1;
	}
	if (ascending) {
		qsort(employees, count, sizeof(Employee), compareEmployeesAsc);
	} else {
		qsort(employees, count, sizeof(Employee), compareEmployeesDesc);
	}
	return 0;
}
int readEmployees(const char *inputFile, Employee **employees, int *count) {
	FILE *file = fopen(inputFile, "r");
	if (!file) {
		return -1;
	}
	*count = 0;
	*employees = NULL;
	int id;
	double salary;
	while (fscanf(file, "%d %lf", &id, &salary) == 2) {
		Employee *temp = realloc(*employees, (*count + 1) * sizeof(Employee));
		if (!temp) {
			fclose(file);
			freeEmployees(*employees, *count);
			return -2;
		}
		*employees = temp;

		(*employees)[*count].id = id;
		(*employees)[*count].salary = salary;
		(*employees)[*count].firstName = NULL;
		int len = 0, capacity = 10;
		(*employees)[*count].firstName = malloc(capacity);
		if (!(*employees)[*count].firstName) {
			fclose(file);
			freeEmployees(*employees, *count);
			return -3;
		}
		int ch = fgetc(file);

		while ((ch = fgetc(file)) != ' ' && ch != EOF && ch != '\n') {
			(*employees)[*count].firstName[len++] = ch;
			if (len >= capacity) {
				capacity *= 2;
				char *newName = realloc((*employees)[*count].firstName, capacity);
				if (!newName) {
					fclose(file);
					freeEmployees(*employees, *count);
					return -3;
				}
				(*employees)[*count].firstName = newName;
			}
		}
		(*employees)[*count].firstName[len] = '\0';

		(*employees)[*count].lastName = NULL;
		len = 0;
		capacity = 10;
		(*employees)[*count].lastName = malloc(capacity);
		if (!(*employees)[*count].lastName) {
			fclose(file);
			freeEmployees(*employees, *count);
			return -3;
		}
		while ((ch = fgetc(file)) != ' ' && ch != EOF && ch != '\n') {
			(*employees)[*count].lastName[len++] = ch;
			if (len >= capacity) {
				capacity *= 2;
				char *newName = realloc((*employees)[*count].lastName, capacity);
				if (!newName) {
					fclose(file);
					freeEmployees(*employees, *count);
					return -3;
				}
				(*employees)[*count].lastName = newName;
			}
		}
		(*employees)[*count].lastName[len] = '\0';

		(*count)++;
	}

	fclose(file);
	return 0;
}

int writeEmployees(const char *outputFile, Employee *employees, int count) {
	FILE *file = fopen(outputFile, "w");
	if (!file) {
		return -1;
	}
	for (int i = 0; i < count; i++) {
		fprintf(file, "%d %s %s %.2f\n", employees[i].id, employees[i].firstName, employees[i].lastName,
		        employees[i].salary);
	}
	fclose(file);
	return 0;
}

void freeEmployees(Employee *employees, int count) {
	for (int i = 0; i < count; i++) {
		free(employees[i].firstName);
		free(employees[i].lastName);
	}
	free(employees);
}
