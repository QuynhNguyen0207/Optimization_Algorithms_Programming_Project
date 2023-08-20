#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

//Defines Hashtable class
class Hashtable {
public:
  Hashtable() {
//Gets constructor method
    for (int i = 0; i < 26; i++) {
      table[i] = "never used";
    }
  }

//Declares getKey method returning the last character of the given string
  char getKey(const string &str) const {
    return str.back();
  }

//Declares getIndex method returning the index of the array slot corresponding to the given key character
  int getIndex(char ch) const {
    int tmpIndex = ch - 'a';
    return tmpIndex;
  }

//Declares locateKey method searching the hashtable, then returning the corresponding value if found or an empty string if not found
  string locateKey(const string &key) const {
    int index = getIndex(getKey(key));
    string empty = "";
    if (table[index] == key) {
      return table[index];
    } else {
      int i = index + 1;
      while (i != index) {
        if (i == 26) {
          i = 0;
        }
        if (table[i] == key) {
          return table[i];
        } else if (table[i] == "never used") {
          return empty;
        }
        i++;
      }
      return empty;
    }
  }

//Declares the addKey method either adding the given key-value pair to the hashtable or updating the value when the key already exists
  void addKey(const string &key) {
    if (locateKey(key) != "") {
      return;
    }
    int index = getIndex(getKey(key));
    if (table[index] == "never used" || table[index] == "tombstone") {
      table[index] = key;
    } else {
      int i = index + 1;
      while (i != index) {
        if (i == 26) {
          i = 0;
        }
        if (table[i] == "never used" || table[i] == "tombstone") {
          table[i] = key;
          return;
        }
        i++;
      }
    }
  }

//Declares deleteKey method removing the given key-value pair from the hashtable or not doing anything if the key is not found
  void deleteKey(const string &key) {
    int index = getIndex(getKey(key));
    if (table[index] == key) {
      table[index] = "tombstone";
      return;
    } else {
      int i = index + 1;
      while (i != index) {
        if (i == 26) {
          i = 0;
        }
        if (table[i] == key) {
          table[i] = "tombstone";
          return;
        } else if (table[i] == "never used") {
          return;
        }
        i++;
      }
      return;
    }
  }

//Declares the print method printing out all the key-value pairs in the hashtable, excepting any empty of tombstone slots
  void print() const {
    for (int i = 0; i < 26; i++) {
      if (table[i] != "never used" && table[i] != "tombstone") {
        cout << table[i] << " ";
      }
    }
    cout << endl;
  }

private:
  string table[26];
};

//Drivers main function
int main() {

//Creates the Hashtable class with a string of input
  Hashtable table;
  string ip;

//Declares getline method
  getline(cin, ip);

//Creates the istringstream class
  istringstream is(ip);

//Get constructor method with the first istream_iterator is the start of the sequence
  vector<string> input((istream_iterator<string>(is)), 
//The second istream_iterator is the end of the sequence
istream_iterator<string>());
  for (const auto &elem : input) {
    if (elem.front() == 'A') {
      table.addKey(elem.substr(1));
    } else {
      table.deleteKey(elem.substr(1));
    }
  }
//Calls print method
  table.print();
  return 0;
}