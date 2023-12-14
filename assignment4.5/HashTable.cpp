#include<iostream>
#include<string>
#include<vector>
#include"HashTable.h"
#include<fstream>
#include<sstream>
#include<istream>

using namespace std;

//DataEntry Class
//public
//contructor for the class
DataEntry::DataEntry(int yearNew, std::string countryNew, int goldNew, int silverNew, int bronzeNew)
{
  year = yearNew;
  country = countryNew;
  gold = goldNew;
  silver = silverNew;
  bronze = bronzeNew;
}
//contructor to add data to the current Data entry
void DataEntry::add(DataEntry* data)
{
  if(country == data -> getCountry()) {
    year = data -> getYear();
    gold += data -> getGold();
    silver += data -> getSilver();
    bronze += data -> getBronze();
  } else {
    cout << "Error adding data, country dosen't match" << endl;
  }
}
//returns country
string DataEntry::getCountry()
{
  return country;
}
//returns year
int DataEntry::getYear()
{
  return year;
}
//returns gold medals
int  DataEntry::getGold()
{
  return gold;
}
//returns silver medals
int DataEntry::getSilver()
{
  return silver;
}
//returns bronze medals
int DataEntry::getBronze()
{
  return bronze;
}

//HashTable Class
//Private
int m;
//returns hash number for given country
int HashTable::hash(string countryS) //for loop, guard against countryies with not 3 letters
{
  int sum = 0;
  char letter;
  for(int i = 0; i < 3; i++) {
    if(int(countryS.size())>=i)
      letter = countryS[i];
    if(isalpha(letter))
      sum += int(letter) * (i + 1);
  }
  return sum % m;
}
//returns the index for the given country (Not the hash number)
int HashTable::search(string country) //non recursive
{
  int hashNum = hash(country);
  for(int i = 0; i < int(table[hashNum].size()); i++) {
    if (table[hashNum][i] -> getCountry() == country)
      return i;
  }
  return -1;
}
//displays data for the given hash number and country
void HashTable::dataDisplay(int hashNum, int index) {
  DataEntry* data = table[hashNum][index];
  cout << data -> getCountry() << ": ";
  cout << data -> getYear() << ", ";
  cout << data -> getGold() << " gold, ";
  cout << data -> getSilver() << " silver, ";
  cout << data -> getBronze() << " bronze" << endl;
}
//inserts a new data entry into the vector
void HashTable::insert(DataEntry* data)
{
  int hashNum = hash(data -> getCountry());
  table[hashNum].push_back(data);
}

//Public
//contructor to set the first vector size
HashTable::HashTable()
{
  m = 17;
  table.resize(m);
}
//insert function getting the input from the file
void HashTable::insertPublic(string file)
{
  string country, yearS, medal;
  int year, gold, silver, bronze;
  fstream inFile;
  inFile.open(file); // e.g. "word1, word2, word3\n"
  string line;
  string header;
  getline(inFile, header);
  while(getline(inFile, line)) {
    gold = 0;
    silver = 0;
    bronze = 0;
    // "word1, word2, word3\n" will be stored in line
    stringstream ss(line); // create a stringstream from string line
    string token;
    //use getline optional delimiter parameter
    getline(ss, yearS, ','); // "word1" will be stored in token
    year = stoi(yearS);
    getline(ss, token, ',');
    getline(ss, token, ',');
    getline(ss, token, ',');
    getline(ss, token, ',');
    getline(ss, token, ',');
    getline(ss, country, ',');
    getline(ss, token, ',');
    getline(ss, token, ',');
    getline(ss, medal);
    if (medal[0] == 'G'){
      gold = 1;
    } else if(medal[0] == 'S'){
      silver = 1;
    } else if (medal[0] == 'B') {
      bronze = 1;
    }
    DataEntry* data = new DataEntry(year, country, gold, silver, bronze);
    add(data);
  }
}
//adds a new data entry, adds to a current data entry, or returns false if year 
//is older than the year already inputed
bool HashTable::add(DataEntry* data)
{
  string country = data -> getCountry();
  int hashNum = hash(country);
  int index = search(country);
  if(index == -1){
    insert(data);
  } else if(table[hashNum][index] -> getYear() > data -> getYear()) {
    return false;
  } else {
    table[hashNum][index] -> add(data);
  }
  return true;
}
//returns the data entry for the given country
DataEntry* HashTable::get(string country)
{
  int hashNum = hash(country);
  int index = search(country);
  if(index == -1) {
    return nullptr;
  }
  return table[hashNum][index];
}
//removes the data for the given country
bool HashTable::removeData(string country)
{
  int hashNum = hash(country);
  int index = search(country);
  if(index == -1) {
    return false;
  }
  DataEntry* del = table[hashNum][index];
  int end = int(table[hashNum].size());
  swap(table[hashNum][index], table[hashNum][end - 1]);
  table[hashNum].pop_back();
  delete del;
  return true;
}
//displays the entire hash table
void HashTable::display()
{
  cout << endl;
  cout << "Hash Table Display:" << endl;
  for(int i = 0; i < m; i++) {
    //if(!table[i].empty()) {
      cout << endl << "Index: " << i << endl;
      for(int x = 0; x < int(table[i].size()); x++) {
        dataDisplay(i, x);
      }
    //}
    
  }
  cout << endl;
}

void HashTable::destroy() 
{
  for(int i = 0; i < m; i++) {
    if(table[i].size() != 0)
      for(int x = int(table[i].size()) - 1; x >= 0; x--) {
        DataEntry* del = table[i][x];
        table[i].pop_back();
        delete del;
      }
  }
}

int HashTable::resize()
{
  int z; int oldM = m;
  
  m = m * 2;
  while(!isPrime(m)) {
    m++;
  }
  table.resize(m);
  for(int i = 0; i < oldM; i++) {
    if(!table[i].empty()) {
      z = int(table[i].size()) - 1;
      for(int x = z; x >= 0; x--) {
        add(table[i][x]);
        DataEntry* temp = table[i][x];
        table[i][x] = table[i][int(table[i].size())-1];
        table[i][int(table[i].size())] = temp;
        table[i].pop_back();
      }
    }
  }
  return m;
}

bool HashTable::isPrime(int m){
  if(m < 1) {
    return false;
  }
  for(int i = 2; i < m/2; i++) {
    if(m % i == 0) {
      return false;
    }
  }
  return true;
}


