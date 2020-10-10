#include <iostream>
#include <fstream>
#include "practice2.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  int size = atoi(argv[1]);

  HashTable HashBrowns(size);

  ifstream infile(argv[2]);

  if(infile.is_open())
  {
    string word;

    while(!infile.eof())
    {
      infile >> word;
      HashBrowns.addWord(word);
    }
    cout << "#\nNumber of collisions: " << HashBrowns.getNumCollisions() << endl;

    HashBrowns.resize(50);

    cout << "#\nNumber of collisions: " << HashBrowns.getNumCollisions() << endl;
  }

  else
  {
    cout << "The text file failed to open." << endl;
  }

  infile.close();
}
