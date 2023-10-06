#include <stdio.h>

unsigned short magic_string;
unsigned int student_count;
unsigned int course_count;
unsigned int enrollment_count;

struct students_info {
    unsigned int id_student;
    unsigned char flag;
    char student_name[23];
    unsigned int student_age;
};

struct courses_info {
    unsigned int id_course;
    char course_name[32];
    unsigned int course_hours;
};

struct enrollments_info {
    unsigned int id_student;
    unsigned int id_course;
    unsigned int enrollment_year;
    unsigned int enrollment_semester;
};

void main(int argc, char *argv[]) {
    FILE *sample_data = fopen(argv[1], "rb");

    fread(&magic_string, sizeof(magic_string), 1, sample_data);
    fread(&student_count, sizeof(student_count), 1, sample_data);
    fread(&course_count, sizeof(course_count), 1, sample_data);
    fread(&enrollment_count, sizeof(enrollment_count), 1, sample_data);

    // READING AND SAVING STUDENTS
    struct students_info students[student_count] = {};

    for (int i = 0; i <= student_count - 1; i++) {
        fread(&(students[i].id_student), sizeof(unsigned int), 1, sample_data);
        fread(&(students[i].flag), sizeof(unsigned char), 1, sample_data);
        fread(&(students[i].student_name), sizeof(char), 23, sample_data);
        fread(&(students[i].student_age), sizeof(unsigned int), 1, sample_data);
    }

    // READING AND SAVING COURSES
    struct courses_info courses[course_count] = {};

    for (int i = 0; i <= course_count - 1; i++) {
        fread(&(courses[i].id_course), sizeof(unsigned int), 1, sample_data);
        fread(&(courses[i].course_name), sizeof(char), 32, sample_data);
        fread(&(courses[i].course_hours), sizeof(unsigned int), 1, sample_data);
    }

    // READING AND SAVING ENROLLMENTS
    struct enrollments_info enrollments[enrollment_count] = {};

    for (int i = 0; i <= enrollment_count - 1; i++) {
        fread(&(enrollments[i].id_student), sizeof(unsigned int), 1, sample_data);
        fread(&(enrollments[i].id_course), sizeof(unsigned int), 1, sample_data);
        fread(&(enrollments[i].enrollment_year), sizeof(unsigned int), 1, sample_data);
        fread(&(enrollments[i].enrollment_semester), sizeof(unsigned int), 1, sample_data);
    }

    puts("---------------------------------------------------");
    puts("Course Name                             Average Age");
    puts("---------------------------------------------------");

    for (int i = 0; i <= course_count - 1; i++) {
        unsigned int sum = 0;
        unsigned int count = 0;

        for (int j = 0; j <= enrollment_count - 1; j++) {
            if (courses[i].id_course == enrollments[j].id_course) {
                sum += students[enrollments[j].id_student - 1].student_age;
                count += 1;
            }
        }

        printf("%-40s", courses[i].course_name);
        printf("%.1f\n", (float) sum / (float) count);
    }

    fclose(sample_data);
}