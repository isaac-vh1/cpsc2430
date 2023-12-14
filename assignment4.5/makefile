assignment4: assignment4.o HashTable.o
	g++ -o hashTest assignment4.o HashTable.o
assignment4.o: assignment4.cpp HashTable.h
	g++ -c -Wall -Werror -pedantic -std=c++11 assignment4.cpp
HashTable.o: HashTable.cpp HashTable.h
	g++ -c -Wall -Werror -pedantic -std=c++11 HashTable.cpp
