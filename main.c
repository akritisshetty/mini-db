#include <stdio.h>
#include <string.h>
#include "database.h"

int main() {
    char command[100];

    printf("Mini In-Memory Database\n");

    while (1) {
        printf("> ");
        fgets(command, 100, stdin);

        if (strncmp(command, "INSERT", 6) == 0) {
            int id, age;
            float cgpa;
            char name[50];
            sscanf(command, "INSERT %d %s %d %f", &id, name, &age, &cgpa);
            insertRecord(id, name, age, cgpa);
        }

        else if (strncmp(command, "SEARCH", 6) == 0) {
            int id;
            sscanf(command, "SEARCH %d", &id);
            Record *r = searchRecord(id);
            if (r)
                printf("%d %s %d %.2f\n", r->id, r->name, r->age, r->cgpa);
            else
                printf("Not found\n");
        }

        else if (strncmp(command, "DELETE", 6) == 0) {
            int id;
            sscanf(command, "DELETE %d", &id);
            deleteRecord(id);
        }

        else if (strncmp(command, "PRINT", 5) == 0) {
            printAll();
        }

        else if (strncmp(command, "SORT", 4) == 0) {
            sortByAge();
        }

        else if (strncmp(command, "FILTER", 6) == 0) {
            float x;
            sscanf(command, "FILTER %f", &x);
            filterCgpa(x);
        }

        else if (strncmp(command, "HISTORY", 7) == 0) {
            showHistory();
        }

        else if (strncmp(command, "QUEUE", 5) == 0) {
            showQueue();
        }

        else if (strncmp(command, "EXIT", 4) == 0) {
            break;
        }
    }

    return 0;
}

