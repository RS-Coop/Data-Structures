#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int insertIntoSortedArray(int arr[], int numEnt, int newVal);
int insertIntoSortedArray2(int arr[], int numEnt, int newVal);

int main(int argc, char *argv[])
{
  int arr100[200];
  string line;
  int k=0;

  ifstream infile(argv[1]);

  if (infile.is_open())
  {
    while (getline(infile,line))
    {
      k = insertIntoSortedArray(arr100, k, stoi(line));

      for(int i=0; i<k; i++)
      {
        cout << arr100[i];

        if(k>0)
        {
          cout << ", ";
        }
      }

      cout << endl;
    }
  }

  else
  {
    cout << "Error" << endl;
  }
  //Test Case
  // arr100[0] = 1;
  // arr100[1] = 2;
  // arr100[2] = 4;
  // arr100[3] = 7;
  // arr100[4] = 12;
  //
  // insertIntoSortedArray(arr100, 5, 4);
  //
  // for(int i=0; i<6; i++)
  // {
  //   cout << arr100[i] << endl;
  // }

  infile.close();
  return (0);
}

int insertIntoSortedArray(int arr[], int numEnt, int newVal)
{
  arr[numEnt] = newVal;
  int temp;
  bool flag = true;

  while(flag)
  {
    flag = false;

    for(int i=numEnt; i>0; i--)
    {
      if(arr[i]<arr[i-1])
      {
        temp = arr[i-1];
        arr[i-1] = arr[i];
        arr[i] = temp;
        flag = true;
      }
    }
  }

  return (numEnt+1);
}

int insertIntoSortedArray2(int arr[], int numEnt, int newVal)
{
  int loc;
  int tempArr[numEnt+1];

  if (numEnt==0)
  {
    arr[0] = newVal;
  }

  else if (numEnt==1)
  {
    if (arr[0]<newVal)
    {
      loc = 1;
    }
    else
    {
      loc = 0;
    }
  }

  else
  {
    for(int i=0; i<numEnt; i++)
    {
      if (i==(numEnt-1))
      {
        if (arr[i]<newVal)
        {
          loc = i+1;
          break;
        }
        else
        {
          loc = i;
          break;
        }
      }

      else if (arr[i]<=newVal && arr[i+1]>=newVal)
      {
        loc = i+1;
        break;
      }

      else if (arr[i]>newVal)
      {
        loc = i;
        break;
      }
    }
  }

    for(int j=0; j<numEnt; j++)
    {
      tempArr[j] = arr[j];
    }

    int l=0;
    for(int k=0; k<(numEnt+1); k++)
    {
      if (k==loc)
      {
        arr[k] = newVal;
        arr[k+1] = tempArr[k];
        k++;
      }

      else
      {
      arr[k] = tempArr[l];
      }

      l++;
    }

  return (numEnt+1);
}
