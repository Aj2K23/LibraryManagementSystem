Struct Definition:

Book struct stores each book’s attributes (bookID, title, author, and publicationYear) and a pointer to the next Book in the linked list.
Functions:

createBook(): Allocates memory for a new Book and initializes its data.
addBook(): Adds a new book to the end of the list.
deleteBook(): Removes a book with a given bookID.
searchBook(): Searches for a book by title.
listBooks(): Lists all books in the library.
saveToFile(): Saves the linked list data to a file.
loadFromFile(): Loads book data from a file into the linked list.