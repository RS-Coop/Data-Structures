#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

int random(int totWeight)
{
  int k;

  k = (rand()%(totWeight-1));
  cout << totWeight << endl;
  return k;
}

int main()
{
  srand(time(NULL));

  int totWeight = 44;

  cout << random(44) << endl;
  cout << random(44) << endl;
  cout << random(44) << endl;
  cout << random(44) << endl;

  return 0;
}
