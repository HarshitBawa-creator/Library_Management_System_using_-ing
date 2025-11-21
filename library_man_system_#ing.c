#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct Book {
    int id;
    char title[50];
    char author[50];
    int quantity;
    struct Book* next;
} Book;

Book* hashTable[SIZE];

int hashFunction(int id) {
    return id % SIZE;
}

void insertBook(int id, char title[], char author[], int quantity) {
    int index = hashFunction(id);

    Book* newBook = (Book*)malloc(sizeof(Book));
    newBook->id = id;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->quantity = quantity;
    newBook->next = NULL;

    if (hashTable[index] == NULL) {
        hashTable[index] = newBook;
    } else {
        Book* temp = hashTable[index];
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newBook;
    }

    printf("\nBook added\n");
}

Book* searchBook(int id) {
    int index = hashFunction(id);
    Book* temp = hashTable[index];

    while (temp != NULL) {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void deleteBook(int id) {
    int index = hashFunction(id);
    Book* temp = hashTable[index];
    Book* prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nBook not\n");
        return;
    }

    if (prev == NULL)
        hashTable[index] = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("\nBook deleted\n");
}

void displayBooks() {
    printf("\nLibrary Books\n");
    for (int i = 0; i < SIZE; i++) {
        Book* temp = hashTable[i];
        if (temp != NULL) {
            printf("\nIndex %d:\n", i);
            while (temp != NULL) {
                printf("ID: %d | Title: %s | Author: %s | Quantity: %d\n",
                       temp->id, temp->title, temp->author, temp->quantity);
                temp = temp->next;
            }
        }
    }
}

int main() {
    int choice, id, quantity;
    char title[50], author[50];

    for (int i = 0; i < SIZE; i++)
        hashTable[i] = NULL;

    while (1) {
        printf("\nLibrary Management System using Hashing\n");
        printf("1. Add Book\n");
        printf("2. Search Book\n");
        printf("3. Delete Book\n");
        printf("4. Display All Books\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Book ID: ");
                scanf("%d", &id);
                printf("Enter Book Title: ");
                scanf("%s", title);
                printf("Enter Author Name: ");
                scanf("%s", author);
                printf("Enter Quantity: ");
                scanf("%d", &quantity);
                insertBook(id, title, author, quantity);
                break;

            case 2: {
                printf("Enter Book ID to search: ");
                scanf("%d", &id);
                Book* found = searchBook(id);
                if (found != NULL)
                    printf("\nFound: %s by %s (Quantity: %d)\n",
                           found->title, found->author, found->quantity);
                else
                    printf("\nBook not found!\n");
                break;
            }

            case 3:
                printf("Enter Book ID to delete: ");
                scanf("%d", &id);
                deleteBook(id);
                break;

            case 4:
                displayBooks();
                break;

            case 5:
                printf("\nExiting program\n");
                exit(0);

            default:
                printf("\nInvalid choice\n");
        }
    }

    return 0;
}
