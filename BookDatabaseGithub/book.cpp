//book.cpp

#include "book.h"


Book::Book(const string& t, const string& a, const string& d, const string& b, const string& i, const string& num)      // defined constructor
: title(t), author(a), dateOfPublication(d), type(b), ISBN_Num(i), numPages(num)
{ }

Book::~Book()
{ }    // destructor


string Book::getTitle() const{
  return title;
}

string Book::getAuthor() const{
  return author;
}

string Book::getDate() const{
  return dateOfPublication;
}

string Book::getType() const{
  return type;
}

string Book::getISBN() const{
  return ISBN_Num;
}

string Book::getNumPages() const{
  return numPages;
}

void Book::setTitle(const string& bookTitle){
  title = bookTitle;
}

void Book::setAuthor(const string& bookAuthor){
  author = bookAuthor;
}

void Book::setDate(const string& bookDatePublication){
  dateOfPublication = bookDatePublication;
}

void Book::setType(const string& bookType){
  type = bookType;
}

void Book::setISBN(const string& bookISBN){
  ISBN_Num = bookISBN;
}

void Book::setNumPages(const string& bookPages){
  numPages = bookPages;
}
