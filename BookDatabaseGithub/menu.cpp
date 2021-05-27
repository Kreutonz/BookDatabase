//menu.cpp

#include "menu.h"


void menu::greeting(){
    cout << "Welcome To The \'BOOK DATABASE\'!" << endl << endl
         << "This Database Stores Specific Book Records Containing:" << endl
         << "Titles, Authors, Publication Dates, Book Types, ISBN Numbers, and Number Of Pages" << endl
         << "_________________________________________________________________________________" << endl << endl;
}


void menu::printOptionMenu(){
    cout << "                              Menu Options:                             " << endl
         << "************************************************************************" << endl << endl
         << "Select The following Numerical Key For Desired Option And Press \'Enter\':" << endl << endl
         << "1 - Print the Book Database" << endl
         << "2 - Add New Book Entry" << endl
         << "3 - Update Previous Book Record" << endl
         << "4 - Delete Previous Book Record" << endl
         << "5 - Search Database" << endl << endl
         << "If You Wish To Exit The Database, Simply Type \'exit()\' And Press \'Enter\'." << endl << endl;
}


string menu::getUserInput(){
    string input;
    cout << "Please Enter Option: ";
    getline(cin, input);
    return input;
}


bool menu::validateUserMenuInput(const string& userMenuInput){
    if(userMenuInput.size() == 0){
      cout << "Sorry, But A Response Is Required. Please Try Again..." << endl;
      return false;
    }else if(userMenuInput == "1" || userMenuInput == "2" || userMenuInput == "3" ||
             userMenuInput == "4" || userMenuInput == "5" || userMenuInput == "exit()"){
      return true;
    }else{
      cout << "Sorry, But \'" << userMenuInput << "\' Is Not A Valid Option. Please Try Again..." << endl;
      return false;
    }
}


string menu::convertToWord(const string& userInput){
    if(userInput == "1"){
      return menuOperations.at(0);                                              //print database
    }else if(userInput == "2"){
      return menuOperations.at(1);                                              //add new book entry
    }else if(userInput == "3"){
      return menuOperations.at(2);                                              //update previous book record
    }else if(userInput == "4"){
      return menuOperations.at(3);                                              //delete previous book record
    }else if(userInput == "5"){
      return menuOperations.at(4);                                              //search database
    }else{
      return menuOperations.at(5);                                              //exit() program
    }
}


menu::menu(){                                             //constructor
    greeting();
}


menu::~menu()                                           //destructor
{ }


string menu::getTask() const{
    return currentTask;
}


void menu::setTask(const string& userInput){
    string wordedInput = convertToWord(userInput);
    currentTask = wordedInput;
}


vector<string> menu::getVectorOfTasks() const{
    return menuOperations;
}


void menu::menuOptions(){
    while(true){
      printOptionMenu();                                                        //print an option menu
      string userInput = getUserInput();                                        //gets user input
      bool isValid = validateUserMenuInput(userInput);                          //check for valid input
      if(isValid == false) continue;                                            //if response is invalid, continues to the next interation of loop and asks user for a new response
      setTask(userInput);                                                       //set task based on input, only will set if valid option
      break;
    }
}


bool menu::checkForWhitespace(const string& toCheck){
    for(int i = 0; i < toCheck.size(); i++){
      if(toCheck.at(i) != SPACE && toCheck.at(i) != TAB){                       //if loop finds a non-space or non-tab char, returns false (not all whitespace)
        return false;
      }
    }
    return true;                                                                //only returns true if all indices are tabs and or spaces
}


string menu::getValidTitle(){
    cout << endl<< "Whats The \'Title\' Of The Book? ";
    string title;
    while(true){
      getline(cin, title);
      if(title.size() == 0){                                                    //does not allow for title of size 0, asks user again to enter
        cout << "Sorry, But At Least One Character Is Required For A Title, Please try again... ";
        continue;
      }
      if(title.size() != 0){                                                    //if passes first condition above, checks the input to ensure its not all whitepsace (Tabs or spaces)
        bool allWhiteSpace = checkForWhitespace(title);
        if(allWhiteSpace == true){                                              //only prints statement if non-space or non-tab char is not found
          cout << "Sorry, But \'" << title << "\' Is Not a Valid Title, Please try again... ";
          continue;
        }
      }
      break;                                                                    //breaks out of the while loop if all conditions are satisfied
    }
    return title;
}


string menu::getValidAuthor(){
    cout << endl << "Whats The \'Author\' Of The Book? ";
    string author;
    while(true){
      getline(cin, author);
      if(author.size() == 0){                                                   //does not allow for title of size 0, asks user again to enter
        cout << "Sorry, But At Least One Character Is Required For An Author, Please try again... ";
        continue;
      }
      if(author.size() != 0){
        bool allWhiteSpace = checkForWhitespace(author);
        if(allWhiteSpace == true){                                              //only prints statement if non-space or non-tab char is not found
          cout << "Sorry, But \'" << author << "\' Is Not a Valid Author, Please try again... ";
          continue;
        }
      }
      break;                                                                    //breaks out of the while loop if all conditions are satisfied
    }
    return author;
}


string menu::convertToProperString(string& toEdit){
    toEdit.at(0) = toupper(toEdit.at(0));                                       //capitalizes first letter
    if(toEdit.size() > 1){
      for(int i = 1; i < toEdit.size(); i++){                                   //makes remaining characters lowercase
        toEdit.at(i) = tolower(toEdit.at(i));
      }
    }
    return toEdit;
}


bool menu::validWord(const string& stringToCheck){
    string copyOfString = stringToCheck;
    for(int i = 0; i < stringToCheck.size(); i++){
      copyOfString.at(i) = tolower(copyOfString.at(i));
      if(copyOfString.at(i) < 'a' || copyOfString.at(i) > 'z'){
        return false;
      }
    }
    return true;
}


int menu::getMonth(){
    string month;
    cout << "Please Enter The Month: ";
    while(true){
      getline(cin,month);
      bool inputValid = validWord(month);
      if(inputValid == false){
        cout << "Sorry, \'" << month << "\' is not valid, please try again... ";
        continue;
      }
      month = convertToProperString(month);                                     //capitalizes first letter, makes remaining lowercase
      for(int i = 0; i < possibleMonths.size(); i++){                           //compares the converted string with a vector of valid months
        if(month == possibleMonths.at(i)){                                      //if valid,returns index for the valid month in the vector, if not, asks the user to try again
          return i;
        }
      }
      cout << "Sorry but \'" << month << "\' Is Not A Valid Month, Please Try Again... ";
      continue;
    }
}


string menu::convertMonthToTwoDigits(const int& monthIndex){
    if(monthIndex == 0) return "01";
    else if(monthIndex == 1) return "02";
    else if(monthIndex == 2) return "03";
    else if(monthIndex == 3) return "04";
    else if(monthIndex == 4) return "05";
    else if(monthIndex == 5) return "06";
    else if(monthIndex == 6) return "07";
    else if(monthIndex == 7) return "08";
    else if(monthIndex == 8) return "09";
    else if(monthIndex == 9) return "10";
    else if(monthIndex == 10) return "11";
    else return "12";
}


string menu::getDay(const int& monthIndex){
    string day;
    int maxDaysInMonth = monthDays.at(monthIndex);                              //uses the month index obtained from another function to determine the maximum days for the month
    cout << "Please Enter The Day (If Day Not Available, Press \'Enter\'): ";
    while(getline(cin, day)){
      bool validDay = checkValidNumber(day);
      if(validDay == false){
        cout << "Sorry, But \'" << day << "\' Is Not a Valid Day For That Month, Please Try from \'1\' up to \'" << maxDaysInMonth << "\'..." ;
        continue;
      }
      if(day.size() == 0){
        day = "00";
        break;                                                //some publication dates dont have days specified, gives user the option to not select a day value
      }
      if(day.size() > 0){
        int convertedDay = stoi(day);                                           //must do integer comparision, string compares at indices, if (3 < day < 10), will have greater valie at first index and think day is greater than max days and ask user again
        if((convertedDay <= maxDaysInMonth && convertedDay > 0)){
          if(day.size() == 1){
            day = "0" + day;
          }
          break;
        }
      }
      cout << "Sorry, But \'" << day << "\' Is Not a Valid Day For That Month, Please Try from \'1\' up to \'" << maxDaysInMonth << "\'..." ;
      }
    return day;
}


int menu::getCurrentYear(){                                                   //https://stackoverflow.com/questions/8343676/how-to-get-current-date-and-time
    time_t theTime = time(NULL);                                                //used this recourse to get the current year
    struct tm *aTime = localtime(&theTime);

    int currentYear = aTime->tm_year + 1900;
    return currentYear;
}


void menu::publicationYearSetter(const int& year){
    publicationYear = year;
}


int menu::publicationYearGetter() const{
    return publicationYear;
}


void menu::convertYearToFourDigits(string& stringToChange){                     //ensures the year string will always be size 4 for sorting purposes
    if(stringToChange.size() == 4) return;
    else if(stringToChange.size() == 3) stringToChange = "0" + stringToChange;
    else if(stringToChange.size() == 2) stringToChange = "00" + stringToChange;
    else stringToChange = "000" + stringToChange;
}


string menu::getYear(){
    string year;
    int currentYear = getCurrentYear();
    cout << "Please Enter the Year: ";
    while(getline(cin, year)){
      bool validYear = checkValidNumber(year);
      if(validYear == false){
        cout << "Sorry, But \'" << year << "\' Is Not A Number. Please Try Again... ";
        continue;
      }
      int convertedYear = stoi(year);                                           //converts string to a integer so comparison can by obtained
      if(convertedYear <= currentYear && convertedYear > 0){
        publicationYearSetter(convertedYear);                                   //sets the private variable for year
        break;                                                                  //break out of loop if valid and publicaiton year is <= current year
      }else{
        cout << "Sorry, But \'" << year << "\' Is Not Valid. Please Try Again... ";
      }
    }
    convertYearToFourDigits(year);
    return year;
}


string menu::getValidPublicationDate(){
    cout << endl << "Whats The \'Publication Date\' Of The Book? (A Year and Month are required): ";
    string date;
    string year = getYear();
    int monthIndex = getMonth();
    string month = convertMonthToTwoDigits(monthIndex);
    string day = getDay(monthIndex);

    date = year + '-' + month + '-' + day;                                      //concatenates the strings for month, day and year into one string
    return date;
}


string menu::getValidBookType(){
    cout << endl << "Whats the \'Book Type\'? (Hardcover, Softcover, or Digital): ";
    string type;
    while(getline(cin, type)){
      if(type.size() > 0){
          type = convertToProperString(type);                                   //capitalizes first letter, and makes rest lowercase
        if(type == "Hardcover" || type == "Softcover" || type == "Digital"){
          break;
        }
      }
      cout << "Sorry, But \'" << type << "\' Is Not Valid. Please Type: \'Hardcover\', \'Softcover\', or \'Digital\'... ";
      continue;
    }
    return type;
}


bool menu::validPart(const string& partOfIsbn){
    for(int i = 0; i < partOfIsbn.size(); i++){                                 //since 'x' character is used in ISBN numbers, had to account for this case
        if((partOfIsbn.at(i) < '0' || partOfIsbn.at(i) > '9') && partOfIsbn.at(i) != 'X' && partOfIsbn.at(i) != 'x'){
          cout << "Sorry, \'" << partOfIsbn << "\' is not valid, please try again... ";
          return false;
        }
    }
    return true;
}


void menu::addToISBN(string& isbn, string& part, int& hyphenCount){
    isbn += part;                                                               //adds the entry to the ISBN
    if((isbn.size() > 0) && (isbn.size() < tenDigitIsbnSize) && (hyphenCount <= alottedHyphens)){   //only adds '-' if conditions are met (alottedHyphens = CONSTANT)
      isbn += '-';                                                              //concatenates hyphen to isbn
      hyphenCount++;
    }
}

void menu::printNote(){
    if(publicationYear >= isbnYearFormatChange){                                //isbnYearFormatChange = CONSTANT
        cout << "Note: Since Publication year is post 2007, 13 digits (or X) are required, separated into 5 parts." << endl
             << "However the First Three integers are still valid" << endl
             << "Please Re-enter ISBN Number after the First Three Digits." << endl;
    }else if(publicationYear < isbnYearFormatChange){
        cout << "Note: Since Publication year is prior to 2007, 10 digits are allowed, separated into 4 parts." << endl
             << "Please Re-enter the ISBN Number." << endl;
    }
}


bool menu::checkForError(const string& isbn, const int& hyphenCount){
    bool isError = false;
    if(hyphenCount > alottedHyphens){
      cout << "The ISBN Number Entered has to many sections. " << endl;
      isError = true;
    }
    if(isbn.at(isbn.size()-1) == '-' && isbn.size() == tenDigitIsbnSize){
      cout << "Sorry, the grouping is incorrect. " << endl;
      isError = true;
    }
    if(isbn.size() > tenDigitIsbnSize){
      cout << "The ISBN Number Entered is too Big." << endl;
      isError = true;
    }
    if(isError == true){
      printNote();
      return true;
    }
    return false;
}


string menu::getTenDigitISBN(){
    string isbn;
    int hyphenCount = 0;
    while(true){
      string part;                                                              //temporary variable that stores digits entered by user
      cout << "Please Enter Digits (X for integer 10) up to a \' - \' (hyphen) and press \'Enter\'. ";
      while(getline(cin, part)){                                                //getline
        bool validEntry = validPart(part);                                      //determines if error is user entered data
        if(validEntry == false) continue;                                       //if error, asks user to try again by iterating to next phase of loop
        addToISBN(isbn, part, hyphenCount);                                     //will only add user data to isbn if valid
        break;
      }//while() inner
      bool error = checkForError(isbn, hyphenCount);                            //determines if there is an error in format of ISBN
      if(error == true){                                                        //if an error occurs, resets the variables and iterates to next part of loop
        isbn = "";
        hyphenCount = 0;
        continue;
      }
      if(isbn.size() == tenDigitIsbnSize && isbn.at(isbn.size() - 1) != '-'){   //breaks out of loop if size is met and last character isnt a '-'
        break;
      }
  }
  return isbn;
}


string menu::getValidISBN(){
    string isbnNum;
    cout << endl;         //spacing
    if(publicationYear >= isbnYearFormatChange){                                //if year >= 2007 (13 digits (extra three digits at beginning of ISBN))
      cout << "Please Enter Digits from the ISBN up to the first \' - \' (Hyphen) and press \'Enter\'. ";
      string digit;
      while(true){
        getline(cin, digit);
        int digitNum = stoi(digit);                                             //converts to integers to do integer comparison
        if(digitNum != after_2007_1 && digitNum != after_2007_2){               //after_2007_1 & after_2007_2 = CONSTANTS
          cout << "Sorry, But \'" << digit << "\' Is Not Valid. Publications After 2007 Begin With \'978\' or \'979\'. Please Try Again... ";
          continue;
        }
        isbnNum += digit + '-';
        break;
      }
    }
    isbnNum += getTenDigitISBN();                                               //if year < 2007, implies 10 digits divided into 4 parts
    return isbnNum;
}


string menu::getValidNumPages(){
    string pages;
    cout << endl << "Please enter the number of pages: ";
    while(getline(cin, pages)){
      bool validNum = checkValidNumber(pages);                                  //checks to see if user input is a valid number, if not asks user again
      if(validNum == false){
        cout << "Sorry but, \'" << pages << "\' is not a Valid Number, Please Try Again... ";
        continue;
      }
      break;
    }
    return pages;
}


void menu::printBook(const Book& bookToPrint){
    string readableDate = convertToReadablePublicationDate(bookToPrint.getDate());
    cout << "1 - Title:           " << bookToPrint.getTitle() << endl
         << "2 - Author:          " << bookToPrint.getAuthor() << endl
         << "3 - Pulication Date: " << readableDate << endl
         << "4 - Book Type:       " << bookToPrint.getType() << endl
         << "5 - ISBN Number:     " << bookToPrint.getISBN() << endl
         << "6 - Number Of Pages: " << bookToPrint.getNumPages() << endl;
}


Book menu::newBookRecord(){                                                         //gets the information for a newBook from the user
    string title = getValidTitle();
    string author = getValidAuthor();
    string publicationDate = getValidPublicationDate();
    string bookType = getValidBookType();
    string isbnNum = getValidISBN();
    string numPages = getValidNumPages();

    Book newBook(title, author, publicationDate, bookType, isbnNum, numPages);       //creates a new Book object based on strings passed in from user

    printBook(newBook);

    cout << "\'" << newBook.getTitle() << "\' Added To Database" << endl;
    return newBook;
}


void menu::printEntryNumAndTitle(const vector<Book>& bookVector){                   //prints shorter version of database, only includes entry number and title
    int columnWidth = 10;
    cout << endl << setw(columnWidth) << left << "" << setw(columnWidth) << left << "Number" << left << "Title" << endl;
    cout << setw(columnWidth) << left << "" << "______________________________" << endl << endl;
    for(int i = 0; i < bookVector.size(); i++){
      cout << setw(columnWidth) << left << "" << setw(columnWidth) << left << (i + 1) << bookVector.at(i).getTitle() << endl;
    }
      cout << endl << "Please Type the corresponding number that matches with the Title desired: ";
}


int menu::getValidIndex(const vector<Book>& bookVector){
    string userInput;
    int convertedUserInput = 0;
    while(getline(cin, userInput)){
      bool validNum = checkValidNumber(userInput);
      if(validNum == false){
        cout << "Sorry, \'" << userInput << "\' is not valid number." << endl
             << "The Minimum number is \'1\' and the Maxmimum number is \'" << bookVector.size() << "\'. Please try again...";
        continue;
      }
      convertedUserInput = stoi(userInput);                                 //if number is valid, converts it to do integer comparison    //reference: https://stackoverflow.com/questions/23567924/convert-string-to-int-in-c
      if(convertedUserInput > bookVector.size() || convertedUserInput < 1){     //if user chooses a number > available entries or less than 1,
        cout << "Sorry, \'" << userInput << "\' is not valid." << endl
             << "The Minimum number is \'1\' and the Maxmimum number is \'" << bookVector.size() << "\'. Please try again...";
        continue;
      }
      break;
    }
    convertedUserInput = convertedUserInput - 1;
    return convertedUserInput;
}


int menu::getIndexToEdit(const vector<Book>& bookVector){                           //prints a menu and gets users input, returns index of value desired to edit
    printEntryNumAndTitle(bookVector);
    return getValidIndex(bookVector);
}


int menu::getTypeToEdit(){
    cout << endl << "Please type the Digit to the corresponding value to Change: ";
    string userInput;
    while(true){
      getline(cin,userInput);
      if(userInput.size() > 1 || userInput.at(0) < '1' || userInput.at(0) > '6'){
        cout << "Sorry, \'" << userInput << "\' is not valid. Please try again... ";
        continue;
      }
      break;
    }
    if(userInput == "1") return 1;
    else if(userInput == "2") return 2;
    else if(userInput == "3") return 3;
    else if(userInput == "4") return 4;
    else if(userInput == "5") return 5;
    else return 6;
}


string menu::getNewValueToChange(const int& task){
    if(task == 1){
      return getValidTitle();
    }else if(task == 2){
      return getValidAuthor();
    }else if(task == 3){
      return getValidPublicationDate();
    }else if(task == 4){
      return getValidBookType();
    }else if(task == 5){
      return newValidISBN();
    }else{
      return getValidNumPages();
    }
}


bool menu::checkValidNumber(const string& toCheck){
    for(int i = 0; i < toCheck.size(); i++){
      if(toCheck.at(i) < '0' || toCheck.at(i) > '9') return false;              //if loop finds a non-integer in the string, will return false
    }
    return true;
}


bool menu::trySearchAgain(){
    string userReply;
    cout << endl << "Would You Like to Try Another Search:" << endl << endl
         << "1 - Yes" << endl
         << "2 - No" << endl << endl
         << "Please Enter Either \'1\' or \'2\': ";
    while(getline(cin, userReply)){
      if(userReply == "1") return true;
      else if(userReply == "2") break;
      cout << "Sorry, \'" << userReply << "\' Is Not Valid, Please Try Again... ";
    }
    return false;
}


void menu::simpleOrAdvancedSearch(database& bookDatabase, vector<Book>& vectorToSearch){
    if(noComponents(menuOperations.at(4), vectorToSearch.size()) == true) return;         //will not perform operation if database is empty
    while(true){
      cout << endl << "Please Select:" << endl << endl
           << "1 - Simple Search   (By A Specific Category)" << endl
           << "2 - Advanced Search (By Multiple Categories)" << endl << endl
           << "Select \'1\' or \'2\' and Press \'Enter\': ";
      string userInput;
      while(getline(cin, userInput)){                                           //will run until user enters a '1' or '2'
        if(userInput == "1" || userInput == "2") break;
        cout << "Sorry, \'" << userInput << "\' is not valid, please try again... ";
      }
      if(userInput == "1"){                                                       //performs simple search
        cout << "\"Simple Search (By A Specific Category)\" selected..." << endl << endl;
        bookDatabase.simpleSearch(vectorToSearch);
      }else{                                                                      //performs advanced search
        cout << "\"Advanced Search (By Multiple Categories)\" selected..." << endl << endl;
        bookDatabase.advancedSearch(vectorToSearch);
      }
      bool again = trySearchAgain();                                            //asks the user if they want to search for something else, if true, function runs again, if false, breaks outs of loop and function ends
      if(again == false) break;
    }
}


void menu::scanAndUpdatePublicationYear(string date){                         //ensures the private variable in menu is updated to current year in Book Entry
    string publicationYear = date.substr(0, 4);
    int year = stoi(publicationYear);                                           //converts to integer
    publicationYearSetter(year);                                                //updates private variable
}


string menu::convertYear(const string& date){
    string year = date.substr(0, 5);                                            //makes a substring for the first 5 characters in data string (YYYY-)
    for(int i = 0; i < year.size(); i++){
      if(year.at(i) != '0'){                                                    //as soon as loop hits first non-zero, it creates a substring for the year to rid beginning zeros
        year = year.substr(i, year.size() - i);
        break;
      }
    }
    return year;
}


string menu::convertMonthToWord(const string& date){
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


string menu::convertDay(const string& date){
    string day = date.substr(7,3);                                              //makes a substring for the separation hyphen and two digits that characterize the day (-DD)
    if(day == "-00") return "";
    return day;
}


string menu::convertToReadablePublicationDate(const string& toChange){
    string year = convertYear(toChange);                                        //creates a substring for the year
    string month = convertMonthToWord(toChange);                                //creates a substring and converts to a month
    string day = convertDay(toChange);                                          //creates empty string if day is "00"

    return year + month + day;                                                  //newly concatenated string formed via new substring values
}


bool menu::validChangeYearISBN(const Book& bookToChange){                     //runs when changing value of ISBN
    scanAndUpdatePublicationYear(bookToChange.getDate());
    int publicationYear = publicationYearGetter();
    string isbn = bookToChange.getISBN();
    if(publicationYear >= isbnYearFormatChange && isbn.size() == tenDigitIsbnSize){           //isbnYearFormatChange && tenDigitIsbnSize = CONSTANT
      cout << "The \'"<< bookToChange.getTitle() << "\' Record now has a Publication Year Equal "
           << "to or Post 2007 and an ISBN Number of 10 Digits, This is Invalid." << endl << endl;
      cout << "Publication Date: " << convertToReadablePublicationDate(bookToChange.getDate()) << endl
           << "ISBN Number     : " << isbn << endl;
      return false;
    }
    if(publicationYear < isbnYearFormatChange &&  isbn.size() == thirteenDigitIsbnSize){           //isbnYearFormatChange && thirteenDigitIsbnSize= CONSTANT
      cout << "The Book Record now has a Publication Year Prior to 2007 and an ISBN Number of 13 Digits, This is Invalid." << endl << endl;
      cout << "Publication Date: " << convertToReadablePublicationDate(bookToChange.getDate()) << endl
           << "ISBN Number     : " << isbn << endl;
      return false;
    }
    return true;
}


string menu::whatISBNSize(){
    cout << "ISBN Type: " << endl << endl
         << "1 - 13 Digit (used for Books Published in 2007 and later)"<< endl
         << "2 - 10 Digit (used for Books Published before 2007)" << endl << endl
         << "Select \'1\' or \'2\' and press \'Enter\': ";
    string choice;
    string isbnNum;
    while(getline(cin, choice)){
      if(choice == "1" || choice == "2") break;                                 //breaks out of loop if user input is '1' or '2', asks again if not
      cout << "Sorry, \'" << choice << "\' is not valid, please try again... ";
    }
    if(choice == "1"){
      cout << endl << "The first three digits for a 13-Digit ISBN must begin with either \'978\' or \'979\'" << endl
           << "Please type \'978\' or \'979\': ";
      string userInput;
      while(getline(cin, userInput)){
        if(userInput == "978" || userInput == "979"){
            isbnNum += userInput + '-';
            break;
        }
        cout << "Sorry, \'" << userInput << "\' is not valid, please try again... ";
      }
    }
    return isbnNum;
}


string menu::newValidISBN(){
    string newISBN = whatISBNSize();                                            //asks user what size of isbn number, returns empty if 10 digit, returns '978' or 979' if 13 digit
    newISBN += getTenDigitISBN();                                               //concatenates a ten digit isbn to current isbn
    return newISBN;
}


void menu::makeValidEntry(database& bookDatabase, const int& index){
    cout << endl << "Which Category Would you Like To Update to Make the Book Record Valid" << endl << endl
         << "1 - Publication Date" << endl
         << "2 - ISBN Number" << endl << endl
         << "Select \'1\' or \'2\' and press \'Enter\': ";
    string userChoice;
    while(getline(cin, userChoice)){
      if(userChoice == "1"){                                                    //runs functions to get a publication data and sets it
        string newDate = getValidPublicationDate();
        scanAndUpdatePublicationYear(newDate);
        bookDatabase.updateBookRecord(3, index, newDate);
        break;
      }else if(userChoice == "2"){                                              //runs functions to get an ISBN number and sets it
        string newISBN = newValidISBN();
        bookDatabase.updateBookRecord(5, index, newISBN);
        break;
      }else{
        cout << "Sorry, \'" << userChoice << "\' is not valid, please try again... ";
      }
    }
}

bool menu::noComponents(const string& operation, const int& size){
    if(size == 0){
      cout << endl << "Sorry, the Database is Empty, the operation \'" << operation << "\' cannot be performed..." << endl << endl << endl;
      return true;
    }
    return false;
}
