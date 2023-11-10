#include <stdio.h>
#include <string.h>

// Structure definition
struct dob
{
    int day;
    int month;
    int year;
};

struct student_info
{
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};

// Function using call-by-value
void StudentInfoByValue(struct student_info student)
{
    student.roll_no = 665;
    strcpy(student.name, "Nishant Yadav"); 
    student.CGPA = 5.7;
    student.age.day = 11;
    student.age.month = 2;
    student.age.year = 2003;
}

// Function using call-by-address
void StudentInfoByAddress(struct student_info *student)
{
    student->roll_no = 665;
    strcpy(student->name, "Nishant Yadav");
    student->CGPA = 5.7;
    student->age.day = 11;
    student->age.month = 2;
    student->age.year = 2003;
}

int main()
{
    // Create a structure instance and populate its members
    struct student_info student;
    student.roll_no = 646;
    strcpy(student.name, "Akshat Jaiswal");
    student.CGPA = 8.75;
    student.age.day = 3;
    student.age.month = 12;
    student.age.year = 2002;

    // Print the initial values
    printf("Initial Student Info:\n");
    printf("Roll Number: %d\n", student.roll_no);
    printf("Name: %s\n", student.name);
    printf("CGPA: %.2f\n", student.CGPA);
    printf("Date of Birth: %d/%d/%d\n\n", student.age.day, student.age.month, student.age.year);

    // Call the function using call-by-value
    StudentInfoByValue(student);
    printf("Student Info (Call by value):\n");
    printf("Roll Number: %d\n", student.roll_no);
    printf("Name: %s\n", student.name);
    printf("CGPA: %.2f\n", student.CGPA);
    printf("Date of Birth: %d/%d/%d\n\n", student.age.day, student.age.month, student.age.year);
    printf("\n");

    // Call the function using call-by-address
    StudentInfoByAddress(&student);
    printf("Student Info (Call by address):\n");
    printf("Roll Number: %d\n", student.roll_no);
    printf("Name: %s\n", student.name);
    printf("CGPA: %.2f\n", student.CGPA);
    printf("Date of Birth: %d/%d/%d\n\n", student.age.day, student.age.month, student.age.year);
    printf("\n");

    return 0;
}
