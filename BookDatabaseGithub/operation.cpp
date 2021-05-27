#include "book.h"
#include "database.h"
#include "menu.h"


void addBookRecord(database& bookDatabase, menu& menu){
  Book newBook = menu.newBookRecord();
  bookDatabase.addBookRecord(newBook);
}

void updateBookRecord(database& bookDatabase, vector<Book>& databaseVector, menu& menu, const vector<string>& vectorOfTasks){
  if(menu.noComponents(vectorOfTasks.at(2), databaseVector.size()) == true) return;  //will not perform operation if database is empty
  int indexToChange = menu.getIndexToEdit(databaseVector);                      //get an index from user
  Book bookToChange = databaseVector.at(indexToChange);                         //makes a copy of the book at the index
  menu.printBook(bookToChange);
  int typeToEdit = menu.getTypeToEdit();                                        //get a book characteristic to edit from user

  string newValue = menu.getNewValueToChange(typeToEdit);                       //gets the new value the user wants to change
  bookDatabase.updateBookRecord(typeToEdit, indexToChange, newValue);           //updates the record with the desired value

  while(true){
    databaseVector = bookDatabase.getSpecialVector();                           //gets the updated database vector for validity
    bookToChange = databaseVector.at(indexToChange);                            //gets the updated Book to check for validity
    bool isValid = menu.validChangeYearISBN(bookToChange);                      //checks publication year and ISBN to make sure they are valid
    if(isValid == true) break;                                                  //will not break out of loop until user has valid data for the Book at the index
    menu.makeValidEntry(bookDatabase, indexToChange);                           //implimentation for changing the invalid values
  }
}

void deleteBookRecord(database& bookDatabase, const vector<Book>& databaseVector, menu& menu, const vector<string>& vectorOfTasks){
  if(menu.noComponents(vectorOfTasks.at(3), databaseVector.size()) == true) return;  //will not perform operation if database is empty
  int indexToRemove = menu.getIndexToEdit(databaseVector);                  //gets an index for a Book Record to be deleted from the user
  bookDatabase.deleteBookRecord(indexToRemove);                             //erases Book from database
  cout << "\'" << databaseVector.at(indexToRemove).getTitle() << "\' has been permanently deleted..." << endl;
}

void operation(){
  database bookDatabase;                                                        //creates a database object
  menu menu;                                                                    //creates a menu object that interacts with the user
  vector<string> vectorOfTasks = menu.getVectorOfTasks();
  vector<Book> databaseVector = {};
  string task;

  while(true){
    databaseVector = bookDatabase.getSpecialVector();                           //gets the vector containing the Book contents
    menu.menuOptions();
    task = menu.getTask();
    cout << "The \'" << task << "\' has been selected..." << endl << endl;
    if(task == vectorOfTasks.at(0)){
      bookDatabase.printVector(databaseVector);
    }else if(task == vectorOfTasks.at(1)){
      addBookRecord(bookDatabase, menu);
    }else if(task == vectorOfTasks.at(2)){
      updateBookRecord(bookDatabase, databaseVector, menu, vectorOfTasks);
    }else if(task == vectorOfTasks.at(3)){
      deleteBookRecord(bookDatabase, databaseVector, menu, vectorOfTasks);
    }else if(task == vectorOfTasks.at(4)){
      menu.simpleOrAdvancedSearch(bookDatabase, databaseVector);
    }else{
      cout << "... Now Closing Database." << endl;
      break;
    }
  }
}

int main(){
  operation();
}
