#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NAME_LENGTH 50
#define MAX_REG_NO_LENGTH 20
#define MAX_STUDENTS 5

typedef struct {
    char name[MAX_NAME_LENGTH];
    char reg_no[MAX_REG_NO_LENGTH];
    int age;
} Student;

void* print_student(void* arg) {
    Student* student = (Student*)arg;
    printf("Name: %s, Registration Number: %s, Age: %d\n", student->name, student->reg_no, student->age);
    pthread_exit(NULL);
}

int main() {
    int num_students;
    printf("Enter the number of students: ");
    scanf("%d", &num_students);

    if (num_students > MAX_STUDENTS) {
        printf("Number of students exceeds the maximum limit.\n");
        return 1;
    }

    pthread_t threads[MAX_STUDENTS];
    Student students[MAX_STUDENTS];

    for (int i = 0; i < num_students; i++) {
        printf("Enter details for Student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].name);
        printf("Registration Number: ");
        scanf("%s", students[i].reg_no);
        printf("Age: ");
        scanf("%d", &students[i].age);
    }

    // Create threads and print student details
    for (int i = 0; i < num_students; i++) {
        pthread_create(&threads[i], NULL, print_student, (void*)&students[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < num_students; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
