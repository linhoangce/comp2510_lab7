#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    char last_name[50];
    char first_name[50];
    char student_number[10];
    int midterm_grade;
    int final_grade;
} Student;

// Function Prototype
int compare_students(const Student *a, const Student *b);
void merge_sort(Student students[], int left, int right);
float calculate_average(const Student *student);
int read_students(const char *filename, Student students[], int max_student);
void write_to_file(const char *filename, const Student students[], int count, int option);

#endif