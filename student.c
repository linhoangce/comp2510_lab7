//
// Created by linho on 2024-11-07.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "student.h"

// Compare two students based on multiple criteria
int compare_students(const Student *a, const Student *b) {
    int cmp;

    cmp = strcmp(a->last_name, b->last_name);   // Compare last names

    if(cmp != 0) {
        return cmp;
    }

    cmp = strcmp(a->first_name, b->first_name);     // Compare first name

    if(cmp != 0) {
        return cmp;
    }

    cmp = strcmp(a->student_number, b->student_number);

    if(cmp != 0) {
        return cmp;
    }

    if(a->midterm_grade != b->midterm_grade) {
        return a->midterm_grade - b->midterm_grade;
    }

    return a->final_grade - b->final_grade;
}

void merge(Student students[], int left, int mid, int right) {
    int n1 = mid - left + 1;        // size of the left half
    int n2 = right - mid;

    // Allocate memory for temporary arrays
    Student *L = (Student *)malloc(n1 * sizeof(Student));
    Student *R = (Student *)malloc(n2 * sizeof(Student));

    // Copy data into the temporary arrays
    for(int i = 0; i < n1; i++) {
        L[i] = students[left + i];
    }

    for(int i = 0; i < n2; i++) {
        R[i] = students[right + 1];
    }

    // Merge the two halves back into the original array
    int i = 0;
    int j = 0;
    int k = left;
    while(i < n1 && j < n2) {
        if(compare_students(&L[i], &R[j]) <= 0) {
            students[k++] = L[i++];
        } else {
            students[k++] = R[j++];
        }
    }

    // Copy remaining elements from the left half
    while(i < n1) {
        students[k++] = L[i++];
    }

    // Copy remaining elements from the right half
    while(j < n2) {
        students[k++] = R[j++];
    }

    // Free allocated memory
    free(L);
    free(R);
}

void merge_sort(Student students[], int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;    // Calculate the mid point
        merge_sort(students, left, mid);        // Sort the left half
        merge_sort(students, mid + 1, right);     // Sort the right half
        merge(students, left, mid, right);          // Merge the sorted halves
    }
}

// Calculate the average grade of a student
float calculate_average(const Student *student) {
    return (student->midterm_grade + student->final_grade) / 2.0;
}

// Read student data from an input file
int read_students(const char *filename, Student students[], int max_students) {
    FILE *file = fopen(filename, "r");

    if(file == NULL) {
        printf("Error: could not open file %s\n", filename);
        return 0;
    }

    int count = 0;      // Counter for the number of students

    // Read data line by line from the file
    while(count < max_students &&
            fscanf(file, "%s %s %s %d %d",
                students[count].last_name,
                students[count].first_name,
                students[count].student_number,
                students[count].midterm_grade,
                students[count].final_grade) == 5
                ) {
        count++;
    }

    fclose(file);
    return count;
}

// Write the student information into the output file
void write_to_file(const char *filename, const Student students[], int count, int option) {
    FILE *file = fopen(filename, "w");

    if(!file) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    // Loop through each student and filter based on the selected option
    for(int i = 0; i < count; i++) {
        float avg = calculate_average(&students[i]);
        int write = 0;      // Initialize the write flag

        // Determine if the student meets the criteria for the selected option
        switch(option) {
            case 1: if(avg > 90) write = 1; break;
            case 2: if(avg >= 80 && avg <=90) write = 1; break;
            case 3: if(avg >= 70 && avg < 80) write = 1; break;
            case 4: if(avg >= 60 && avg < 70) write = 1; break;
            case 5: if(avg < 60) write = 1; break;
            default: printf("Error: invalid option %d\n", option); return;
        }

        // Write if the student's data meets the criteria
        if(write) {
            fprintf(file, "%s %s %s %d %d %.2f\n",
                    students[i].last_name,
                    students[i].first_name,
                    students[i].student_number,
                    students[i].midterm_grade,
                    students[i].final_grade,
                    avg);
        }
    }

    fclose(file);
}