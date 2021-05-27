//book.h

#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

using namespace std;

class Book{
private:
  string title;
  string author;
  string dateOfPublication;
  string type;
  string ISBN_Num;
  string numPages;

public:
  Book(const string& t, const string& a, const string& d, const string& b, const string& i, const string& num);                        //defined constructor
  ~Book();                                                                      //destructor

  string getTitle() const;                                                      //getters
  string getAuthor() const;
  string getDate() const;
  string getType() const;
  string getISBN() const;
  string getNumPages() const;

  void setTitle(const string& bookTitle);                                       //setters
  void setAuthor(const string& bookAuthor);
  void setDate(const string& bookDatePublication);
  void setType(const string& bookType);
  void setISBN(const string& bookISBN);
  void setNumPages(const string& bookPages);
};

#endif
