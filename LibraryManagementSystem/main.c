#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a file name for saving and loading data
#define FILE_NAME "library_data.txt"

// Define a structure for a book
typedef struct Book {
    int id;                     // Unique book ID
    char title[100];            // Book title
    char author[100];           // Author's name
    int year;                   // Publication year
    struct Book* next;          // Pointer to the next book in the list
} Book;

Book* head = NULL; // Start of the linked list (empty at the beginning)

// Function to create a new book
Book* createBook(int id, char title[], char author[], int year) {
    Book* newBook = (Book*)malloc(sizeof(Book));  // Allocate memory for the new book
    newBook->id = id;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->year = year;
    newBook->next = NULL;  // Set the next pointer to NULL since it's the last book in the list
    return newBook;
}

// Function to add a new book to the library
void addBook(int id, char title[], char author[], int year) {
    Book* newBook = createBook(id, title, author, year);  // Create the new book
    if (head == NULL) {  // If the library is empty, make this book the first book
        head = newBook;
    } else {  // Otherwise, add the book to the end of the list
        Book* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
    printf("Book added successfully!\n");
}

// Function to delete a book by its ID
void deleteBook(int id) {
    if (head == NULL) {  // Check if the library is empty
        printf("No books available to delete.\n");
        return;
    }

    if (head->id == id) {  // If the book to delete is the first one in the list
        Book* temp = head;
        head = head->next;  // Move the head pointer to the next book
        free(temp);  // Free memory for the deleted book
        printf("Book deleted successfully.\n");
        return;
    }

    Book* temp = head;
    while (temp->next != NULL && temp->next->id != id) {  // Search for the book by ID
        temp = temp->next;
    }

    if (temp->next == NULL) {  // If the book is not found
        printf("Book not found.\n");
    } else {  // If the book is found, delete it
        Book* toDelete = temp->next;
        temp->next = toDelete->next;
        free(toDelete);
        printf("Book deleted successfully.\n");
    }
}

// Function to search for a book by title
void searchBook(char title[]) {
    Book* temp = head;
    while (temp != NULL) {  // Go through each book in the list
        if (strcmp(temp->title, title) == 0) {  // Check if the title matches
            printf("Book found: ID: %d, Author: %s, Year: %d\n", temp->id, temp->author, temp->year);
            return;
        }
        temp = temp->next;
    }
    printf("Book not found.\n");  // If no match was found
}

// Function to list all books in the library
void listBooks() {
    if (head == NULL) {
        printf("No books in the library.\n");
        return;
    }
    Book* temp = head;
    while (temp != NULL) {
        printf("ID: %d, Title: %s, Author: %s, Year: %d\n", temp->id, temp->title, temp->author, temp->year);
        temp = temp->next;
    }
}

// Function to save all books to a file
void saveToFile() {
    FILE* file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    Book* temp = head;
    while (temp != NULL) {  // Save each book's data to the file
        fprintf(file, "%d,%s,%s,%d\n", temp->id, temp->title, temp->author, temp->year);
        temp = temp->next;
    }
    fclose(file);
    printf("Library data saved to %s\n", FILE_NAME);
}

// Function to load books from a file
void loadFromFile() {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    head = NULL;  // Clear the current list
    int id, year;
    char title[100], author[100];
    while (fscanf(file, "%d,%99[^,],%99[^,],%d\n", &id, title, author, &year) == 4) {
        addBook(id, title, author, year);  // Rebuild the list with data from the file
    }
    fclose(file);
    printf("Library data loaded from %s\n", FILE_NAME);
}

// Main function
int main() {
    int choice, id, year;
    char title[100], author[100];

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Search Book\n");
        printf("4. List All Books\n");
        printf("5. Save Library\n");
        printf("6. Load Library\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Book ID: ");
                scanf("%d", &id);
                printf("Enter Title: ");
                getchar();  // Clear newline character
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;  // Remove newline from title
                printf("Enter Author: ");
                fgets(author, sizeof(author), stdin);
                author[strcspn(author, "\n")] = 0;  // Remove newline from author
                printf("Enter Year: ");
                scanf("%d", &year);
                addBook(id, title, author, year);
                break;
            case 2:
                printf("Enter Book ID to delete: ");
                scanf("%d", &id);
                deleteBook(id);
                break;
            case 3:
                printf("Enter Title to search: ");
                getchar();  // Clear newline character
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                searchBook(title);
                break;
            case 4:
                listBooks();
                break;
            case 5:
                saveToFile();
                break;
            case 6:
                loadFromFile();
                break;
            case 7:
                printf("Exiting system.\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}
