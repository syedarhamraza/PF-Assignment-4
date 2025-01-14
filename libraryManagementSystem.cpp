#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct library
{
    int id;
    int quantity;
    string title;
    string author;
};

const int maxBooks = 20;
library books[maxBooks];
int bookCount = 0;

void loadBooks()
{
    ifstream mybook("library.txt");
    if (mybook.is_open())
    {
        mybook >> bookCount;
        mybook.ignore();
        for (int i = 0; i < bookCount; i++)
        {
            mybook >> books[i].id;
            mybook.ignore();
            getline(mybook, books[i].title);
            getline(mybook, books[i].author);
            mybook >> books[i].quantity;
        }
    }
    else
    {
        cout << "Error Loading Database!. Starting fresh.";
    }
    mybook.close();
}

bool isBookIdUnique(int userBookId)
{
    for (int i = 0; i < bookCount; i++)
    {
        if (userBookId == books[i].id)
        {
            return false;
        }
    }
    return true;
}

bool isBookTitleUnique(string &userBookTitle)
{
    for (int i = 0; i < bookCount; i++)
    {
        if (userBookTitle == books[i].title)
        {
            return false;
        }
    }
    return true;
}

void addBook()
{
    cout << "**************Library Management System**************" << endl;
    if (bookCount >= maxBooks)
    {
        cout << "\nDatabase is full!\n";
    }
    else
    {
        library book;
        cout << endl;
        cout << endl;
        cout << "Enter Book ID: ";
        cin >> book.id;
        if (isBookIdUnique(book.id) == false)
        {
            for (int i = 0; i < 10; i++)
            {
                cout << endl;
            }
            cout << "\nBook Id Taken!\n";
            return;
        }
        cout << "Enter Book Title: ";
        cin.ignore();
        getline(cin, book.title);
        if (isBookTitleUnique(book.title) == false)
        {
            for (int i = 0; i < 10; i++)
            {
                cout << endl;
            }
            cout << "\nTitle Taken!\n";
            return;
        }
        cout << "Enter Book Author: ";
        getline(cin, book.author);
        cout << "Enter Book Quantity: ";
        cin >> book.quantity;

        books[bookCount] = book;
        bookCount++;
    }
}

void searchBook()
{
    int id;
    cout << "Enter Book ID: ";
    cin >> id;

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == id)
        {
            cout << "Book Found!\n";
            cout << "\n-------------------------------------------------------------\n";
            cout << "Book ID: " << books[i].id << "\n"
                 << "Book Title: " << books[i].title << "\n"
                 << "Book Author: " << books[i].author << "\n"
                 << "Book Quantity: " << books[i].quantity << "\n";
            cout << "-------------------------------------------------------------\n";
        }
    }
}

void displayBooks()
{
    for (int i = 0; i < bookCount; i++)
    {
        cout << "\n-------------------------------------------------------------\n";
        cout << "Book ID: " << books[i].id << "\n"
             << "Book Title: " << books[i].title << "\n"
             << "Book Author: " << books[i].author << "\n"
             << "Book Quantity: " << books[i].quantity << "\n";
        cout << "-------------------------------------------------------------\n";
    }
}

void saveBooks()
{
    ofstream mybook("library.txt");
    if (mybook.is_open())
    {
        cout << endl;
        cout << "Saving Books!";
        mybook << bookCount << endl;
        for (int i = 0; i < bookCount; i++)
        {
            mybook << books[i].id << endl;
            mybook << books[i].title << endl;
            mybook << books[i].author << endl;
            mybook << books[i].quantity << endl;
        }
    }
    else
    {
        cout << "Error Saving Database!";
    }
    mybook.close();
}

void menu()
{
    int choice;
    do
    {
        cout << "\n1. Add a new book to the inventory\n";
        cout << "2. Search for a book by Book ID \n";
        cout << "3. Display all available books\n";
        cout << "4.Exit\n";
        cout << endl;
        cout << "Enter you choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            searchBook();
            break;
        case 3:
            displayBooks();
            break;
        case 4:
            cout << "Closing...";
            break;

        default:
            cout << "Please select a valid option!";
            break;
        }

    } while (choice != 4);
}

int main()
{
    loadBooks();
    menu();
    saveBooks();
    return 0;
}
