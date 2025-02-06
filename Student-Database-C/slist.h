#ifndef SLIST_H
#define SLIST_H

typedef struct student {
    char *lastname;
    char *firstname;
    long id;
    char *year;
    int graduation_year;
    struct student *next;
    struct student *prev;
} student_t;

student_t *createStudent();
void appendStudent(student_t **head, student_t **tail, student_t *newStudent);
void deleteStudentsByLastName(student_t **head, student_t **tail, const char *lastname);
void printListForward(student_t *head);
void printListBackward(student_t *tail);
void freeStudent(student_t *student);
void freeList(student_t *head);

#endif /* SLIST_H */

