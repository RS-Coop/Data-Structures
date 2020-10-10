#include <iostream>
#include <fstream>
#include "HashTable.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  int size = atoi(argv[4]);

  HashTable HashBrowns(size);

  HashBrowns.getStopWords(argv[3]);

  ifstream infile(argv[2]);

  if(infile.is_open())
  {
    string word;

    while(!infile.eof())
    {
      infile >> word;

      // if(word[0] < 'a' || word[0] > 'z')
      //   cout << word << endl;

      //cout << word << endl;
      if(!HashBrowns.isStopWord(word))
        HashBrowns.addWord(word);
    }
    //cout << "Here" << endl;
    int top = atoi(argv[1]);
    HashBrowns.printTopN(top);

    cout << "#\nNumber of collisions: " << HashBrowns.getNumCollisions()
    << "\n#\nUnique non-stop words: " << HashBrowns.getNumUniqueWords()
    << "\n#\nTotal non-stop words: " << HashBrowns.getTotalNumberNonStopWords() << endl;

  }

  else
  {
    cout << "The text file failed to open." << endl;
  }

  infile.close();
}
