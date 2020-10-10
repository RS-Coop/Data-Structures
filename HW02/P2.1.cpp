#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include <algorithm>

using namespace std;

struct wordItem
{
  string word;
  int count;
};

void getStopWords(char *ignoreWordFileName, string ignoreWords[]);
bool isStopWord(string word, string ignoreWords[]);
int getTotalNumberNonStopWords(wordItem list[], int length);
int getTotalNumberUniqueWords(wordItem list[], int length);
void arraySort(wordItem list[], int length);
void printTopN(wordItem wordItemList[], int topN);
void resize(wordItem **arrayPtr, int *capacity, int *doubles);
void fileParse(char *fileName, wordItem list[], int *capacity, string ignoreWords[], int *length, int *doubles);

// bool sortOrder(wordItem thing1, wordItem thing2)
// {
//   return (thing1.count>thing2.count);
// }

int main(int argc, char *argv[])
{
  string ignoreWords[50];
  getStopWords(argv[3], ignoreWords);

  //Define an array but it needs to dynamically resize

  int *length = new int(0);
  int *doubles = new int(0);
  int *capacity = new int(100);
  wordItem *listPtr = new wordItem [*capacity];
  fileParse(argv[2], listPtr, capacity, ignoreWords, length, doubles);
  cout << "Check1" << endl;
  int totalNonCommon = getTotalNumberNonStopWords(listPtr, *length);
  cout << "Check2" << endl;
  int totalUnique = getTotalNumberUniqueWords(listPtr, *length);
  cout << "Check3" << endl;

  cout<<*length<<endl;
  for(int i=0; i<*length; i++)
  {
    cout << listPtr[i].word << endl;
  }

  arraySort(listPtr, *length);
  //sort(listPtr[0],listPtr[*length-1], sortOrder);
  cout << "Check4" << endl;

  int top = int(*argv[1])-48;
  cout << "Check5" << endl;
  printTopN(listPtr, top);
  cout << "#\n" << "Array doubled: " << *doubles << "\n#\n"
  << "Unique non-common words: " << totalUnique << "\n#\n" << "Total non-common words: "
  << totalNonCommon << endl;

  //Testing stop words function.
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

int getTotalNumberUniqueWords(wordItem list[], int length)
{
  int total = 0;

  for(int i=0; i<length; i++)
  {
    if(list[i].count == 1)
    {
      total++;
    }
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
          cout << l << endl;
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

void fileParse(char *fileName, wordItem list[], int *capacity, string ignoreWords[], int *length, int *doubles)
{
  ifstream infile(fileName);
  string line;
  bool ignore = false;
  bool newWord = true;

  if(infile.is_open())
  {
    while(getline(infile,line))
    {
      if(line.length()>1&&line!=" ")
      {
        ignore = false;
        newWord = true;
        stringstream ss(line);
        while(getline(ss,line,' '))
        {
          newWord = true;
          for(int i=0; i<50; i++)
          {
            if(isStopWord(line, ignoreWords))
            {
              ignore = true;
              break;
            }
          }
          if(ignore == false)
          {
            if(*length > 0)
            {
              if(*length==*capacity)
              {
                //cout << "Resizing" << endl;
                resize(&list, capacity, doubles);
                //cout << "Resized" << endl;
              }
              for(int i=0; i<*length; i++)
              {
                if(list[i].word == line)
                {
                  (list[i].count)++;
                  newWord = false;
                  break;
                }
              }
              if(newWord == true)
              {
                list[*length].word = line;
                list[*length].count = 1;
                //cout << list[*length].word << "new" <<endl;
                (*length) = *length +1;
                //cout << *length << endl;
              }
            }
            else
            {
              list[0].word = line;
              list[0].count = 1;
              //cout << list[*length].word << endl;
              (*length) = *length +1;
              //cout << *length << endl;
            }
          }
        }
        //cout << "Check" << endl;
      }
      //cout << "Check" << endl;
    }
    // cout << *length << endl;
    // for(int i=0; i<*length; i++)
    // {
    //   cout << list[i].word << endl;
    // }
  }
  else
  {
    cout << "Error" << endl;
  }

  infile.close();
}
