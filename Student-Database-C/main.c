#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"

int main() {
    student_t *head = NULL;
    student_t *tail = NULL;
    char lastname[100];

    while (1) {
        int choice;
        printf("1. Add student\n");
        printf("2. Delete student by last name\n");
        printf("3. Print list forward\n");
        printf("4. Print list backward\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                printf("Adding a new student:\n");
                student_t *newStudent = createStudent();
                appendStudent(&head, &tail, newStudent);
                break;
            case 2:
                printf("Enter last name to delete: ");
                fgets(lastname, sizeof(lastname), stdin);
                lastname[strcspn(lastname, "\n")] = '\0'; // Remove the newline character
                deleteStudentsByLastName(&head, &tail, lastname);
                break;
            case 3:
                printf("Printing list forward:\n");
                printListForward(head);
                break;
            case 4:
                printf("Printing list backward:\n");
                printListBackward(tail);
                break;
            case 5:
                printf("Exiting program.\n");
                freeList(head);
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

