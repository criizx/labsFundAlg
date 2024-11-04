#include "student.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Student *loadStudentsFromFile(const char *filePath, int *count) {
    FILE *file = fopen(filePath, "r");
    if (!file) return NULL;

    fscanf(file, "%d", count);
    Student *students = malloc(sizeof(Student) * (*count));
    if (!students) {
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < *count; i++) {
        students[i].grades = malloc(5 * sizeof(unsigned char));
        if (!students[i].grades) {
            freeStudents(students, i);
            fclose(file);
            return NULL;
        }

        fscanf(file, "%d %ms %ms %ms", &students[i].id, &students[i].firstName, &students[i].lastName, &students[i].group);
        
        for (int j = 0; j < 5; j++) {
            fscanf(file, "%hhu", &students[i].grades[j]);
        }
    }

    fclose(file);
    return students;
}

void freeStudents(Student *students, int count) {
    for (int i = 0; i < count; i++) {
        free(students[i].firstName);
        free(students[i].lastName);
        free(students[i].group);
        free(students[i].grades);
    }
    free(students);
}

void sortStudents(Student *students, int count, int (*compare)(const void *, const void *)) {
    qsort(students, count, sizeof(Student), compare);
}

int searchById(Student *students, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) return i;
    }
    return -1;
}

void saveStudentByIdToFile(const Student *students, int count, int id, const char *filePath) {
    FILE *file = fopen(filePath, "w");
    if (!file) return;
    int index = searchById((Student *)students, count, id);
    if (index != -1) {
        double averageGrade = 0;
        for (int j = 0; j < 5; j++) {
            averageGrade += students[index].grades[j];
        }
        averageGrade /= 5.0;
        fprintf(file, "ID: %d, Name: %s %s, Group: %s, Average Grade: %.2f\n", students[index].id,
                students[index].firstName, students[index].lastName, students[index].group, averageGrade);
    }
    fclose(file);
}

void saveAboveAverageStudentsToFile(const Student *students, int count, const char *filePath) {
    FILE *file = fopen(filePath, "w");
    if (!file) return;

    double totalAverage = 0;
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 5; j++) {
            totalAverage += students[i].grades[j];
        }
    }
    totalAverage /= (5.0 * count);

    for (int i = 0; i < count; i++) {
        double averageGrade = 0;
        for (int j = 0; j < 5; j++) {
            averageGrade += students[i].grades[j];
        }
        averageGrade /= 5.0;

        if (averageGrade > totalAverage) {
            fprintf(file, "%s %s, Group: %s, Average Grade: %.2f\n", students[i].lastName, students[i].firstName,
                    students[i].group, averageGrade);
        }
    }
    fclose(file);
}

int compareById(const void *a, const void *b) { return ((Student *)a)->id - ((Student *)b)->id; }

int compareByFirstName(const void *a, const void *b) {
    return strcmp(((Student *)a)->firstName, ((Student *)b)->firstName);
}

int compareByLastName(const void *a, const void *b) {
    return strcmp(((Student *)a)->lastName, ((Student *)b)->lastName);
}

int compareByGroup(const void *a, const void *b) { return strcmp(((Student *)a)->group, ((Student *)b)->group); }
