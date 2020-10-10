#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct wordItem
{
  string word;
  int count;
};

void getStopWords(char *ignoreWordFileName, string ignoreWords[]);
bool isStopWord(string word, string ignoreWords[]);
int getTotalNumberNonStopWords(wordItem list[], int length);
void arraySort(wordItem list[], int length);
void printTopN(wordItem wordItemList[], int topN);
void resize(wordItem **arrayPtr, int *capacity, int *doubles);

// bool sortOrder(wordItem thing1, wordItem thing2)
// {
//   return (thing1.count>thing2.count);
// }

int main(int argc, char *argv[])
{
  string ignoreWords[50];
  getStopWords(argv[3], ignoreWords);
  /*
  for(int z=0; z<20; z++)
  {
    cout << ignoreWords[z] << " end " << endl;
  }
  */

  //Define an array but it needs to dynamically resize

  int length = 0;
  int doubles = 0;
  int *capacity = new int(100);
  wordItem *listPtr = new wordItem [*capacity];

  /////////////////////////////////////////////

  ifstream infile(argv[2]);
  string line;
  //bool ignore = false;
  bool newWord = true;

  if(infile.is_open())
  {
    while(getline(infile,line))
    {
      if(line.length()!=0 && line!=" ")
      {
        //ignore = false;
        //newWord = true;
        stringstream ss(line);
        while(getline(ss,line,' '))
        {
          newWord = true;
          if(line.length() == 0)
          {
            continue;
          }
          if(line.front() == '\n' || line.front() == ' ')
          {
            line = line.erase(0,1);
          }
          if(line.back() == '\n' || line.front() == ' ')
          {
            line = line.erase(line.length()-1,1);
          }
          // if(isStopWord(line, ignoreWords))
          // {
          //   ignore = true;
          //   //cout << "Ignoring" << endl;
          // }
          if(!(isStopWord(line, ignoreWords)))
          {
            if(length > 0)
            {
              if(length>=*capacity)
              {
                //cout << "Resizing" << endl;
                resize(&listPtr, capacity, &doubles);
                //cout << "Resized" << endl;
              }
              for(int i=0; i<length; i++)
              {
                if(line == listPtr[i].word)
                {
                  listPtr[i].count = listPtr[i].count + 1;
                  newWord = false;
                  break;
                }
              }
              if(newWord == true)
              {
                listPtr[length].word = line;
                listPtr[length].count = 1;
                //cout << list[*length].word << "new" <<endl;
                length++;
                //cout << *length << endl;
              }
            }
            else
            {
              listPtr[0].word = line;
              listPtr[0].count = 1;
              //cout << list[*length].word << endl;
              length++;
              //cout << *length << endl;
            }
          }
        }
        //cout << "Check" << endl;
      }
      //cout << "Check" << endl;
    }
    // cout << *length << endl;
    // for(int i=0; i<length; i++)
    // {
    //   cout << listPtr[i].word << listPtr[i].count << endl;
    // }
  }
  else
  {
    cout << "Error" << endl;
  }

  infile.close();

  /////////////////////////////////////////////

  //cout << "Check1" << endl;
  int totalNonCommon = getTotalNumberNonStopWords(listPtr, length);
  //cout << "Check2" << endl;
  //cout << "Check3" << endl;

  // cout<<length<<endl;
  // for(int i=0; i<length; i++)
  // {
  //   cout << listPtr[i].word << endl;
  // }

  arraySort(listPtr, length);
  //sort(listPtr[0],listPtr[*length-1], sortOrder);
  //cout << "Check4" << endl;
  // for(int i=0; i<length; i++)
  // {
  //   cout << listPtr[i].word << listPtr[i].count << endl;
  // }

  int top = atoi(argv[1]);
  //cout << "Check5" << endl;
  printTopN(listPtr, top);
  cout << "#\n" << "Array doubled: " << doubles << "\n#\n"
  << "Unique non-common words: " << length << "\n#\n" << "Total non-common words: "
  << totalNonCommon << endl;

  // Testing stop words function.
  // for(int i=0; i<50; i++)
  // {
  //     cout << ignoreWords[i] << endl;
  // }
}

void getStopWords(char *ignoreWordFileName, string ignoreWords[])
{
  ifstream infile_ignore(ignoreWordFileName);
  string line;
  int i = 0;

  if(infile_ignore.is_open())
  {
    while(getline(infile_ignore,line))
    {
      if(line.front() == '\n' || line.front() == ' ')
      {
        line = line.erase(0,1);
      }
      if(line.back() == '\n' || line.back() == ' ')
      {
        line = line.erase(line.length()-1,1);
      }
      ignoreWords[i] = line;
      i++;
    }
  }
  else
  {
    cout << "Error" << endl;
  }
  infile_ignore.close();
}

bool isStopWord(string word, string ignoreWords[])
{
  for(int i=0; i<50; i++)
  {
    if(word == ignoreWords[i])
    {
      return true;
    }
  }

  return false;
}

int getTotalNumberNonStopWords(wordItem list[], int length)
{
  int total = 0;

  for(int i=0; i<length; i++)
  {
    total = total + list[i].count;
  }

  return total;
}

void arraySort(wordItem list[], int length)
{
  int start = -1; //Starting position at first element.
  int end = length; //Ending position at last element
  wordItem holder; //Holder for swaps.
  bool sort = true; //Logical for whether or not to keep sorting.

  while(sort == true) //Loop while sorting flag is true and sorting needs to be
  //done.
  {

      sort = false; //Assume array is sorted and set flag to false.

      for(int i=start+1; i<end-1; i++) //Iterate up the array from current starting position
      //to current ending position.
      {
          if (list[i].count < list[i+1].count) //If ith value is larger than i+1 value
          //enter here.
          {
              holder = list[i]; //Holder value equals ith value.
              list[i] = list[i+1]; //Ith value equals i+1 value.
              list[i+1] = holder; //i+1 value equals the ith value.
              sort = true; //Set flag to true. Sorting needs to be done.
          }
          //cout << i << endl;
      }
      end--; //Subtract one from the ending position.

      if(sort == false) //If sort is false and array is already sorted enter here.
      {
          break; //Exit loop.
      }

      sort = false; //Reset sort to false. Assume it is sorted.

      for(int l=end-1; l>start+1; l--) //Iterates down the array from ending current ending
      //position to current starting position.
      {
          if(list[l].count > list[l-1].count) //If the jth value is less than the j+1
          //value then enter here.
          {
              holder = list[l]; //Holder value equals jth values.
              list[l] = list[l-1]; //jth value equals j-1 value.
              list[l-1] = holder; //j-1 value equals jth value.
              sort = true; //Set flag equal to true. Sorting needs to be done
          }
      }
      start++; //Increase the starting postion by one.

      if(sort == false) //If sort is false then enter here. The array is sorted.
      {
          break; //Exit loop.
      }
  }
}

void printTopN(wordItem wordItemList[], int topN)
{
  for(int i=0; i<topN; i++)
  {
    cout << wordItemList[i].count << " - " << wordItemList[i].word << endl;
  }
}

void resize(wordItem **arrayPtr, int *capacity, int *doubles)
{
	int newCapacity = *capacity*2;
	wordItem *newArray = new wordItem [newCapacity];
  //cout << "Here" << endl;
  //cout << *capacity << endl;

	for(int i=0; i<*capacity; i++)
	{
		*(newArray+i) = (*arrayPtr)[i];
	}
  //cout << "Here2" << endl;
  delete [] *arrayPtr;

  *arrayPtr = newArray;

	*capacity = newCapacity;
  (*doubles)++;
}
