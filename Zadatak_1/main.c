#include <stdio.h>
#include <stdlib.h>
#define UKUPNO_BODOVA 100

struct Idiots {
    char name[50];
    char surname[50];
    int points;
};

typedef struct Idiots Student;

int get_lines();
int read_students(int size, Student *students);




int main()
{
 Student *students;
    int lines_to_get;
    int i;


    int line_to_get = get_lines();
    students = (Student *)malloc(sizeof(Student) * line_to_get);
    read_students(line_to_get, students);


    float relative_points;

    printf("Ime Prezime Postotak Bodovi\n");
    for(i=0; i<line_to_get; i++) {
        relative_points = (float)students[i].points / (float)UKUPNO_BODOVA;
        printf(
                "%s %s %.2f %d\n",
                students[i].name,
                students[i].surname,
                relative_points*100,
                students[i].points
        );
    }

    return 0;
}

int get_lines() {


	FILE *file = fopen("Students.txt", "r");

    if(file == NULL) {
        printf("Could not open file !");
        return 0;
    }

    char char_buffer;
    int line_counter = 0;
    while(!feof(file)) {
        char_buffer = fgetc(file);
        if(char_buffer == '\n') {
            line_counter++;
        }
    }

    rewind(file);
    return line_counter;
}

int read_students(int size, Student *students) {


	FILE *file = fopen("Students.txt", "r");

    if(file == NULL) {
        printf("Could not open file !");
        return 1;
    }


    for(int i=0; i<size; i++) {
        fscanf(
                file,
                "%s %s %d",
                students[i].name,
                students[i].surname,
                &students[i].points
        );
    }

	fclose(file);

	return 0;
}
