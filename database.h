#ifndef DATABASE_H
#define DATABASE_H

typedef struct Record {
    int id;
    char name[50];
    int age;
    float cgpa;
    struct Record *next;
} Record;

/* MAJOR DATABASE OPERATIONS */

// Inserts a new record into the database.
void insertRecord(int id, char *name, int age, float cgpa);

// Searches for a record using id.
Record* searchRecord(int id);

// Deletes a record from the database using id.
void deleteRecord(int id);

// Prints all records present in the database.
void printAll();

// Prints records having CGPA greater than given value.
void filterCgpa(float x);

// Displays records sorted by age using BST.
void sortByAge();

/* SUPPORTING DATA STRUCTURES */

// Displays command history using Stack.
void showHistory();

// Displays result messages using Queue.
void showQueue();

#endif
