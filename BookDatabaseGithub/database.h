//database.h

#ifndef DATABASE_H
#define DATABASE_H

#include "book.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>    //reading in files
#include <iomanip>    //formats display
#include <algorithm>  //needed for sorts
#include "cmpt_error.h" //needed for reading in files if error occurs

using namespace std;

class database{
private:
  vector<Book> vectorOfBooks;
  vector<string> rows;
  static const int SPACER = 4;

  void readInFile();
  void writeFile();
  void split();
  int getLongestString(const string& type, const vector<Book>& vectorToPrint);

public:
  database();
  ~database();

  void updateBookRecord(const int& toGet, const int& index, const string& newValue);
  void addBookRecord(Book newBook);
  void deleteBookRecord(const int& indexToRemove);
  vector<Book> getSpecialVector();
  string convertYear(const string& date);
  string convertMonthToWord(const string& date);
  string convertDay(const string& date);
  string convertToReadablePublicationDate(const string& toChange);
  void printVector(const vector<Book> vectorToPrint);
  void sortVector(const string& sortBy, vector<Book>& vectorToSort);
  string changeFromNumToType(const string& numValue);
  string getSortBy();
  string searchFor(const string& category);
  string getDesiredString(const int& index, const string& searchBy, const vector<Book>& vectorOfBooks);
  int binarySearchInclusion(const string& lookFor, const string& searchBy, const vector<Book>& vectorOfBooks, int begin, int end);
  void linearSearchUpInclusion(const string& value, const string& searchBy, const vector<Book>& vectorOfBooks, vector<Book>& searchResults, const int& firstIndex);
  void linearSearchDownInclusion(const string& value, const string& searchBy, const vector<Book>& vectorOfBooks, vector<Book>& searchResults, const int& firstIndex);
  void linearSearchUpExclusion(const string& value, const string& searchBy, const vector<Book>& vectorOfBooks, vector<Book>& searchResults, const int& mid);
  void linearSearchDownExclusion(const string& value, const string& searchBy, const vector<Book>& vectorOfBooks, vector<Book>& searchResults, const int& mid);
  bool validIndex(const int& index);
  void getOrder(vector<Book>& vectorOfSearchResults);
  void simpleSearch(vector<Book>& databaseVector);
  string inclusion(const string& type);
  void advancedSearchInfoGetter(vector<string>& categories, vector<string>& inSearch, const int& index, const string& type);
  void setUpSearchVectorFilters(vector<string>& categories, vector<string>& inSearch);
  void performAdvancedSearch(const string& word, const string& included, vector<Book>& temp, vector<Book>& results, const string& type);
  void searchDisplay(vector<Book>& results);
  void advancedSearch(const vector<Book>& databaseVector);
  static bool byTitle(const Book& first, const Book& second);
  static bool byAuthor(const Book& first, const Book& second);
  static bool byDate(const Book& first, const Book& second);
  static bool byType(const Book& first, const Book& second);
  static bool byISBN(const Book& first, const Book& second);
  static bool byNumPages(const Book& first, const Book& second);

};//database class

#endif
