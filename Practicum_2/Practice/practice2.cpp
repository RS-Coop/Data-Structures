#include "practice2.hpp"
#include <string>

using namespace std;

HashTable::HashTable(int hashTableSize_input)
{
  numCollisions = 0;

  hashTableSize = hashTableSize_input;

  hashTable = new wordItem*[hashTableSize];
}


HashTable::~HashTable()
{
  delete hashTable;
}


bool HashTable::isInTable(string word)
{
  wordItem* temp = searchTable(word);

  if(temp != NULL)
    return true;
  else
    return false;
}


void HashTable::incrementCount(string word)
{
  wordItem* temp = searchTable(word);

  if(temp != NULL)
    (temp->count)++;
}


void HashTable::addWord(string word)
{
  if(!isInTable(word))
  {
    int index = getHash(word);
    wordItem* newWord = new wordItem;
    newWord->count = 1;
    newWord->next = NULL;
    newWord->word = word;

    wordItem* temp = hashTable[index];

    if(temp == NULL)
      hashTable[index] = newWord;
    else
    {
      while(temp->next != NULL)
      {
        temp = temp->next;
      }
      temp->next = newWord;
      numCollisions++;
    }
  }
  else
  {
    incrementCount(word);
  }
}


int HashTable::getNumCollisions()
{
  return numCollisions;
}


void HashTable::resize(int newSize)
{
  wordItem** oldHashTable = hashTable;
  int oldSize = hashTableSize;

  hashTable = new wordItem*[newSize];
  hashTableSize = newSize;
  numCollisions = 0;

  string word;
  wordItem* temp;
  for(int i = 0; i<oldSize; i++)
  {
    if(oldHashTable[i] != NULL)
    {
      temp = oldHashTable[i];

      while(temp->next != NULL)
      {
        addWord(temp->word);
        temp = temp->next;
      }
      addWord(temp->word);
    }
  }

  delete [] oldHashTable;
}


int HashTable::getHash(string word)
{
  int hash = 5381;

  for(int i=0; i<word.length(); i++)
  {
    hash = hash*33 + word[i];
  }

  hash = hash%hashTableSize;

  if(hash < 0)
    hash += hashTableSize;

  return hash;
}


wordItem* HashTable::searchTable(string word)
{
  int index = getHash(word);
  wordItem* temp = hashTable[index];

  if(temp == NULL)
    return NULL;

  while(temp->next != NULL)
  {
    //cout << "Here" << endl;
    if(temp->word == word)
    {
      return temp;
    }
    temp = temp->next;
  }
  if(temp->word == word)
    return temp;

  return NULL;
}
