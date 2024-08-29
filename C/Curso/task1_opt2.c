# include <stdio.h>
# include <time.h>
# include <stdlib.h>

// Enum constant for identifying each department with an index
typedef enum {HR, Sales, Research, Software, Executive} Department;

// struct for representing an employee
typedef struct {
    Department dept;
    int salary;
    unsigned int social_security;
} Employee;

// functions for random generation

// generate a random salary from a department
int salary_generator(Department d) {
    int base_salary;    // depending on the department
    int offset;     // generate randomly depending also on the department

    switch(d) {
        case HR:
            base_salary = 20000;
            offset = rand() % 10000;
            break;
        case Sales:
            base_salary = 23000;
            offset = rand() % 7000;
            break;
        case Research:
            base_salary = 25000;
            offset = rand() % 15000;
            break;
        case Software:
            base_salary = 35000;
            offset = rand() % 20000;
            break;
        case Executive:
            base_salary = 40000;
            offset = rand() % 20000;
            break;
        default:
            base_salary = offset = 0;
            break;
    }
    return base_salary+offset;
}

// function for printing a string depending on the number of the department (according to the enum constant)
char *get_dept(Department d) {
    switch (d) {
    case HR: return "HR";
    case Sales: return "Sales";
    case Research: return "Research";
    case Software: return "Software";
    case Executive: return "Executive";
    default: return "Unknown";
    }
}

int main(void) {
    Employee employees_arr[10];
    int i;
    unsigned int base_security_number = 1000000000;
    srand(time(NULL));      // to set a seed

    for (i=0; i<10; i++) {
        employees_arr[i].dept = rand() % 5;     // random generation of department
        employees_arr[i].salary = salary_generator(employees_arr[i].dept);
        employees_arr[i].social_security = base_security_number + (rand() % 10000000);
    }
    
    for (i=0; i<10; i++) {
        printf("Employee %d: Department: %s; Salary: %d$; SSN: %u\n", 
        i+1, get_dept(employees_arr[i].dept), employees_arr[i].salary, employees_arr[i].social_security);
    }
}
