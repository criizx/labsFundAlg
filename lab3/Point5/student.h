#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
	int id;
	char *firstName;
	char *lastName;
	char *group;
	unsigned char *grades;
} Student;

Student *loadStudentsFromFile(const char *filePath, int *count);
void freeStudents(Student *students, int count);
void sortStudents(Student *students, int count, int (*compare)(const void *, const void *));
int searchById(Student *students, int count, int id);
void saveStudentByIdToFile(const Student *students, int count, int id, const char *filePath);
void saveAboveAverageStudentsToFile(const Student *students, int count, const char *filePath);

int compareById(const void *a, const void *b);
int compareByFirstName(const void *a, const void *b);
int compareByLastName(const void *a, const void *b);
int compareByGroup(const void *a, const void *b);

#endif