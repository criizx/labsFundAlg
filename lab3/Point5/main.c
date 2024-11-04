#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

void printStudent(const Student *student) {
	double averageGrade = 0;
	for (int j = 0; j < 5; j++) {
		averageGrade += student->grades[j];
	}
	averageGrade /= 5.0;
	printf("ID: %d, Name: %s %s, Group: %s, Average Grade: %.2f\n", student->id, student->firstName, student->lastName,
	       student->group, averageGrade);
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Usage: %s <input_file> <output_file>\n", argv[0]);
		return 1;
	}

	int studentCount;
	Student *students = loadStudentsFromFile(argv[1], &studentCount);
	if (!students) {
		printf("Error loading students from file.\n");
		return 1;
	}

	int choice;
	while (1) {
		printf(
		    "Choose an action:\n1. Search by ID\n2. Sort\n3. Save student by ID to file\n4. Save students with above "
		    "average to file\n0. Exit\n");
		scanf("%d", &choice);

		switch (choice) {
			case 0:
				printf("Exiting program.\n");
				freeStudents(students, studentCount);
				return 0;

			case 1: {
				int id;
				printf("Enter ID: ");
				scanf("%d", &id);
				int index = searchById(students, studentCount, id);
				if (index != -1) {
					printf("Found student:\n");
					printStudent(&students[index]);
				} else {
					printf("Student not found.\n");
				}
				break;
			}

			case 2: {
				printf("Choose sorting criterion:\n1. By ID\n2. By First Name\n3. By Last Name\n4. By Group\n");
				int sortChoice;
				scanf("%d", &sortChoice);
				switch (sortChoice) {
					case 1:
						sortStudents(students, studentCount, compareById);
						break;
					case 2:
						sortStudents(students, studentCount, compareByFirstName);
						break;
					case 3:
						sortStudents(students, studentCount, compareByLastName);
						break;
					case 4:
						sortStudents(students, studentCount, compareByGroup);
						break;
					default:
						printf("Invalid choice\n");
						break;
				}
				printf("Sorted student list:\n");
				for (int i = 0; i < studentCount; i++) {
					printStudent(&students[i]);
				}
				break;
			}

			case 3: {
				int id;
				printf("Enter ID to save: ");
				scanf("%d", &id);
				saveStudentByIdToFile(students, studentCount, id, argv[2]);
				printf("Student saved to file.\n");
				break;
			}

			case 4: {
				saveAboveAverageStudentsToFile(students, studentCount, argv[2]);
				printf("Above-average students saved to file.\n");
				break;
			}

			default:
				printf("Invalid choice\n");
				break;
		}
	}
}