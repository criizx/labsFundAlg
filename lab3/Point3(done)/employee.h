#ifndef EMPLOYEE_H
#define EMPLOYEE_H

typedef struct {
	int id;
	double salary;
	char *firstName;
	char *lastName;
} Employee;

int readEmployees(const char *inputFile, Employee **employees, int *count);
int writeEmployees(const char *outputFile, Employee *employees, int count);
void freeEmployees(Employee *employees, int count);
int sortEmployees(Employee *employees, int count, int ascending);

#endif
