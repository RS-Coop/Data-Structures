#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void resize(int *oldArray, int *capacity);

int main(int argc, char *argv[])
{
  if(argc!=2)
  {
    cout << "Error" << endl;

    return -1;
  }

  else
  {
    ifstream infile(argv[1]);

    if(infile.is_open())
    {
      string line;
      while(getline(infile,line))
      {

      }
    }

    else
    {
      cout << "Error" << endl;
    }
  }
}

void resize(int *oldArray, int *capacity)
{

}
