#include "HashTable.hpp"
#include <fstream>
#include <string>

using namespace std;

HashTable::HashTable(int hashTableSize_input)
{
  numCollisions = 0;
  numUniqueWords = 0;

  hashTableSize = hashTableSize_input;

  hashTable = new wordItem*[hashTableSize];
}
HashTable::~HashTable()
{
  delete hashTable;
}
void HashTable::getStopWords(char *ignoreWordFileName)
{
  ifstream infile(ignoreWordFileName);

  if(infile.is_open())
  {
    string word;
    int i=0;

    while(!infile.eof())
    {
      getline(infile,word);

      if(word.length() != 0)
        vecIgnoreWords[i] = word;

      i++;
    }

    //cout << "Ignore words file succesfully parsed." << endl;
  }

  else
  {
    //cout << "Ignore words file did not open." << endl;
  }

  infile.close();

  // for(int i=0; i<50; i++)
  // {
  //   cout << vecIgnoreWords[i] << endl;
  // }
}
bool HashTable::isStopWord(string word)
{
  // for(auto x : vecIgnoreWords)
  // {
  //   if(x == word)
  //     return true;
  // }
  // cout << word << endl;
  // cout << vecIgnoreWords[0] << endl;
  for(int i=0; i<50; i++)
  {
    if(vecIgnoreWords[i] == word)
    {
      //cout << "True" << endl;
      return true;
    }
    //cout << i << endl;
  }
  return false;
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
    numUniqueWords++;
  }
  else
  {
    incrementCount(word);
  }
}
int HashTable::getTotalNumberNonStopWords()
{
  wordItem* temp;
  int total = 0;

  for(int i=0; i<hashTableSize; i++)
  {
    temp = hashTable[i];

    if(temp != NULL)
    {
        while(temp->next != NULL)
        {
          total += temp->count;
          temp = temp->next;
        }
        total += temp->count;
    }
  }
  return total;
}
void HashTable::printTopN(int n)
{
  unsigned long long int capacity = hashTableSize;
  wordItem** topWords = new wordItem*[capacity];

  wordItem* temp;
  int elements = 0;

  for(int i=0; i<hashTableSize; i++)
  {
    temp = hashTable[i];

    if(temp != NULL)
    {
      while(temp->next != NULL)
      {
      //cout << "Before" << endl;
        if(elements == capacity)
        {
          topWords = resize(topWords, &capacity);
          //cout << capacity << endl;
        }

        topWords[elements] = temp;
        elements++;
        temp = temp->next;
      }

      if(elements == capacity)
      {
        topWords = resize(topWords, &capacity);
        //cout << capacity << endl;
      }

      topWords[elements] = temp;
      elements++;

      //cout << elements << " 2with cap " << capacity << endl;
    }
  }

  bubbleSort(topWords, elements, n);

  for(int i=elements-1; i>elements-n-1; i--)
  {
    cout << topWords[i]->count << " - " << topWords[i]->word << endl;
  }
}

int HashTable::getNumUniqueWords()
{
  return numUniqueWords;
}
int HashTable::getNumCollisions()
{
  return numCollisions;
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

void HashTable::bubbleSort(wordItem* array[], int elements, int n) //Function definition with array input.
{
    int start = -1; //Starting position at first element.
    int end = elements; //Ending position at last element
    wordItem* holder; //Holder for swaps.
    bool sort = true; //Sorting flag set to true. Wether or not sorting needs
    //to be done.
    int topWords = 0;

    while(sort == true) //Loop while sorting flag is true and sorting needs to be
    //done.
    {
        sort = false; //Assume array is sorted and set flag to false.

        for(int i=start+1; i<end-1; i++) //Iterate up the array from current starting position
        //to current ending position.
        {
            if (array[i]->count > array[i+1]->count) //If ith value is large than i+1 value
            //enter here.
            {
                holder = array[i]; //Holder value equals ith value.
                array[i] = array[i+1]; //Ith value equals i+1 value.
                array[i+1] = holder; //i+1 value equals the ith value.
                sort = true; //Set flag to true. Sorting needs to be done.
            }
        }
        end--; //Subtract one from the ending position.
        topWords++;

        if(sort == false || topWords == n) //If sort is false and array is already sorted enter here.
        {
            break; //Exit loop.
        }
    }
}
wordItem** HashTable::resize(wordItem** arrayPtr, unsigned long long int *capacity)
{
	unsigned long long int newCapacity = *capacity*2;
	wordItem** newArray = new wordItem* [newCapacity];


	for(int i=0; i<*capacity; i++)
	{
	    //cout << "Here" << endl;
		newArray[i] = arrayPtr[i];
	}
	//cout << "Deleting" << endl;
	delete [] arrayPtr;

	//cout << "Resized" << endl;

	*capacity = newCapacity;

	//cout << "Huh";

	return newArray;
}
