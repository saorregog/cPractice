#include <stdio.h>
#include <stdlib.h>

unsigned short magic_string;
unsigned int student_count;
unsigned int course_count;
unsigned int enrollment_count;

unsigned int id_student;
unsigned char flag;
unsigned char *genre;
unsigned char degree;
char student_name[23];
unsigned int student_age;

void main(int argc, char *argv[]) {
    FILE *sample_data = fopen(argv[1], "rb");

    fread(&magic_string, sizeof(magic_string), 1, sample_data);
    fread(&student_count, sizeof(student_count), 1, sample_data);
    fread(&course_count, sizeof(course_count), 1, sample_data);
    fread(&enrollment_count, sizeof(enrollment_count), 1, sample_data);

    for (int i = 0; i <= student_count - 1; i++) {
        fread(&id_student, sizeof(id_student), 1, sample_data);
        fread(&flag, sizeof(flag), 1, sample_data);

        if (flag == 192 || flag == 128) {
            genre = "Female";
        } else {
            genre = "Male";
        };

        fread(student_name, sizeof(student_name), 1, sample_data);
        fread(&student_age, sizeof(student_age), 1, sample_data);

        if (i == 0) {
            puts("-----------------------------------");
            puts("Name                   Age   Gender");
            puts("-----------------------------------");
        }

        if (student_age < atoi(argv[2]) || student_age > atoi(argv[3])) {
            continue;
        }

        printf("%-23s", student_name);
        printf("%-6.u", student_age);
        printf("%s\n", genre);
    }

    fclose(sample_data);
}