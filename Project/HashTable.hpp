#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct wordItem
{
    string word;
    int count;
    wordItem* next;
};

class HashTable{
public:
	HashTable(int hashTableSize);
	~HashTable();
	bool isInTable(string word);
	void incrementCount(string word);
	void addWord(string word);
	int getNumCollisions();
  void resize(int newSize);

private:
	int getHash(string word);
	wordItem* searchTable(string word);
	int numCollisions;
	int hashTableSize;
	wordItem** hashTable;
};

#endif
