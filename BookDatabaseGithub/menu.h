//menu.h

#ifndef MENU_H
#define MENU_H

#include "book.h"
#include "database.h"
#include <string>
#include <vector>

class menu{
  string usersInput;
  vector<string> menuOperations = {"Print the Book Database", "Add New Book Entry", "Update Previous Book Record", "Delete Previous Book Record", "Search Database", "exit()"};
  string currentTask;
  int publicationYear = 0;
  static const char SPACE = 32;
  static const char TAB = 9;
  const vector<string> possibleMonths = {"January", "February", "March", "April", "May", "June" , "July", "August", "September", "October", "November", "December"};
  const vector<int> monthDays = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  static const int tenDigitIsbnSize = 13;                                       //10 digits + 3 hyphens for a total of 13 characters
  static const int thirteenDigitIsbnSize = 17;                                  //13 digits + 4 hyphens for a total of 17 characters
  static const int alottedHyphens = 3;
  static const int isbnYearFormatChange = 2007;
  static const int after_2007_1 = 978;
  static const int after_2007_2 = 979;

  void greeting();
  void printOptionMenu();
  string getUserInput();
  bool validateUserMenuInput(const string& userMenuInput);
  string convertToWord(const string& userInput);

public:
  menu();
  ~menu();

  string getTask() const;
  void setTask(const string& userInput);
  vector<string> getVectorOfTasks() const;
  void menuOptions();
  bool checkForWhitespace(const string& toCheck);
  string getValidTitle();
  string getValidAuthor();
  string convertToProperString(string& toEdit);
  bool validWord(const string& stringToCheck);
  int getMonth();
  string getDay(const int& monthIndex);
  int getCurrentYear();
  void publicationYearSetter(const int& year);
  int publicationYearGetter() const;
  string convertMonthToTwoDigits(const int& monthIndex);
  void convertYearToFourDigits(string& stringToChange);
  string convertYear(const string& date);
  string convertMonthToWord(const string& date);
  string convertDay(const string& date);
  string convertToReadablePublicationDate(const string& toChange);
  string getYear();
  string getValidPublicationDate();
  string getValidBookType();
  bool validPart(const string& partOfIsbn);
  void addToISBN(string& isbn, string& part, int& hyphenCount);
  void printNote();
  bool checkForError(const string& isbn, const int& hyphenCount);
  string getTenDigitISBN();
  string getValidISBN();
  string getValidNumPages();
  void printBook(const Book& bookToPrint);
  Book newBookRecord();
  void printEntryNumAndTitle(const vector<Book>& bookVector);
  int getValidIndex(const vector<Book>& bookVector);
  int getIndexToEdit(const vector<Book>& bookVector);
  int getTypeToEdit();
  string getNewValueToChange(const int& task);
  bool checkValidNumber(const string& toCheck);
  bool trySearchAgain();
  void simpleOrAdvancedSearch(database& bookDatabase, vector<Book>& vectorToSearch);
  void scanAndUpdatePublicationYear(string date);
  bool validChangeYearISBN(const Book& bookToChange);
  string whatISBNSize();
  string newValidISBN();
  void makeValidEntry(database& bookDatabase, const int& index);
  bool noComponents(const string& operation, const int& size);
};



#endif
