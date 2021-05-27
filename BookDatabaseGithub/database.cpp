//database.cpp

#include "database.h"

using namespace std;


void database::readInFile(){
  ifstream inFile;                                                              //creates a object that can be read in
  inFile.open("books.txt");                                                     //opens the test file

  if(inFile.fail()){
    cmpt::error("unable to open, program terminated..." );                       //throws an error and terminates the program if file cannot be opened
  }
  string row;
  while(true){                                                                  //loops through items in the file by line
    getline(inFile, row);
    if(inFile.fail() || row.empty()){
      break;
    }
    rows.push_back(row);                                                        //adds the items to a vector of strings
  }
  inFile.close();                                                               //closes the file
}


void database::writeFile(){
  ofstream fileOut;                                                             //creates and object that can write output
  fileOut.open("books.txt");                                                    //opens the file

  if(fileOut.fail()){
    cmpt::error("unable to open, program terminated...");                       // terminates the program if file cannot be opened
  }
  for(int i = 0; i < vectorOfBooks.size(); i++){                                //loops through items in Book vector, creates a string out of the strings, concatenates and writes to the file
    string output = (vectorOfBooks.at(i).getTitle() + '|'
                  + vectorOfBooks.at(i).getAuthor() + '|'
                  + vectorOfBooks.at(i).getDate() + '|'
                  + vectorOfBooks.at(i).getType() + '|'
                  + vectorOfBooks.at(i).getISBN() + '|'
                  + vectorOfBooks.at(i).getNumPages() + '|'
                );
    fileOut << output << endl;
  }
  fileOut.close();                                                              //closes the file
}


void database::split(){
  //scan through string, elements separated by '|'                              //LIMITATION, the book cannot have a '|' in any of its contents
    for(int i = 0; i < rows.size(); i++){                                       //loops through string vector, creating a new vector for each row
      vector<string> temp;
      int startIndex = 0;
      int size = 0;
      string currentString = rows.at(i);                                        //gets the current row string
      string edited;
      for(int j = startIndex; j < currentString.size(); j++){
        size++;                                                                 //increases the size variable each time through loop
        if(currentString.at(j) == '|'){
          if(currentString.at(startIndex) == '|'){                              //increases the start index by one to avoid adding a '|' to the value
            startIndex++;
          }
          edited = currentString.substr(startIndex, size - 1);                  //creates a substring based on starting index and size
          temp.push_back(edited);                                               //adds the substring to a temp vector
          startIndex = j;                                                       //resets the starting index to be the current index
          size = 0;                                                             //resets the size for next time substr() is used
        }
      }
      Book currentBook(temp.at(0), temp.at(1), temp.at(2), temp.at(3), temp.at(4), temp.at(5));   // creates a new book object and initializes its values based on whats in temp vec
      vectorOfBooks.push_back(currentBook);                                     //adds the newly created book object to a vector of Books
    }
}


int database::getLongestString(const string& type, const vector<Book>& vectorToPrint){    //gets the longest strings for each column to ensure column values and headers allign
  int longestStringValue = type.size();                                         //Ensures the length cannot be less than the header type
  string temp;
  for(int i = 0; i < vectorToPrint.size(); i++){
    if(type == "Title") temp = vectorToPrint.at(i).getTitle();
    else if(type == "Author") temp = vectorToPrint.at(i).getAuthor();
    else if(type == "Publication Date") temp = vectorToPrint.at(i).getDate();
    else if(type == "Book Type") temp = vectorToPrint.at(i).getType();
    else if(type == "ISBN Number") temp = vectorToPrint.at(i).getISBN();
    else if(type == "Number of Pages") temp = vectorToPrint.at(i).getNumPages();
    if(temp.size() > longestStringValue){
      longestStringValue = temp.size();
    }
  }
  return longestStringValue;
}


database::database(){
    readInFile();
    split();
}


database::~database(){
    writeFile();
}


void database::updateBookRecord(const int& toGet, const int& index, const string& newValue){
    if(toGet == 1) vectorOfBooks.at(index).setTitle(newValue);
    else if(toGet == 2) vectorOfBooks.at(index).setAuthor(newValue);
    else if(toGet == 3) vectorOfBooks.at(index).setDate(newValue);
    else if(toGet == 4) vectorOfBooks.at(index).setType(newValue);
    else if(toGet == 5) vectorOfBooks.at(index).setISBN(newValue);
    else if(toGet == 6) vectorOfBooks.at(index).setNumPages(newValue);
}


void database::addBookRecord(Book newBook){
    vectorOfBooks.push_back(newBook);                                           //adds the new Book object entry to the vectorOfBooks (database)
    cout << "The Book \'" << newBook.getTitle() << "\' Has Been Successfully Added To The Database." << endl;
}


void database::deleteBookRecord(const int& indexToRemove){
    vectorOfBooks.erase(vectorOfBooks.begin() + indexToRemove);
}


vector<Book> database::getSpecialVector(){
    return vectorOfBooks;
}


string database::convertYear(const string& date){
    string year = date.substr(0, 5);                                            //makes a substring for the first 5 characters in data string (YYYY-)
    for(int i = 0; i < year.size(); i++){
      if(year.at(i) != '0'){                                                    //as soon as loop hits first non-zero, it creates a substring for the year to rid beginning zeros
        year = year.substr(i, year.size() - i);
        break;
      }
    }
    return year;
}


string database::convertMonthToWord(const string& date){
    string numericalMonth = date.substr(5, 2);                                  //makes a substring for the two characters that characterize the month (MM)
    if(numericalMonth == "01") return "January";
    else if(numericalMonth == "02") return "February";
    else if(numericalMonth == "03") return "March";
    else if(numericalMonth == "04") return "April";
    else if(numericalMonth == "05") return "May";
    else if(numericalMonth == "06") return "June";
    else if(numericalMonth == "07") return "July";
    else if(numericalMonth == "08") return "August";
    else if(numericalMonth == "09") return "September";
    else if(numericalMonth == "10") return "October";
    else if(numericalMonth == "11") return "November";
    else return "December";
}


string database::convertDay(const string& date){
    string day = date.substr(7,3);                                              //makes a substring for the separation hyphen and two digits that characterize the day (-DD)
    if(day == "-00") return "";
    return day;
}


string database::convertToReadablePublicationDate(const string& toChange){
    string year = convertYear(toChange);                                        //creates a substring for the year
    string month = convertMonthToWord(toChange);                                //creates a substring and converts to a month
    string day = convertDay(toChange);                                          //creates empty string if day is "00"

    return year + month + day;                                                  //newly concatenated string formed via new substring values
}


void database::printVector(const vector<Book> vectorToPrint){                    //creates a dynamic table, adjusts based on longest string for the header, if size < header, header.size() is length
    int titleWidth = getLongestString("Title", vectorToPrint) + SPACER;
    int authorWidth = getLongestString("Author", vectorToPrint) + SPACER;
    int publicationDateWidth = getLongestString("Publication Date", vectorToPrint) + SPACER;
    int bookTypeWidth = getLongestString("Book Type", vectorToPrint) + SPACER;
    int isbnNumberWidth = getLongestString("ISBN Number", vectorToPrint) + SPACER;
    int numberOfPagesWidth = getLongestString("Number of Pages", vectorToPrint) + SPACER;
    cout << endl << endl;
    cout << setw(titleWidth) << left << "Title"                                  //http://www.cplusplus.com/reference/ios/left/    left -> shifts all strings to the left when using the setw function
         << setw(authorWidth) << left << "Author"
         << setw(publicationDateWidth) << left << "Publication Date"
         << setw(bookTypeWidth) << left << "Book Type"
         << setw(isbnNumberWidth) << left << "ISBN Number"
         << setw(numberOfPagesWidth) << left << "Number of Pages"  << endl << endl;

    for(int i = 0; i < vectorToPrint.size(); i++){
      cout << setw(titleWidth) << left << vectorToPrint.at(i).getTitle();
      cout << setw(authorWidth) << left << vectorToPrint.at(i).getAuthor();
      cout << setw(publicationDateWidth) << left << convertToReadablePublicationDate(vectorToPrint.at(i).getDate());
      cout << setw(bookTypeWidth) << left << vectorToPrint.at(i).getType();
      cout << setw(isbnNumberWidth) << left << vectorToPrint.at(i).getISBN();
      cout << setw(numberOfPagesWidth) << left << vectorToPrint.at(i).getNumPages() << endl;
    }
    cout << endl << endl;
}


void database::sortVector(const string& sortBy, vector<Book>& vectorToSort){
    if(sortBy == "Title"){
      sort(vectorToSort.begin(), vectorToSort.end(), byTitle);                  //sort by title
    }else if(sortBy == "Author"){
      sort(vectorToSort.begin(), vectorToSort.end(), byAuthor);                 //sort by author
    }else if(sortBy == "Publication Date"){
      sort(vectorToSort.begin(), vectorToSort.end(), byDate);                   //sort by date
    }else if(sortBy == "Book Type"){
      sort(vectorToSort.begin(), vectorToSort.end(), byType);                   //sort by type
    }else if(sortBy  == "ISBN Number"){
      sort(vectorToSort.begin(), vectorToSort.end(), byISBN);                   //sort by isbn
    }else if(sortBy == "Number Of Pages"){
      sort(vectorToSort.begin(), vectorToSort.end(), byNumPages);               //sort by number of pages
    }
}


string database::changeFromNumToType(const string& numValue){
    if(numValue == "1") return "Title";
    else if(numValue == "2") return "Author";
    else if(numValue == "3") return "Publication Date";
    else if(numValue == "4") return "Book Type";
    else if(numValue == "5") return "ISBN Number";
    else return "Number Of Pages";
}


string database::getSortBy(){
    string sortBy;
    cout << "1 - By \'Title\'" << endl
         << "2 - By \'Author\'" << endl
         << "3 - By \'Publication Date\'" << endl
         << "4 - By \'Book Type\'" << endl
         << "5 - By \'ISBN Number\'" << endl
         << "6 - By \'Number Of Pages\'" << endl;
    cout << "Please Enter the Numerical Value Corresponding to the Category: ";
    while(getline(cin, sortBy)){
      if(sortBy != "1" && sortBy != "2" && sortBy != "3" && sortBy != "4" && sortBy != "5" && sortBy != "6"){
        cout << "Sorry, \'" << sortBy << "\' Is Not A Valid Option, Please try again By Entering A Numerical Value Between \'1\' and \'6\'... ";
        continue;
      }
      break;
    }
    sortBy = changeFromNumToType(sortBy);
    return sortBy;
}


string database::searchFor(const string& category){
    string searchFor;
    cout << "What \'" << category << "\' would you like to Search for (case sensitive): ";
    getline(cin, searchFor);
    return searchFor;
}


string database::getDesiredString(const int& index, const string& searchBy, const vector<Book>& vectorOfBooks){       //gets the string defined by type at the index
    if(searchBy == "Title") return vectorOfBooks.at(index).getTitle();
    else if(searchBy == "Author") return vectorOfBooks.at(index).getAuthor();
    else if(searchBy == "Publication Date") return vectorOfBooks.at(index).getDate();
    else if(searchBy == "Book Type") return vectorOfBooks.at(index).getType();
    else if(searchBy == "ISBN Number") return vectorOfBooks.at(index).getISBN();
    else return vectorOfBooks.at(index).getNumPages();
}


int database::binarySearchInclusion(const string& lookFor, const string& searchBy, const vector<Book>& vectorOfBooks, int begin, int end){
    while(begin < end){
      int mid = (begin + end) / 2;
      string value = getDesiredString(mid, searchBy, vectorOfBooks);            //gets the string defined by type at the index
      if(value == lookFor){
          return mid;
      }else if(lookFor < value){
        end = mid;
      }else if(lookFor > value){
        begin = mid + 1;
      }
    }
    return -1;
}


void database::linearSearchUpInclusion(const string& value, const string& searchBy, const vector<Book>& vectorOfBooks, vector<Book>& searchResults, const int& firstIndex){
    for(int i = firstIndex + 1; i < vectorOfBooks.size(); i++){
      string valueAtIndex = getDesiredString(i, searchBy, vectorOfBooks);
      if(value == valueAtIndex){
        searchResults.push_back(vectorOfBooks.at(i));
      }else{
        break;
      }
    }
}// looks at indices greater than index found in binary search, if value at index is same as value at binary search index, adds the book object to a vector


void database::linearSearchDownInclusion(const string& value, const string& searchBy, const vector<Book>& vectorOfBooks, vector<Book>& searchResults, const int& firstIndex){
    for(int i = firstIndex; i >= 0; i--){
      string valueAtIndex = getDesiredString(i, searchBy, vectorOfBooks);
      if(value == valueAtIndex){
        searchResults.push_back(vectorOfBooks.at(i));
      }else{
        break;
      }
    }
}// looks at indices less than and equal to index found in binary search, if value at index is same as value at binary search index, adds the book object to a vector


void database::linearSearchUpExclusion(const string& value, const string& searchBy, const vector<Book>& vectorOfBooks, vector<Book>& searchResults, const int& mid){
    for(int i = mid + 1; i < vectorOfBooks.size(); i++){
      string valueAtIndex = getDesiredString(i, searchBy, vectorOfBooks);
      if(value != valueAtIndex){                                                //if value cannot equal desired value at index, adds the books from current position to end
        for(int j = i; j < vectorOfBooks.size(); j++){
          searchResults.push_back(vectorOfBooks.at(j));
        }
        break;
      }
    }
}// looks at indices greater than index found in binary search, if value at index is NOT same as value at binary search index, adds the book object to a vector


void database::linearSearchDownExclusion(const string& value, const string& searchBy, const vector<Book>& vectorOfBooks, vector<Book>& searchResults, const int& mid){
    for(int i = mid; i >= 0; i--){
      string valueAtIndex = getDesiredString(i, searchBy, vectorOfBooks);
      if(value != valueAtIndex){                                                //if value cannot equal desired value at index, adds the books from current position to beginning
        for(int j = i; j >= 0; j--){
          searchResults.push_back(vectorOfBooks.at(j));
        }
        break;
      }
    }
}// looks at indices less than and equal to index found in binary search, if value at index is NOT same as value at binary search index, adds the book object to a vector


bool database::validIndex(const int& index){                                            //used to determine if binary search found a value
    if(index == -1){
      return false;
    }
    return true;
}


void database::getOrder(vector<Book>& vectorOfSearchResults){
    cout << "1 - Ascending Order" << endl
         << "2 - Descending Order" << endl << endl
         << "Press Numerical Key That Coresponds With Value: ";
    string userOrder;
    while(getline(cin, userOrder)){
      if(userOrder == "1"){
        break;
      }else if(userOrder == "2"){
        reverse(vectorOfSearchResults.begin(), vectorOfSearchResults.end());
        break;
      }
      cout << "Sorry, \'" << userOrder << "\' Is Not Valid, Please Try again... ";
    }
}


void database::simpleSearch(vector<Book>& databaseVector){
    string type = getSortBy();                                                  //gets the type to sort by (Title, author, etc.)
    if(type == "Publication Date"){
      cout << endl << "Format for Searching By Publication Date is \'YYYY-MM-DD\', Please enter numerical values accordingly." << endl;
    }
    sortVector(type, databaseVector);
    string search = searchFor(type);                                            //gets the value to search for
    vector<Book> vectorOfSearchResults = {};

    int begin = 0;
    int end = databaseVector.size();

    int index = binarySearchInclusion(search, type, databaseVector, begin, end);
    bool isFound = validIndex(index);
    if(isFound == true){
        linearSearchUpInclusion(search, type, databaseVector, vectorOfSearchResults, index);        //takes the binary search index and searches for value greater than index
        linearSearchDownInclusion(search, type, databaseVector, vectorOfSearchResults, index);      //takes the binary search index and searches for value less than index
        cout << endl << "The Search for \'" << search << "\' in \'" << type << "\' Found \'" << vectorOfSearchResults.size() << " Result(s)\'" << endl;

        if(vectorOfSearchResults.size() > 1){                                   //will only sort data if results return more than 1
          cout << endl << "Display Data By: " << endl;
          string userChoiceOfSort = getSortBy();                                //asks the user how to sort data
          sortVector(userChoiceOfSort, vectorOfSearchResults);
          getOrder(vectorOfSearchResults);                                      //asks the user how to display data, ascending/decending
        }
    }
    if(vectorOfSearchResults.size() == 0){
      cout << "\'" << search << "\' Returned \'0\' Results..." << endl;
    }
    printVector(vectorOfSearchResults);
}


string database::inclusion(const string& type){
    string choice;
    cout << endl << "1 - Including " << endl
         << "2 - Not Including" << endl << endl
         << "Please Choose Either \'1\' or \'2\' To include or exclude \'" << type << "\' for the search: ";
    while(getline(cin, choice)){
      if(choice == "1" || choice == "2"){
        cout << endl;
        break;
      }
      cout << "Sorry, \'" << choice << "\' Is Not Valid, Please Try Again... ";
    }
    return choice;
}


void database::advancedSearchInfoGetter(vector<string>& categories, vector<string>& inSearch, const int& index, const string& type){
     if(type == "Publication Date"){
       cout << endl << "Format for Searching By Publication Date is \'YYYY-MM-DD\', Please enter numerical values accordingly." << endl;
     }

     cout << type << ": ";
     string value;

     getline(cin, value);
     categories.at(index) = value;
     if(value.size() > 1){
       inSearch.at(index) = inclusion(value);                                   //including or not including
     }
}


void database::setUpSearchVectorFilters(vector<string>& categories, vector<string>& inSearch){
     cout << endl << "Fill In Fields Accordingly, If field Does Not Require a Value to be Filtered For Search, Simply Press \'Enter\'." << endl << endl;
     advancedSearchInfoGetter(categories, inSearch, 0, "Title");                //get filters from user what to search for, include or exclude
     advancedSearchInfoGetter(categories, inSearch, 1, "Author");
     advancedSearchInfoGetter(categories, inSearch, 2, "Publication Date");
     advancedSearchInfoGetter(categories, inSearch, 3, "Book Type");
     advancedSearchInfoGetter(categories, inSearch, 4, "ISBN Number");
     advancedSearchInfoGetter(categories, inSearch, 5, "Number Of Pages");
}


void database::performAdvancedSearch(const string& word, const string& included, vector<Book>& temp, vector<Book>& results, const string& type){
    int begin = 0;
    int end = temp.size();
    sortVector(type, temp);

    int index = binarySearchInclusion(word, type, temp, begin, end);            //perform the binary search, first value found thats equal, returns index
    bool isFound = validIndex(index);
    if(isFound == false && included == "2"){
      results = temp;
    }else{
      if(included == "1"){
        linearSearchUpInclusion(word, type, temp, results, index);              //perform inclusion search (All values equal to word)
        linearSearchDownInclusion(word, type, temp, results, index);
      }else{
        linearSearchUpExclusion(word, type, temp, results, index);              //perform exclusion search (All values NOT equal to word)
        linearSearchDownExclusion(word, type, temp, results, index);
      }
      temp = results;                                                           //changes temp to equal that of results so that it doesnt check over same index that wont be valid
      results = {};                                                             //resets the results vector
    }
}


void database::searchDisplay(vector<Book>& results){
    if(results.size() > 0){
        cout << endl << "The Advanced Search Found \'" << results.size() << " Result(s)\'" << endl;
        if(results.size() > 1){                                                 //will only sort data if results vector has more than 1 element
          cout << "Display Data By: " << endl;
          string userChoiceOfSort = getSortBy();                                //asks user how to display data (By Title, By Author, etc.)
          sortVector(userChoiceOfSort, results);
          getOrder(results);                                                    //asks the user how to display data (ascending/decending)
        }
        printVector(results);
    }else{
      cout << "Advanced Search Returned \'0\' Results..." << endl;
    }
}


void database::advancedSearch(const vector<Book>& databaseVector){
    vector<string> categories = {"", "", "", "", "", ""};                       //vector that stores inclusion/exclusion for searching (maximum 6 searches - Title, Author, etc)
    vector<string> inSearch = {"", "", "", "", "", ""};                         //vector that stores the values used in search (maximum 6 searches - Title, Author, etc)

    vector<Book> results = {};                                                  //vector that will store books resulting from search
    vector<Book> temp = databaseVector;                                         //temporary vector that will be searched through

    setUpSearchVectorFilters(categories, inSearch);                             //gets information from user, uses filters for searching

    if(categories.at(0) != ""){
      performAdvancedSearch(categories.at(0), inSearch.at(0), temp, results, "Title");
    }if(categories.at(1) != ""){
      performAdvancedSearch(categories.at(1), inSearch.at(1), temp, results, "Author");
    }if(categories.at(2) != ""){
      performAdvancedSearch(categories.at(2), inSearch.at(2), temp, results, "Publication Date");
    }if(categories.at(3) != ""){
      performAdvancedSearch(categories.at(3), inSearch.at(3), temp, results, "Book Type");
    }if(categories.at(4) != ""){
      performAdvancedSearch(categories.at(4), inSearch.at(4), temp, results, "ISBN Number");
    }if(categories.at(5) != ""){
      performAdvancedSearch(categories.at(5), inSearch.at(5), temp, results, "Number Of Pages");
    }
    results = temp;
    searchDisplay(results);                                                     //prints the results of the search
}


bool database::byTitle(const Book& first, const Book& second){                   //passed into sort function to compare titles
    return first.getTitle() < second.getTitle();
}


bool database::byAuthor(const Book& first, const Book& second){                  //passed into sort function to compare authors
    return first.getAuthor() < second.getAuthor();
}


bool database::byDate(const Book& first, const Book& second){                    //passed into sort to compare publication dates
    return first.getDate() < second.getDate();
}


bool database::byType(const Book& first, const Book& second){                    //passed into sort to compare book types
    return first.getType() < second.getType();
}


bool database::byISBN(const Book& first, const Book& second){                    //passed into sort to compare ISBN numbers
    return first.getISBN() < second.getISBN();
}

bool database::byNumPages(const Book& first, const Book& second){                //passed into sort to compare number of pages
    return first.getNumPages() < second.getNumPages();
}
