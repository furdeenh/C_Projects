#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"

// Function to create a new student
student_t *createStudent() {
    student_t *newStudent = (student_t *)malloc(sizeof(student_t));
    if (newStudent == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    printf("Enter last name: ");
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character
    newStudent->lastname = strdup(buffer);

    printf("Enter first name: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character
    newStudent->firstname = strdup(buffer);

    printf("Enter student ID: ");
    scanf("%ld", &newStudent->id);

    printf("Enter Classification: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character
    newStudent->year = strdup(buffer);

    printf("Enter graduation year: ");
    scanf("%d", &newStudent->graduation_year);

    newStudent->next = NULL;
    newStudent->prev = NULL;

    return newStudent;
}

// Function to append a student to the end of the list
void appendStudent(student_t **head, student_t **tail, student_t *newStudent) {
    if (*head == NULL) {
        *head = newStudent;
        *tail = newStudent;
    } else {
        (*tail)->next = newStudent;
        newStudent->prev = *tail;
        *tail = newStudent;
    }
}

// Function to delete students by last name
void deleteStudentsByLastName(student_t **head, student_t **tail, const char *lastname) {
    student_t *current = *head;
    
    while (current != NULL) {
        if (strcmp(current->lastname, lastname) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            if (*head == current) {
                *head = current->next;
            }
            if (*tail == current) {
                *tail = current->prev;
            }
            freeStudent(current);
        }
        current = current->next;
    }
}
/*
// Function to print the list forward
void printListForward(student_t *head) {
    student_t *current = head;
    
    while (current != NULL) {
        printf("Last Name: %s\n", current->lastname);
        printf("First Name: %s\n", current->firstname);
        printf("Student ID: %ld\n", current->id);
        printf("Year: %s\n", current->year);
        printf("Graduation Year: %d\n\n", current->graduation_year);
        current = current->next;
    }
}
*/

void printListForward(student_t *head) {
    student_t *current = head;

    while (current != NULL) {
        printf("%s %s %ld %s %d\n", current->lastname, current->firstname, current->id, current->year, current->graduation_year);
        current = current->next;
    }
}
void printListBackward(student_t *tail) {
    student_t *current = tail;

    while (current != NULL) {
        printf("%d %s %ld %s %s\n", current->graduation_year, current->year, current->id, current->firstname, current->lastname);
        current = current->prev;
    }
}



/*

// Function to print the list backward
void printListBackward(student_t *tail) {
    student_t *current = tail;
    
    while (current != NULL) {
        printf("Last Name: %s\n", current->lastname);
        printf("First Name: %s\n", current->firstname);
        printf("Student ID: %ld\n", current->id);
        printf("Year: %s\n", current->year);
        printf("Graduation Year: %d\n\n", current->graduation_year);
        current = current->prev;
    }
}
*/
// Function to free memory for a student
void freeStudent(student_t *student) {
    free(student->lastname);
    free(student->firstname);
    free(student->year);
    free(student);
}

// Function to free the entire list
void freeList(student_t *head) {
    while (head != NULL) {
        student_t *next = head->next;
        freeStudent(head);
        head = next;
    }
}

