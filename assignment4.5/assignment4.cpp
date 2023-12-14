#include<iostream>
#include<string>
#include<vector>
#include"HashTable.h"
#include<fstream>
#include<sstream>

using namespace std;

int main(int argc, char* argv[])
{
  HashTable table;
  if(argc != 2) {
    cout << "Usage: assignment1 <testFileName>" << endl;
    return 1;
  }
  string filename = argv[1];
  ifstream infile(filename);
  if(!infile.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return 1;
  }
  string line;
  DataEntry* data;
  int size;
  while(getline(infile, line)) {
    string country, yearS, goldS, silverS, bronzeS;
    int year, gold, silver, bronze;
    char choice = line[0];
    string file;
    bool ret;
    switch(choice)
    {
    case 'i':
      getline(infile, file);
      // Option i: Insert pet (will be followed by Pet Name and Pet Age)
      cout << "Initializing hash table from file " << file << endl;
      table.insertPublic(file);
      break;
    case 'a':
      // Option a: Add data entry
      getline(infile, yearS, ',');
      year = stoi(yearS);
      getline(infile, country, ',');
      getline(infile, goldS, ',');
      gold = stoi(goldS);
      getline(infile, silverS, ',');
      silver = stoi(silverS);
      getline(infile, bronzeS);
      bronze = stoi(bronzeS);
      data = new DataEntry(year, country, gold, silver, bronze);
      ret = table.add(data);
      if (ret) {
        cout << "Adding data entry for ";
      } else {
        cout << "NOT adding data for ";
      }
      cout << data -> getCountry() << ": ";
      cout << data -> getYear() << ", ";
      cout << data -> getGold() << " gold, ";
      cout << data -> getSilver() << " silver, ";
      cout << data -> getBronze() << " bronze" << endl;
      break;
    case 'g':
      // Option g: Get data entry
      getline(infile, country);
      data = table.get(country);
      if(data == nullptr) {
      cout << "Data entry for " << country << " does not exist." << endl;
      } else {
        cout << "Data entry for " << country << ": ";
      cout << data -> getYear() << ", ";
      cout << data -> getGold() << " gold, ";
      cout << data -> getSilver() << " silver, ";
      cout << data -> getBronze() << " bronze" << endl;
      }
      break;
    case 'r':
      // Option r: Remove entry
      getline(infile, country);
      ret = table.removeData(country);
      if(!ret) {
    cout << "Data entry for " << country << " does not exist." << endl;
    } else {
    cout << "Removing data entry for " << country << endl;
    }
      break;
    case 'd':
      // Option d: display
      table.display();
      break;
    case 'h':
      //Option h: resize
      size = table.resize();
      cout << "New table size is: " << size << endl;
      break;
    }
  }
  table.destroy();
}