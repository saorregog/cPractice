#include <stdio.h>
#include <stdlib.h>

unsigned short magic_string;
unsigned int student_count;
unsigned int course_count;
unsigned int enrollment_count;

struct students_info {
    unsigned int id_student;
    unsigned char flag;
    char genre;
    char degree;
    char student_name[23];
    unsigned int student_age;
    unsigned char used;
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

        if (students[i].flag == 192) {
            students[i].genre = 'F';
            students[i].degree = 'G';
        }

        if (students[i].flag == 128) {
            students[i].genre = 'F';
            students[i].degree = 'U';
        }

        if (students[i].flag == 64) {
            students[i].genre = 'M';
            students[i].degree = 'G';
        }

        if (students[i].flag == 0) {
            students[i].genre = 'M';
            students[i].degree = 'U';
        }

        fread(&(students[i].student_name), sizeof(char), 23, sample_data);
        fread(&(students[i].student_age), sizeof(unsigned int), 1, sample_data);

        students[i].used = 0;
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

    // OBTAINING UNIQUE YEARS
    short *years = 0;
    short years_size = 0;
    short exists = 0;

    for (int i = 0; i <= enrollment_count - 1; i++) {
        if (years_size == 0) {
            years = realloc(NULL, (years_size + 1) * sizeof(short));
            years[years_size] = enrollments[i].enrollment_year;
            ++years_size;
            continue;
        }

        exists = 0;

        for (int j = 0; j < years_size; j++) {
            if (years[j] == enrollments[i].enrollment_year) {
                exists = 1;
                break;
            }
        }

        if (exists == 0) {
            years = realloc(years, (years_size + 1) * sizeof(short));
            years[years_size] = enrollments[i].enrollment_year;
            ++years_size;
        }
    }

    // OBTAINING UNIQUE SEMESTERS
    char *semesters = 0;
    char semesters_size = 0;
    exists = 0;

    for (int i = 0; i <= enrollment_count - 1; i++) {
        if (semesters_size == 0) {
            semesters = realloc(NULL, (semesters_size + 1) * sizeof(char));
            semesters[semesters_size] = enrollments[i].enrollment_semester;
            ++semesters_size;
            continue;
        }

        exists = 0;

        for (int j = 0; j < semesters_size; j++) {
            if (semesters[j] == enrollments[i].enrollment_semester) {
                exists = 1;
                break;
            }
        }

        if (exists == 0) {
            semesters = realloc(semesters, (semesters_size + 1) * sizeof(char));
            semesters[semesters_size] = enrollments[i].enrollment_semester;
            ++semesters_size;
        }
    }
    
    // PRINTING
    puts("------------------------------------------------------------------------");
    puts("Year  Semester  Male Undergrad  Female Undergrad  Male Grad  Female Grad");
    puts("------------------------------------------------------------------------");

    for (int i = 0; i <= years_size - 1; i++) {
        for (int j = 0; j <= semesters_size - 1; j++) {
            int m_u = 0;
            int f_u = 0;
            int m_g = 0;
            int f_g = 0;

            for (int k = 0; k <= enrollment_count - 1; k++) {
                if (enrollments[k].enrollment_year == years[i] && enrollments[k].enrollment_semester == semesters[j]) {
                    if (students[enrollments[k].id_student - 1].genre == 'M' && students[enrollments[k].id_student - 1].degree == 'U' && students[enrollments[k].id_student - 1].used == 0) {
                        students[enrollments[k].id_student - 1].used = 1;
                        m_u += 1;
                    }

                    if (students[enrollments[k].id_student - 1].genre == 'F' && students[enrollments[k].id_student - 1].degree == 'U' && students[enrollments[k].id_student - 1].used == 0) {
                        students[enrollments[k].id_student - 1].used = 1;
                        f_u += 1;
                    }

                    if (students[enrollments[k].id_student - 1].genre == 'M' && students[enrollments[k].id_student - 1].degree == 'G' && students[enrollments[k].id_student - 1].used == 0) {
                        students[enrollments[k].id_student - 1].used = 1;
                        m_g += 1;
                    }

                    if (students[enrollments[k].id_student - 1].genre == 'F' && students[enrollments[k].id_student - 1].degree == 'G' && students[enrollments[k].id_student - 1].used == 0) {
                        students[enrollments[k].id_student - 1].used = 1;
                        f_g += 1;
                    }
                }
            }
            for (int l = 0; l <= student_count - 1; l++) {
                if (students[l].used == 1) {
                    students[l].used = 0;
                }
            }
            printf("%-5u %-9u %-15i %-17i %-10i %i\n", years[i], semesters[j], m_u, f_u, m_g, f_g);
        }
    }

    free(years);
    free(semesters);

    fclose(sample_data);
}