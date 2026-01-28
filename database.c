#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

#define SIZE 100

/* RECORD */

Record *head = NULL;
Record *hashTable[SIZE];

/* STACK (COMMAND HISTORY) */

typedef struct Stack {
    char cmd[100];
    struct Stack *next;
} Stack;

Stack *stackTop = NULL;

void push(char *cmd) {
    Stack *s = malloc(sizeof(Stack));
    strcpy(s->cmd, cmd);
    s->next = stackTop;
    stackTop = s;
}

void showHistory() {
    Stack *temp = stackTop;
    printf("\nCommand History:\n");
    while (temp) {
        printf("%s\n", temp->cmd);
        temp = temp->next;
    }
}

/* QUEUE (RESULT BUFFER) */

typedef struct Queue {
    char data[100];
    struct Queue *next;
} Queue;

Queue *front = NULL, *rear = NULL;

void enqueue(char *msg) {
    Queue *q = malloc(sizeof(Queue));
    strcpy(q->data, msg);
    q->next = NULL;
    if (!rear) front = rear = q;
    else {
        rear->next = q;
        rear = q;
    }
}

void showQueue() {
    Queue *temp = front;
    printf("\nResult Queue:\n");
    while (temp) {
        printf("%s\n", temp->data);
        temp = temp->next;
    }
}

/* HASH */

int hash(int id) {
    return id % SIZE;
}

/* INSERT */

void insertRecord(int id, char *name, int age, float cgpa) {
    Record *r = malloc(sizeof(Record));
    r->id = id;
    strcpy(r->name, name);
    r->age = age;
    r->cgpa = cgpa;
    r->next = head;
    head = r;

    int idx = hash(id);
    hashTable[idx] = r;

    enqueue("Inserted record");
}

/* SEARCH */

Record* searchRecord(int id) {
    int idx = hash(id);
    return hashTable[idx];
}

/* DELETE */

void deleteRecord(int id) {
    Record *temp = head, *prev = NULL;

    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        enqueue("Record not found");
        return;
    }

    if (!prev) head = temp->next;
    else prev->next = temp->next;

    hashTable[hash(id)] = NULL;
    free(temp);
    enqueue("Record deleted");
}

/* PRINT */

void printAll() {
    Record *temp = head;
    printf("\nAll Records:\n");
    while (temp) {
        printf("%d %s %d %.2f\n",
               temp->id, temp->name, temp->age, temp->cgpa);
        temp = temp->next;
    }
}

/* FILTER */

void filterCgpa(float x) {
    Record *temp = head;
    printf("\nCGPA > %.2f\n", x);
    while (temp) {
        if (temp->cgpa > x)
            printf("%s (%.2f)\n", temp->name, temp->cgpa);
        temp = temp->next;
    }
}

/* BST (SORT) */

typedef struct Node {
    Record *rec;
    struct Node *left, *right;
} Node;

Node* newNode(Record *r) {
    Node *n = malloc(sizeof(Node));
    n->rec = r;
    n->left = n->right = NULL;
    return n;
}

Node* insertBST(Node *root, Record *r) {
    if (!root) return newNode(r);
    if (r->age < root->rec->age)
        root->left = insertBST(root->left, r);
    else
        root->right = insertBST(root->right, r);
    return root;
}

void inorder(Node *root) {
    if (!root) return;
    inorder(root->left);
    printf("%s (%d)\n", root->rec->name, root->rec->age);
    inorder(root->right);
}

void sortByAge() {
    Node *root = NULL;
    Record *temp = head;
    while (temp) {
        root = insertBST(root, temp);
        temp = temp->next;
    }
    printf("\nSorted by Age:\n");
    inorder(root);
}
