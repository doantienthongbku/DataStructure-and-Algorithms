#include <bits/stdc++.h>
using namespace std;


class Book
{
private:
    char* title;
    char* authors;
    int publishingYear;

public:
    Book() {
        this->publishingYear = 0;
        this->title = nullptr;
        this->authors = nullptr;
    }

    Book(const char* title, const char* authors, int publishingYear) {
        this->publishingYear = publishingYear;
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
        this->authors = new char[strlen(authors) + 1];
        strcpy(this->authors, authors);
    }

    Book(const Book &book) {
        this->publishingYear = book.publishingYear;
        this->title = new char[strlen(book.title) + 1];
        strcpy(this->title, book.title);
        this->authors = new char[strlen(book.authors) + 1];
        strcpy(this->authors, book.authors);
    }
    
    void setTitle(const char* title) {
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
    }

    void setAuthors(const char* authors) {
        this->authors = new char[strlen(authors) + 1];
        strcpy(this->authors, authors);
    }

    void setPublishingYear(int publishingYear) {
        this->publishingYear = publishingYear;
    }

    char* getTitle() const {
        return this->title;
    }

    char* getAuthors() const {
        return this->authors;
    }

    int getPublishingYear() const {
        return this->publishingYear;
    }

    ~Book() {
        this->publishingYear = 0;
        this->title = nullptr;
        this->authors = nullptr;
    }

    void printBook(){
        printf("%s\n%s\n%d", this->title, this->authors, this->publishingYear);
    }
};

int main() {
    Book book1("Giai tich 1","Nguyen Dinh Huy",2000);
    Book book2 = book1;
    book2.printBook();
    cout << endl;

    return 0;
}