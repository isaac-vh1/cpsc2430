#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <vector>

  class DataEntry {
  private:
    int year; // up to this year
    std::string country;
    int gold; //total gold medal count for country
    int silver; //total silver medal count for country
    int bronze; //total bronze medal count for country
  public:
    DataEntry();
    DataEntry(int yearNew, std::string countryNew, int goldNew, int silverNew, int bronzeNew);
    void add(DataEntry* add);
    std::string getCountry();
    int getYear();
    int getGold();
    int getSilver();
    int getBronze();
  };

class HashTable {
  private:
  int m;
  std::vector<std::vector<DataEntry*>> table;
  int hash(std::string country);
  int search(std::string country);
  void dataDisplay(int hashNum, int index);
  void insert(DataEntry* data);
  public:
  HashTable();
  void insertPublic(std::string file);
  bool add(DataEntry* data);
  DataEntry* get(std::string country);
  bool removeData(std::string country);
  void display();
  void destroy();
  int resize();
  bool isPrime(int m);
};
#endif
