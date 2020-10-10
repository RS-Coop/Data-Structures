#include"HashTable.h"

/*
Inserts an item in the hash table.
Use the hash function on the key to get the slot.
Insert the key in that slot of hash table.
*/
void Hash::insertItem(int key)
{
  int index = hashFunc(key);

  hashTable[index].push_back(key);
}

/*
Given a key, search if the key exists in the hash table.
*/
void Hash::searchItem(int key)
{
     //Compute the index by using the hash function
     int index = hashFunc(key);
    //Search the list at that specific index, write print statements to justify if you did/didn't find the key

    bool found = false;
    int i = 0;

    for(auto x : hashTable[index])
    {
      i++;

      if(x == key)
        found = true;
    }

    if(!found)
    {
      cout << key << " not found in the hash table"<<endl;
    }
    else
      cout << "The value -> " << key << " was found in the table at position " << index
      << "," << i << endl;
}

char stringCharFreq(string str, vector<int> *table)
{
  Hash charHash(str.length()-1);
  int index;

  for(int i=0; i<str.length(); i++)
  {
    index = tolower(str[i]) - 'a';

    table[index] += 1;
  }
}

// main program
int main()
{
  // array that contains keys to be mapped
  int a[] = {15, 11, 27, 8, 12, 7, 18};
  int n = 7;

  // Creates a hash table of size 7
  Hash h(7);

  // insert the keys into the hash table
  for (int i = 0; i < n; i++)
    h.insertItem(a[i]);

  h.searchItem(8);
  h.searchItem(10);
  cout<<endl<<endl;

  cout<<"Contents of the hash table are"<<endl;
  // display the Hash table
  h.displayHash();

  string str = "abcdeafgbac";
  Hash charHash(str.length()-1);

  char character = stringCharFreq(str, charHash.hashTable);

  cout << character << endl;

  return 0;
}
