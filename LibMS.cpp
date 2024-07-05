#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

class Book {
public:
    std::string title;
    std::string author;
    std::string ISBN;
    bool isAvailable;

    Book(std::string t, std::string a, std::string i) : title(t), author(a), ISBN(i), isAvailable(true) {}
};

class Borrower {
public:
    std::string name;
    std::string borrowedBookISBN;
    time_t borrowTime;

    Borrower(std::string n) : name(n), borrowedBookISBN(""), borrowTime(0) {}
};

class Library {
private:
    std::vector<Book> books;
    std::vector<Borrower> borrowers;

    Book* findBookByISBN(const std::string& ISBN) {
        for (auto& book : books) {
            if (book.ISBN == ISBN) return &book;
        }
        return nullptr;
    }

    Borrower* findBorrowerByName(const std::string& name) {
        for (auto& borrower : borrowers) {
            if (borrower.name == name) return &borrower;
        }
        return nullptr;
    }

public:
    void addBook(const std::string& title, const std::string& author, const std::string& ISBN) {
        books.emplace_back(title, author, ISBN);
    }

    void addBorrower(const std::string& name) {
        borrowers.emplace_back(name);
    }

    void searchBook(const std::string& query, const std::string& type) {
        for (const auto& book : books) {
            if ((type == "title" && book.title == query) ||
                (type == "author" && book.author == query) ||
                (type == "ISBN" && book.ISBN == query)) {
                std::cout << "Found Book: " << book.title << " by " << book.author << " (ISBN: " << book.ISBN << ")\n";
                return;
            }
        }
        std::cout << "Book not found.\n";
    }

    void checkoutBook(const std::string& ISBN, const std::string& borrowerName) {
        Book* book = findBookByISBN(ISBN);
        Borrower* borrower = findBorrowerByName(borrowerName);

        if (book && borrower) {
            if (book->isAvailable) {
                book->isAvailable = false;
                borrower->borrowedBookISBN = ISBN;
                borrower->borrowTime = std::time(0);
                std::cout << borrowerName << " has checked out " << book->title << "\n";
            } else {
                std::cout << "Book is already checked out.\n";
            }
        } else {
            std::cout << "Invalid book ISBN or borrower name.\n";
        }
    }

    void returnBook(const std::string& borrowerName) {
        Borrower* borrower = findBorrowerByName(borrowerName);

        if (borrower && !borrower->borrowedBookISBN.empty()) {
            Book* book = findBookByISBN(borrower->borrowedBookISBN);
            if (book) {
                book->isAvailable = true;
                time_t currentTime = std::time(0);
                double days = difftime(currentTime, borrower->borrowTime) / (60 * 60 * 24);
                double fine = days > 14 ? (days - 14) * 0.50 : 0;
                std::cout << borrowerName << " has returned " << book->title << "\n";
                if (fine > 0) {
                    std::cout << "Fine for overdue book: $" << std::fixed << std::setprecision(2) << fine << "\n";
                }
                borrower->borrowedBookISBN.clear();
                borrower->borrowTime = 0;
            }
        } else {
            std::cout << "No book to return for " << borrowerName << ".\n";
        }
    }

    void userInterface() {
        int choice;
        std::string title, author, ISBN, name, type, query;

        while (true) {
            std::cout << "\nLibrary Management System\n";
            std::cout << "1. Add Book\n";
            std::cout << "2. Add Borrower\n";
            std::cout << "3. Search Book\n";
            std::cout << "4. Checkout Book\n";
            std::cout << "5. Return Book\n";
            std::cout << "6. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    std::cout << "Enter title: ";
                    std::cin.ignore();
                    std::getline(std::cin, title);
                    std::cout << "Enter author: ";
                    std::getline(std::cin, author);
                    std::cout << "Enter ISBN: ";
                    std::getline(std::cin, ISBN);
                    addBook(title, author, ISBN);
                    break;
                case 2:
                    std::cout << "Enter borrower name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    addBorrower(name);
                    break;
                case 3:
                    std::cout << "Search by (title/author/ISBN): ";
                    std::cin >> type;
                    std::cout << "Enter search query: ";
                    std::cin.ignore();
                    std::getline(std::cin, query);
                    searchBook(query, type);
                    break;
                case 4:
                    std::cout << "Enter ISBN: ";
                    std::cin >> ISBN;
                    std::cout << "Enter borrower name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    checkoutBook(ISBN, name);
                    break;
                case 5:
                    std::cout << "Enter borrower name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    returnBook(name);
                    break;
                case 6:
                    std::cout << "Exiting...\n";
                    return;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

int main() {
    Library library;
    library.userInterface();
    return 0;
}
