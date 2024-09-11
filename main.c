#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
  char title[100];
  char author[100];
  int year;
  char isbn[20];
  bool available;
} Book;

#define MAX_BOOKS 100

void addBook(Book library[], int *numBooks)
{
  if (*numBooks >= MAX_BOOKS)
  {
    printf("Library is full.\n");
    return;
  }
  printf("Enter book title: ");
  fgets(library[*numBooks].title, sizeof(library[*numBooks].title), stdin);
  printf("Enter book author: ");
  fgets(library[*numBooks].author, sizeof(library[*numBooks].author), stdin);
  printf("Enter publication year: ");
  scanf("%d", &library[*numBooks].year);
  printf("Enter ISBN: ");
  scanf("%s", library[*numBooks].isbn);
  getchar();

  library[*numBooks].available = true;
  (*numBooks)++;
}

void borrowBook(Book library[], int *numBooks, char *isbn)
{
  for (int i = 0; i < *numBooks; i++)
  {
    if (strcmp(library[i].isbn, isbn) == 0)
    {
      library[i].available = false;
      printf("Book borrowed.\n");
      return;
    }
  }
  printf("Book not found.\n");
}

void removeBook(Book library[], int *numBooks, char *isbn)
{
  for (int i = 0; i < *numBooks; i++)
  {
    if (strcmp(library[i].isbn, isbn) == 0)
    {
      for (int j = i; j < *numBooks - 1; j++)
      {
        library[j] = library[j + 1];
      }
      (*numBooks)--;
      printf("Book removed.\n");
      return;
    }
  }
  printf("Book not found.\n");
}

void listBooks(Book library[], int numBooks)
{
  for (int i = 0; i < numBooks; i++)
  {
    printf("\nTitle: %s", library[i].title);
    printf("Author: %s", library[i].author);
    printf("Year: %d\n", library[i].year);
    printf("ISBN: %s\n", library[i].isbn);
    printf("Available: %s\n\n", (library[i].available?"yes":"no"));
  }
}

void searchBooks(Book library[], int numBooks, char *keyword)
{
  for (int i = 0; i < numBooks; i++)
  {
    if (strstr(library[i].title, keyword) != NULL ||
        strstr(library[i].author, keyword) != NULL)
    {
      printf("Title: %s", library[i].title);
      printf("Author: %s", library[i].author);
      printf("Year: %d\n", library[i].year);
      printf("ISBN: %s\n\n", library[i].isbn);
    }
  }
}

void saveLibrary(Book library[], int numBooks, const char *filename)
{
  FILE *file = fopen(filename, "wb");
  if (file == NULL)
  {
    perror("Error opening file");
    return;
  }
  fwrite(&numBooks, sizeof(int), 1, file);
  fwrite(library, sizeof(Book), numBooks, file);
  fclose(file);
}

void loadLibrary(Book library[], int *numBooks, const char *filename)
{
  FILE *file = fopen(filename, "rb");
  if (file == NULL)
  {
    perror("Error opening file");
    return;
  }
  fread(numBooks, sizeof(int), 1, file);
  fread(library, sizeof(Book), *numBooks, file);
  fclose(file);
}

int main()
{
  Book library[MAX_BOOKS];
  int numBooks = 0;
  int choice;
  char isbn[20];
  char keyword[100];

  while (1)
  {
    printf("1. Add Book\n");
    printf("2. Borrow Book\n");
    printf("3. Remove Book\n");
    printf("4. List Books\n");
    printf("5. Search Books\n");
    printf("6. Save Library\n");
    printf("7. Load Library\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
      addBook(library, &numBooks);
      break;
    case 2:
      printf("Enter ISBN of the book to borrow: ");
      scanf("%s", isbn);
      getchar();
      borrowBook(library,&numBooks,isbn);
      break;
    case 3:
      printf("Enter ISBN of the book to remove: ");
      scanf("%s", isbn);
      getchar();
      removeBook(library, &numBooks, isbn);
      break;
    case 4:
      listBooks(library, numBooks);
      break;
    case 5:
      printf("Enter keyword to search: ");
      fgets(keyword, sizeof(keyword), stdin);
      keyword[strcspn(keyword, "\n")] = 0; // remove newline character
      searchBooks(library, numBooks, keyword);
      break;
    case 6:
      saveLibrary(library, numBooks, "library.dat");
      break;
    case 7:
      loadLibrary(library, &numBooks, "library.dat");
      break;
    case 8:
      return 0;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }
}
