//
//  Project 1: DNA Profiling
//  UIN : 677725560 , Name : Jash Shah 
//  Creative Component a command that can count all STR instances
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "ourvector.h"

using namespace std;

struct People {
  string Name;
  ourvector<int> Value;
};

// FUNCTION DECLARATION LIST
// Function to process all the commands
void ProccessCommand(string cmd, ourvector<ourvector<char>> &STRs,
                     ourvector<People> &Database, ourvector<char> &DNA);

// Function and 2 subfunctions to load data from txt file to STRs vector and
// Database vector
void loadData(string cmd, ourvector<ourvector<char>> &STRs,
              ourvector<People> &Database);
void loadSTRs(ourvector<ourvector<char>> &STRs, string line);
void loadInfo(ourvector<People> &Database, string line);

// Function and 3 subfunctions to display Data
void displayData(ourvector<People> &Database, ourvector<char> &DNA,
                 ourvector<int> &count, ourvector<ourvector<char>> &STRs);
void displayDatabase(ourvector<People> &Database);
void displayDNA(ourvector<char> &DNA);
void displayCount(ourvector<int> &count, ourvector<ourvector<char>> &STRs);

// Function to load data from txt file to DNA vector
void loadDNA(ourvector<char> &DNA);

// Function and 3 subfunctions to Process DNA
void ProcessDNA(ourvector<ourvector<char>> &STRs, ourvector<char> &DNA,
                ourvector<int> &count, ourvector<People> &Database);
int processSTR(ourvector<char> &STR, ourvector<char> &DNA);
bool match(ourvector<char> &STR, ourvector<char> &DNA, int index);
int max(ourvector<int> &rep);

// Function and 2 subfunction to search for name after processing DNA
void search(ourvector<People> &Database, ourvector<char> &DNA,
            ourvector<int> &count);
int searchDNA(int index, ourvector<People> &Database, ourvector<int> &count);
bool matchDNA(int index, ourvector<People> &Database, ourvector<int> &count);

// 6 Creative Component a command that can count all STR instances
void allSTR(ourvector<ourvector<char>> &STRs, ourvector<char> &DNA,
            ourvector<int> &count, ourvector<People> &Database);
int processALLSTR(ourvector<char> &STR, ourvector<char> &DNA);

//  FUNCTION DEFINITION

// 1. Function load data into Database vector
void loadData(string cmd, ourvector<ourvector<char>> &STRs,
              ourvector<People> &Database) {
  // clearing vectors so if they have any thing in them it gets cleared
  STRs.clear();
  Database.clear();
  string filename;  // get filename
  cin >> filename;
  cout << "Loading database..." << endl;
  ifstream infile(filename);  // open the file
  if (!infile.good()) {
    cout << "Error: unable to open '" << filename << "'" << endl;
  } else {
    string line;
    infile >> line;        // get first line from the file i.e (name,agct,agat)
    loadSTRs(STRs, line);  // load AGCT,AGAT into our STRS vector

    string tempLine;

    infile >> tempLine;
    while (!infile.eof()) {  // looping to get every remaining line from txt
                             // file and storing data from it
      loadInfo(Database, tempLine);
      infile >> tempLine;
    }
  }
}

// 1(a) loading STRs into database vector
void loadSTRs(ourvector<ourvector<char>> &STRs, string line) {
  stringstream parser(line);  // parse the line as object
  string name, val;
  getline(parser, name, ',');          // get the "name" from line and throw it
  while (getline(parser, val, ',')) {  // loop through the line
    ourvector<char> str;
    for (char c : val) {
      str.push_back(c);  // store A,G,A,C,T letter by letter into a vector
    }
    STRs.push_back(str);  // push the vector stored above into another vector
  }
}

// 1(b) loading Name and their repititon of STRs into database vector
void loadInfo(ourvector<People> &Database, string line) {
  stringstream parse(line);  // make object
  string name, val;
  People Temp;
  getline(parse, name, ',');  // get name and store it in a temp struct
  Temp.Name = name;
  while (getline(parse, val, ',')) {  // get the remaining stuff from the line
    Temp.Value.push_back(stoi(val));  // push them back in our temp struct
  }
  Database.push_back(Temp);  // push the struct into our vector of structs
}

// 2. Displaying count,Dna,Database and STR's vector
void displayData(ourvector<People> &Database, ourvector<char> &DNA,
                 ourvector<int> &count, ourvector<ourvector<char>> &STRs) {
  // outputting database
  displayDatabase(Database);
  // outputting dna
  displayDNA(DNA);
  // outputting count
  displayCount(count, STRs);
}

// 2(a).outputting database vector
void displayDatabase(ourvector<People> &Database) {
  // outputting database
  if (Database.size() == 0) {
    cout << "No database loaded." << endl;
  // loop through the vector and output
  }else {
    cout << "Database loaded: " << endl;
    for (int i = 0; i < Database.size(); i++) {
      cout << Database[i].Name;
      for (int j = 0; j < Database[i].Value.size(); j++) {
        cout << " " << Database[i].Value[j];
      }
      cout << endl;
    }
  }
}

// 2(b).outputting dna vector
void displayDNA(ourvector<char> &DNA) {
  // outputting DNA vector
  if (DNA.size() == 0) {
    cout << "No DNA loaded." << endl;
  // loop through the vector and output
  }else {
    cout << endl;
    cout << "DNA loaded: " << endl;
    for (char c : DNA) {
      cout << c;
    }
    cout << endl;
  }
}

// 2(c).outputting count and STRs vector
void displayCount(ourvector<int> &count, ourvector<ourvector<char>> &STRs) {
  // outputting Count vector
  if (count.size() == 0) {
    cout << endl;
    cout << "No DNA has been processed." << endl;
  // loop through the vector and output
  }else {
    cout << endl;
    cout << "DNA processed, STR counts: " << endl;
    for (int x = 0; x < STRs.size(); x++) {
      for (int y = 0; y < STRs[x].size(); y++) {
        cout << STRs[x][y];
      }
      cout << ": " << count[x] << endl;
    }
    cout << endl;
  }
}

// 3. loading DNA vector from Dna files
void loadDNA(ourvector<char> &DNA) {
  // clearing DNA vector , so there is nothing in it
  DNA.clear();
  string filename;  // get filename
  cin >> filename;
  cout << "Loading DNA..." << endl;
  ifstream infile(filename);  // open the file
  if (!infile.good()) {
    cout << "Error: unable to open '" << filename << "'" << endl;
  } else {
    string line;
    infile >> line;
    stringstream parser(line);  // create an object of the line
    string temp;
    getline(parser, temp);  // get every letter from line
    for (char c : temp) {
      DNA.push_back(c);  // push letter in DNA vector
    }
  }
}

// 4 Processing DNA to get the  consecutive repeated STRs
void ProcessDNA(ourvector<ourvector<char>> &STRs, ourvector<char> &DNA,
                ourvector<int> &count, ourvector<People> &Database) {
  // if database size = 0  means no data from database
  if (Database.size() == 0) {
    cout << "No database loaded." << endl;
  // if DNA size = 0  means no data from DNA
  }else if (DNA.size() == 0) {
    cout << "No DNA loaded." << endl;
  // if DNA and database are both loaded then we process
  }else {
    cout << "Processing DNA..." << endl;
    for (ourvector<char> &STR :
         STRs) {  // get a single STR from our vectors of STRs
      count.push_back(processSTR(STR, DNA));  // processing one STR such as AGCT
    }
  }
}

// 4(a) processing one STR (AGACT,etc) to return the amount of time its repeated
// consecutively
int processSTR(ourvector<char> &STR, ourvector<char> &DNA) {
  // making a vector to get the max repititive count of a STR
  ourvector<int> repeat;
  int count = 0;
  for (int i = 0; i < DNA.size(); i++) {
    if (STR[0] == DNA[i]) {
      // checking the first letter of STR AGCT matches the letter from DNA
      // vector (A,G,C)
      if (match(STR, DNA,
                i)) {  // match returns true if first letter is same and so are
                       // the letters after that in DNA vector
        count++;       // we store count
        i = i + STR.size();  // change current index since we found similiar STR
        // making a bool to stop our while loop
        bool x = true;
        while (x) {
          if (match(STR, DNA, i)) {  // checks if the Strings after current are
                                     // the same as our STR
            i = i + STR.size();
            // if there is a match we incerement i
            count++;
            // increment count
          } else {
            x = false;
          }
        }
        repeat.push_back(
            count);  // pushback every consecutive STR  number we get
      }
    }
    count = 0;  // reset count to 0 for next pushback count
  }
  int maxi = max(repeat);  // find max from repeat vector
  return maxi;             // return max
}

// 4(b) matching the rest of strings for processSTr after first string are
// common for DNA and STR vectors
bool match(ourvector<char> &STR, ourvector<char> &DNA, int index) {
  // returns true or false after finding match of the first letter between DNA
  // and STR
  for (int c = 0; c < STR.size(); c++) {
    // index is invalid from DNA
    if (index >= DNA.size()) {
      return false;
    }
    if (STR[c] != DNA[index]) {
      return false;
    }
    index++;
  }
  return true;
}

// 4(c) finding max in a vector of int of amount of times a STR was repeated
int max(ourvector<int> &rep) {
  // Max function
  int Max;
  // if repeat is zero there is no maximum element
  if (rep.size() == 0) {
    Max = 0;
  // if repeat size is 1 , only one element return it
  }else {
    Max = rep[0];
    if (rep.size() == 1) {
      return Max;
    }
    // loop if size is greater than 1 and check for Max
    for (int i = 0; i < rep.size(); i++) {
      if (Max < rep[i]) {
        Max = rep[i];
      }
    }
  }
  return Max;
}

// 5 searching the count vector and finding names for it in our database
void search(ourvector<People> &Database, ourvector<char> &DNA,
            ourvector<int> &count) {
  // search function after processing and getting a vector count back with the
  // repetitive strs
  if (Database.size() == 0) {
    cout << "No database loaded." << endl;
  } else if (DNA.size() == 0) {
    cout << endl;
    cout << "No DNA loaded." << endl;
  } else if (count.size() == 0) {
    cout << "No DNA processed." << endl;
  } else {
    // search database if everything is loaded and processed
    cout << "Searching database..." << endl;
    // index -1 to keep track if we found  a match or not
    int i = -1;
    i = searchDNA(i, Database, count);  // see if there is a match for our
                                        // vector count in Database vector
    if (i != -1) {                      // print name for index if match found
      cout << "Found in database!  DNA matches: " << Database[i].Name << endl;
    } else {
      cout << "Not found in database." << endl;
    }
  }
}

// 5(a)searching the name of person with the DNA and returning index of that
// name
int searchDNA(int index, ourvector<People> &Database, ourvector<int> &count) {
  // checking if first number of count and first letter of any Database.Value
  // vector is same, then matching the rest numbers
  int x = 0;
  index = -1;
  if (count.size() != Database[x].Value.size()) {
    return index;
  } else {
    for (x = 0; x < Database.size(); x++) {
      if (count[0] == Database[x].Value[0]) {  // matching first numbers
        if (matchDNA(x, Database, count)) {    // matching rest numbers
          return x;  // returning the index back to our search function  if we
                     // find a match
        }
      }
    }
  }
  return index;  // if no match return -1
}

// 5(b) matching the numbers of count and Database.Value to see if they are same
// for searchDNA
bool matchDNA(int index, ourvector<People> &Database, ourvector<int> &count) {
  for (int x = 0; x < count.size(); x++) {
    if (count[x] != Database[index].Value[x]) {  // looping to match
      return false;  // if any element are not same return false
    }
  }
  return true;  // true if match found
}

// 6 Creative function-> counting all str occurences, processing each str
// seperately and returning respective counts of that str in the vector
void allSTR(ourvector<ourvector<char>> &STRs, ourvector<char> &DNA,
            ourvector<int> &count, ourvector<People> &Database) {
  // if database size = 0  means no data from database
  if (Database.size() == 0) {
    cout << "No database loaded." << endl;
  // if DNA size = 0  means no data from DNA
  }else if (DNA.size() == 0) {
    cout << "No DNA loaded." << endl;
  // if DNA and database are both loaded then we process
  }else {
    cout << "Processing DNA..." << endl;
    for (ourvector<char> &STR :
         STRs) {  // get a single STR from our vectors of STRs
      count.push_back(
          processALLSTR(STR, DNA));  // processing one STR such as AGCT
    }
  }
  displayCount(count, STRs);
}

// 6(A) returning counts of number of str in vector for allSTR
int processALLSTR(ourvector<char> &STR, ourvector<char> &DNA) {
  // making a vector to get the max repititive count of a STR;
  int count = 0;
  for (int i = 0; i < DNA.size(); i++) {
    if (STR[0] == DNA[i]) {
      // checking the first letter of STR AGCT matches the letter from DNA
      // vector (A,G,C)
      if (match(STR, DNA, i)) {
        count++;             // we store count
        i = i + STR.size();  // change current index since we found similiar STR
        // making a bool to stop our while loop
      }
    }
  }
  return count;
}

// loop to undergo all commands
void ProccessCommand(string cmd, ourvector<ourvector<char>> &STRs,
                     ourvector<People> &Database, ourvector<char> &DNA,
                     ourvector<int> &count) {  // command to run the while loop
                                               // with different commands
  while (cmd != "#") {
    cout << "Enter command or # to exit: ";
    cin >> cmd;  // take user command and loop through if it matches something
    if (cmd == "load_db") {
      loadData(cmd, STRs, Database);  // loading data into our STRs vector
    } else if (cmd == "display") {
      displayData(Database, DNA, count, STRs);  // displaying all our data
    } else if (cmd == "load_dna") {
      loadDNA(DNA);  // loading DNA into our DNA vector
    } else if (cmd == "process") {
      ProcessDNA(STRs, DNA, count,
                 Database);  // processing DNA to get count vector data
    } else if (cmd == "search") {
      search(Database, DNA,
             count);  //  searching using count vector to get match
    } else if (cmd == "search_all") {  // searching for all instances of STR in
                                       // STRs vector
      allSTR(STRs, DNA, count, Database);
    } else if (cmd != "#") {
      cout << "command does not exist" << endl;  // invalid command user input
    }
  }
}

int main() {
  string cmd;
  ourvector<ourvector<char>> STRs;  // vector to store [(a,g,c,g),(c,g,a,t)]
  ourvector<People> Database;  // vector of struct to store Name -> Value vector
  ourvector<char> DNA;         // vector to store dna data [a,g,c,g,t,a,g]
  ourvector<int> count;        // vector to store repetitive STRs [14,3,0]
  cout << "Welcome to the DNA Profiling Application." << endl;
  ProccessCommand(cmd, STRs, Database, DNA, count);  // processing all commands
  return 0;
}